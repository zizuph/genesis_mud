inherit "/std/workroom";
#include "/sys/stdproperties.h";
#include "/d/Roke/common/defs.h"

create_workroom()
{
  ::create_workroom();

set_short("Varls Meditation Chamber.\n");
set_long(BS("Each of the four walls of this chamber contains"
+ " a scene of one of the four elements. To the north a vision"
+ " of vast plains stretches before you. To the east a wide open"
+ " space where avian creatures fly unconcerned. To the south"
+ " a vision of hell, where flames burn perpetually and daemons"
+ " stalk the unwary. To the west, a vast ocean with dolphins"
+ " and mammoth whales swimming in and unending waterscape."
+ " A number of portals shimmer and flicker in the air around"
+ " a pentagram of silver. Runes carved into the floor shine"
+ " with an unearthly light, and braziers at each of the points"
+ " on the pentagram glow with a hellish light.\n",70));


add_exit("/d/Earthsea/travellers/room/start","travguild",0);
remove_exit("start");

}

