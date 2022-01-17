build: compile clean

compile:
	latexmk -pdf --shell-escape -f -output-directory=build

clean:
	latexmk -c

html:
	latex2html -split=0 -nonavigation -noinfo -html_version=4.0 -dir=public -style=style.css coenv.tex