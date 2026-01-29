#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",
    "conifforest",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "vale6","northwest",0);
    add_exit(ROOM + "vale2","north",0);
    add_exit(ROOM + "vale1","east",0);
    add_exit(ROOM + "vale7","southwest",0);     
    add_exit(ROOM + "vale4","south",0);

    add_item(({"valley","vale","wide vale","protected vale",
        "isolated valley","floor","centre"}),
        "You stand within a wide vale rimmed by mountains. Aspens and " +
        "firs grow in abundance here, although the most notable feature " +
        "of this valley is the towering peak that rises from its " +
        "centre.\n");
    add_item(({"aspen","aspen trees","aspens"}), "Native to cold " +
        "regions with cool summers, aspen trees grow in large numbers " +
        "here.\n");
    add_item(({"fir","fir trees","firs"}), "Growing throughout the " +
        "Tharkadan Range are large fir trees, evergreen coniferous " +
        "trees common to mountainous regions.\n");
    add_item(({"trees","tree"}),"Aspens and firs grow in abundance " +
        "here and the vale.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano","foot"}),
        "Before you rises the steep walls of a towering peak, likely " +
        "once an ancient volcano, standing alone amongst a sea of aspen " +
        "and fir trees.\n");
    add_item(({"walls","steep walls","icy walls"}), "Steep, icy walls " +
        "of a towering peak rise high above you.\n");

    add_cmd_item(({"walls","peak","towering peak","wall","steep walls"}),
        "climb", "The steep walls of the peak are too icy to climb " +
        "here.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "at the foot of a towering peak in an isolated valley";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
        case SPRING:
        case SUMMER:
	    str = "mountains. ";
	    break;
        case AUTUMN:
        case WINTER:
	    str = "ice-capped mountains. ";
	    break;
    }
    return str;
}

string
long_descr()
{
    return "You stand at the foot of a towering peak in the centre of " +
       "a wide vale rimmed by " +mountain_desc()+
       "Aspens and firs grow in abundance here and the vale is somewhat " +
       "protected from the wind and cold.\n";
}

