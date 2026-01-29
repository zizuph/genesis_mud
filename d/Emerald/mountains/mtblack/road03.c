/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

int
ne_block()
{
    write("You scramble over some boulders and find " +
       "a narrow path leading up the mountainside.\n");
    return 0;
}

void
create_road()
{
    set_long("   The road here curves around the foot of the black "+
	     "mountain. The dark, black stone is glistening with the "+
             "moisture of a recent rainfall, as well as that of very "+
	     "small streams of water which drip down off of the peak "+
	     "through cracks and depressions in the side of the "+
	     "mountain. The road continues to the north of here, where "+
	     "you can see the foot of the black mountain give way to "+
	     "reveal the base of the volcano. The narrow, jagged peak "+
	     "stands tall against the backdrop of shifting clouds "+
	     "in the sky, creating a dizzying effect if stared at for "+
	     "too long.\n\n");
    add_item( ({"streams", "small streams"}),
              "There are small streams of water no wider than your hand "+
              "trickling down the edge of the black mountain from the "+
              "snowy peak above.\n");

    add_exit(MBLACK_DIR + "road04", "north");
    add_exit(MBLACK_DIR + "road02", "southeast");
    add_exit("path1", "northeast", ne_block, 3, 1);
}
