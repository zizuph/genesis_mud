/*
ROOM: South corner of Town Square
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object man;

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   INSIDE;
   
   set_short("sage's office");
   set_long(
      "This is Hernan, the sage's office. It is stuffed with books, "+
      "papers, pens, desks and officials running around using it all. "+
      "In the back of the room, Hernan's own large oak-desk is situated, upon a plateau.\n"
   );
  add_item("desk","Its a large desk made of oak.\n");
   add_item("books","All around you, you see books, books and books. "+
      "This man, Hernan, has really done some reading during his "+
      "lifetime.\n");
   
   
   add_exit(CENTRAL(plaza/sq_south),"northwest",0,-1,-1);
   
   
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(man))
      {
      man = clone_object("/d/Kalad/common/central/npc/q_tmaster");
      man -> move_living("M",TO);
      man -> command("emote lifts his eyebrows to look at you, "+
         "and then lowers them down towards some papers.");
   }
}
