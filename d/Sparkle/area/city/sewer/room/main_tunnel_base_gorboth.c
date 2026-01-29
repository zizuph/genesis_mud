/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel_base.c
 *
 *  This will be the base file for every sewer tunnel room
 *
 *  Aeg
 */
#pragma strict_types

#include "defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

inherit SPARKLE_ROOM_BASE;

/* Global Variables */
public string    Long_Extra = ""; /* optional tag for long descriptions */


/* Prototypes */
nomask void        create_sparkle();
public void        create_tunnel_room();

public void        set_long_extra(string s) { Long_Extra = s; }


/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sparkle()
{
    string  long_desc;

    long_desc = "This is a sewer room. Thus, we create a generic"
              + " and rather short description to indicate such. ";

    set_short("Lower main tunnel");
           
    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Call the base creation function for sewers
    create_tunnel_room();

    /* The child room will set the value of Long_Extra for us, so now
     * it is safe to make our long description call.
     */
    set_long(long_desc + Long_Extra + "\n\n");

    // Add the try_items after create_sewer_room so that it will not
    // replace the items added by subclasses
    // Room Item Section  
                                
    try_item( ({ "environment", "area", "sewer", "room", "tunnel", 
                 "subterranean environment", "scene"} ),
             "A tunnel extends upward and downward with classic "
           + "architecture. The walls and ceiling are crafted "
           + "with a post and lintel style and are "
           + "in imperfect shape. The floor is made of stone and is "
           + "covered with downward flowing sewage.\n");
    
    try_item( ({ "upward", "downward" }),
             "The tunnel extends and allows the sewage to flow "
           + "from the higher level to the lower level. Looking "
           + "far into each direction yields only darkness.\n");

    try_item( ({ "darkness", "cracks", "crevices" }),
             "Yes. Darkness, utter darkness.\n");
         
    try_item( ({ "post", "post and lintel", "architecture", 
                 "walls", "posts" }),
             "The tunnel is made of stone posts, or blocks of solid rock, "
           + "that are held in place by a heavy capstone, or lintel. The "
           + "weight of the lintel keeps the stone walls in place and "
           + "you safe. If the lintel cracks and lightens, the posts will "
           + "likely cave in and crush you.\n");
           
    try_item( ({ "stone", "stones", "blocks", "block" }),
             "These stones are solid looking and cold to the touch.\n");

    try_item( ({ "ceiling", "lintel", "capstone" }),
             "The lintel, or capstone, forms the solid stone ceiling. It must "
           + "be solid, or the walls would cave into the tunnel. For your "
           + "sake, the lintel appears to be in decent shape.\n");

    try_item( ({ "floor", "water", "sewage", "poo", "pee", "current", "ground" }),
             "Ah, sewage; the undeniable proof of living beings. Any city, "
           + "nay dwelling, produces a certain amount of waste. This waste, "
           + "in which you currently walk, is the excrement of the city of "
           + "Sparkle. Being an odd cross between dark green and brown, the "
           + "sewage is surprisingly water-like in flow. The smell is "
           + "malodourous and the taste... well... try for yourself. "
           + "Furry looking algae and other subterranean plantlife cling "
           + "to the moist and submerged stones. An adapted beast of a fish, "
           + "or worse, might lurk in the current.\n");

    try_item( ({ "alga", "algae", "plantlife", "plant", "plants", }),
            "Subterranean plants eek out an existence in this environment.\n");
 
                              
} // create_sparkle

/*
 * Function name:        create_sewer_room
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_tunnel_room()
{
    
} // create_sewer_room
