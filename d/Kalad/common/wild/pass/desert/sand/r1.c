inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int pres,i;
object *ob;
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_LIGHT,0);
   INSIDE;
   set_short("Inside a ruined tower");
   set_long("You find yourself at the base of the ruined tower.\n"+
      "The crumbling stone walls of the tower surround you, threatening "+
      "to come crashing down at the slightest provocation. The air here "+
      "is dry and extremely stale, pervaded with an underlying odor of death "+
      "and decay. A nearly ruined flight of steps leads from one side of the "+
      "circular tower up to the second level. Lying around the room are the "+
      "smashed remains of chairs, desks and other furniture. Old, cracked "+
      "paintings line the walls around you, save for the east, where a "+
      "firmly locked iron door still stands.\n");
   add_item(({"crumbling stone walls","crumbling walls","stone walls","walls","wall"}),
      "The aged and crumbling stones look quite unstable, as if they may "+
      "collapse at any moment.\n");
   add_item(({"flight of steps","flight","steps","step"}),
      "A curving stone staircase that has crumbled in some parts, though it "+
      "is still serviceable.\n");
   add_item(({"chairs","desks","furniture","chair","desk"}),
      "The wooden objects have nearly crumbled. Not for any effect of the "+
      "elements, but from the ravages of termites.\n");
   add_item(({"old paintings","cracked paintings","paintings","painting"}),
      "The aged paintings portray images of a black robed figure atop a "+
      "dark grey tower. Flaming balls of fire are leaping from his hands, "+
      "burning the woodlands that surround the tower. On each of the "+
      "paintings is an image of a sun as black as night.\n");
   add_item(({"locked iron door","locked door","iron door","door"}),
      "An extremely weathered iron barrier. It lies in the eastern side "+
      "of the tower and for attempts and purposes is firmly shut and "+
      "locked.\n");
   add_exit(CPASS(desert/sand/r2),"up","@@check",-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(obj/rt_mcorpse));
      ob1 -> move(TO);
      tell_room(TO,"A mummified corpse at the center of the room attracts "+
         "your attention.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/rt_spectre));
      ob2 -> move_living("M",TO);
      tell_room(TO,"A faint moaning arises from the mummified corpse in the room.\n");
      tell_room(TO,"A spectral figure rises forth from it!\n");
   }
   if(!ob3)
      {
      ob3 = clone_object("/d/Immortal/island/obj/pearls/black_pearl3");
      ob3 -> add_prop(OBJ_I_HIDE,90);
      ob3 -> move(TO);
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres  = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Spectre")
         {
         pres = 1;
        }
   }
   if(pres == 1)
      {
      write("The chilling horrific spectre refuses to let you leave!\n");
      say(QCTNAME(TP) + " tries to leave but is immediately stopped by the "+
         "chilling horrific spectre!\n");
   }
   return pres;
}
