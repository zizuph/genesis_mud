inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
create_room()
 {
  set_short("Cavern");
  set_long("You have entered a small cavern in the gith fortress.  "
  	+"Stacked against the rough hewn walls are large wooden "
  	+"crates and some big barrels.  Apparently this is a room "
  	+"used for storing things out of the sun.\n");
  add_item("walls","They are roughly carved from the mountain above "
        +"you.\n");
  add_item(({"barrels","barrel","big barrel","big barrels"}),"These "
        +"wooden barrels are stacked against the wall for storage.\n");
  add_item(({"crate","crates","wooden crates","wooden crate"}),
        "These sturdy crates are stacked against the wall with some "
        +"barrels.  The crates are all emblazoned with the symbol of "
        +"a spear piercing the twin suns of Athas.\n");
  add_item("cavern","You are inside of it.\n");
 
  add_exit(CAMP + "c19","northeast");
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith2",1,1,GITH_NPC+"gith2",1);
}

