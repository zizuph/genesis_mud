#include "../defs.h"

inherit ALT_STD + "room.c";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("scarab",ALT_NPC+"scarab.c",7,0);
}

void
create_street()
{

    short_name("in a dark alley in Altaruk.");
    extra_line("The alley looks darker than the streets" +
        " and less clean.");
    last_line("This is a dead end.");
    
    add_item("alley", "A messy place. Not one door is left" +
        " unlocked here.\n");
    add_item(({"end", "dead-end", "dead end"}), "There's a" +
        " wall blocking your way south.\n");

    add_exit("03.c", "north", 0,1,0);
    reset_room();
}
