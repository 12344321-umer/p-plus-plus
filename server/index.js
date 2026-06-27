const express = require("express");
const cors = require("cors");
const { compile } = require("./compile");

const app = express();
const PORT = 3001;

app.use(cors());
app.use(express.json());

// Health check
app.get("/", (req, res) => {
  res.json({ status: "P++ compiler server running" });
});

// Main compile endpoint
app.post("/compile", async (req, res) => {
  const { code } = req.body;

  if (!code || code.trim() === "") {
    return res.status(400).json({
      success: false,
      error: "No code provided",
    });
  }

  try {
    const result = await compile(code);
    res.json(result);
  } catch (err) {
    res.status(500).json({
      success: false,
      error: err.message,
    });
  }
});

app.listen(PORT, () => {
  console.log(`P++ server running at http://localhost:${PORT}`);
});
