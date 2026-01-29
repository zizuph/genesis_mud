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
    "   The air is think with the stench of death and decay. The "+
    "hallway continues further into darkness in both directions. "+
    "A large pillar is stands in the center of the hallway.\n\n");
    
    add_item("pillar","The pillar is crafted of smooth black marble, "+
    "much like the floor. Only, you see swirls of dark green and red "+
    "mixed in with it. Placed every foot or so, are platinum "+
    "sculptures of a grim skull. The eyes of the skull sparkle "+
    "because they are made of valuable emerald gems.\n");

    INSIDE;
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   
    add_exit(KHIRAA_DIR(temple/rooms/t12),"west",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t14),"east",0,-1);
    clone_object(KHIRAA_DIR(temple/doors/studydoor1))->move(TO);
//    clone_object(KHIRAA_DIR(temple/doors/lpcoffindoor1))->move(TO);
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him. He who is the pillar of our strength.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}
