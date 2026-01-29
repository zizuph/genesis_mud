inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(OBJ_I_HAS_FIRE,1);
   set_short("A smelly chamber");
   set_long("This roughly-hewn stone chamber reeks of stale sweat and "+
      "excrements that have been lying around for ages. A pile of wood lies "+
      "in the far side of the chamber while a small fire provides light "+
      "at the center of the room. A tunnel in the west leads back towards "+
      "the central chamber.\n");
   add_item(({"roughly-hewn stone chamber","roughly-hewn chamber","stone chamber","chamber","room"}),
      "A warm, dark place within the depths of the Desertrise mountains.\n");
   add_item(({"excrements","excrement"}),
      "Stains lie in many parts of the floor, and even the walls. However, "+
      "there are no actual piles of it present, for it appears that the "+
      "current inhabitant has made at least some effort to reduce the "+
      "filthiness of this place.\n");
   add_item(({"pile of wood","pile","wood"}),
      "A large stack of firewood. It is nearly five feet in height.\n");
   add_item(({"small fire","fire"}),
      "It provides a modest amount of light to the chamber, and also serves "+
      "to make it uncomfortably warm.\n");
   add_item(({"tunnel"}),
      "A short passage that leads to the west.\n");
   add_item(({"walls","wall","floor","ceiling"}),
      "The interior of this chamber is made of the same dark grey stone "+
      "that comprises the entirety of the Desertrise range of mountains.\n");
   add_exit(CPASS(desert/mount/g2),"west");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/stone_giant));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"You feel strong vibrations on the ground and turn to find "+
         "yourself faced with a stone giant!\n");
   }
}
