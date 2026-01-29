/* /d/Raumdor/common/temple/lair1.c 
*
*Lair of the Khiraa 
*
*
* Refurbishing the original khiraa lair2
*
* Nerull 2020
*
*/
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;


string
query_k_rune()
{
    /*if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless One. All hail to "+
        "His might. Lord of the Damned Grave.\n";*/
    return "The runes and symbols that cover the "+
    "walls and archway are unknown to you.\n";
}


void
create_room()
{
    ::create_room();
	
	add_prop(ROOM_I_LIGHT,0);
	
    set_short("A stairwell within the Temple of the Khiraa");
	
    set_long("\n   You are standing at the base of a stone stairwell. "+
    "Intricatly carved walls encase you on your east and south sides. "+
    "An open archway leads to the northwest into what looks like a "+
    "large foyer. To the west, the semi-hallway you are in leads "+
    "to another set of stairs.\n"+ 
    "   Strange looking runes and symbols "+
    "adorn the top of the archway going northwest. The air has an "+
    "earthen smell to it, as well as a slight stench of death and "+
    "decay. Clumps of moss reside along the cracks in the walls "+
    "and ground. The ceiling above you is low, but, going past the "+
    "archway, it suddenly vaults up. You can see a strange looking "+
    "statue in the foyer to the northwest.\n\n");
	
	add_item("walls","The walls are made of dark grey stone, and "+
    "look very old. There are some cracks forming on them, as well "+
    "as clumps of wet moss. Along many of them, you see what appear "+
    "to be ancient runes and symbols of some sort.\n");
	
    add_item("stairwell","The stairwell that leads up to the top "+
    "levels of the temple. It is made of the same dark grey "+
    "stone that the walls are made of.\n");
	
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
    "now, but vaults up high to the northwest.\n");
	
    add_item("floor","The cold stone floor is covered with debris "+
    "from the walls, as well as old moss.\n");
	
    add_item("statue","It looks like robed creature of some sort. "+
    "perhaps if you got closer you could see more details.\n");
		
    add_exit(TEMPLE_DIR + "lair2", "west", 0);
	add_exit(TEMPLE_DIR + "lair4", "northwest", 0);
	add_exit(TEMPLE_DIR + "temple04", "up", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}

