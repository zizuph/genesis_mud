#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    set_long("   The gathering of trees here is so thick, and the trees "+
             "are so young, it seems as though they form cell bars on "+
             "either side of the path. The trees bend upward and across "+
             "the narrow opening in the forest. A cool breeze blows north "+
             "to south here, whipping the new branches back and forth, "+
             "swatting them at your face. Further north, through the mist, "+
                   "you can see the path get smaller, more narrow, and darker. "+
             "The passage through the forest widens as it continues to the "+
             "south.\n\n");

    add_fexit(CORAMAR+"f16", "northwest", 0);
    add_fexit(CORAMAR+"f14", "south", 0);
}
