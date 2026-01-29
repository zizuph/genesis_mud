/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel_base.c
 *
 *  This will be the base file for every sewer tunnel room in Gont.
 *  Originally coded for Sparkle sewers, moved to Gont. 2021, Aeg
 *
 *  
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>             /* for QCTNAME             */

/* So herbs will work! */
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/herbs/herb_sets/underground_herbs.h"

inherit SEWER_ROOM_BASE;
inherit "/d/Earthsea/lib/room_tell";
inherit "/d/Earthsea/lib/stream_lib";


/* Global Variables */
public string    Long_Extra = ""; /* optional tag for long descriptions */

/* Prototypes */
nomask void        create_sewer();
public void        create_tunnel_room();
public void        set_long_extra(string s) { Long_Extra = s; }

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
} /* init */

/*
 * Function name:        create_sewer
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sewer()
{
    
    string  long_desc;

    long_desc = "Shadows hold many secrets underneath the city. "
           + "Allowing your eyes to adjust to the scene, "
           + "darkness surrenders and shapes are revealed. "
           + "You are standing in a shadowed tunnel that extends with a "
           + "gradual slope. The walls and ceiling are crafted "
           + "with a post and lintel architectural technique and are "
           + "in imperfect condition. The floor is made of stone and is "
           + "covered with downward flowing sewage. ";
              
    set_short("Lower main tunnel");
           
    /* Properties Section */
    add_prop(ROOM_I_INSIDE, 1);
    set_tell_time(300);
    
    /* Call the base creation function for sewers */
    create_tunnel_room();

    /* The child room will set the value of Long_Extra for us, so now
     * it is safe to make our long description call.
     */
    set_long(long_desc + Long_Extra + "\n\n");

    // Add the try_items after create_sewer_room so that it will not
    // replace the items added by subclasses
    // Room Item Section  
                                
    try_item( ({ "environment", "area", "sewer", "room", "tunnel", 
                 "subterranean environment", "scene", "details"} ),
             "A tunnel extends upstream and downstream with post and "
           + "lintel architecture. The walls and ceiling are crafted "
           + "with large stone slabs quarried from the mountain. "
           + "The floor is also made of stone and is "
           + "covered with the downward flowing sewage, in which you "
           + "stand.\n");
    
    try_item( ({ "upward", "upstream", "downstream", "downward" }),
             "The tunnel extends and allows the sewage to flow "
           + "from the higher level to the lower level. Looking "
           + "far into each direction yields only darkness.\n");

    try_item( ({ "darkness", "cracks", "crevices", "shadows", "shadow", 
                 "shapes" }),
             "Darkness, utter darkness.\n");
         
    try_item( ({ "post", "post and lintel", "architecture", "slab", 
                 "walls", "posts", "classic architecture", "slabs" }),
             "The tunnel is made of stone posts, or blocks of solid rock, "
           + "that are held in place by a heavy capstone, or lintel. The "
           + "weight of the lintel keeps the stone walls in place and "
           + "you safe. If the lintel cracks and lightens, the posts will "
           + "likely cave in and crush you.\n");
           
    try_item( ({ "stone", "stones", "blocks", "block", "rock", "solid rock",
                 "wet walls" }),
             "These stones are solid looking and are cold to the touch.\n");

    try_item( ({ "ceiling", "lintel", "capstone" }),
             "The lintel, or capstone, forms the solid stone ceiling. It must "
           + "be solid, or the walls would cave into the tunnel. In this "
           + "specific example, the lintel appears to be in decent shape.\n");

    try_item( ({ "floor", "water", "sewage", "poo", "pee", "current",
                 "ground", "shit" }),
             "Ah, sewage; the undeniable proof of living beings. Any city, "
           + "even dwelling, produces a certain amount of waste. This waste, "
           + "in which you currently stand, is the excrement of the city of "
           + "Gont. Being an odd cross between dark green and brown, the "
           + "sewage is surprisingly water-like in flow. The smell is "
           + "malodourous and the taste... well... you best not. "
           + "Furry looking algae and other subterranean plantlife cling "
           + "to the submerged stones and wet walls. A well adapted beast "
           + "of a fish, or worse, might lurk in the current.\n");

    try_item( ({ "alga", "algae", "plantlife", "plant", "plants", }),
             "Subterranean plants eke out an existence in this "
           + "environment.\n");
 
    try_item( ({ "smell", "smells" }),
             "The waste of an entire city assaults your nose.\n");
            
    try_item( ({ "sound", "sounds" }),
             "Listening closely, a combination of near and far noises can "
           + "be heard. They include, but are not limted to, drips, drops "
           + "sloshing sounds, shuffling noises, and the odd scuffle.\n");
           
    try_item( ({ "pipe", "pipes", "tributary", "tributaries", "drainpipes" }),
             "Pipes of all sizes pierce through the walls and drain their "
           + "contents onto the ground. They enter the tunnel in all "
           + "directions to provide for the best water drainage flow for "
           + "the city. There are large pipes and small pipes.\n");
           
    try_item( ({ "large pipes", "large pipe", "big pipes", "big pipe"}),
             "Large pipes leave this area of tunnel in sloped, but general "
           + "horizontal angles.\n");
           
    try_item( ({ "small pipes", "smaller pipes", "little pipes", "small pipe",
             "tiny pipe", "tiny pipes", "smaller pipe" }),
             "Smaller pipes leave this area of tunnel in a sloped, but "
           + "general vertical angle. Some of them might be able to "
           + "accomodate your fist, but not much more.\n");
           
    try_item( ({ "city", "gont", "Gont", "dwelling" }),
              "The city of Gont Port is above you and its waste is "
              + "flowing through your legs.\n");
              
    /* add_tells for all sewers */

    add_tell("Water drips from the ceiling to the ground, creating a small "
           + "splash and a hollow echo.\n");
    add_tell("Drip. drip. drip. The sewers echo with the sound of dripping "
           + "water.\n");
    add_tell("A muffled scream can be heard in the distance. Something must "
	       + "have just happened further down the tunnel.\n");	           
    add_tell("You hear a slow drip.\n");
    add_tell("You hear a distant squeaking sound.\n");
    add_tell("You hear a twang followed by a thud.\n");
    add_tell("You suddenly realize it is unnaturally quiet.\n");
    add_tell("You hear something shatter in the distance.\n");
    add_tell("You barely hear faint splashing.\n");
    
    
    
    /* apply herbs */                 
    set_up_herbs(select_herb_files(UNDERGROUND_HERBS), UNDERGROUND_LOCATIONS,
             3);


    add_cmd_item(({ "sewage", "water", "muck" }), "drink", "@@drink");

    
} // create_sewer

/*
 * Function name:        create_sewer_room
 * Description :        dummy routine for inheriting files
 */
public void
create_tunnel_room()
{
    
} // create_sewer_room


/*
 * This allows for players to attempt to drink the water
 * 
 */
public int
drink()
{
    write("You attempt to drink the sewer water, but as you bring it "
        + "close to your mouth, you gag, retch, and decide to stop.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " tries to drink"
        + " the sewer water, but fails.\n", ({ this_player() }));
    this_player()->command("gag");
    return 1;
}


/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this room. We want
 *                       to allow for broadcasting movement to rooms that
 *                       look onto this location.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    enter_inv_stream(ob, from);

    ::enter_inv(ob, from);

    start_room_tells();
} /* enter_inv */

