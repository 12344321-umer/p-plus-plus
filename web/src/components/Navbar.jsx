export default function Navbar() {
  return (
    <nav className="navbar">
      <div className="navbar-left">
        <span className="logo">
          P<span className="logo-accent">++</span>
        </span>
        <span className="tagline">Pakistani Gen-Z Programming Language</span>
      </div>
      <div className="navbar-right">
        <a href="https://github.com" target="_blank" rel="noreferrer">
          GitHub
        </a>
      </div>
    </nav>
  );
}
