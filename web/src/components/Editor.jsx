const SAMPLE_PROGRAMS = {
  hello: `sceneOnHa
    spillTea "Salam Duniya!" !!
    wapas 0 !!
sceneOffHa`,

  loop: `sceneOnHa
    numYesKarao counter <- 0 !!
    numYesKarao limit <- 5 !!
    chalBro (counter < limit)
    basYar
        spillTea "looping..." !!
        counter <- counter ^+ 1 !!
    wapas 0 !!
sceneOffHa`,

  conditional: `sceneOnHa
    numYesKarao score <- 8 !!
    lowkey (score > 5)
    basYar
        spillTea "noCap passing" !!
    warnaBro
    basYar
        spillTea "cap failing" !!
    wapas 0 !!
sceneOffHa`,
};

export default function Editor({ code, setCode, onCompile, loading }) {
  return (
    <div className="editor-panel">
      <div className="editor-header">
        <span>Code Editor</span>
        <div className="sample-buttons">
          <span>Samples:</span>
          {Object.keys(SAMPLE_PROGRAMS).map((key) => (
            <button
              key={key}
              className="sample-btn"
              onClick={() => setCode(SAMPLE_PROGRAMS[key])}
            >
              {key}
            </button>
          ))}
        </div>
      </div>
      <textarea
        className="code-input"
        value={code}
        onChange={(e) => setCode(e.target.value)}
        spellCheck={false}
        placeholder="Write your P++ code here..."
      />
      <button className="run-btn" onClick={onCompile} disabled={loading}>
        {loading ? "Compiling..." : "▶  Run"}
      </button>
    </div>
  );
}
