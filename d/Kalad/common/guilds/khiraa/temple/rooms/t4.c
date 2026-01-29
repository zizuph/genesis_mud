#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary
inherit "/d/Kalad/room_std";


void
create_room()
{
    set_short("In a large chamber");
    
    set_long("\n   You are now in a large chamber within what looks like "+
    "a temple complex. The ground below you is covered with broken "+
    "pieces of dark grey brick that the walls and ceiling are made "+
    "of. The ceiling is vaulted up high, and you can see parts of it "+
    "are covered with moss. Moss, actually, covers a great deal of "+
    "the area around here. Some of the walls have strange runes and "+
    "symbols, but not as much as the walls back to the south do. In "+
    "the center here, you see a large statue. Behind the statue, "+
    "you see another archway that leads into some kind of hall. What "+
    "is unique, and a little unsettling, about this archway is that "+
    "it is shaped like a skull, and the entrance being the mouth. "+
    "On either side of the skull-archway, you notice two large wooden "+
    "crosses about human height. The stench of death and decay is "+
    "stronger here.\n\n");
    add_item("walls","The walls are made of dark grey brick. Some "+
    "parts contain strange symbols and runes. It is falling apart "+
    "in a lot of places, while moss covers other parts.\n");
    add_item("floor","The floor is covered with debris from the "+
    "walls and ceilings, as well as moss.\n");
    add_item("ceiling","The large vaulted ceiling goes up several "+
    "feet and looks quite impressive.\n");
    add_item("archway","The archway is shaped like a skull with a "+
    "wide open, screaming mouth where the entrance is. You notice "+
    "that there are strange runes covering the skull.\n");
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("moss","The moss is grey and greenish. It grows in "+
    "clumps all over the place and smells bad. It is slightly "+
    "damp.\n");
    add_item("crosses","The crosses are made of rotting dark wood. "+
    "They look very old. On them, you can see dried blood.\n");

    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    clone_object(KHIRAA_DIR(temple/obj/ent_statue))->move(TO);
    add_exit(KHIRAA_DIR(temple/rooms/t5),"north",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t3),"southeast",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t2),"south",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t1),"southwest",0,-1);
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP) )
        return "They are praises to the Nameless One. His might "+
        "unmatched, the Netherworld shall rule.\n";
    return "The runes and symbols are "+
    "ancient looking, and you are not sure what they mean.\n";
}

