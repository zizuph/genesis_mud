inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("within a smith in Underhome");
   set_long("This room is filled with a black smoke "+
      "created from the hearth in the wall and the "+
      "unending shoveling of coal into it. A pile of the fuel "+
      "fills the room, making it hard to stand here.\n");
   add_item("coal","Its the substance that fuels the hearth.\n");
   add_item("hearth","It is a part of the furnace where the "+
      "dwarves throw in the coal.\n");
   
   add_exit(CPASS(dwarf/smith/s1),"west",0,-1,-1);
   set_alarm(2.0,0.0,"reset_room");
   
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/npc/coal_man));
      ob1->arm_me();
      ob1->move_living("M",TO);
      tell_room(TO,"A dirty deep dwarf starts to shovel coal.\n");
   }
}
