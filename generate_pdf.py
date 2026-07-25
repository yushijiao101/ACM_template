#!/usr/bin/env python3
"""Generate a printable PDF from all algorithm competition templates."""

import os
import re
import sys
from pathlib import Path

from pygments import highlight
from pygments.lexers import CppLexer, CLexer
from pygments.formatters import HtmlFormatter

BASE = Path(r"D:\CF\templates")
OUTPUT_HTML = BASE / "templates.html"
OUTPUT_PDF = BASE / "算法竞赛模板集.pdf"

# Folder ordering and display names
FOLDERS = [
    ("Data Structure", "数据结构"),
    ("Graph Theory", "图论"),
    ("Trees", "树"),
    ("String", "字符串"),
    ("Dynamic Programing", "动态规划"),
    ("Number Theory", "数论"),
    ("Math(mainly Combination)", "数学（组合数学）"),
    ("Computational Geometry", "计算几何"),
    ("Other", "其他"),
]

# Exclude patterns
EXCLUDE_DIRS = {".cph", ".vscode", "example"}


def strip_extension(name: str) -> str:
    for ext in (".cpp", ".c"):
        if name.endswith(ext):
            return name[:-len(ext)]
    return name


def process_file(filepath: Path) -> str:
    """Read a C/C++ file and return syntax-highlighted HTML."""
    text = filepath.read_text(encoding="utf-8", errors="replace")
    ext = filepath.suffix
    lexer = CppLexer() if ext == ".cpp" else CLexer()
    return highlight(text, lexer, HtmlFormatter(linenos=False, nowrap=True))


def generate_html() -> str:
    """Build the complete HTML document."""
    pygments_css = HtmlFormatter().get_style_defs('.highlight')

    # Build sections
    sections_html = []
    toc_items = []

    for folder_name, display_name in FOLDERS:
        folder_path = BASE / folder_name
        if not folder_path.exists():
            continue

        # Collect .cpp and .c files, excluding hidden dirs
        files = []
        for f in folder_path.rglob("*"):
            if f.suffix not in (".cpp", ".c"):
                continue
            # Skip excluded dirs
            parts = f.relative_to(BASE).parts
            if any(p in EXCLUDE_DIRS for p in parts):
                continue
            files.append(f)

        files.sort(key=lambda f: f.stem)

        if not files:
            continue

        toc_items.append(f'<li><a href="#section-{folder_name}">{display_name}</a> ({len(files)} 个模板)</li>')

        files_html = []
        for f in files:
            name = strip_extension(f.name)
            code_html = process_file(f)
            files_html.append(f'''
            <div class="template">
                <h3 class="template-title">{name}</h3>
                <div class="code-block">
                    {code_html}
                </div>
            </div>
            ''')

        sections_html.append(f'''
        <section id="section-{folder_name}" class="topic-section">
            <h2 class="topic-title">{display_name}</h2>
            {''.join(files_html)}
        </section>
        ''')

    toc_html = '<ul class="toc">' + '\n'.join(toc_items) + '</ul>'

    return f'''<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<title>算法竞赛模板集</title>
<style>
    {pygments_css}

    /* ======== Page setup ======== */
    @page {{
        size: A4;
        margin: 1.5cm 1.2cm;
        @bottom-center {{
            content: "— " counter(page) " —";
            font-family: "Segoe UI", "Microsoft YaHei", sans-serif;
            font-size: 9pt;
            color: #888;
        }}
    }}

    * {{ box-sizing: border-box; }}

    body {{
        font-family: "Segoe UI", "Microsoft YaHei", "Noto Sans SC", sans-serif;
        font-size: 11pt;
        line-height: 1.55;
        color: #222;
        max-width: 100%;
        margin: 0;
        padding: 0;
    }}

    /* ======== Cover page ======== */
    .cover {{
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        height: 100vh;
        page-break-after: always;
        text-align: center;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
    }}
    .cover h1 {{
        font-size: 42pt;
        margin-bottom: 0.3em;
        letter-spacing: 0.05em;
        text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
    }}
    .cover .subtitle {{
        font-size: 16pt;
        opacity: 0.9;
        margin-bottom: 1em;
    }}
    .cover .info {{
        font-size: 12pt;
        opacity: 0.8;
    }}

    /* ======== TOC ======== */
    .toc-page {{
        page-break-after: always;
        padding: 2em 1em;
    }}
    .toc-page h2 {{
        font-size: 20pt;
        border-bottom: 3px solid #667eea;
        padding-bottom: 0.3em;
        margin-bottom: 0.8em;
    }}
    .toc {{
        list-style: none;
        padding: 0;
    }}
    .toc li {{
        font-size: 13pt;
        padding: 0.4em 0;
        border-bottom: 1px dotted #ccc;
    }}
    .toc li a {{
        color: #333;
        text-decoration: none;
    }}
    .toc li a:hover {{
        color: #667eea;
    }}

    /* ======== Section headers ======== */
    .topic-section {{
        page-break-before: always;
        padding: 0.5em 0;
    }}
    .topic-title {{
        font-size: 18pt;
        color: #444;
        border-left: 6px solid #667eea;
        padding-left: 0.5em;
        margin-bottom: 0.6em;
        page-break-after: avoid;
    }}

    /* ======== Template blocks ======== */
    .template {{
        margin-bottom: 1.2em;
        page-break-inside: avoid;
    }}
    .template-title {{
        font-size: 11pt;
        color: #555;
        background: #f0f0f5;
        padding: 0.3em 0.6em;
        margin: 0.5em 0 0.2em 0;
        border-radius: 4px 4px 0 0;
        page-break-after: avoid;
    }}
    .code-block {{
        overflow-x: auto;
        font-size: 9pt;
        line-height: 1.45;
        background: #fafafa;
        border: 1px solid #e0e0e0;
        border-radius: 0 0 4px 4px;
        padding: 0.5em;
    }}
    .code-block .highlight {{
        margin: 0;
    }}
    .code-block pre {{
        margin: 0;
        white-space: pre-wrap;
        word-break: break-all;
    }}

    /* ======== Print overrides ======== */
    @media print {{
        body {{
            font-size: 10pt;
        }}
        .code-block {{
            font-size: 8.5pt;
        }}
        .topic-section {{
            page-break-before: always;
        }}
        .template-title {{
            page-break-after: avoid;
        }}
    }}
</style>
</head>
<body>

<div class="cover">
    <h1>算法竞赛模板集</h1>
    <p class="subtitle">Algorithm Competition Template Collection</p>
    <p class="info">共收录 {sum(1 for d, _ in FOLDERS for f in (BASE/d).rglob("*") if f.suffix in (".cpp",".c") and not any(p in EXCLUDE_DIRS for p in f.relative_to(BASE).parts))} 个模板</p>
</div>

<div class="toc-page">
    <h2>目录</h2>
    {toc_html}
</div>

{''.join(sections_html)}

</body>
</html>'''


def html_to_pdf_edge(html_path: Path, pdf_path: Path):
    """Convert HTML to PDF using Microsoft Edge headless mode."""
    import subprocess

    edge_paths = [
        "C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe",
        "C:/Program Files/Microsoft/Edge/Application/msedge.exe",
    ]

    edge_exe = None
    for p in edge_paths:
        if Path(p).exists():
            edge_exe = p
            break

    if not edge_exe:
        print("Edge not found. Trying Chrome...")
        chrome_paths = [
            "C:/Program Files/Google/Chrome/Application/chrome.exe",
            "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe",
        ]
        for p in chrome_paths:
            if Path(p).exists():
                edge_exe = p
                break

    if not edge_exe:
        return False

    print(f"Using browser: {edge_exe}")
    url = f"file:///{html_path.as_posix()}"
    cmd = [
        edge_exe,
        "--headless",
        "--disable-gpu",
        f"--print-to-pdf={pdf_path}",
        "--no-pdf-header-footer",
        url,
    ]
    result = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        timeout=60,
    )
    if pdf_path.exists() and pdf_path.stat().st_size > 1000:
        # Look for the "bytes written" confirmation in stderr
        for line in result.stderr.splitlines():
            if "bytes written" in line.lower():
                print(f"  {line.strip()}")
        print(f"PDF generated successfully: {pdf_path}")
        print(f"File size: {pdf_path.stat().st_size / 1024:.1f} KB")
        return True
    else:
        print("PDF generation may have failed")
        print("stderr (last 5 lines):")
        for line in result.stderr.splitlines()[-5:]:
            print(f"  {line}")
        return False


def main():
    print("Generating HTML...")
    html = generate_html()
    OUTPUT_HTML.write_text(html, encoding="utf-8")
    print(f"HTML saved to: {OUTPUT_HTML}")
    print(f"File size: {OUTPUT_HTML.stat().st_size / 1024:.1f} KB")

    # Try Edge headless first (most reliable on Windows)
    print("\nConverting to PDF via Edge headless mode...")
    if html_to_pdf_edge(OUTPUT_HTML, OUTPUT_PDF):
        print("\nDone! PDF is ready for printing.")
        return

    # Fallback to weasyprint
    try:
        from weasyprint import HTML as WHtml
        print("Converting to PDF via weasyprint...")
        WHtml(string=html).write_pdf(str(OUTPUT_PDF))
        print(f"PDF saved to: {OUTPUT_PDF}")
        print(f"File size: {OUTPUT_PDF.stat().st_size / 1024:.1f} KB")
        return
    except Exception as e:
        print(f"weasyprint failed: {e}")

    print(f"""
================================================================
Automatic PDF conversion failed. Manual options:

1. Open the HTML in Edge/Chrome → Print → Save as PDF:
   {OUTPUT_HTML}

2. Install wkhtmltopdf:
   winget install wkhtmltopdf
   wkhtmltopdf {OUTPUT_HTML} {OUTPUT_PDF}
================================================================
""")


if __name__ == "__main__":
    main()
