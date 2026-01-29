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

    add_exit(ROOM + "path16","northwest",0);
    add_exit(ROOM + "path9","northeast",0);

    add_item(({"narrow canyon","canyon"}),"You stand within a dark " +
        "narrow canyon between two ridges of the Tharkadan Mountain " +
        "Range. It continues to your northwest, while to your northeast " +
        "it opens up to a trail through the mountains.\n");
    add_item(({"ridges","two ridges","ridge"}),
        "Two walls of two ridges make the narrow canyon you now stand " +
        "in.\n");
    add_item(({"walls","wall","canyon walls","ice"}),
        "The walls of the canyon are uncomfortably close and slick " +
        "with ice, making climbing them impossible.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");

    add_prop(ROOM_S_DARK_LONG, "A dark, narrow canyon. The shadows " +
          "are too deep to see anything without a light source.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The shadows of the canyon are too deep " +
           "to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "dark narrow canyon between two ridges of the Tharkadan " +
        "Mountains";
}

string
long_descr()
{
    return "You stand in a narrow canyon between two ridges of the " +
       "Tharkadan Mountains. The height and closeness of the canyon " +
       "walls cast deep shadows around you, and you doubt the light " +
       "of the sun gets down here often. To your northeast the " +
       "canyon opens up to a trail, while it continues to your " +
       "northwest.\n";
}

