const isEmbeded = (()=>{
    try { return (window.self !== window.top); }
    catch { return true; }
})();

window.addEventListener("load", ()=>{
    if(isEmbeded) {
        const remove = document.getElementsByClassName("dont-embed");
        for(var elm of remove)
            elm.remove();
    }

    if(window.location.hash && window.location.hash.length == 3) {
        const nid = "0x"+window.location.hash.substring(1).toUpperCase();
        const nids = document.getElementsByClassName("nid");
        for(var elm of nids)
            elm.innerText = nid;
    }
});