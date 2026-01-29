// file name:    /d/Avenir/common/village/temple_base.c
// creator(s):   Lilith, Hannah April, 2002
// revisions: 
// purpose:          
// note:         This file is to be inherited in all temple rooms.  
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
#include "/d/Avenir/include/defs.h"            /* Short-hand macros */
#include "/d/Avenir/include/paths.h"           /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */
#include "/sys/macros.h"                       /* macros like VBFC and QNAME */
#include "/sys/stdproperties.h"                /* self-explanatory */


/* Prototypes */
/* These are the add_items and add_cmd_items for 
 * (see below)
 */

void add_source();
void add_crystals();
void add_ground_floor();
void add_gallery();
void add_vault();

/*
 * Function name: create_temple_room
 * Description:   This function should be called to create streets.
 */
void create_temple_room()
{
}

/*
 * Function name: reset_street_room
 * Description:   This function should be called to reset street rooms.
 */
void reset_temple_room()
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
//  set_area("temple_pale_p");
    set_tell_time (150);

    /* Tells made to player when a room is occupied */
 
    add_tell("A cool breeze ruffles your hair.\n");

    /* If an add_item will be in every room, add it here */

   add_source();

    
    /* There is light in this area (see ~Avenir/common/common.h 
     * for this define and the one following) */
    LIGHT;

    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN;

    add_prop(ROOM_I_HIDE, 0);

    create_temple_room();
    reset_temple_room();
}

/* These are the add_items and add_cmd_items for the temple pale.
 * (Those used more than once in the area). If you want to add some
 * scultpures or ornamental bushes, inherit outside_decor.c
 */

void 
add_source()
{
    /* Default in every room */
    add_item(({"source", "Source", "light", "illumination"}),
        "The muted, yellow-white glow of the Source permeates "+
        "the air.\n");
}

void 
add_crystals()
{
    add_item(({ "crystals" }),
        "These crystals have a metallic luster at first "+
        "glance, then as the light shifts, they sparkle with "+
        "an iridescence that ranges from a deep blue to "+
        "purple and black.\n");
}

void
add_ground_floor()
{

    add_item(({ "floor", "floors", "ground" }),
        "The floor is made of large even flagstones cut from the "+
        "same quarry as the pale granite of the walls.  It has "+
        "been worn smooth by the passage of time.\n");
}

void 
add_gallery()
{
    add_ground_floor();
    add_crystals();

    add_item(({ "archway", "archways" }),
        "Which archway do you wish to examine?\n");

    add_item(({"lintel", "lintels" }),
        "There are three lintels, one over each archway.\n");

    add_item(({ "symbol", "symbols" }),
        "There are several symbols depicted here. Which one "+
        "did you wish to examine?\n");

    add_item(({ "screen", "north screen", "metal screen", "filigree",
        "filigree screen" }),
        "This screen made of precious copper has a light green "+
        "patina from the sea air. The intricate metalwork wrought "+
        "by the hand of a Master depicts small vine shoots and "+
        "tiny leaves that seem to sway in the lamplight. Looking "+
        "through it you can see a gravelled walk.\n");

    add_item(({ "gravelled walk", "walk", "walkway", "gravel" }),
        "You see a gravelled walk through the screen.\n");

    add_item(({ "ceiling" }),
        "The broad barrel vault ceiling of the gallery is "+
        "supported at regular intervals by rounded arches.\n");

    add_item(({ "arches", "arch" }),
        "These rounded arches comprise the ceiling of the "+
        "gallery, forming a long barrel-shaped vault.\n");

    add_item(({ "lamp", "lamps", "flickering lamp" }),
        "The lamp is of unusual design and beauty. It is made of "+
        "tin with twelve pieces of mirror used as reflectors. "+
        "The light of its single candle is empowered twelve " +
        "times, eliminating the need of additional lamps or "+
        "torches. It is mounted high on the wall.\n");
}

void 
add_vault()
{
    
     add_ground_floor();


     add_item(({"arch", "arches" }),
         "Underneath each arch is a stone carved with a "+
         "figure of a man who appears to be holding the weight " +
         "of the arch on his back, his body and face are twisted " +
         "as if in pain. They start here and curve upwards towards " +
         "the center of the vault forming a large open dome.\n");

     add_item(({"dome" }),
         "The dome is made up of several arches that start here and "+
         "and continue above the center of the vault. The Source pulsates "+
         "as it passes through the dome, reflecting off the pale stone "+
         "of the arches.\n");

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
