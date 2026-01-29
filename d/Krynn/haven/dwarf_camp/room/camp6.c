/* Dwarven camp by Morrigan */

#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf1, dwarf2, dwarf3, dwarf4;

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
    if (!objectp(dwarf4))
    {
	dwarf4 = clone_object(STD + "dwarf_base");
	dwarf4->move(TO);
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(DROOM + "camp2", "northwest");
    add_exit(DROOM + "camp3", "north");
    add_exit(DROOM + "camp4", "northeast");
    add_exit(DROOM + "camp7", "east");
    add_exit(DROOM + "campg", "southeast");
    add_exit(DROOM + "campf", "south");
    add_exit(DROOM + "campe", "southwest");
    add_exit(DROOM + "camp5", "west");

    add_item(({"tent", "canvas tent", "large canvas tent"}),
               "The large canvas tent seems like good place to seek " +
               "protection from bad weather.\n");

    OUTSIDE;
    reset_haven_room();
}

string
my_desc()
{
    if (!present(dwarf1, TO) && !present(dwarf2, TO) && !present(dwarf3, TO) && !present(dwarf4, TO))
	return "You're in the center of the dwarven encampment. To the "+
               "north is the entrance to the camp. To the south is where "+
               "all the goods and supplies are kept. You also notice a large canvas tent.\n";

    return "You're in the center of the dwarven encampment. The dwarves "+
           "bustle all around you, getting ready to trade with the inhabitants of "+
           "Haven. The entrance is to the north. To the south is where all the "+
           "good and supplies are kept. You also notice a large canvas tent.\n";
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
   TP->move_living("M",DROOM + "tent6",0,0);
   return 1;
}

