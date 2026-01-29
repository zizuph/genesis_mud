/* Pax Tharkas, inside Sla-Mori.
 *
 * 950406 by Rastlin 
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit PAXINROOM;

int secret_door_open = 1;
int first_reset = 0;
object banshee;

void
reset_pax_room()
{
   if(secret_door_open && first_reset)
    TO->set_door_closed();
   first_reset = 1;

   if(!objectp(banshee))
   {
     banshee = clone_object(PMONSTER + "banshee");
     banshee->move(TO);
   }

}

void
create_pax_room()
{
    set_short("Treasure vault of Kith-Kanan");
    set_long("You stand in a large room nearly filled with yellow, " +
      "brick-like objects covered in a thick layer of dust. " +
      "@@long_desc");

    add_item(({"objects","yellow brick-like objects","yellow objects",
      "brick-like objects","bricks","gold","treasure"}),
      "The room is filled with the treasure of Kith-Kanan, many " +
      "bricks of gold. Unfortunately they are now worthless since the " +
      "cataclysm, with steel now being the preferred currency of Krynn.\n");

    add_item(({"dust","thick layer of dust","layer of dust"}),
      "Hundreds of years of dust has formed a thick layer over the bars " +
      "of gold filling this large room.\n");

    add_item(({"wall","secret door","door","west wall"}),"@@wall_desc");

    add_cmd_item(({"wall","secret door","door"}),"slide","@@slide_door");

    add_exit(PSLA + "chainroom", "west", "@@not_open");

    add_prop(ROOM_I_LIGHT, 0);

    reset_pax_room();
}

void
set_door_open()
{
   if(!secret_door_open)
   {
      string chainroom = PSLA + "chainroom";

      secret_door_open = 1;
      tell_room(PSLA + "chainroom", "A secret door slides open in the eastern wall.\n");
      add_exit(PSLA + "chainroom", "west", "@@not_open");
      find_object(chainroom)->set_door_open();
   }
}

void
set_door_closed()
{
   string chainroom = PSLA + "chainroom";

   secret_door_open = 0;
   tell_room(PSLA + "chainroom", "The opening to the east closes, leaving a noticeable " +
      "outline of a secret door in the wall.\n");
   tell_room(TO, "The secret door to the west slides shut, leaving a noticeable " +
      "outline of a secret door in the wall.\n");

   remove_exit("west");

   find_object(chainroom)->set_door_closed();
}

string
slide_door()
{
   if(secret_door_open)
     return "The secret door is currently open.\n";

   write("You push hard against the wall, and a secret door slides open " +
       "to the west.\n");
   say(QCTNAME(TP)+ " pushes hard against the wall, and a secret door " +
       "slides open to the west.\n");

   set_door_open();
   return "";
}

string
long_desc()
{
   if(secret_door_open)
     return "A sliding secret door stands open to your west.\n";
   else
     return "The outline of a secret door lines the wall to your west. " +
       "You could probably slide it open.\n";
}

string
wall_desc()
{
   if(secret_door_open)
     return "A sliding secret door stands open in the wall to your west.\n";
   else
     return "The outline of a secret door lines the wall to your west. " +
       "You could probably slide it open.\n";
}


int
not_open()
{
   if(secret_door_open)
    return 0;

   write("The secret door has closed! You will need to slide it open.\n");
    return 1;

}
