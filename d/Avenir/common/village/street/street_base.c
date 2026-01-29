// file name:    /d/Avenir/common/village/street/street_base.c
// creator(s):   Lilith, Oct 98
// revisions:    Lilith Nov 2021/
// purpose:          
// note:         This file is to be inherited in all village streets.  
//               The more frequent add_items should be placed here.
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */


/* Prototypes */
/* These are the add_items and add_cmd_items for 
 * (see below)
 */
void add_air();
void add_cobbles();
void add_grass();
void add_hedge();
void add_moss();
void add_source();

/*
 * Function name: create_street_room
 * Description:   This function should be called to create streets.
 */
void create_street_room()
{
}

/*
 * Function name: reset_street_room
 * Description:   This function should be called to reset street rooms.
 */
void reset_street_room()
{
    reset_domain_room();
}

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
public void
create_domain_room()
{
//    set_area("vstreet_p");
    set_tell_time (150);

    /* Tells made to player when a room is occupied */
    add_tell("A puff of wind carries to you the scent of crushed herbs.\n");
    add_tell("Cobblestones echo hollowly as someone passes nearby.\n");
    add_tell("You hear the muted sound of voices from beyond the hedge.\n");
    add_tell("A cool breeze ruffles your hair.\n");

    /* If an add_item will be in every room, add it here */
    add_air();
    add_cobbles();
    add_hedge();
    add_source();
    
    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;

    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    add_prop(ROOM_I_HIDE, 0);

    create_street_room();
    reset_street_room();
}

/* These are the add_items and add_cmd_items for the village streets.
 * (Those used more than once in the area). If you want to add some
 * scultpures or ornamental bushes, inherit outside_decor.c
 */
void
add_air()
{
    /* Default in every room */
    add_cmd_item("air", "smell", "The warm air is perfumed with a "+
        "variety of scents, all of them pleasant.\n");
}

void
add_cobbles()
{
    /* Default in every room */
    add_item(({"cobbles", "cobblestones", "cobblestone", "road", 
        "street", "path"}),
        "These are rounded cobblestones made of white granite. "+
        "The flecks of feldspar and quartz in the unfinished "+
        "surfaces of the cobbles sparkle in the light of the "+
        "Source.\n");
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
    /* Default in every room */
    add_item(({"hedge","hedges","bush","bushes","ribbon"}),
        "The hedges serve both as ornamentation and barriers. "+
        "They are composed of bushes with delicate, variegated "+
        "leaves, grown closely together and to an impressive "+
        "height. These hedges have been groomed with such "+
        "precision as to present a flawless, flowing ribbon of "+
        "green that is very pleasing to the eye.\n");
    add_item(({"leaves","small leaves"}),
        "The tiny green leaves form a living carpet on the "+
        "branches of the hedgerows.\n");

}

void
add_moss()
{
    add_item(({"moss", "seams"}),
        "Spongy and green moss grows in the seams of the cobbles, "+
        "making a lovely contrast against the white stone.\n");        
}

void 
add_source()
{
    /* Default in every room */
    add_item(({"source", "Source", "light", "illumination"}),
        "The yellow-white glow emanates from the ceiling of "+
        "this great cavern.\n");
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
