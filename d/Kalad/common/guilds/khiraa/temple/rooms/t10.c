#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";


void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You find yourself in a large, dark hall. The walls "+
    "here are made of black stone, and are smooth to the touch. The "+
    "floor is made of solid black marble, and it reflects little "+
    "light. The scent of death and decay is strong.\n"+
    "   A large stone archway leads to the north, in which you can "+
    "only darkness. The hallways contines to the south and east, "+
    "through another archway into the main temple.\n\n");
    add_item("walls","The walls are made of solid black stone, and "+
    "are smooth and almost polished. They radiate a coldness that "+
    "you have never felt before.\n");
    add_item("ceiling","The ceiling is made of dark stone much like "+
    "the walls. On it you can see a large symbol.\n");
    add_item("symbol","The symbol is that of a large S shaped symbol "+
    "with a staff going through it.\n");
    add_item("floor","The floor is made of solid, polished black "+
    "marble that reflects little light.\n");
    add_item("archway","@@query_k@@");
    
    INSIDE;
    add_exit(KHIRAA_DIR(temple/rooms/temple_libr),"north",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/temple_main),"east",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t14),"south",0,-1);
}

int
block()
{
    if(IS_DK(TP) || IS_LP(TP))
        return 0;
    write("You strange magical shield suddenly appears and pushes "+
    "you back.\n");
    say(QCTNAME(TP)+" tries to go south, but is blocked by a magical "+
    "shield.\n");
    return 1;
}

string
query_k()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "The runes on the archway read: The Library of the "+
        "Khiraa, in His Honor.\n";
    return "The north archway contains many strange runes on it, "+
    "but you can recognize one that seems to look like a book.\n";
}

