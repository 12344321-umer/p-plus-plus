const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const COMPILER_PATH = path.join(__dirname, "..", "compiler", "p-plus-plus.exe");
const TEMP_DIR = path.join(__dirname, "..", "compiler");

function compile(code) {
  return new Promise((resolve) => {
    // Write temp file inside compiler folder itself
    const tmpFile = path.join(TEMP_DIR, `temp_input.ppp`);
    fs.writeFileSync(tmpFile, code, "utf8");

    // Run from inside the compiler directory
    const cmd = `cd "${TEMP_DIR}" && p-plus-plus.exe temp_input.ppp --json`;

    exec(cmd, (error, stdout, stderr) => {
      // Clean up temp file
      try {
        fs.unlinkSync(tmpFile);
      } catch (e) {}

      console.log("stdout:", stdout);
      console.log("stderr:", stderr);
      console.log("error:", error);

      if (stdout && stdout.trim()) {
        try {
          const result = JSON.parse(stdout.trim());
          resolve({
            success: true,
            data: result,
            stderr: stderr || "",
          });
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
