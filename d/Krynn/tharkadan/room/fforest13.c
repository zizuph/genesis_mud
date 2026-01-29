#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","eversnow", 
                                           "conifforest", }));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "fforest14","southwest",0);
    add_exit(ROOM + "fforest12","northwest",0);
    add_exit(ROOM + "fforest16","southeast",0);
    add_exit(ROOM + "fforest15","south",0);

    add_item(({"woods","mountain woods","forest","vale","trees",
        "fallen forest","valley"}),
        "You stand within the depths of an alpine forest where aspen, " +
        "fir and lodgepole pine form a secluded mountain woods known as " +
        "'the Fallen Forest'.\n");
    add_item(({"aspen","aspen trees"}),"Native to cold regions with " +
        "cool summers, aspen trees grow in large numbers in the woods " +
        "to your east.\n");
    add_item(({"fir","fir trees"}),"Growing throughout the Tharkadan " +
        "Range are large fir trees, evergreen coniferous trees common " +
        "to mountainous regions.\n");
    add_item(({"lodgepole pine","lodgepole pine trees","pine",
        "pine trees"}), "A thin and narrow-crowned tree also known as " +
        "the twisted pine that is common in alpine regions such as the " +
        "Tharkadan Range.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_forest_snow");
    add_item(({"watchtower","tower","dwarven watchtower","ancient " +
        "dwarven watchtower"}), "Rising out of the forest is the ruin " +
        "of a watchtower from the days of the Dwarfgate Wars. While " +
        "dwarven made, 300 years of neglect has left it partially " +
        "collapsed, and its rusted iron door hangs twisted and open, " +
        "allowing you easy entry. At the top of the tower you notice " +
        "the light and smoke of a fire, so while ruined it seems it " +
        "isn't abandoned.\n");
    add_item(({"rusted iron door","iron door","door"}),
        "The once impressive iron door now is pitted and heavily " +
        "rusted, twisted off its hinges, allowing you to enter the " +
        "tower if you wish.\n");
    add_item(({"top of the tower","top of tower","tower top","fire",
        "smoke","light"}), "At the top of the tower you notice the " +
        "light and smoke of a fire.\n");

    add_cmd_item(({"tower","watchtower","door","iron door"}),"enter",
        "@@enter_tower");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_forest_desc()+ ", near the ruins of a dwarven watchtower";
}

string
long_descr()
{
    return long_forest_desc()+"To your east rises the ruins of an " +
        "ancient dwarven watchtower, its rusted iron door hanging " +
        "twisted and open.\n";
}

string
enter_tower()
{
    write("You push past the rusted iron door into the watchtower...\n");
    TP->move_living("into the ruined watchtower", ROOM + 
         "fwatchtower", 0, 0);
    return "";
}