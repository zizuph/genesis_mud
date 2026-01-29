// file name:   /d/Avenir/common/village/garth_base.c
// creator(s):  Lilith, Oct '96
// revisions: 
// purpose:     Pocket gardens and rest areas in the village.
//                   Garth (n.) : an open courtyard enclosed by a 
//                   cloister; a small yard or garden.
// note:       Inherit in all 'green' areas where herbs and such
//             would be found, ie gardens, arbors, bowers. The more  
//             common add_items should be added here.
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"
#include "/d/Avenir/include/defs.h"            /* Short-hand macros */
#include "/d/Avenir/include/paths.h"           /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */
#include "/sys/stdproperties.h"                /* self-explanatory */

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"

/* Depending on the type of garth, we'll have different herbs */
public string *cv = HERB_MASTER->query_herbs( ({"cave", "desert"}) );
public string *ju = HERB_MASTER->query_herbs( ({"jungle"}) );
public string *st = HERB_MASTER->query_herbs( ({"stream"}) );
public string *ma = HERB_MASTER->query_herbs( ({"marsh"}) );

/* Prototypes */
/* These are the most common add_items and add_cmd_items for 
 * the garth rooms (see below)
 */
void add_air();
void add_cobbles();
void add_fern();
void add_grass();
void add_hedge();
void add_moss();
void add_pool();
void add_spring();
void add_source();
void add_step_stones();

/*
 * Function name: create_garth_room
 * Description:   Used for creating garth rooms.
 */
void create_garth_room()
{
}

/*
 * Function name: reset_garth_room
 * Description:   Called to reset garth rooms.
 */
void reset_garth_room()
{
    set_searched(0);
    reset_domain_room();
}

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
public void
create_domain_room()
{
//    set_area("garthp");
    set_tell_time (200);

    /* Tells made to player when a room is occupied */
    add_tell("A sense of peace envelopes you.\n");
    add_tell("It is so quiet, you think you can hear the plants growing.\n");
    add_tell("The faintest hint of a breeze brushes your skin.\n");
    add_tell("The hedges seem to glow with inner light as the Source "+
        "flares above.\n");

    /* If an add_item will be in every room, add it here */
    add_air();
    add_hedge();
    add_source();
    
    /* There is light in this area (see ~Avenir/include/defs.h 
     * for this define and the one following) */
    LIGHT;
    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    add_prop(ROOM_I_HIDE, 0);

/* Put these in the individual garth rooms, I think.
    set_up_herbs(({ ONEOF(cv), ONEOF(cv), ONEOF(cv) }), 
        ({ "rock", "cliff", "litter", "lichen", "wall", "stone" }), 5);
    set_up_herbs(({ ONEOF(ju), ONEOF(ju), ONEOF(ju) }), 
        ({ "tree", "vines", "trees", "moss", "ferns", "plants",
           "bushes", "vegetation"}), 5);
    set_up_herbs(({ GET_ONE(st), GET_ONE(st), GET_ONE(st) }), 
        ({ "stream", "shore", "grass", "greenery" }), 5);    
    set_up_herbs(({ GET_ONE(ma), GET_ONE(ma), GET_ONE(ma) }), 
        ({ "marsh", "mat", "sphagnum" }), 5);    
*/
    create_garth_room();
    reset_garth_room();
}

/* These are the add_items and add_cmd_items for the garth rooms 
 * (Those used more than once in the area)
 */
void
add_air()
{
    add_cmd_item("air", "smell", "The air is cool and smells of green, "+
        "growing things.\n");
}

void 
add_fern()
{
    add_item(({"fern", "ferns", "maidenhair"}),
        "The delicate maidenhair ferns proliferate in the moist, "+
        "rich soil here. Their fronds tremble in the fingers of "+
        "a breeze like a maiden on her wedding night.\n");
}

void
add_cobbles()
{
    add_item(({"cobbles", "cobblestones", "cobblestone"}),
        "Here, the rounded, white granite cobbles are partially "+
        "grown-over with moss and spongy ground-cover, lending "+
        "this space a feeling of privacy and isolation.\n");
}

void
add_grass()
{
    add_item(({"grass", "lawn"}),
        "The grass has the vibrant green of new growth. It "+
        "is thick, close-cropped, and looks invitingly cool.\n");
}

void
add_hedge()
{
    add_item(({"hedge","hedges","bush","bushes"}),
        "The hedges, with their delicate, variegated leaves, have "+
        "been permitted to grow higher here, lending a sense of "+
        "isolation and privacy to this small space.\n");
}

void
add_moss()
{
    add_item(({"moss"}),
        "Spongy green moss grows in the spaces between the cobbles "+
        "and in the spots where poor soil prevents other plants from "+
        "taking hold.\n");        
}

void 
add_pool()
{
    add_item(({"pool", "pool of water", "water"}),
        "This pool of water is so small as to be little more than "+
        "a puddle. It is fed by a small spring that trickles music"+
        "ally over a pile of stones.\n");
    add_item(({"pile of stones"}),
        "It is a pile of pale stones composed chiefly of mica and "+
        "quartz. Moss grows on some of the surfaces, softening the "+
        "the glitter of the stones. You can hear the faintest "+
        "whisper of sound as water trickles through them.\n");
}

void
add_spring()
{
    add_item(({"spring", "water"}),
        "Water wells up from a tiny spring of crystal-clear water "+
        "that trickles off into the hedges enclosing this place.\n");
}

void 
add_source()
{
    add_item(({"source", "Source", "light", "illumination"}),
        "The yellow-white glow emanates from the ceiling of "+
        "this great cavern.\n");
}

void
add_step_stones()
{
    add_item(({"step stones", "stepping stones", "stepping stone"}),
        "There are stepping stones leading through this enclosure, "+
        "back toward the cobbled streets of the village. They are "+
        "composed of dark, volcanic stone, probably basalt, worn "+
        "smooth over the years by the passage of many feet.\n");
}


/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
