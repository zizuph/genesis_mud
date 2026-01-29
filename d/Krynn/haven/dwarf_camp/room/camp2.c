/* Dwarven camp by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf1, dwarf2, dwarf3;

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
    if (!objectp(dwarf3))
    {
	dwarf3 = clone_object(STD + "dwarf_base");
	dwarf3->move(TO);
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(DROOM + "camp1", "northeast");
    add_exit(DROOM + "camp3", "east");
    add_exit(DROOM + "camp6", "southeast");
    add_exit(DROOM + "camp5", "south");
    add_exit(DROOM + "campa", "southwest");

    add_item(({"tent", "canvas tent", "large canvas tent"}),
               "The large canvas tent seems like good place to seek " +
               "protection from bad weather.\n");

    OUTSIDE;
    reset_haven_room();
}

string
my_desc()
{
    if (!present(dwarf1, TO) && !present(dwarf2, TO) && !present(dwarf3, TO))
	return "You're on the western side of the dwarven encampment. The "+
               "entrance is to the northeast. You also notice a large canvas tent.\n";

    return "You're on the western side of the dwarven encampment. The dwarves "+
           "bustle all around you, getting ready to trade with the inhabitants of "+
           "Haven. The entrance is to the northeast. You also notice a large canvas tent.\n";
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
   TP->move_living("M",DROOM + "tent2",0,0);
   return 1;
}



