import os
from enum import Enum
from typing import Callable
from html.parser import HTMLParser
dir_src = './docs/custom'
dir_dst = './docs/doxygen/html/'

class HtmlNodeType(Enum):
    TEXT = 0,
    ELEMENT = 1,

class HtmlNode:
    def __init__(self, type : HtmlNodeType):
        self.type = type
        self.parent : HtmlElement = None
        
class HtmlTextContent(HtmlNode):
    def __init__(self, content : str | None):
        super().__init__(HtmlNodeType.TEXT)
        self.content = str(content or '')
        
    def __str__(self, level : int = 0):
        lines = self.content.splitlines(True)
        indent = ("  " * level)
        return indent + indent.join(lines)

class HtmlElement(HtmlNode):
    def __init__(self, tag, attrs : list[tuple[str,str | None]]):
        super().__init__(HtmlNodeType.ELEMENT)
        self.tagname = tag
        self.id : str | None = None
        self.classList : list[str] | None = None
        self.attrs = dict()
        for pair in attrs:
            if(len(pair) < 2 or pair[1] is None):
                self.attrs[pair[0]] = None
            else: self.attrs[pair[0]] = pair[1]
            if(pair[0].lower() == "class"):
                if(len(pair) < 2 or pair[1] is None): continue
                if(self.classList is None): self.classList = []
                self.classList.extend(pair[1].split(" "))
            elif(pair[0].lower() == "id"):
                if(len(pair) < 2 or pair[1] is None): continue
                self.id = pair[1].split(" ",2)[0]
        self.nodes = HtmlNodes(self)

    def innerText(self, content : str):
        self.nodes.clear()
        self.nodes.append(HtmlTextContent(content))

    def __str__(self, level : int = 0):
        content = "<"+str(self.tagname)
        for name in self.attrs:
            value = self.attrs[name]
            content = content + " " + name
            if(value is not None):
                content = content + f"=\"{value}\""
        return ('  ' * level) + content + ">"

class HtmlNodes:
    def __init__(self, owner : HtmlElement | None):
        self.children : list[HtmlNode] = []
        self.owner = owner
    def __len__(self):
        return self.children.__len__()
    def append(self, node : HtmlNode):
        if(node.parent is not None):
            node.parent.nodes.remove(node)
        node.parent = self.owner
        self.children.append(node)
    def remove(self, node : HtmlNode):
        if(node.parent == self):
            self.children.remove(node)
            node.parent = None
    def clear(self):
        self.children.clear()
    def searchPredicate(self, predicate : Callable[[HtmlElement],bool]):
        found : list[HtmlElement] = []
        if(self.owner is not None and predicate(self.owner)):
            found.append(self.owner)
        for child in self.children:
            if(child.type == HtmlNodeType.ELEMENT):
                elm : HtmlElement = child
                found.extend(elm.nodes.searchPredicate(predicate))
        return found

    def __str__(self, level=0):
        content = str()
        if(self.owner is not None):
            if(len(self.owner.nodes)):
                content = content + ('  ' * level) + str(self.owner) + "\n"
                for child in self.children:
                    if(child.type == HtmlNodeType.ELEMENT):
                        elm : HtmlElement = child
                        content = content + elm.nodes.__str__(level + 1)
                    else: content = content + child.__str__(level + 1) + "\n"
                content = content + ('  ' * level) + "</" + self.owner.tagname + ">\n"
            else:
                content = content + ('  ' * level) + str(self.owner) + "</" + self.owner.tagname + ">\n"
        else:
            for child in self.children:
                if(child.type == HtmlNodeType.ELEMENT):
                    elm : HtmlElement = child
                    content = content + elm.nodes.__str__(level + 1)
                else: content = content + child.__str__(level + 1) + "\n"
        return content
            

class HtmlFragment(HTMLParser):
    def __init__(self):
        super().__init__()
        self.root = HtmlNodes(None)
        self.cnode : HtmlElement = None

    def handle_starttag(self, tag, attrs):
        node = HtmlElement(tag, attrs)
        if(self.cnode is not None):
            self.cnode.nodes.append(node)
        else:
            self.root.append(node)
        self.cnode = node

    def handle_endtag(self, tag):
        if(self.cnode is None):
            raise Exception("HTML: end tag came before a start tag!")
        if(self.cnode.tagname != tag):
            raise Exception(f"HTML: end tag \"{tag}\" doesn't match the current node's tag \"{self.cnode.tagname}\".")
        self.cnode = self.cnode.parent

    def handle_data(self, data):
        if(data.isspace()): return
        if(self.cnode is None):
            raise Exception(f"HTML: data, \"{data}\", came before a start tag!")
        self.cnode.nodes.append(HtmlTextContent(data))

    def getElementsByTagname(self, tagname : str):
        def findTagname(elm : HtmlElement):
            return elm.tagname.lower() == tagname.lower()
        return self.root.searchPredicate(findTagname)

    def getElementById(self, id : str):
        def findId(elm : HtmlElement):
            return elm.id == id
        elms = self.root.searchPredicate(findId)
        if(len(elms) > 0): return elms[0]
        return None

    def getElementsByClassname(self,classname : str):
        def findClassname(elm : HtmlElement):
            if(elm.classList is None): return False
            for className in elm.classList:
                if(className == classname):
                    return True
            return False
        return self.root.searchPredicate(findClassname)

    def __str__(self):
        return self.root.__str__(0)

header_match = "<!--header-->"
footer_match = "<!-- start footer part -->"

header_trail = "<div class=\"contents\" id=\"main-fragment-contents\">"
footer_preamble = "</div></div>"

def getHeaderInfo():
    file = open(os.path.join(dir_dst, 'index.html'), 'r')
    content = file.read()
    file.close()
    header_marker = content.find(header_match)
    footer_marker = content.find(footer_match)
    header = content[:header_marker] + header_trail
    footer = footer_preamble + content[footer_marker + len(footer_match):len(content)]
    return (header, footer)

header, footer = getHeaderInfo()

def parseHtmlTemplate():
    fragment = HtmlFragment()
    fragment.feed(header + footer)
    if(fragment.cnode is not None):
        raise Exception(f"HtmlFragment ended without a closing tag, opentags: {fragment.cnode.tagname}!")
    ret = dict()
    ret["fragment"] = fragment
    elms = fragment.getElementsByTagname("title")
    if(len(elms) > 0): ret["title"] = elms[0]
    elms = fragment.getElementsByClassname("title")
    if(len(elms) > 0): ret["h-title"] = elms[0]
    elm = fragment.getElementById("main-fragment-contents")
    if(elm is not None): ret["content-body"] = elm
    return ret

htmlFragment = parseHtmlTemplate()

def getHtmlContent(src : str):
    fsrc = open(src, "r")
    content = fsrc.read()
    fsrc.close()

    j = 0
    ret = dict()
    lines = content.splitlines()
    for i in range(0,len(lines)):
        line = lines[i]
        if(line.startswith("<!--") and line.endswith("-->")):
            line = line[4:len(line)-3]
            tmp = line.split(":",2)
            if(len(tmp) == 2):
                tmp[0] = tmp[0].lower()
                if(tmp[0] == "copy-html"):
                    convertHtml(tmp[1])
                else:
                    ret[tmp[0]] = tmp[1]
            else:
                print(f"Unknown preamble comment \"{line}\" in \"{src}\" file?")
        else: break
        j = i

    ret["filename"] = src
    ret["content"] = "\n".join(lines[j:])
    return ret

def applyHeaderHtmlPreamble(info : dict):
    title = info.get("title", info.get("filename", "<unknown>"))
    hTitle : HtmlElement = htmlFragment.get("h-title", None)
    if(hTitle is not None):
        hTitle.innerText(title)
    hTitle : HtmlElement = htmlFragment.get("title", None)
    if(hTitle is not None):
        hTitle.innerText(title)

    content : HtmlElement = htmlFragment.get("content-body", None)
    if(content is not None):
        content.innerText(info.get("content", ""))


def convertHtml(src : str, dst : str):
    info = getHtmlContent(src)
    applyHeaderHtmlPreamble(info)
    fdst = open(dst, "w")
    fdst.write(str(htmlFragment["fragment"]))
    fdst.close()
    print(f"Converted {src} into a doxygen compatible file at {dst}")


for filename in os.listdir(dir_src):
    src = os.path.join(dir_src, filename)
    if os.path.isfile(src) and (src.endswith(".html") or src.endswith(".htm")):
        dst = os.path.join(dir_dst, filename)
        convertHtml(src, dst)
