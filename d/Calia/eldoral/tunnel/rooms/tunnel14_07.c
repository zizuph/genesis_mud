/*
 * Eldoral Undead Tunnels
 *
 * Originally coded by Jaacar (Mike Phipps), October 2003
 * Adapted by Petros, November 2008
 */
 
#include <composite.h>
#include "defs.h"
inherit UNDERGROUND_BASE;

void
create_tunnel_room()
{
    try_item( ({"skeletons", "bones", "leftovers"}),
        "They seem to be some humanoid bones. Perhaps you should turn "
      + "back!\n");
    try_item( ({ "tunnel system", "system", "cave system", "caves",
                "tunnels", "passageway" }),
        "The tunnel system you are in appears to be quite large. Though "
      + "the passageway is narrow, it feels quite expansive, especially "
      + "above you. You cannot even see the ceiling of the tunnel.\n");
    try_item( ({ "sunlight", "cracks", "east", "light" }),
        "The wall to your east has cracks in it. Sunlight shines through "
      + "the cracks. The cracks seem to be big enough for you to pass "
      + "through it safely.\n");
    try_item( ({ "ground" }),
        "The ground here is strewn with the remains of former humanoids.\n");
    
    add_exit(ROOMS + "tunnel13_07.c","west");
    add_exit(ROOMS + "crack_entrance","east");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
}

/*
 * Function     : query_tunnel_short
 * Description  : Returns the short description for this particular
 *                room.
 * Arguments    : none
 * Returns      : short description
 */
public string
query_tunnel_short()
{
    return "In a narrow tunnel";
}

/*
 * Function     : query_tunnel_long
 * Description  : Returns the long description for this particular
 *                room.
 * Arguments    : none
 * Returns      : long description
 */
public string
query_tunnel_long()
{
    string * exits;
    string desc;
    
    exits = query_obvious_exits();
    desc = "You have stopped at a narrow tunnel of what seems to "
      + "be a big tunnel system. It continues "+COMPOSITE_WORDS(exits)
      + ". Some sunlight shines through the cracks in the wall to "
      + "your east. Old skeletons and bones are strewn along the "
      + "ground here. Further to your west, it gets much darker.\n";
    
    return desc;
}


