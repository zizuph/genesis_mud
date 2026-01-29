#include "../defs.h"
inherit "/d/Cirath/std/room.c";
#include "/d/Cirath/common/teamer.h"

void
create_room()
{
    set_short("the barracks is Altaruk.");
    set_long("This is the bunk room of the town guards. Several rows" +
        " of bunks are here. Most of the men are out on duty now," +
        " but there are always a groups of mercs ready in case" +
        " something happens.\n");

    add_item(({"wall", "walls", "columns"}), "The walls are bare" +
        " sandstone with not as much speck of dirt on them.\n");

    add_item(({"bunk", "bunks"}), "Wooden bunks, just big enough for" +
        " one person to sleep in. There is a whole bunch of them in here." +
        " Some are even in use right now.\n");
    
    add_prop(ROOM_I_INSIDE,1);
    add_exit("barracks1.c","west",0,1,0);
    add_exit(ALT_SQU + "03.c","south",0,1,0);

    reset_room();
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(ALT_NPC+"alt_guard",1,4,ALT_NPC+"alt_guard",1);
}