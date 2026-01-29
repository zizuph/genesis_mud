#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You are at the end of a dark hall in the "+
    "temple of the Khiraa. The walls here are made of cold dark "+
    "stone. Upon the walls you see a few runes and symbols. The "+
    "air is filled with the stench of death and decay. The cold "+
    "marble floor reflects no light.\n"+
    "   You see that the hallway ends here at many doors. The "+
    "hallway also continues to the west, where you see nothing "+
    "but more darkness. The darkness is most comforting to your "+
    "cold soul.\n\n");
    
    INSIDE;
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   

    add_exit(KHIRAA_DIR(temple/rooms/t16),"west",0,-1);
    clone_object(KHIRAA_DIR(temple/doors/rackdoor1))->move(TO);
    clone_object(KHIRAA_DIR(temple/doors/forgedoor1))->move(TO);

}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him, Lord of Eternity, Master of the Grave.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}
