inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#define DMG 50
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Cave entrance");
   set_long("The dirt pathway ends here, at the entrance into a dark "+
      "and foreboding cave in the hillside. Tall grasses and a few stunted "+
      "trees grow around the entrance, adding to the eerie landscape. "+
      "Twisted shrubbery forms a thorny barrier to the northwest, barring "+
      "you from entering that way. The only viable option seems to be the "+
      "entrance in the northeast.\n");
   add_item(({"dirt pathway","pathway"}),"The narrow, well-used path "+
      "heads back to the southeast.\n");
   add_item(({"entrance","dark cave","foreboding cave","cave"}),"The "+
      "cave is located on the side of one of the foothills and the entrance "+
      "has been split so that it forks to the northwest and northeast. "+
      "However, several thorny shrubs block the way to the northwest.\n");
   add_item(({"hillside","foothills","foothill","hills","hill"}),"The "+
      "rolling hills are all around you, with the one immediately to your "+
      "north being the closest, as well as possessing a cave entrance.\n");
   add_item(({"tall grasses","grasses","grass"}),"Hardy plants suited "+
      "to this somewhat dry climate.\n");
   add_item(({"stunted trees","trees","tree"}),"The trees look as if "+
      "they lack an adequate amount of water.\n");
   add_item(({"twisted shrubbery","shrubbery","thorny barrier","barrier","thorny shrubs","shrubs","shrub"}),
      "Like a living wall, a great mass of the plants grows at the "+
      "northwestern entrance into the cave, blocking it to casual entrance.\n");
   add_exit(CPASS(goblin/g9),"northwest","@@check_gob");
   add_exit(CPASS(goblin/g11),"northeast",0);
   add_exit(CPASS(goblin/g7),"southeast",0,2,1);
}
check_gob()
{
   if(TP->query_race_name() != "goblin")
      {
      write("You try to go northwest, but simply can't squeeze yourself through the thorny shrubs.\n");
      write("You get scratched badly!\n");
      TP->heal_hp(-DMG);
      say(QCTNAME(TP) + " tries to go northwest but gets nothing but scratches for " + TP->query_possessive() + " effort.\n");
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to squeeze through the shrubs without harm!\n");
   return 0;
}
