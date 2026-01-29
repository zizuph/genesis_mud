/* The arena where the fighting goes on... */
/* Made by Korat */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void
create_room()
{
   ::create_room();
   hear_bell = 3;
   add_prop(ROOM_I_INSIDE,1);
   set_short("the arena");
   set_long ("You find yourself out on the battle-field of the arena. "+
      "The sandy ground feels warm below your feet, and you barely "+
      "notice the blood-stains covering it. All your attention is "+
      "focused on the upcoming fight...where you will either survive "+
      "or die, so you don't bother to look for any exits.\n");
   
   add_item (({"exit","exits"}),"As you knew before entering this "+
      "arena, there are only two exits away from it; Either alive "+
      "or dead....So you better win this!\n");
   add_item(({"sand","sands"}),"Plain sand that radiates the heat from "+
      "the sun. Some bloodstains can be recognized in it.\n");
   add_item (({"blood","bloodstain","bloodstains"}),"Just some ordinary dried blood "+
      "that the keeper of the arena couldn't clean up...\n");
   
}
