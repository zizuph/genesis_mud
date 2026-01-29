#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary
inherit "/d/Kalad/room_std";


void
create_room()
{
    set_short("A stairwell within the Temple of the Khiraa");
    set_long("\n   You are standing in a short hall at the back end of "+
    "a large cavern. To the east and west, you see stairwells. "+
    "Three archways are placed along this hall, one in front of "+
    "you here, and one at each stairwell area. The archway in "+
    "front of you is adorned with strange runes and symbols.\n"+
    "   The walls around you are made of dark grey brick. The air "+
    "is filled with the scent of earth as well as decay. Clumps "+
    "of moss cover the debris covered ground. Through the archway "+
    "to the north, you see a large foyer area, where the ceiling "+
    "vaults up high into the air. A strange statue is standing in "+
    "the center.\n\n");
    INSIDE;
    add_item("walls","The walls are made of dark grey stone, and "+
    "look very old. There are some cracks forming on them, as well "+
    "as clumps of wet moss. Along many of them, you see what appear "+
    "to be ancient runes and symbols of some sort.\n");
    add_item("archway","The archway itself is very tall, and "+
    "along its sides, you see many strange runes and symbols, "+
    "very similar to what is on the walls. However, right in "+
    "the center, you see the unmistakable picture of a very "+
    "grim looking skull. Beyond the archway, you can see a "+
    "foyer of some sort, in which stands a statue.\n");
    add_item("foyer","It is on a raised platform, made of the "+
    "same grey brick. The ceiling is vaulted up high. The "+
    "ground is scattered with fallen mortar from the walls and "+
    "ceiling. Moss and other plantlife grow in abundance. A "+
    "strange statue is set in the center of it, and behind it, "+
    "you can see what looks like another archway. You will have to "+
    "get closer to investigate better.\n");
    add_item(({"symbols","runes"}),"@@query_k_rune@@");
    add_item("moss","Mostly grey and green kinds of mosses. They are "+
    "slightly damp.\n");
    add_item("ceiling","The ceiling is constructed of the same type of "+
    "dark grey brick the rest of the place is made of. It is "+
    "unadorned, however. It is low where you are standing right "+
    "now, but vaults up high to the north.\n");
    add_item("floor","The cold stone floor is covered with debris "+
    "from the walls, as well as old moss.\n");
    add_item("statue","It looks like robed creature of some sort. "+
    "perhaps if you got closer you could see more details.\n");
    
    add_prop(ROOM_I_LIGHT,0);
    add_exit(KHIRAA_DIR(temple/rooms/t4),"north",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t3),"east",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t1),"west",0,-1);
}

string
query_k_rune()
{
    if(IS_DK(TP) || IS_LP(TP))
        return "They are praises to the Nameless One. He who is "+
        "without mortal name, and who's evil is unspeakable.\n";
    return "The runes and symbols on the walls and archway are "+
    "unknown to you.\n";
}


