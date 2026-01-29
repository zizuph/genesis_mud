#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",
                                           "conifforest",}));
object tent, b1, b2, b3;

void
reset_tharkadan_room()
{
    set_searched(0);

    if(!objectp(tent))
    {
        tent = clone_object(TOBJ+ "tent");
        tent->move(TO,1);
        tent->command("set up tent");
    }

    if(!objectp(b1))
    {
        b1 = clone_object(LIVING+ "refugee");
        b1->move(TO,1);
        b1->command("set up tent");
        b1->command("enter tent");
    }

    if(!objectp(b2))
    {
        b2 = clone_object(LIVING+ "refugee");
        b2->move(TO,1);
        b2->command("set up tent");
    }

    if(!objectp(b3))
    {
        b3 = clone_object(LIVING+ "refugee");
        b3->move(TO,1);
        b3->command("set up tent");
    }

}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_prop(LIVE_I_CAN_FISH, "alpine_lake");
    
    add_exit(ROOM + "hvale5","north",0);
    add_exit("/d/Krynn/guilds/OotS/room/joinroom","northwest",0);
    add_exit(ROOM + "hvale4","west",0);

    add_item(({"valley","vale","wide vale","protected vale",
        "secluded valley","hopeful vale","centre"}),
        "You stand within a secluded valley rimmed by mountains to the " +
        "north and an ice-free lake to the south. Pines and firs grow " +
        "in abundance here, and scattered beneath the trees rise the " +
        "encampment of refugees from the lands to the north who escaped " +
        "the mines of Pax Tharkas and fled south here to what they now " +
        "call 'the Hopeful Vale'.\n");
    add_item(({"aspen","aspen trees","aspens"}),"Native to cold regions " +
        "with cool summers, aspen trees grow in large numbers here.\n");
    add_item(({"lodgepole pine","lodgepole pine trees","pine",
        "pine trees"}), "A thin and narrow-crowned tree also known as " +
        "the twisted pine that is common in alpine regions such as the " +
        "Tharkadan Range.\n");
    add_item(({"fir","fir trees","firs"}),"Growing throughout the " +
        "Tharkadan Range are large fir trees, evergreen coniferous " +
        "trees common to mountainous regions.\n");
    add_item(({"trees","tree"}),"Pines and firs grow in abundance here " +
        "in this secluded valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_forest_snow");
    add_item(({"encampment","tents","nomadic tents"}), "The refugee " +
        "encampment consists largely of nomadic tents of Abanasinian " +
        "design. Considering the barbarians of the plains make up a " +
        "large proportion of the refugees, this doesn't surprise you.\n");
    add_item(({"refugees","barbarians"}),
        "You notice the refugees seem to come from a range of locations " +
        "- Abanasinian barbarians, townfolk of Solace and Haven, even " +
        "the odd gully dwarf!\n");
    add_item(({"lake","ice-free lake"}),
        "You stand at the bank of an ice-free lake that forms the " +
        "southern border of a secluded wooded valley. Serene and " +
        "crystal clear, you feel calmed looking at it.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_hopeful_vale_desc() +", before an ice-free lake";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "mountains ";
	break;
    case AUTUMN:
    case WINTER:
	str = "ice-capped mountains ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand within a secluded valley rimmed by " +
        mountain_desc() + "to the north and an ice-free lake to the " +
        "south. Pines and firs grow in abundance here, and scattered " +
        "beneath the trees rise the encampment of refugees from the " +
        "lands to the north who escaped the mines of Pax Tharkas " +
        "and fled south here to what they now call 'the Hopeful Vale'.\n";
}

