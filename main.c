#include <stdio.h>
#include "nanosvg.h"

int main() {

struct SVGPath* plist = NULL;
char *filename = "../path1.svg";
plist = svgParseFromFile(filename);

	// Use...

	struct SVGPath* it = plist;
	puts("{");
for (; it; it = it->next)
{
        //glBegin(it->closed ? GL_LINE_LOOP : GL_LINE_STRIP);
		int i = 0;
		puts("{ ");
        for (; i < it->npts; ++i) {
			//printf("it->pts[%d*2] = %f\n", i, it->pts[i*2]);
			//printf("it->pts[%d*2+1] = %f\n", i, it->pts[i*2+1]);
			printf("{x=%f, y=%f},\n", it->pts[i*2], it->pts[i*2+1]);
		}
		puts("},");
          //      glVertex2f(it->pts[i*2], it->pts[i*2+1]);
        //glEnd();
}
puts("}");

// Delete
svgDelete(plist);

	return 0;
}
