function ASTNode({ node, depth = 0 }) {
  if (!node) return null;

  const indent = depth * 20;

  const getLabel = () => {
    switch (node.type) {
      case "Program":
        return "Program";
      case "VarDecl":
        return `VarDecl [${node.value}]`;
      case "Assign":
        return `Assign [${node.value}]`;
      case "If":
        return "If";
      case "IfElse":
        return "IfElse";
      case "IfElseIf":
        return "IfElseIf";
      case "While":
        return "WhileLoop";
      case "Print":
        return "Print";
      case "Return":
        return "Return";
      case "Break":
        return "Break";
      case "Continue":
        return "Continue";
      case "BinOp":
        return `BinOp [${node.value}]`;
      case "Condition":
        return `Condition [${node.value}]`;
      case "IntLit":
        return `Int [${node.value}]`;
      case "FloatLit":
        return `Float [${node.value}]`;
      case "StringLit":
        return `String [${node.value}]`;
      case "BoolLit":
        return `Bool [${node.value}]`;
      case "Identifier":
        return `Identifier [${node.value}]`;
      default:
        return node.type;
    }
  };

  return (
    <div>
      <div className="ast-node" style={{ marginLeft: `${indent}px` }}>
        <span className="ast-dot">◆</span>
        <span className="ast-label">{getLabel()}</span>
      </div>
      {node.left && <ASTNode node={node.left} depth={depth + 1} />}
      {node.right && <ASTNode node={node.right} depth={depth + 1} />}
      {node.extra && <ASTNode node={node.extra} depth={depth + 1} />}
      {node.next && <ASTNode node={node.next} depth={depth} />}
    </div>
  );
}

function SymbolTable({ symbols }) {
  if (!symbols || symbols.length === 0) {
    return <p className="empty-msg">No variables declared.</p>;
  }
  return (
    <table className="symbol-table">
      <thead>
        <tr>
          <th>Name</th>
          <th>Type</th>
          <th>Line</th>
        </tr>
      </thead>
      <tbody>
        {symbols.map((s, i) => (
          <tr key={i}>
            <td>{s.name}</td>
            <td>{s.type}</td>
            <td>{s.line}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}

export default function Output({ result }) {
  if (!result) {
    return (
      <div className="output-panel">
        <div className="output-placeholder">
          <p>Write some P++ code and hit Run ▶</p>
        </div>
      </div>
    );
  }

  if (!result.success) {
    return (
      <div className="output-panel">
        <div className="output-error">
          <h3>Error</h3>
          <pre>{result.error}</pre>
        </div>
      </div>
    );
  }

  const { parseOk, semErrors, ast, symbols } = result.data;

  return (
    <div className="output-panel">
      <div className="status-bar">
        <span className={parseOk ? "status-ok" : "status-fail"}>
          {parseOk ? "✓ Parse OK" : "✗ Parse Failed"}
        </span>
        <span className={semErrors === 0 ? "status-ok" : "status-fail"}>
          {semErrors === 0
            ? "✓ Semantic OK"
            : `✗ ${semErrors} Semantic Error(s)`}
        </span>
      </div>

      <div className="output-section">
        <h3>Abstract Syntax Tree</h3>
        <div className="ast-container">
          <ASTNode node={ast} />
        </div>
      </div>

      <div className="output-section">
        <h3>Symbol Table</h3>
        <SymbolTable symbols={symbols} />
      </div>
    </div>
  );
}
