#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "ledge6","north",0);
    add_exit(ROOM + "ledge8","southwest",0);

    add_item(({"valley","vale","wide vale","protected vale",
         "isolated valley", "floor","centre","forested valley"}),
         "You stand on the side of a towering peak overlooking a wide " +
         "vale rimmed by mountains. Aspens and firs grow in abundance, " +
         "although the most notable feature of this valley is the " +
         "towering peak you currently stand on.\n");
    add_item(({"mountains"}),"Mountains rim the valley beneath you.\n");
    add_item(({"aspen","aspen trees","aspens"}), "You see aspen trees " +
         "growing in large numbers in the valley below.\n");
    add_item(({"fir","fir trees","firs"}), "You see large fir trees " +
         "growing in the valley below.\n");
    add_item(({"trees","tree"}), "Aspens and firs grow in abundance " +
         "below in the valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	 "white","snow-covered land","winters snow","winter's snow"}),
         "@@add_item_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano",
         "mountain","ledge"}), "You are standing on a ledge on the side " +
         "of a towering peak, likely once an ancient volcano. Far below " +
         "you can see this mountain stands alone amongst a sea of aspen " +
         "and fir trees.\n");
    add_item(({"summit"}),"You look up towards the summit, and estimate " +
         "you are getting close to the top.\n");
    add_item(({"cavernous opening","opening","cave"}),"Like the maw of " +
         "a great beast is a cavernous opening in the side of the " +
         "peak, leading into darkness. No doubt the result of volcanic " +
         "activity from the ancient past.\n");
    add_item(({"darkness"}),"Within the cave before you, all you can " +
         "see is darkness.\n");

    add_cmd_item(({"opening","cave","cavernous opening","darkness"}),
         "enter","@@enter_cave");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "in front of a cavernous opening in the side of a " +
        "towering peak";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "The ledge runs steeply upwards to your southwest and " +
           "downwards to your north. ";
	break;
    case AUTUMN:
    case WINTER:
	str = "The snow-covered ledge runs steeply upwards to your " +
            "southwest and downwards to your north. ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand high on a ledge running along the side of a " +
        "towering peak that sits in the centre of a forested valley. " +
        mountain_desc()+ "Gaping wide before you like the maw of a " +
        "great beast is a cavernous opening in the side of the peak, " +
        "leading into darkness.\n";
}

string
enter_cave()
{
    write("You step into the cavernous opening in the side of the " +
        "peak...\n");
    TP->move_living("into the cavernous opening", 
        CAVERNS + "cavern1", 1, 0);
    return "";
}