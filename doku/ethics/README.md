# Ethical Evalutation of CoEnv

This repository contains the outcome of the course Global Citizenship at my study program Code&Context.

It also contains a [Github Action Pipeline](./.github/workflows/output.yml) that compiles and publishes a LaTeX Document to a [PDF](https://jim-fx.github.io/coenv-ethics/coenv.pdf) and [HTML](https://jim-fx.github.io/coenv-ethics).

## How to Setup

**Install Dependancies**
- latexmk
- latex2html [INSTALL](https://github.com/latex2html/latex2html/blob/master/INSTALL)
- texlive-lang-german

[How to install dependancies (Ubuntu)](https://gist.github.com/rain1024/98dd5e2c6c8c28f9ea9d)

[How to install dependancies (MaxOSX, untested)](https://macappstore.org/basictex/)


## Neovim

I use:
- [**VimTex**, auto compilation](https://github.com/lervag/vimtex)

To start the compilation in neovim run the command `\ll`.

Then open the `main.pdf` in a PDF viewer which supports reloading. (I use [evince](https://wiki.gnome.org/Apps/Evince) on debian).
- [**LspConfig**, configuring the lsp](https://github.com/neovim/nvim-lspconfig)
```lua
require "lspconfig".ltex.setup{}
```
- [**LspInstaller**, installing lsps](https://github.com/williamboman/nvim-lsp-installer)
```bash
:LspInstall ltex
```
- [**TreeSitter**, syntax highlighting](https://github.com/nvim-treesitter/nvim-treesitter)
```bash
:TSInstall latex
```
## Makefile Scripts

```bash
make compile # --> Compiles PDF to main.pdf

make clean # --> Remove Temporary Latex Files

make build # --> Comile & Clean

make html # --> Compile to HTML files in /main
```

## Bookmark to create BibTex entries from Websites [Credit](https://github.com/dmstern/html2biblatex)
```js
javascript:"use strict";(function(){var _document$querySelect,_document$querySelect2,_document$querySelect3;function copyToClipboard(text){window.prompt("Copy to clipboard: Ctrl+C, Enter",text)}function jsDate2bibTex(date){var dd=date.getDate();var mm=date.getMonth()+1;var yyyy=date.getFullYear();if(dd<10){dd="0"+dd}if(mm<10){mm="0"+mm}return yyyy+"-"+mm+"-"+dd}function date2YearTex(date){var yyyy=date.getFullYear();return""+yyyy}var title=document.title;var url=document.URL;var author_tag=document.querySelector("[name=author]");var author=author_tag==null?"":author_tag.content;var today=new Date;var urldate=jsDate2bibTex(today);var publishedTime=(_document$querySelect=document.querySelector(%27meta[property="article:published_time"%27))===null||_document$querySelect===void 0?void 0:_document$querySelect.getAttribute("content");var someTimeTag=(_document$querySelect2=document.querySelector("time[datetime]"))===null||_document$querySelect2===void 0?void 0:_document$querySelect2.getAttribute("datetime");var someTimeTagWithoutDatetime=(_document$querySelect3=document.querySelector("time"))===null||_document$querySelect3===void 0?void 0:_document$querySelect3.innerHTML;var lastModifiedTime=document.lastModified;var pageTime=new Date(publishedTime||someTimeTag||someTimeTagWithoutDatetime||lastModifiedTime);var date=jsDate2bibTex(pageTime);var year=date2YearTex(pageTime);var title_key=title.replace(/[^0-9a-z]/gi,"");var citationKey=title_key+"-"+date;var type="@Online";var filename=":./references/"+window.location.pathname.slice(1).replace(/\//g,"-")+".html:html";var title_tex=title.replace(/\u00e4/g,%27\\"a%27).replace(/\u00c4/g,%27\\"A%27).replace(/\u00f6/g,%27\\"o%27).replace(/\u00d6/g,%27\\"O%27).replace(/\u00fc/g,%27\\"u%27).replace(/\u00dc/g,%27\\"U%27).replace(/\u00DF/g,%27\\"s%27);var bibTexEntry=type+" {"+citationKey+",\r  title = {"+title_tex+"},\r  date = {"+date+"},\r  year = {"+year+"},\r"+(author?"  author = {"+author+"},\r":"")+"  file = {"+filename+"},\r  url = {"+url+"},\r  urldate = {"+urldate+"}\r}";copyToClipboard(bibTexEntry)})();
```

## LateX commands used/learned
```tex
% starts a new paragraph
\section{SectionName} 

% Creates Sub Sections 
\subsection{SectionName}
\subsubsection{SectionName}

% Creates linebreaks and pagebreaks
\newline
\newpage

% Use extensions/addons in the Document
\usepackage{Packagename}
% For example:
\usepackage{amsmath}
\usepackage{dirtytalk}

% Create a title
\maketitle

% Starts a block of the specified types
% types: document, figure 
\begin{figure}
\end{figure}
```
