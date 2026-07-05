import { Routes, Route } from "react-router-dom";
import Navbar from "./components/Navbar";
import Playground from "./pages/Playground";
import Docs from "./pages/Docs";
import "./index.css";

export default function App() {
  return (
    <div className="app">
      <Navbar />
      <Routes>
        <Route path="/" element={<Playground />} />
        <Route path="/docs" element={<Docs />} />
      </Routes>
    </div>
  );
}
