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

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
      "@@add_item_path");

    add_exit(ROOM + "path11","northwest",0);
    add_exit(ROOM + "path13","south",0);

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
    return long_mountain_desc() + "The trail begins to slope downwards " +
        "to the south here.\n";
}
