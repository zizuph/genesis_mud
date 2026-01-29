inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object shrine;
object scrolls;

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a temple");
   set_long("You seem to have arrived inside a huge chamber in a temple "+
      "that has avoided the destiny of destruction and pillaging. "+
      "back to the west you will leave this place of peace. "+
      "This chamber is very clean and has a sacred feel to it. "+
      "The large banners, attached to the walls, combined with "+
      "a large shrine in the center brands this room as the "+
      "temples most holy area. You bow your head in respect.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "This temple has avoided the destruction, not through pure "+
      "luck but by a poweful curse of protection.\n");
   add_item(({"exits","exit"}),"You see one that "+
      "goes back west towards the center of this temple.\n");
   add_item(({"banner","banners"}),"They seem to be old standards "+
      "of the temple-warriors that once were the elite "+
      "fighters of the deep dwarves.\n");
   add_exit(CPASS(dwarf/temple/t16),"west");
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(shrine))
      {
      shrine=clone_object(CPASS(dwarf/obj/shrine));
      shrine->move(TO);
   }
}
