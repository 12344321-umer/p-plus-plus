import { useState } from "react";
import { useNavigate } from "react-router-dom";

/* ══════════════════════════════════════
   REFERENCE DATA
   Every keyword/operator in the language,
   grouped by category, each with a tiny
   runnable snippet showing it in context.
══════════════════════════════════════ */
const CATEGORIES = [
  {
    name: "Program Structure",
    items: [
      {
        kw: "sceneOnHa",
        meaning:
          "Marks the start of every P++ program. Every file needs exactly one.",
        snippet: `sceneOnHa\n    wapas 0 !!\nsceneOffHa`,
      },
      {
        kw: "sceneOffHa",
        meaning: "Marks the end of the program. Pairs with sceneOnHa.",
        snippet: `sceneOnHa\n    wapas 0 !!\nsceneOffHa`,
      },
      {
        kw: "!!",
        meaning:
          "Ends every statement — like a semicolon. Forget this and you'll get a syntax error.",
        snippet: `numYesKarao x <- 5 !!`,
      },
      {
        kw: "basYar",
        meaning:
          "Opens the body of an if, else, elseif, while, or function — like a { in C-style languages.",
        snippet: `numYesKarao x <- 5 !!\nlowkey (x > 0)\nbasYar\n    spillTea "positive" !!\nyehLo`,
      },
      {
        kw: "yehLo",
        meaning:
          "Closes an if/elseif/else chain or a while loop's body — like a }. Only one yehLo per lowkey...phirBro...warnaBro chain, placed at the very end.",
        snippet: `numYesKarao x <- 0 !!\nchalBro (x < 5)\nbasYar\n    x <- x ^+ 1 !!\nyehLo`,
      },
    ],
  },
  {
    name: "Declaring Variables",
    items: [
      {
        kw: "numYesKarao",
        meaning: "Declares an integer variable.",
        snippet: `numYesKarao age <- 21 !!`,
      },
      {
        kw: "floatYesKarao",
        meaning: "Declares a floating-point (decimal) variable.",
        snippet: `floatYesKarao price <- 4.99 !!`,
      },
      {
        kw: "<-",
        meaning:
          "Assignment operator. Used both when declaring a variable and when updating an existing one.",
        snippet: `numYesKarao x <- 10 !!\nx <- x ^+ 1 !!`,
      },
    ],
  },
  {
    name: "Control Flow",
    items: [
      {
        kw: "lowkey",
        meaning: "if — runs its body only when the condition is true.",
        snippet: `numYesKarao score <- 8 !!\nlowkey (score > 5)\nbasYar\n    spillTea "passing" !!\nyehLo`,
      },
      {
        kw: "warnaBro",
        meaning:
          "else — runs when the lowkey condition was false. Must come right after the lowkey body, before yehLo.",
        snippet: `numYesKarao score <- 3 !!\nlowkey (score > 5)\nbasYar\n    spillTea "noCap passing" !!\nwarnaBro\nbasYar\n    spillTea "cap failing" !!\nyehLo`,
      },
      {
        kw: "phirBro",
        meaning:
          "else if — checks a second condition only if the first lowkey condition was false. Only one phirBro per chain is supported right now (no phirBro chaining, and no warnaBro after a phirBro).",
        snippet: `numYesKarao x <- 3 !!\nlowkey (x ==? 1)\nbasYar\n    spillTea "one" !!\nphirBro (x ==? 3)\nbasYar\n    spillTea "three" !!\nyehLo`,
      },
      {
        kw: "chalBro",
        meaning:
          "while — repeats its body as long as the condition stays true.",
        snippet: `numYesKarao counter <- 0 !!\nchalBro (counter < 5)\nbasYar\n    counter <- counter ^+ 1 !!\nyehLo`,
      },
      {
        kw: "ghosted",
        meaning:
          "break — immediately exits the nearest enclosing chalBro loop. Note: the loop condition itself must always be a real comparison (like x < 10) — a bare noCap/cap by itself isn't a valid condition in this language.",
        snippet: `numYesKarao x <- 0 !!\nchalBro (x < 10)\nbasYar\n    lowkey (x ==? 5)\n    basYar\n        ghosted !!\n    yehLo\n    x <- x ^+ 1 !!\nyehLo\nspillTea x !!`,
      },
      {
        kw: "missKara",
        meaning:
          "continue — skips to the next iteration of the nearest enclosing chalBro loop.",
        snippet: `numYesKarao x <- 0 !!\nchalBro (x < 10)\nbasYar\n    x <- x ^+ 1 !!\n    lowkey (x ==? 5)\n    basYar\n        missKara !!\n    yehLo\n    spillTea x !!\nyehLo`,
      },
    ],
  },
  {
    name: "Functions",
    items: [
      {
        kw: "kaamKaro",
        meaning:
          "Declares a function. Params go between two ::: separators, then the body between basYar and yehLo.",
        snippet: `kaamKaro square ::: n ::: basYar\n    wapas n ^* n !!\nyehLo`,
      },
      {
        kw: ":::",
        meaning:
          "Separator used around a function's parameter or argument list. Use an empty ::: ::: if there are no params/args.",
        snippet: `kaamKaro greet ::: ::: basYar\n    spillTea "hi" !!\nyehLo\ngreet ::: ::: !!`,
      },
      {
        kw: "wapas",
        meaning:
          "return — sends a value back from a function (or ends main with an exit code).",
        snippet: `kaamKaro double ::: n ::: basYar\n    wapas n ^* 2 !!\nyehLo`,
      },
    ],
  },
  {
    name: "Output & Values",
    items: [
      {
        kw: "spillTea",
        meaning:
          "print — writes a value (number, string, or bool) to the output.",
        snippet: `spillTea "Salam Duniya!" !!`,
      },
      {
        kw: "noCap",
        meaning: "The boolean value true.",
        snippet: `numYesKarao isReady <- noCap !!`,
      },
      {
        kw: "cap",
        meaning: "The boolean value false.",
        snippet: `numYesKarao isDone <- cap !!`,
      },
      {
        kw: "gintiBata",
        meaning: "Returns the length of a string variable, as an integer.",
        snippet: `numYesKarao name <- "Umer" !!\nspillTea gintiBata name !!`,
      },
    ],
  },
  {
    name: "Operators",
    items: [
      {
        kw: "^+",
        meaning:
          "Addition (also does string concatenation if either side is a string).",
        snippet: `spillTea 2 ^+ 3 !!`,
      },
      { kw: "^-", meaning: "Subtraction.", snippet: `spillTea 10 ^- 4 !!` },
      { kw: "^*", meaning: "Multiplication.", snippet: `spillTea 6 ^* 7 !!` },
      { kw: "^/", meaning: "Division.", snippet: `spillTea 20 ^/ 4 !!` },
      {
        kw: "^%",
        meaning: "Modulo (remainder).",
        snippet: `spillTea 10 ^% 3 !!`,
      },
      {
        kw: "==?",
        meaning: "Equality comparison.",
        snippet: `numYesKarao x <- 5 !!\nlowkey (x ==? 5)\nbasYar\n    spillTea "matched" !!\nyehLo`,
      },
      {
        kw: "<  >  <=  >=",
        meaning: "Less than, greater than, less/greater-or-equal.",
        snippet: `numYesKarao age <- 20 !!\nlowkey (age >= 18)\nbasYar\n    spillTea "adult" !!\nyehLo`,
      },
      {
        kw: "aurBhai",
        meaning: "Logical AND, used between two conditions.",
        snippet: `numYesKarao age <- 20 !!\nnumYesKarao hasID <- noCap !!\nlowkey (age >= 18 aurBhai hasID ==? noCap)\nbasYar\n    spillTea "allowed in" !!\nyehLo`,
      },
      {
        kw: "yaBhai",
        meaning: "Logical OR, used between two conditions.",
        snippet: `numYesKarao isAdmin <- cap !!\nnumYesKarao isMod <- noCap !!\nlowkey (isAdmin ==? noCap yaBhai isMod ==? noCap)\nbasYar\n    spillTea "has access" !!\nyehLo`,
      },
      {
        kw: "nahi",
        meaning: "Logical NOT — flips a condition.",
        snippet: `numYesKarao isBanned <- cap !!\nlowkey (nahi isBanned ==? noCap)\nbasYar\n    spillTea "welcome" !!\nyehLo`,
      },
    ],
  },
];

/* ══════════════════════════════════════
   FULL WORKED PROGRAMS
══════════════════════════════════════ */
const EXAMPLES = [
  {
    title: "Hello World",
    desc: "The smallest possible P++ program.",
    code: `sceneOnHa\n    spillTea "Salam Duniya!" !!\n    wapas 0 !!\nsceneOffHa`,
  },
  {
    title: "Variables & Math",
    desc: "Declaring integers and doing arithmetic.",
    code: `sceneOnHa\n    numYesKarao x <- 10 !!\n    numYesKarao y <- 5 !!\n    numYesKarao result <- x ^+ y !!\n    spillTea result !!\n    wapas 0 !!\nsceneOffHa`,
  },
  {
    title: "If / Else If / Else",
    desc: "Full branching using lowkey, phirBro, and warnaBro together.",
    code: `sceneOnHa\n    numYesKarao score <- 75 !!\n    lowkey (score >= 90)\n    basYar\n        spillTea "A grade" !!\n    phirBro (score >= 60)\n    basYar\n        spillTea "B grade" !!\n    yehLo\n    wapas 0 !!\nsceneOffHa`,
  },
  {
    title: "While Loop",
    desc: "Counting up using chalBro.",
    code: `sceneOnHa\n    numYesKarao counter <- 0 !!\n    numYesKarao limit <- 5 !!\n    chalBro (counter < limit)\n    basYar\n        spillTea "looping..." !!\n        counter <- counter ^+ 1 !!\n    yehLo\n    wapas 0 !!\nsceneOffHa`,
  },
  {
    title: "Functions",
    desc: "Declaring a function with kaamKaro and calling it.",
    code: `sceneOnHa\n    kaamKaro square ::: n ::: basYar\n        wapas n ^* n !!\n    yehLo\n    square ::: 6 ::: !!\n    wapas 0 !!\nsceneOffHa`,
  },
];

export default function Docs() {
  const navigate = useNavigate();
  const [selected, setSelected] = useState(CATEGORIES[0].items[0]);

  function tryIt(code) {
    navigate("/", { state: { code } });
  }

  return (
    <div className="docs-page">
      <section className="docs-intro">
        <h1>Learn P++</h1>
        <p>
          Every P++ program starts with <code>sceneOnHa</code> and ends with{" "}
          <code>sceneOffHa</code>. Every statement ends with <code>!!</code>,
          and every block (if/while/function body) opens with{" "}
          <code>basYar</code> and closes with <code>yehLo</code>. That's the
          whole shape of the language — everything else below is just
          vocabulary.
        </p>
      </section>

      {/* ── Interactive keyword reference ── */}
      <section className="docs-reference">
        <h2>Keyword & Operator Reference</h2>
        <div className="docs-reference-grid">
          <div className="docs-kw-list">
            {CATEGORIES.map((cat) => (
              <div key={cat.name} className="docs-kw-category">
                <h3>{cat.name}</h3>
                <div className="docs-kw-chips">
                  {cat.items.map((item) => (
                    <button
                      key={item.kw}
                      className={
                        "docs-kw-chip" +
                        (selected.kw === item.kw ? " docs-kw-chip--active" : "")
                      }
                      onClick={() => setSelected(item)}
                    >
                      {item.kw}
                    </button>
                  ))}
                </div>
              </div>
            ))}
          </div>

          <div className="docs-kw-detail">
            <div className="docs-kw-detail-header">
              <span className="docs-kw-detail-kw">{selected.kw}</span>
            </div>
            <p className="docs-kw-detail-meaning">{selected.meaning}</p>
            <pre className="docs-kw-detail-code">{selected.snippet}</pre>
            <button
              className="docs-try-btn"
              onClick={() =>
                tryIt(
                  selected.snippet.includes("sceneOnHa")
                    ? selected.snippet
                    : `sceneOnHa\n    ${selected.snippet.replace(
                        /\n/g,
                        "\n    ",
                      )}\n    wapas 0 !!\nsceneOffHa`,
                )
              }
            >
              ▶ Try it in Editor
            </button>
          </div>
        </div>
      </section>

      {/* ── Worked example programs ── */}
      <section className="docs-examples">
        <h2>Example Programs</h2>
        <div className="docs-examples-grid">
          {EXAMPLES.map((ex) => (
            <div key={ex.title} className="docs-example-card">
              <h3>{ex.title}</h3>
              <p>{ex.desc}</p>
              <pre>{ex.code}</pre>
              <button className="docs-try-btn" onClick={() => tryIt(ex.code)}>
                ▶ Try it in Editor
              </button>
            </div>
          ))}
        </div>
      </section>
    </div>
  );
}
