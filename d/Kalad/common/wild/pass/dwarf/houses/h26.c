inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1, ob2, ob3;

void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Within a cave-house in the dwarven city of Underhome");
   set_long("You find yourself inside a small cave that "+
      "is lighted up from the hearth in the corner. The "+
      "warmth makes you feel doucy. Along the walls "+
      "you see one bed, a small table and a wooden chair. "+
      "All of it looks fairly well used.\n");
   add_item("hearth","It is an open fireplace in the corner, "+
      "that radiates a doucy heat and a red, weak light.\n");
   add_item(({"bed","chair","table"}),"They are all "+
      "made of wood, and looks fairly well used.\n");

   add_exit(CPASS(dwarf/houses/h23),"northwest");
   set_alarm(2.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(ob1))
   {
      ob1=clone_object(CPASS(dwarf/npc/dwarf));
      ob1->arm_me();
      ob1->move_living("M",TO);
   }
   if(!objectp(ob2))
   {
      ob2=clone_object(CPASS(dwarf/npc/dwarf));
      ob2->arm_me();
      ob2->move_living("M",TO);
      tell_room(TO,"A deep dwarf stands up from the chair as you arrive.\n");
   }
   if(!objectp(ob3))
   {
      ob3=clone_object(CPASS(dwarf/npc/dwarf));
      ob3->arm_me();
      ob3->move_living("M",TO);
   }
   ob1->set_stat(5,100);
   ob1->team_join(ob2);
   ob1->team_join(ob3);
}
