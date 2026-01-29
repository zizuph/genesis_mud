/*  /d/Faerun/phlan/rooms/church2.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;

/*
*   Checking to see if the player is purified in order to go to the next
*   floor.
*/

int
check_purified()
{
    if(this_player()->query_prop("_purified_by_water"))        
    {  
        return 0;
    }   
    write("You have not purified yourself!\n");
    return 1;
}

/*
*   Remove purification upon leaving room.
*/

int
remove_purified()
{
    if(this_player()->query_prop("_purified_by_water"))
    {
        this_player()->remove_prop("_purified_by_water");
        this_player()->catch_msg("You feel your purification dissipate.\n"); 
        return 0;
    }
}    

/*
*   Making the basic room
*/

void
create_phlan_room()
{
    set_long("Church of Tyr purification room.\n"
        +"This is the purification room of the Church of Tyr The Even-Handed."
        +" It is circular with a diameter of approximately ten feet."
        +" Warm soft light is shed from glowing orbs floating near the ceiling"
        +" that are emitting peaceful music. The circular walls are draped"
        +" with turquoise blue wallhangings between the four windows at the"
        +" cardinal points of the compass. A font of holy water sits in the "
        +" middle of the room and a spiral staircase leads down to the first"
        +" floor or up to the third floor.\n");
    
    set_short("Purification room");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are made of a translucent lazulite, darkening with depth"
        +" to the point you cannot see what comprises the outer walls."
        +" Between the four windows hang beautiful turquoise blue wallhangings.\n");

    add_item(({"hangings", "wallhangings"}),
        "The wallhangings of gauzy turquoise blue are suspended from the ceiling"
        +" to the floor. Strangely you do not see anything supporting them.\n");

    add_item(({"floor", "ground"}),
        "The floor is covered in a thick blue carpet that stretches"
        +" from wall to wall.\n");

    add_item(({"carpet"}),
        "This carpet extends from wall to wall. It is soft enough to muffle"
        +" footsteps. It is the same turquoise blue as the wallhangings.\n");

    add_item(({"ceiling"}),
        "The ceiling, like the walls, is made of translucent lazulite. It"
        +" deepens and darkens as if looking into a deep pool.\n");

    add_item(({"orb", "orbs"}),
        "Transparent orbs of crystal shed a soft, warm, magical light.\n");

    add_item(({"font"}),
        "This font, approximately three feet high and eighteen inches in"
        +" diameter is fashioned from a single azurite. It is filled"
        +" to two inches below the rim with holy water.\n");
        
    add_item(({"water", "holy water"}),
        "The surface of the holy water in the azurite font is perfectly"
        +" still, reflecting the magical light from the orbs. It seems"
        +" to be here for people to purify themselves before ascending"
        +" to the higher levels of the temple.\n");

    add_item(({"windows"}),
        "There are four windows, north, south, east and west. Which do"
        +" you want to view?\n");

        
    add_item(({"north window"}),
        "Looking out the north window you see "
        +" the Stojanow River, the mansions beyond and the Quivering Forest"
        +" far off in the distance.\n"
        +"  \n"
        +" __________________________________\n"
        +" |   ^      ^              ^       |\n"
        +" |  ^|^    ^|^     ^      ^|^      |\n"
        +" |   |      |     ^|^     ^|^      |\n"
        +" |               ^^|^^     |       |\n"
        +" |                                 |\n"
        +" |                                 |\n"
        +" |----             ___             |\n"
        +" |   /|           /  /|-           |\n"
        +" |--  |         /|  |/ /|       ~~~|\n"
        +" |  |/         =======  |      ~~~~|\n"
        +" |--          |      | /      ~~~~~|\n"
        +" |            |      |/      ~~~~~~|\n"
        +" |~~~~~~~~~   -------       ~~~~~~ |\n"
        +" |~~~~~~~~~~               ~~~~~   |\n"
        +" |~~~~~~~~~~~~~~~~~~~~~~~~~~~~     |\n"
        +" |_________________________________|\n");  
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"mansion", "mansions"}),
        "The mansions of Phlan have been rebuilt over the years from their"
        +" sad state of disrepair a century ago.\n");

    add_item(({"forest", "quivering forest"}),
        "The Quivering Forest, far off to the north, is a verdant green"
        +" sea of trees stretching to the horizon.\n");       

    add_item(({"south window"}),
        "Looking out the south window you see Sokol Keep standing on its "
        +" small rocky island.\n"
        +" \n"
        +" _________________________________ \n"
        +" |                      / /|~~~~~~|\n"
        +" |_   __   __   __   __/ / |*~~~~~|\n"
        +" | |_|  |_|  |_|  |_|  |/  |**~~~~|\n"
        +" |                     |   |***~~~|\n"
        +" |                     |   |****~~|\n"
        +" |      ____           |  /****~~~|\n"
        +" |      |##|           | /****~~~~|\n"
        +" |      |##|           |/****~~~~~|\n"
        +" |=====================*****~~~~~~|\n"
        +" |************************~~~~~~~~|\n"
        +" |**********************~~~~~~~~~~|\n"
        +" |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
        +" |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
        +" |________________________________|\n");  
        
    add_item(({"keep", "sokol keep"}),
        "Sokol Keep is a small fortification on a rocky island, Thorn Island,"
        +" just south of the city.\n");

    add_item(({"island", "rocky island", "thorn island"}),
        "Thorn Island is a small rocky island south of the city. A defensive"
        +" fortification is built on it to guard seaward access to the city.\n");          

    add_item(({"west window"}),
        "looking out the west window you see the inland parts of Phlan. In"
        +" the distance you see the Cadorna textile mill, Kuto's Well,"
        +" and far to the west, the Valhingen graveyard.\n");  

    add_item(({"mill", "textile mill"}),
        "The Cadorna textile mill is the largest in Phlan. That is why the"
        +" family is so prominent.\n");

    add_item(({"well", "kuto's well"}),
        "Kuto's Well used to house dangerous humanoids, but is now one of"
        +" focal points of Phlan.\n");

    add_item(({"graveyard", "valhingen graveyard"}),
        "The Valhingen graveyard is hundreds of years old and massive."
        +" A century ago a vampire took up residence there and terrorized"
        +" the town.\n");          
        
    add_item(({"east window"}),
        "Looking out the east window you see the harbour and the Moonsea"
        +" beyond.\n"); 

    add_item(({"harbour", "harbor"}),
        "The harbour cuts into the land in a deep calm anchorage that led"
        +" to the formation of the town.\n");

    add_item(({"sea", "moonsea"}),
        "The Moonsea stretches as far to the eastern horizon as you can see."
        +" Its deep blue depths reflect the sky above while whitecaps top"
        +" the rolling waves.\n");        

    add_item(({"staircase", "spiral staircase"}),
        "A simple wrought iron staircase a descending counter-clockwise"
        +" twist. This would make it difficult for ascending attackers to"
        +" effectively use a weapon.\n"); 

/*
*   Sound effects
*/

    add_room_tell("The peaceful music is relaxing and turns your thoughts from the"
        +" trivialities of the day to those more introspective. It suits"
        +" this place of purification."); 
    add_room_tell("The wallhangings ruffle slightly as a light breeze comes"
        +" in from the east window.");     

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "church1", "down", remove_purified); 
    add_exit(ROOM_DIR + "church3", "up", check_purified);
}


void
reset_faerun_room()
{
    set_searched(0);
}


/*
*   Getting the purification tag.
*/
 
int action_purify(string str)
{
    if(this_player()->query_prop("_purified_by_water"))
    {
        write("You have not left the purity of the church.\n");
        return 1;
    }

    if(str == "in water" | str == "in the water"
    | str == "in holy water" | str == "in the holy water"
    | str == "with water" | str == "with the water"
    | str == "with holy water" | str == "with the holy water"
    | str == "in font" | str == "in the font"
    | str == "in azurite font" | str == "in the azurite font"
    | str == "me in water" | str == "me in the water"
    | str == "me in holy water" | str == "me in the holy water"
    | str == "me with water" | str == "me with the water"
    | str == "me with holy water" | str == "me with the holy water"
    | str == "me in font" | str == "me in the font"
    | str == "me in azurite font" | str == "me in the azurite font"
    | str == "myself in water" | str == "myself in the water"
    | str == "myself in holy water" | str == "myself in the holy water"
    | str == "myself with water" | str == "myself with the water"
    | str == "myself with holy water" | str == "myself with the holy water"
    | str == "myself in font" | str == "myself in the font"
    | str == "myself in azurite font" | str == "myself in the azurite font")
    
    {
        this_player()->catch_msg("You purify yourself with the holy water.\n");
        say(QCTNAME(this_player()) + " purifies themself with the holy water.\n");
        this_player()->add_prop("_purified_by_water", 1);
        return 1;
    }
}

void init()
{
    ::init();
    add_action("action_purify", "purify");
}



