const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const COMPILER_DIR = path.join(__dirname, "..", "compiler");

/* 
  On Windows use the pre-built exe.
  On Linux (Railway) use the compiled binary.
*/
const IS_WINDOWS = process.platform === "win32";
const COMPILER_BINARY = IS_WINDOWS
  ? path.join(COMPILER_DIR, "p-plus-plus.exe")
  : path.join(COMPILER_DIR, "p-plus-plus");

function compile(code) {
  return new Promise((resolve) => {
    const tmpFile = path.join(COMPILER_DIR, `temp_input.ppp`);
    fs.writeFileSync(tmpFile, code, "utf8");

    const cmd = IS_WINDOWS
      ? `cd "${COMPILER_DIR}" && p-plus-plus.exe temp_input.ppp --json`
      : `cd "${COMPILER_DIR}" && ./p-plus-plus temp_input.ppp --json`;

    exec(cmd, (error, stdout, stderr) => {
      try {
        fs.unlinkSync(tmpFile);
      } catch (e) {}

      console.log("stdout:", stdout);
      console.log("stderr:", stderr);
      console.log("error:", error);

      if (stdout && stdout.trim()) {
        try {
          const result = JSON.parse(stdout.trim());
          resolve({ success: true, data: result, stderr: stderr || "" });
        } catch (e) {
          resolve({
            success: false,
            error: "Failed to parse compiler output",
            raw: stdout,
            stderr: stderr || "",
          });
        }
      } else {
        resolve({
          success: false,
          error: stderr || error?.message || "Unknown compiler error",
          stderr: stderr || "",
        });
      }
    });
  });
}

module.exports = { compile };
