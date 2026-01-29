/* Dwarven camp by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf1, dwarf2;

// Prototypes
string my_desc();
int enter_tent(string str);

void
reset_haven_room()
{
    if (!objectp(dwarf1))
    {
	dwarf1 = clone_object(STD + "dwarf_base");
	dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
	dwarf2 = clone_object(STD + "dwarf_base");
	dwarf2->move(TO);
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(DROOM + "camp2", "north");
    add_exit(DROOM + "camp3", "northeast");
    add_exit(DROOM + "camp6", "east");
    add_exit(DROOM + "campf", "southeast");
    add_exit(DROOM + "campe", "south");
    add_exit(DROOM + "campd", "southwest");
    add_exit(DROOM + "campa", "west");

    add_item(({"tent", "canvas tent", "large canvas tent"}),
               "The large canvas tent seems like good place to seek " +
               "protection from bad weather.\n");

    OUTSIDE;
    reset_haven_room();
}

string
my_desc()
{
    if (!present(dwarf1, TO) && !present(dwarf2, TO))
	return "You're on the western side of the dwarven encampment. To the "+
               "northeast is the entrance to the camp, and the center is to the "+
               "east. You also notice a large canvas tent.\n";

    return "You're in the western part of the dwarven encampment. The dwarves "+
           "bustle all around you, getting ready to trade with the inhabitants of "+
           "Haven. The entrance is to the northeast, and the center is to the east. You also notice a large canvas tent.\n";
}


init()
{
    add_action(enter_tent, "enter");
    ::init();
}

int
enter_tent(string str)
{
   if(str &&
      str != "tent" && 
      str != "canvas tent" && 
      str != "large tent" &&
      str !="large canvas tent")
   {
       notify_fail("Enter what? The tent?\n");
       return 0;
   }
   write("You enter the canvas tent.\n");
   tell_room(this_object(), QCTNAME(TP)+" enters the canvas tent.\n", TP);
   TP->move_living("M",DROOM + "tent5",0,0);
   return 1;
}
