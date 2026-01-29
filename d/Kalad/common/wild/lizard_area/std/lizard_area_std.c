/* 
 * The base indoor room for Saurian Caverns
 * Replacing old Lizard Man Area - Near Blob
 * Mirandus - February 8, 2022
 *
 * Update Log: -
 *
 *                     E-o-o
 *                          \
 *           o-o-o           o-o-o                    E - Entrance
 *          /     \               \                   C - Centre
 *     o-o-o       \               o-o-o-o-o
 *    /             o-o-o                    \
 *    o-o-o              \        o-o-o-o-o-o-o
 *         \              C      /
 *          \                   /
 *           o-o-o       o-o-o-o
 *               \     /
 *                o-o-o
 *                  |
 *                  o
 */
#pragma strict_types

#include "../local.h"
inherit "/std/room";
inherit STDIR + "room_tell";
inherit STDIR + "lizard_tells";

/* Definitions */


/* Prototypes */
public nomask void  create_room();
public void         create_std_lizard();
public void         add_lizard_items();

string smell_air(string str);

/*
 * This function creates the room
 */
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    create_std_lizard();
    add_lizard_items();
    set_tell_time(random(600) + 90);
    add_tell("@@get_tells@@" + "\n");
    
    
}
/* Function name:        create_std_lizard
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_lizard()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} 
/*
 * Function name:        add_lizard_items
 * Description  :        Adds the standard items for the road
 *
 */
public void
add_lizard_items()
{  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "The walls "
    +"of this cavernous area have beem hewn by clawed hands. They have "
    +"been well established and, certainly a cared for. They appear to "
    +"be composed of a very strong stone.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
    "pieces of wood", "wood"}), "The ceiling of the area is maintained"
    +"by rough hewn beams of wood. They act as support to the roof "
    +"so that it does not collapse down upon the area.\n");
    add_item(({"floor", "floors"}), "The floors are that of an underground "
    +"area. They are cleaner than one would expect, but still covered in "
    +"dirt and small pebbles.\n");
    add_item(({"dirt","dust","pebble","small pebbles","pebbles",
    "small pebble","bone","bit of bone"}),"Small pebbles, dirt, dust, and "
    +"the occasional bit of bone are strewn about the area.\n");
    add_item(({"stone", "material", "substance", "black stone"}), "The "
    +"stone of this wall appears to be the same black marble that is "
    +"used in the city above. It's more roughly hewn here by clawed "
    +"hands, but it is clear that these caverns are the source of this "
    +"stone.\n");
    add_item(({"tools", "tool", "racks", "rack"}),"At various points along "
    +"the wall you see well made tools tipped with the same stone that "
    +"makes up the wall. Clearly whoever has made these tools is skilled "
    +"and quite intellgient given their design.\n");
    add_item(({"design", "tool design", "tools design", "designs"}), "The "
    +"tools are intricate and represent the epitome of function. While they "
    +"do not hold the same flourishes as those tools used by those on the "
    +"the surface, they seem far more functional.\n");
    add_item(({"pillar", "pillars", "hewn pillars", "well-hewn pillars",
    "well hewn pillars", "hewn pillar", "well-hewn pillar", 
    "well hewn pillar"}), "Large cylindric pillars have been  "
    +"carved with intricate patterns and designs. They do not "
    +"appear to represent anything specific that you can tell, "
    +"but flow in concentric circles and intersecting lines. The "
    +"amount of effort and skill to carve these pillars is hard "
    +"to fathom. They are not only beautiful but functional and "
    +"support the ceiling above you.\n")
    
}


int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them, an intrigued look crossing their face.\n");
    write("You smell the air around you and are intrigued to find it's not mildewy "
    +"or musty but that there is a hint of sage or spruce.\n");
    return 1;
}

/*
 * Function name: get_all_no_exits
 * Description: Returns an array of strings with exits for use with
 *              set_no_exit_msg()
 * Argument: Array of exits to exclude, for simplicity you can use
 *           nw instead of northwest, etc.
 */
string *
get_all_no_exits(string *exits)
{
    string *r_exits = m_values(NORMAL_EXITS);
    foreach (string exit: exits) {
        foreach (string ind, string val: NORMAL_EXITS) {
            if (exit == ind || exit == val) {
                r_exits -= ({ val });            
            }
        }
    }
    return r_exits;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}