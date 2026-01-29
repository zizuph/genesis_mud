#include "../defs.h"
inherit "/d/Cirath/std/room.c";
#include "/d/Cirath/common/teamer.h"

void
create_room()
{
    set_short("the barracks is Altaruk.");
    set_long("This is the hall of the town guards. Stone tiles" +
        " cover the ground. The floor is spotless. The hall is" +
        " quite large with stone columns to cover the span of" +
        " of the ceiling. North lies the office of Arisphistaneles" +
        " the commander of this contingent of mercenaries. To the" +
        " east the mercs have their bunks.\n");

    add_item(({"wall", "walls", "columns"}), "The walls are sandstone" +
        " with columns to carry the roof. The columns are round with" +
        " no decorations.\n");
       
    add_prop(ROOM_I_INSIDE,1);
    add_exit(ALT_STR + "06.c","west",0,1,0);
    add_exit("barracks2.c","east",0,1,0);
    add_exit("comoffice.c","north",0,1,0);

    reset_room();
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(ALT_NPC+"alt_guard",1,1,ALT_NPC+"alt_guard",1);
}
