/*
 * The toilet has been adapted from Gelan lavatory
 * Tapakah, 04/2009
*/


#pragma save_binary

inherit "/d/Calia/gelan/rooms/lavatory";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

object * payers = ({0,0,0,0,0,0,0,0,0,0});      /* array of players who have paid
                                                   the fee */

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
create_room()
{
    /* doors */

  door_1 = clone_object(CADU_DOORS + "lavatory_m");
  door_1->move(this_object());

  door_2 = clone_object(CADU_DOORS + "lavatory_f");
  door_2->move(this_object());
  
  door_3 = clone_object(CADU_DOORS + "lavatory_n");
  door_3->move(this_object());
    /* descriptions */

  set_short("Pier toilets");
  set_long("You're standing next to a stall on the pier of Cadu. "
           + "Next to you are three surprisingly clean small cabins. "
           + "In front of the cabins there is a small desk and a rickety "
           + "chair on which an elderly goblin sits. On the desk there is "
           + "a cardboard box, and a poster hangs from a pole next to it. "
           + "To the west and to the east you see piers, and beyond the "
           + "water to the north, you can see the beaches of Cadu.\n");
  
  /* properties */
  
  add_prop(ROOM_I_INSIDE, 0);		/* this room is outside! */
  
  /* exits */

  add_exit("cadu_pier3", "west","@@leave_lavatory");
  add_exit("cadu_pier4", "east","@@leave_lavatory");
    
  /* items in the room */

  add_item(({"cabins"}),"They are very clean, made of some light wood.\n");
  add_item("box", "The box is made of sturdy cardboard and it is closely "
           + "watched by the goblin. A sign on the front of the box says: "
           + "'Use <pay fee> to pay the fee to use the lavatory. You "
           + "don't get any money back! All money paid is lost when you leave "
           + "the lavatory !'.\n");
  add_item(({"poster","sign","note"}), "@@poster");
  add_cmd_item(({"poster","sign","note"}), "read", "@@poster"); 
  add_item("box","The box is made of metal and looks very hard to "
           + "break, so don't try it. A sign on the front of the box says: "
           + "'Use <pay fee> to pay the fee to use the lavatory. You "
           + "don't get any money back! All money paid is lost when you leave "
           + "the lavatory !'.\n");
  add_item("door","You have to be more specific, which door do you mean?\n");
  add_item("lock","You have to be more specific, which lock do you mean?\n");
  add_item(({"attendant","toilet attendant"}), "She's responsible for "
           + "this lavatory. She controls if you pay and if you leave the "
           + "lavatory as clean as you found it.\n");
} /* create_room */

void
init()
{
  ::init();
}

void
clean_up()
{
  ::clean_up();
}



