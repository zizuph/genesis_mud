#include "../defs.h"
inherit ALT_STD + "room.c";
#include "/d/Cirath/common/teamer.h"

void
create_street()
{

    short_name("a busy street in Altaruk.");
    last_line("The post office is west of you.");
  
    add_exit(ALT_HOU + "postoffc.c", "west", 0,1,0);
    add_exit("20.c", "east", 0,1,0);
    add_exit("21.c", "south", 0,1,0);
    add_exit("22.c", "southeast", 0,1,0);
    reset_room();
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(ALT_NPC+"alt_guard2",1,3,ALT_NPC+"alt_guard2",1);
}