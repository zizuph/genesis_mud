// Lilith Dec 2021  converted to Terel std room, removed BSN usage,
//                  removed cloning of Mystic apple.

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>

// #define BSN(xx)             break_string(xx + "\n", 70)
// #define MOQ_DIR             "/d/Terel/mecien/valley/guild/quest/"

#define NO_OF_APPLES        10

int noa;

void
reset_room() 
{
    noa = NO_OF_APPLES;
}

void
init() 
{
    ::init();
    add_action("pick", "pick");
}

void
create_room()
{

    set_short("Trees On The Moor");
    set_long("A strange clump of trees is here, out in the moor. They " +
        "stand alone, like an island. The trees are tall birch, " +
        "poplar, ash and fir. Here in their midst there is a frail " +
        "peace, a simple harmony, which you find serene and uplifting.\n");
    add_item(({"trees", "tree", "clump"}), 
	"Among the birches, poplars, ashes, and firs also a lonely " +
	"apple tree stands.\n");
    add_item(({"apple tree"}), "@@my_atree");
    add_item(({"apple", "apples"}), "@@my_apple");

    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
   add_item(({"heather", "ground", "moss"}),"The ground is covered in heather "+
       "and moss and standing water due to poor drainage.\n");
   add_item(("shrubs"),"Small shrubs litter the area.\n");
   add_item(({"hill","hills","moor", "moors"}),"Rolling hills covered in mist.\n");


    add_exit("moor3", "west", 0);

    reset_room();
}

string
my_atree()
{
    if (noa > 0) {
	return "The apple tree contains some apples.\n";
    } else {
	return "Someone seems to have picked all the apples " +
		   "from the apple tree.\n";
    }
}

string
my_apple()
{
    if (noa == 1) return "There is one apple left.\n";
    if (noa > 1) {
	return "There are apples in the tree. Maybe you can pick " +
		   "them.\n";
    } else {
	return "There are no apples left in the tree.\n";
    }
}

int
pick(string what)
{
    object ob;

    if (!what) return 0;

    if (what != "apple") {
	write("Pick what?\n");
	return 1;
    }

    if (noa <= 0) {
	write("There are no apples left to pick!\n");
	return 1;
    }

    noa--;
    ob = clone_object("/d/Terel/common/moor/obj/apple");
    if (ob->move(TP)) {
        ob->move(TO);
        tell_room(TO, "You see an apple fall to the ground.\n");
    } else {
	write("You pick an apple.\n");
	say(QCTNAME(TP) + " picks an apple.\n");
    }
    return 1;
}
