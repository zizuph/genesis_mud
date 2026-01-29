#include "../defs.h"
inherit ALT_STD + "room.c";
#include "/d/Cirath/common/teamer.h"

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants. The buildings" +
        " here are erratic, many of them are nothing more than" +
        " make-shift tents. People are running carrying wares from" +
        " the caravans.");
    last_line("A road seem to form leading north into the desert.");
    
    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defences," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");    
    
    add_exit("01", "north", 0,1,0);
    add_exit("03", "east", 0,1,0);
    add_exit("05", "southeast", 0,1,0);
    add_exit("04", "south", 0,1,0);

    reset_room();
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(ALT_NPC+"alt_guard2",1,3,ALT_NPC+"alt_guard2",1);
}