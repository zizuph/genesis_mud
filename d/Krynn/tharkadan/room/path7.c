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
    add_item(({"path","road","rugged pass","rugged path","trail"}),
      "@@add_item_path");

    add_exit(ROOM + "path6","northeast","@@snow_blocked_return");
    add_exit(ROOM + "path8","south",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

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
    return long_mountain_desc()+"\n";
}

int
snow_blocked_return()
{
    int snow;

    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
    case AUTUMN:
	snow = 0;
	break;
    case WINTER:
        write("The winter snow is deep here. You manage to push " +
            "your way through, however you doubt you will be able " +
            "to return that way until the snows melt in spring!\n");
        say(QCTNAME(TP)+ " pushes through the winter snow " +
           "covering the road.\n");
	snow = 1;
	break;
    }
    return 0;
}
