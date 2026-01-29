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
        "Range. Here the trail splits to your west and southeast " +
        "along the side of a crystal clear mountain lake.\n");
    add_item(({"lake","crystal clear lake","clear lake","mountain lake"}),
        "A clear lake to your southwest reflects the peaks of the " +
        "Tharkadan Mountain Ranges.\n");

    add_exit(ROOM + "path18","northeast",0);
    add_exit(ROOM + "path20","west",0);
    add_exit(ROOM + "path21","southeast",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "before a crystal clear lake in the Tharkadan Mountains";
}

string
long_descr()
{
    return long_mountain_desc()+ "Stretching out to your southwest " +
       "is a crystal clear mountain lake, along which the trail " +
       "branches off to your west and southeast, while also heading " +
       "into the mountains to your northeast.\n";
}
