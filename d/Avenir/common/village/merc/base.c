// file name:	/d/Avenir/common/village/merc/base.c
// creator(s):	Lilith, Lucius
// revisions: 	Lucius Oct 2008
// purpose:          
// note:         This file is to be inherited in all merc streets.  
//               The more frequent add_items should be placed here.
// bug(s):           
// to-do:            
#pragma strict_types

/* Inherit the standard room object */
inherit "/std/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "../village.h"


/* Prototypes */
/* These are the add_items and add_cmd_items for 
 * (see below)
 */
static void add_cobbles(void);
static void add_source(void);
static void add_hedge(void);
static void add_fence(void);
static void add_fount(void);
static void add_merch(void);
static void add_berm(void);

/*
 * Function name: create_street_room
 * Description:   This function should be called to create streets.
 */
static void
create_merc_room(void)	{ }

/*
 * Function name: reset_street_room
 * Description:   This function should be called to reset street rooms.
 */
static void
reset_merc_room(void)	{ reset_room(); }

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
private nomask void
create_room(void)
{
    setuid();
    seteuid(getuid());

    set_tell_time(200);

    /* Tells made to player when a room is occupied */
    add_tell("A puff of wind carries to you the sounds of the bazaar.");
    add_tell("A piece of brightly coloured fabric catches in the breeze.");
    add_tell("A cacophany of scents and sounds floods your senses.");
    add_tell("The crunch of cobbles can be heard underfoot as "+
	"shoppers mill and move about.");
    add_tell("The voice of a distant hawker arrives on a snatch of wind.");

    /* If an add_item will be in every room, add it here */
    add_cobbles();
    add_source();
    add_merch();
    add_fence();
    add_fount();
    add_berm();
    
    add_item(({"air", "wind", "breeze", "scent", "scents"}),
	"You cannot see it, but perhaps you could use your sense of smell.\n");

    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;

    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    add_prop(ROOM_I_HIDE, 0);

    create_merc_room();
}

public void
hook_smelled(string str)
{
    switch(str)
    {
    case "scent": case "scents":
    case "flower": case "flowers":
    case "air": case "wind": case "breeze":
	write("The warm air is perfumed with a variety of scents, "+
	    "all of them pleasant.\n");
	break;
    }
}

/* These are the add_items and add_cmd_items for the village merchs.
 * (Those used more than once in the area). If you want to add some
 * scultpures or ornamental bushes, inherit outside_decor.c
 */
static void
add_cobbles(void)
{
    /* Default in every room */
    add_item(({"cobbles", "cobblestones", "cobblestone"}),
        "These are rounded cobblestones made of yellow quartz. "+
        "The flecks of feldspar and other minerals in the unfinished "+
        "surfaces of the cobbles sparkle in the light of the "+
        "Source.\n");
}

static void 
add_source(void)
{
    /* Default in every room */
    add_item(({"source", "light", "illumination"}),
        "The yellow-white glow emanates from the ceiling of "+
        "this great cavern.\n");
}

static void
add_hedge(void)
{
    add_item(({"hedge","hedges","bush","bushes","ribbon"}),
	"The hedges serve both as ornamentation and barriers. "+
	"They are composed of bushes with delicate, variegated "+
	"leaves, grown closely together and to an impressive "+
	"height. These hedges have been groomed with such "+
	"precision as to present a flawless, flowing ribbon of "+
	"green that is very pleasing to the eye.\n");
}

static void
add_fence(void)
{
    add_item(({"fence", "stone fence", "wall", "stone wall" }),
        "It is made from stone excavated when the ground was leveled. "+
        "It rises to shoulder-height on a tall elf, and forms a "+
        "horseshoe around the garment district, with its opening "+
	"facing to the north where it buts against hedgerows "+
	"leading up to the bazaar.\n");
}

static void
add_fount(void)
{
    add_item(({"fountain", "copper fountain", "clepsydra"}),
	"At the center of the garment district, a large, copper "+
	"clepsydra stands tall. Its time telling waterworks doubles "+
	"as a communal fountain for the denizens of this market.\n");
}

static void
add_berm(void)
{
    add_item(({"berm","mound","causeway","earthworks","embankment"}),
	"This berm is a formed mound of stone and dirt, a type of "+
	"earthworks. It is similar to a causeway or embankment in "+
	"this case wherein it prevents the depressed bowl of the "+
	"garment district from being flooded. Also in that it has "+
	"a cobbled pathway running over its surface.\n");
}

static void
add_merch(void)
{
    add_item(({"market", "merchant", "merchants", "shop", "shops",
	"people", "patron", "patrons", "stall", "stalls" }),
	"All along the top of the berm can be seen and heard the "+
	"merchant stalls and their hawking garment sellers. Determined "+
	"patrons stride through the milling throngs of the casual shopper "+
	"and voyeuristic seeker. Cries and conversation blend with the "+
	"sounds of crunching foot traffic to fill the market with life.\n");
}

static void 
add_fabric(void)
{
    add_item(({"fabric", "fabrics", "material", "materials", "cloth"}),
        "Fabrics in a wide range of colours flutter in the breeze.\n");
}


/* Start the room tells as soon as someone enters the room */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}
