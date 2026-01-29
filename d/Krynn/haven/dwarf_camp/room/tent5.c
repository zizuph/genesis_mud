#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object dwarf1, dwarf2, dwarf3, dwarf4;

// Prototypes

string my_desc();

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
   add_exit(DROOM + "camp5", "out");

   add_item("table", "The table is filled with various papers and maps, all of "+ 
                     "them completely drenced in a foul smelling liquid. Four "+
                     "mugs of ale and four dirty plates stand on it.\n");

   add_item(({"chair","chairs"}), "The chairs have been made from newly cut wood, "+ 
                                  "they look primitive, but sturdy.\n");

   add_item(({"mug","mugs"}), "The mugs are filled with a foul smelling liquid.\n");

   add_item(({"bed","beds"}), "The beds consists of nothing more then a pile of "+ 
                              "staw with a thick quilt.\n"); 

   add_item(({"papers", "maps"}), "They are completely ruined and unreadable.\n");
   add_item(({"liquid", "foul liquid", "foul smelling liquid", "smelling liquid"}),
              "It is spilled all over the table.\n");

   INSIDE;

   reset_haven_room();

}

string
my_desc()
{
      return "You are standing in a large canvas tent. The air is thick with smoke "+
             "and a heavy stench of old ale and dwarven spirit fills the air. "+
             "Several primitive beds have been placed against the north side and a "+ 
             "large wooden table with four chairs stand in the middle of the tent. "+
             "You can pull the entrance flap aside and step out.\n";
}
void 
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(interactive(ob))
  {
    tell_room(this_object(), QCTNAME(ob)+" arrives from the outside.\n", ob);
  }
}
