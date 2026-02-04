/*
 * Genesis ShipLines - Cadu office.
 * TAPAKAH, 10/2008
 */

#include <stdproperties.h>
#include "/d/Sparkle/area/city/shiplines/lib/gs_office.h";
#include "gs_office.h"

inherit GSL_OFFICE_BASE;
inherit "/d/Calia/gelan/rooms/lavatory";

object door_1;                                  /* Pointer to the doors */
object door_2;                                  /* Pointer to the doors */
object door_3;                                  /* Pointer to the doors */

string
poster()
{
   return 
     "Dear Customer:\n\n"
     + "   Genesis ShipLines Company cares for its customers! Now you can\n"
     + "   comfortably relieve yourself while waiting for the ships.\n"
     + "   We hope that you leave this building as clean as you found it.\n"
     + "   The GSL management will pursue every traveller who breaks\n"
     + "   this rule.\n"
     + "   Each customer of the lavatory has to pay a fee of \n"
     + "                       1 Gold Coin\n"
     + "   to guarantee the future support of the lavatory.\n"
     + "   When a cabin is occupied, you can knock at the door to tell\n"
     + "   the player to hurry up. To enter a cabin, just type the word\n"
     + "   written on the door.\n"
     + "   The customer is pleased to follow the following rules:\n\n"
     + "       - don't stay too long in the cabinet\n"
     + "       - only one person per cabin\n"
     + "       - use the right cabin\n"
     + "       - leave the cabin as you found it\n"
     + "       - don't write any texts on the walls\n"
     + "                                   Genesis ShipLines Company\n\n";
}

void
create_room ()
{
  ::create_gsl_office();
  setuid();
  seteuid(getuid());
  door_1 = clone_object(DOOR_M_IN);
  door_1->move(this_object());

  door_2 = clone_object(DOOR_F_IN);
  door_2->move(this_object());
  
  door_3 = clone_object(DOOR_N_IN);
  door_3->move(this_object());

  set_short("Inside the Last Town Office of Genesis ShipLines");
  set_long("You are inside the Last Town Office of Genesis ShipLines Company."+
           "A small but cozy shack has a window in its south wall. " +
           "and a few short but comfortably looking benches. "+
           "A small desk is at the "+
           "three doors in the western wall, and an attendant sits next to it "+
           "and a glass-like timetable is bolted to the eastern wall.\n");
  add_npc(TOILET_KEEPER, 1, &->equip_me());
  set_timetable_file(TIMETABLE);
  add_object(TIMETABLE);
  add_exit(EXIT_TO_PIER, "north");
  add_prop(ROOM_I_INSIDE, 1);
  add_item(({"windows", "window"}),
           "Through the window in the south wall and the icicles you can see " +
           " the southeastern shore of the Last Town in Terel.\n");
  add_item(({"north door", "northern door"}),
           "The door in the northern wall is open and leads out.\n");
  add_item("box", "The box is made of sturdy cardboard and it is closely "
           + "watched by the goblin. A sign on the front of the box says: "
           + "'Use <pay fee> to pay the fee to use the lavatory. You "
           + "don't get any money back! All money paid is lost when you leave "
           + "the lavatory !'.\n");
  add_item(({"poster","sign","note"}), "@@poster");
  add_cmd_item(({"poster","sign","note"}), "read", "@@poster"); 
  add_item(({"door","doors"}),
           "You have to be more specific, which door do you mean?\n");
  add_item("lock","You have to be more specific, which lock do you mean?\n");
  add_item( ({ "desk", "wooden desk", "simple desk",
               "simple wooden desk" }),
            "A new simple wooden desk. A large cardboard box is sitting on it, "
            +"and a heap of leaflets is piled next to the box.\n");
  add_item( ({ "heap of leaflets", "leaflets", "leaflet", "heap", "pile" }),
            "The leaflets look like they contain some valuable "
            + "information. You think you might be able to <grab> one.\n");
    
  remove_item("attendant");
}

public void
init()
{
  ::init();
  add_action(get_leaflet, "get");
  add_action(get_leaflet, "take");
  add_action(get_leaflet, "pick");
  add_action(get_leaflet, "grab");
}
