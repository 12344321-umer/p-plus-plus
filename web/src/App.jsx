import { useState } from "react";
import Navbar from "./components/Navbar";
import Editor from "./components/Editor";
import Output from "./components/Output";
import { compileCode } from "./api/compilerApi";
import "./index.css";

export default function App() {
  const [code, setCode] = useState(`sceneOnHa
    numYesKarao counter <- 0 !!
    numYesKarao limit <- 5 !!
    chalBro (counter < limit)
    basYar
        spillTea "looping..." !!
        counter <- counter ^+ 1 !!
    wapas 0 !!
sceneOffHa`);

  const [result, setResult] = useState(null);
  const [loading, setLoading] = useState(false);

  async function handleCompile() {
    setLoading(true);
    setResult(null);
    const res = await compileCode(code);
    setResult(res);
    setLoading(false);
  }

  return (
    <div className="app">
      <Navbar />
      <main className="main">
        <Editor
          code={code}
          setCode={setCode}
          onCompile={handleCompile}
          loading={loading}
        />
        <Output result={result} />
      </main>
    </div>
  );
}
