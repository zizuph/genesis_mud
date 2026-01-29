#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You are now walking along a cold, dark "+
    "hallway. The hall here bends to the north and east. The "+
    "walls echo your footsteps throughout the hallway. You "+
    "notice tiny runes on the ceiling and walls.\n"+
    "   You see nothing but darkness further east and north. "+
    "The dark shadows feel good to your cold soul.\n\n");
    INSIDE;
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   

    add_exit(KHIRAA_DIR(temple/rooms/t11),"north",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t16),"east",0,-1);
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him, Lord of Eternity.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}
