inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define HARD_TO_MOVE 40
#define DAMAGE 75
string long;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("At the bottom of a well");
   set_long("This is the very bottom of the well, at least the bottom of "+
      "the dry portion. Only a narrow three foot wide ledge running "+
      "along the outer edge of the well supports your weight. The center "+
      "is occupied by a very dark and unnaturally still pool of water.\n");
   add_item(({"bottom","well","slick walls","slick wall","walls","wall"}),
      "The ash-colored stones of the surrounding well are slightly slick from the "+
      "moisture-laden air here at the bottom of the well.\n");
   add_item(({"ledge","outer edge","edge"}),
      "A very narrow three foot wide space surrounding the pool of water "+
      "at the center of the well.\n");
   add_item(({"center","pool of water","pool","water"}),
      "The dark, nearly stagnant pool of liquid is barely recognizable as "+
      "water, so still and thick is it.\n");
   add_exit(CPASS(desert/oasis/o4),"up","@@check_climb",3);
   add_exit(CPASS(desert/oasis/u2),"down","@@msg",3);
   set_alarm(1.0,0.0,"reset_room");
}
check_climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_MOVE))
      {
      write("You attempt to scale the slick walls of the well, but fail.\n");
      say(QCTNAME(TP) + " attempts to scale the slick walls of the well, but fails.\n");
      write("You are hurt in the attempt.\n");
      say(QCTNAME(TP) + " is hurt in the attempt.\n");
      TP->heal_hp(-DAMAGE);
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You successfully scale the slick walls of the well.\n");
   say(QCTNAME(TP) + " successfully scales the slick walls of the well.\n");
   return 0;
}
msg()
{
   TP->catch_msg("You dive down into the water-filled bottom of the well!\n");
   say(QCTNAME(TP) + " dives down into the water-filled bottom of the well!\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/water_sprite));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A small creature appears.\n");
      ob1 -> command("giggle");
   }
}
