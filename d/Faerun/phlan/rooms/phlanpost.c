/*  /d/Faerun/phlan/rooms/phlanpost.c
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
inherit "/d/Genesis/lib/post";

/*
*   Check to see if player is on quest
*/

int
check_quest()
{
    if(this_player()->query_prop("_phlan_tour2_start"))
    {
        this_player()->remove_prop("_phlan_tour2_start");
        this_player()->catch_msg("You are ready to return to Daari for your reward.\n");
        this_player()->add_prop("_phlan_tour2_prop", 1);        
        return 0;
    }
} 

void
create_phlan_room()
{
    set_long("Phlan post office.\n"
        +"This the the city post office. It is small, simple and efficient,"
        +" just the way the mail delivery system prefers. There are several"
        +" small booths just large enough for one person were mail can be"
        +" composed privately. Young runners and delivery boys frequently"
        +" dash out the door with posts and parcels. Lighting is provided"
        +" in each individual booth with a larger lamp suspended from the"
        +" ceiling beams.\n");
    
    set_short("Phlan post office");    
        
    add_item(({"walls", "wall"}),
        "The walls are rough cut cedar. They give off an aromatic scent that"
        +" is supposed to keep away moths, thus protecting paper and"
        +" parchment from insect damage.\n");

    add_item(({"beam", "beams"}),
        "Large cedar beams support the peaked ceiling. A large brass"
        +" lamp spreads its light over the whole room.\n");

    add_item(({"floor", "ground"}),
        "The floor is plain unadorned wood. It is clean but not polished."
        +" There are various ink stains from accidental spills. This is"
        +" probably why they are not polished or carpeted.\n");

    add_item(({"ink", "stain", "stains", "ink stains"}),
        "Black ink forms patterns here and there were an occasional"
        +" quill has been dropped or inkpot spilled. One of them looks"
        +" kind of like a pretty girl. Another seems to be a juicy"
        +" steak. You wonder if that means anything.\n");

    add_item(({"booth", "booths"}),
        "Small booths large enough for one person provide a writing surface"
        +" pen, inkpot, paper and envelopes for composing private"
        +" missives. Each has a small candle that can be lit from"
        +" the main lamp to provide additional light.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same material as the walls. It seems"
        +" to be cleaned regularly as there are no cobwebs or dust."
        +" Large beams give it support.\n");

    add_item(({"lamp"}),
        "A single large brass lamp with an open flame provides overall"
        +" lighting for the room. Individual candles from the writing"
        +" booths can be lit from this torch.\n");

    add_item(({"candle", "candles"}),
        "Thick slow-burning candles are placed in each booth to provide"
        +" additional light if needed.\n");
        
    add_item(({"pen", "pens"}),
        "Brass tipped broad pens perfect for writing letters.\n");

    add_item(({"inkpot", "inkpots"}),
        "Small pots of ink are available for writing notes.\n");
        
    add_item(({"paper", "parchment"}),
        "Sheets of parchment or paper are available for your writing needs"
        +" depending on preference.\n");         

    add_item(({"envelope", "envelopes"}),
        "Large paper envelopes that can be sealed with wax from the"
        +" candles.\n");

    add_item(({"runner", "runners", "boy", "boys"}),
        "Young children ten to twelve years old are busy taking mail to"
        +" various parts of town and beyond.\n");

    add_item(({"door", "doors"}),
        "The door stands to the south and will take you back to the street.\n"); 

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road16", "south");

}


void
init()
{
    ::init();
    post_init();
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}


void
reset_faerun_room()
{
    set_searched(0);
}