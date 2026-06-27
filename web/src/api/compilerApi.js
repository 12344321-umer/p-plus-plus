import axios from "axios";

const API_URL = "http://localhost:3001";

export async function compileCode(code) {
  try {
    const response = await axios.post(`${API_URL}/compile`, { code });
    return response.data;
  } catch (error) {
    return {
      success: false,
      error: error.response?.data?.error || "Server not reachable",
    };
  }
}
