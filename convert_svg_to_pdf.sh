for i in *.svg; do inkscape $i --export-pdf=${i%.svg}.pdf; done

