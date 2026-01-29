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

    add_exit(ROOM + "ledge11","northwest",0);
    add_exit(ROOM + "ledge13","northeast",0);

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
         "you are getting very close to the top.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "near the top of a towering peak in the Tharkadan mountain " +
        "range";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "You can continue towards the top of the mountain by " +
            "heading northeast or you can make your way down by heading " +
            "northwest. ";
	break;
    case AUTUMN:
    case WINTER:
	str = "The snow is thick at this height, making it difficult " +
            "to travel, although you can continue towards the top of " +
            "the mountain to your northeast or down the peak to your " +
            "northwest. ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand near the summit of a towering peak " +
       "that sits in the centre of a forested valley. " +
       mountain_desc()+ "\n";
}
