const addrModes = { 
    NONE        : { class: "none", name: "Unimplemented", desc: "No implementation!"},
    PREFIX      : { class: "Prefix", desc: "Prefixes an instruction and manipulates it in some way." },
    IMPLIED     : { class: "Implied", desc: "The instruction implies its information, usually nothing." },
    REGISTER    : { class: "Register", desc: "Uses one or two registers." },
    DIRECTMA    : { class: "DirectMemAddr", desc: "Uses a memory address." },
    INDIRECTMA  : { class: "InDirectMemAddr", desc: "Uses a memory address to get the final memory address." },
    INDEXEDMA   : { class: "IndexedMemAddr", desc: "Uses a memory address and a register to index at that memory address." },
    IOADDRESS   : { class: "IOAddress", desc: "Interacts directly with an I/O port." },
}

const instructions = {
    "rsvd" : { name: "rsvd", link: "rsvd.htm#{nid}", addrMode: addrModes.NONE },
    0x00   : { name: "EXT", addrMode: addrModes.PREFIX },
    0x01   : { name: "nop", addrMode: addrModes.IMPLIED },
    0x02   : { name: "mov", addrMode: addrModes.REGISTER },
    0x03   : { name: "mov", addrMode: addrModes.DIRECTMA },
    0x04   : { name: "mov", addrMode: addrModes.INDIRECTMA },
    0x05   : { name: "mov", addrMode: addrModes.INDEXEDMA },
}

function openIFrame(url) {
    const container = document.getElementById("instruction-table-iframe-container");
    if(!container) {
        alert("Couldn't open the instruction in an embeded page!");
        return false;
    }
    var iframe;
    if(!container.childElementCount || container.children[0].tagName !== "IFRAME") {
        container.innerHTML = "";
        iframe = document.createElement("iframe");
        container.append(iframe);
    }
    else iframe = container.children[0];
    iframe.src = url;
    iframe.scrollIntoView({"behavior":"smooth"});
    return true;
}

function resolveInstructionURL(inst, nid) {
    var url;
    if(inst.link)
        url = "./cpu-instructions/"+inst.link.replace("{nid}", nid.toString(16).padStart(2, "0"));
    else url = "./cpu-instructions/"+inst.name+".htm";
    return url;
}

function clickedInstruction(inst, id, ev) {
    const useIFrame = document.getElementById("IFrameUsage").checked;
    if(!useIFrame) {
        ev.preventDefault();
        window.location.href = resolveInstructionURL(inst, id);
        return;
    }
    if(!openIFrame(resolveInstructionURL(inst, id)))
        ev.preventDefault();
}

function buildAddrModeTable() {
    const table = document.getElementById("addrMode-table");
    table.innerHTML = "";
    var row, cell;
    row = document.createElement("tr");
    cell = document.createElement("th");
    cell.innerText = "Addressing Mode";
    row.append(cell);
    cell = document.createElement("th");
    cell.innerText = "Description";
    row.append(cell);
    table.append(row);
    for(var i in addrModes) {
        var mode = addrModes[i];
        row = document.createElement("tr");
        cell = document.createElement("td");
        if(mode.class) cell.classList.add("addrMode-"+mode.class);
        cell.innerText = mode.name ? mode.name : mode.class;
        row.append(cell);
        cell = document.createElement("td");
        cell.innerText = mode.desc;
        row.append(cell);
        table.append(row);
    }
}

function buildInstructionTable() {
    buildAddrModeTable();
    var row, cell, elm;
    const table = document.getElementById("instruction-table");
    table.innerHTML = "";
    // Populate the first row, which is just our low byte's; aka row numbers.
    {
        row = document.createElement("tr");
        // Empty first cell for column information.
        cell = document.createElement("th");
        row.append(cell);
        for(var i = 0x0; i <= 0xf; i++) {
            cell = document.createElement("th");
            cell.innerText = "0x"+i.toString(16).padStart(2, '0').toUpperCase();
            row.append(cell);
        }
        table.append(row);
    }
    // Loop over the instruction set grid and fill things out.
    for(var high = 0x00; high <= 0xf0; high += 0x10) {
        row = document.createElement("tr");
        cell = document.createElement("th");
        cell.innerText = "0x"+high.toString(16).padStart(2, '0').toUpperCase();
        row.append(cell);
        for(var low = 0x00; low <= 0x0f; low += 0x01) {
            let identifier = (high + low);
            var inst = instructions[identifier];
            if(!inst) inst = instructions["rsvd"];
            cell = document.createElement("td");
            if(inst.addrMode)
                cell.classList.add("addrMode-"+inst.addrMode.class);
            row.append(cell);
            elm = document.createElement("a");
            elm.href="#"+identifier.toString(16).padStart(2, "0");
            elm.addEventListener("click", clickedInstruction.bind(null, inst, identifier));
            // if(inst.link) 
            //     elm.href = "./cpu-instructions/" + inst.link.replace("{nid}", identifier.toString(16).padStart(2, "0"));
            // else elm.href = "./cpu-instructions/" + inst.name + ".htm";
            cell.append(elm); cell = elm;
            elm = document.createElement("h6");
            elm.innerText = inst.name;
            cell.append(elm);
        }
        table.append(row);
    }

    if(window.location.hash && window.location.hash.length == 3) {
        const nid = window.location.hash.substring(1);
        const id = parseInt(nid, 16);
        if(id !== NaN) {
            var inst = instructions[id];
            if(!inst) inst = instructions["rsvd"];
            openIFrame(resolveInstructionURL(inst, id));
        }
    }
}
window.addEventListener("load",buildInstructionTable);