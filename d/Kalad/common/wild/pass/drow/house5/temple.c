inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void create_yochlol();
int spell_done;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("A temple to Lolth, the Spider Queen");
   set_long("This great circular chamber of midnight-black stone is "+
      "dominated by the huge statue of Lolth, located against the eastern "+
      "wall of the room. A large, blood-stained altar lie beneath the "+
      "recreation of Lolth, while the rest of this vast chamber is bare save "+
      "for a pair of platinum braziers standing at the northern and southern "+
      "sides of the room. To the west, a darkened archway lies, leading back "+
      "to the main hall of House Kilsek.\n"+
      "A glowing column of blood red light occupies the center of this temple to "+
      "Lolth.\n");
   add_item(({"glowing column","column","blood red light","red light","light"}),
      "A six foot high column of crimson energy, it appears to lead down "+
      "through the floor of this chamber and into another room.\n");
   add_item(({"great circular chamber","great chamber","circular chamber","chamber","room","vast chamber"}),
      "It is where you are currently standing, have a look around.\n");
   add_item(({"midnight-black stone","stone"}),
      "An unusually dark rock commonly found here within the Dark Dominion, "+
      "and used by the drow as building material for their buildings.\n");
   add_item(({"huge statue","statue","lolth"}),
      "A gigantic effigy carved in stone so black, it appears as if it is "+
      "darkness given solid form. Not a single mar or scratch can be seen "+
      "on its lightless form, one which depicts the body of a huge spider "+
      "with the head of a drow female of unearthly beauty.\n");
   add_item(({"large blood-stained altar","large altar","blood-stained altar","altar"}),
      "A great slab of dark stone from which the lighter-colored stain of "+
      "blood is visible.\n");
   add_item(({"pair of platinum braziers","platinum braziers","platinum brazier","braziers","brazier"}),
      "Standing at five feet in height and filled with a slowly burning and "+
      "extremely potent incense, they provide a dim yellow light that fills "+
      "this room with incense-choked smoke.\n");
   add_item(({"darkened archway","archway"}),
      "A doorway of blackness that lies in the west.\n");
   add_item(({"ground","floor","walls","wall","ceiling"}),
      "It is composed of a dark black stone.\n");
   add_item("thesummoningspellfortheyochlol","@@summon_servant");
   add_exit(CPASS(drow/house5/main_hall),"west",0,-1,-1);
   add_exit(CPASS(drow/house5/sac_chamber),"down","@@msg",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
msg()
{
   write("You feel yourself grow lighter as the blood red column of light "+
      "transports you downwards.\n");
   say(QCTNAME(TP) + " seems to grow lighter as the blood red column of "+
      "light slowly transports " + TP->query_objective() + " downwards.\n");
   return 0;
}
void
reset_room()
{
   spell_done = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h5_priest1));
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
   return;
}
string
summon_servant()
{
   if(spell_done)
      return("The spell has been cast already.\n");
   set_alarm(3.0,0.0,"create_yochlol");
   return("The spell has not been cast yet.\n");
}
void
create_yochlol()
{
   int i;
   spell_done = 1;
   for(i = 0; i < 3; i++)
   {
      clone_object(CPASS(drow/npc/yochlol))
      ->move(TO);
      tell_room(TO,"With a puff of smoke, a yochlol suddenly appears before you!\n");
   }
}
