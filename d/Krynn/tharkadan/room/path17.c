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
    set_searched(random(2));
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass"}),
        "You stand on a trail running through the Tharkadan Mountain " +
        "Range. On either side of the path loom snow-covered peaks and " +
        "ridgelines.\n");
    add_item(({"valley","towering peak","peak"}), "To your northwest " +
        "opens a forested valley. In the center of the valley a " +
        "towering peak rises.\n");

    add_exit(ROOM + "vale8","northwest",0);
    add_exit(ROOM + "path18","southeast",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a valley pass in the Tharkadan Mountains";
}

string
long_descr()
{
    return long_mountain_desc()+ "To your northwest opens a valley " +
       "dominated by a towering peak in the center.\n";
}
