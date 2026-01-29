/*
 *  temple7.c
 *
 *  This is a room for the druid temple in Mithas.
 *
 *  Created by Carnak, January 2016
 */
#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_IN;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#include "./local.h"


public int     pass_tapestry(string str);

create_mithas_room()
{
    set_short("Sleeping quarters");
    set_long("@@long_desc");
	
    add_exit(TDIR +"temple4", "south", &pass_tapestry("south"));
    
    add_item(({"floor","ground","weeds","grass","rocks"}),
    "The floor is tiled with smooth rocks and covered in dirt, some "+
    "grass and weeds have emerged from beneath the granite rocks.\n");
    
    add_item(({"ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");
	
    add_item(({"stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");
	
    add_item(({"walls","roots","wall","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability.\n");
	
    add_item(({"roof","ceiling"}),
    "The wooden roof appears to be in good condition, someone "+
    "must have maintained it well.\n");
	
    add_item(({"hallway"}),
    "The hallway extends southwards through an arched doorway.\n");
	
    add_item(({"decorations","decor","furniture"}),
    "The furniture, like in the rest of the temple, is plain. A "+
    "large wooden wardrobe and four sets of bunk beds are all "+
    "that decorates the sleeping quarters.\n");
	
    add_item(({"wardrobe"}),
    "The wardrobe is of simple make, due to the appealing grain "+
    "markings you believe the wood to be oak.\n");
	
    add_item(({"bunk beds","beds"}),
    "There are eight beds in the form of bunk beds in this room, "+
    "however only one is free of dust. The beds are extremely "+
    "hard, as if it is only a blanket on a wooden frame.\n");
	
    add_item(({"bunk bed","bed","dust free bed","dust free bunk bed"}),
    "It appears that someone has slept in this bed more recently "+
    "than the rest of beds in this room, the absence of dust is "+
    "what lead you to this conclusion.\n");
	
    add_item(({"doorway","arched doorway","arch"}),
    "This is a stone doorway in the form of an arch, it leads "+
    "south.\n");
	
    add_cmd_item(({"wardrobe","wooden wardrobe","door"}),"open",
    "@@open_wardrobe");
	
    add_cmd_item(({"on bed","bed","in bed"}),({"sleep","rest","lie"}),
    "@@sleep_bed");
	 
}

string
long_desc()
{
    return ""+ 
    "This is the innermost part of the temple, it has been "+
    "furnished with four sets of bunk beds, and a large "+
    "wardrobe. " + sleep_desc();
}

int
pass_tapestry(string str)
{
    write("You step through the arched doorway, into the temple "+
    "study.\n");
    say(QCTNAME(TP) + " steps through the arched doorway, towards "+
    "the temple study.\n");
    return 0;
}

int
open_wardrobe()
{
    write("You open the door to the wooden wardrobe, but find "+
    "little of interest. The interior is as plain as its exterior, "+
    "and a few sets of grey robes hang inside, covered in dust. "+
    "You close the wardrobe door.\n");
    say(QCTNAME(TP) + " takes a look inside the wardrobe.\n");
    return 1;
}

int
sleep_bed()
{
    write("You consider resting on the dust free bed, but decide "+
    "against it.\n");
    say(QCTNAME(TP) + " glances towards the dustfree bed with "+
    "a contemplating expression.\n");
    return 1;
}