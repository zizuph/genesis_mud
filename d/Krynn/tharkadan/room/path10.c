#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "path9","northwest",0);
    add_exit(ROOM + "path11","southeast",0);
    add_invis_exit(ROOM + "fforest1","north","@@enter_forest");
    add_invis_exit(ROOM + "fforest2","northeast","@@enter_forest");

    add_item(({"woods","mountain woods","forest","vale","trees",
        "fallen forest"}), "To your north-northeast the pass opens up " +
        "to a vale where aspen, fir and lodgepole pine form a secluded " +
        "mountain woods known as 'the Fallen Forest'.\n");
    add_item(({"aspen","aspen trees"}),"Native to cold regions with " +
        "cool summers, aspen trees grow in large numbers in the " +
        "woods to your southeast.\n");
    add_item(({"fir","fir trees"}),"Growing throughout the Tharkadan " +
        "Range are large fir trees, evergreen coniferous trees common " +
        "to mountainous regions.\n");
    add_item(({"lodgepole pine","lodgepole pine trees","pine",
        "pine trees"}), "A thin and narrow-crowned tree also known as " +
        "the twisted pine that is common in subalpine regions such as " +
        "the Tharkadan Range.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
       "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
       "@@add_item_path");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_mountain_desc();
}

string
long_descr()
{
    return long_mountain_desc()+ "To your north and northeast a vale " +
        "opens up between two mountain ranges where aspen, fir and " +
        "lodgepole pine form a secluded mountain woods.\n";
}

int
enter_forest()
{
   write("You step off the mountain path and enter the woods...\n");
   return 0;
}

