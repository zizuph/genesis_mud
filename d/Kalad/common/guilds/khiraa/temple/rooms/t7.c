#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You are walking along a short, cold hallway. The "+
    "walls and ceiling are made of smooth black stone, while the "+
    "floor is formed of polished black marble. Small red runes "+
    "decorate the sides of the walls.\n"+
    "   The air is thick with the stench of death and decay. The "+
    "hallway continues further into darkness to the north, while "+
    "also leading back to the main chamber through a small doorway "+
    "in the south wall.\n\n");

    INSIDE;
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   

    add_prop(ROOM_I_LIGHT,0);
    add_exit(KHIRAA_DIR(temple/rooms/t8),"north",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/temple_main),"south",0,-1);
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him. Khiraa.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}
