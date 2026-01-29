/* 
Citadel, office
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;
object ob2;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   hear_bell = 2;
   set_short("Citadel, office");
   set_long("You see several large desks here in this office."+
      " Several books, letters and other types of sheets lies spread out on "+
      "them in neat orders, showing that the people working here likes to have "+
      "control. What attracts your attention though is a decorated bronze door "+
      "that leads westwards. It must be the High Lords office! All around you "+
      "paintings, statues and other fanciful decorations are spread out, as like "+
      "the owner of this place were trying to "+
      "dazzle you with its magnificence.\n");
   
   add_item("desks","The desks are of plain oak and contains several books "+
      "and sheets, all neatly arranged.\n");
   add_item(({"painting","paintings","decoration","decorations","statues","statue"}),
      "They almost cramp the room up, stuffing the air with the value they "+
      "symbolizes.\n");
   
   add_exit(CENTRAL(citadel/cit24),"southwest",0,-1,-1);
   add_exit(CENTRAL(citadel/cit19),"east",0,-1,-1);
   add_exit(CENTRAL(citadel/cit21),"southeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit23),"south",0,-1,-1);
   
   clone_object("/d/Kalad/common/central/doors/high_lord_door1")->move(TO);
   set_alarm(0.0,0.0,"reset_room");
}


reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_elite_c");
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_elite_c");
      ob2 -> arm_me();
      ob2 -> move_living("xxx",TO);
   }
   ob1 -> team_join(ob2);
}
