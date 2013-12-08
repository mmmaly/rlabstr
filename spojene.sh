#!/bin/bash

for((i=0;i<=127;i++))
do
for X in A B
do

I=`printf %03d $i`
FILE="spojene_$I$X.tex"

cat << END > $FILE
\documentclass[12pt,oneside]{book}
\usepackage{a4wide}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\date{16. jún 2013}

\usepackage{color}
\usepackage{colortbl}
\usepackage{array}
\usepackage{MnSymbol}
\usepackage[labelformat=empty]{caption}
\usepackage[labelformat=empty]{subcaption}
\usepackage{setspace}
\usepackage{float}

\usepackage{epsfig}

\begin{document}
\pagestyle{empty}


\begin{figure}
END

echo "\\subfloat[0]{\\includegraphics[width=0.33\\textwidth]{history_$I$X-crop}}" >> $FILE
echo "\\subfloat[1]{\\includegraphics[width=0.4\\textwidth]{history_$I}}" >> $FILE

cat << END >> $FILE
\label{fig:development}
\end{figure}

\end{document}
END
done
done
