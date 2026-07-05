import { useState, useEffect } from "react";
import { useLocation } from "react-router-dom";
import Editor from "../components/Editor";
import Output from "../components/Output";
import { compileCode } from "../api/compilerApi";

const DEFAULT_CODE = `sceneOnHa
    numYesKarao counter <- 0 !!
    numYesKarao limit <- 5 !!
    chalBro (counter < limit)
    basYar
        spillTea "looping..." !!
        counter <- counter ^+ 1 !!
    wapas 0 !!
sceneOffHa`;

export default function Playground() {
  const location = useLocation();
  const [code, setCode] = useState(DEFAULT_CODE);
  const [result, setResult] = useState(null);
  const [loading, setLoading] = useState(false);

  // If we got here from the Docs page's "Try it" button,
  // location.state.code will hold the example that was clicked.
  useEffect(() => {
    if (location.state?.code) {
      setCode(location.state.code);
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [location.state]);

  async function handleCompile() {
    setLoading(true);
    setResult(null);
    const res = await compileCode(code);
    setResult(res);
    setLoading(false);
  }

  return (
    <main className="main">
      <Editor
        code={code}
        setCode={setCode}
        onCompile={handleCompile}
        loading={loading}
      />
      <Output result={result} />
    </main>
  );
}
