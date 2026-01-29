#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
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
    add_item(({"trail","pass","valley pass"}),
      "You stand on a trail running through the Tharkadan Mountain " +
      "Range. Here the trail heads northwest out of the valley.\n");
    add_item(({"lake","crystal clear lake","clear lake","mountain lake"}),
      "Through the pine trees to your south you can make out a clear " +
      "mountain lake created from glacial melt.\n");
    add_item(({"unsed path","path"}), "A path rarely used heads south " +
      "from here towards a mountain lake.\n");
    add_item(({"hall","hall of slayers"}), "To your north stands the " +
      "largest of the buildings in the village, a hall dedicated to " +
      "those hill dwarves who have taken a death oath, the Doomseekers.\n");
    add_item(({"store","general store","dwarven general store"}),
      "To your northeast is a small lodgepole cabin that is marked to " +
      "be the general store of this dwarven village.\n");
    add_item(({"village","wooden cabins","cabins","cabin","dwarven village",
      "lodgepole buildings","buildings","lodgepole cabins","encampment"}),
      "Before you is a village of lodgepole cabins nestled into a "+
      "narrow valley of pine trees. Based on their precise " +
      "construction and low height it looks like an encampment of hill " +
      "dwarves of the Neidar clan. The smell of wood fire from the " +
      "cabins fills the fresh mountain air.\n");
    add_item(({"pines","pine trees","trees","lodgepole pine trees"}),
      "Here in the valley lodgepole pines grow crowded together, with " +
      "the cabins of the village made from these very pines.\n"); 
    add_item(({"smoke", "blue-grey smoke"}),"Smoke rises up from the " +
      "cabins here, filling mountain air with a blue-grey smoke.\n");

    add_exit(ROOM + "xx","northwest","@@closed_path");
    add_exit(ROOM + "path20","east",0);
    add_exit(ROOM + "dwarf/hall","north", 0);
    add_exit(ROOM + "dwarf/shop","northeast", 0);
    add_exit("/d/Ansalon/guild/neidar/rooms/ancestor_tree","south",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "centre of a dwarven village of lodgepole cabins";
}

string
long_descr()
{
    return long_mountain_desc()+ "The trail is nestled within a narrow " +
        "valley amongst great pine trees is a village of lodgepole " +
        "cabins, the home of a clan of hill dwarves. To your north " +
        "stands the largest of the village buildings - the Hall of " +
        "Slayers, while to your northeast is a dwarven general store. " +
        "The trail leads out of the valley to your northwest, while " +
        "to your south an unused path heads up out of the valley to " +
        "the edge of a mountain lake.\n"; 
}

int
closed_path()
{
   write("You head up the trail to your northwest, but quickly return " +
     "after being gruffly rebuffed by the local hill dwarf residents.\n");
   say(QCTNAME(TP)+ " heads up the trail to your northwest into the " +
     "village, but quickly returns after being rebuffed by the local " +
     "hill dwarf residents.\n");
   return 1;
}
