inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
create_room()
{
   set_short("Inside a Tent");
   set_long("You have entered a squalid tent inside the courtyard "
   	+"of the gith fortress.  Rough mats and dirty cloth lay "
   	+"on the floor here, obviously some sort of bedding, while "
   	+"in the center of the tent, a small firepit sits smoking.  "
   	+"The smell in here is horrible, a combination of filthy "
   	+"gith, and rancid meat.\n");
   add_item(({"mats","mat","cloth","dirty cloth"}),"This looks to "
   	+"be some form of rough bedding, that only a creature as "
   	+"filthy as the gith would use.\n");
   add_item("firepit","A small ring of rock forms a small circle "
   	+"roughly a foot in diameter that is obviously used as a "
   	+"firepit.  In the desert at night, it has been known to "
   	+"become very cold very fast, so this is not that "
   	+"surprising.\n");
   add_exit(CAMP + "c13","out");
     set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
   bring_room_team(GITH_NPC+"gith3",1,1,GITH_NPC+"gith3",1);
}

