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
    try_item( ({ "ruins", "ancient ruins", "ancient looking ruins",
                 "remains"}),
        "There are many ruined columns and what appears to be the "
      + "remains of some type of altar.\n");
    try_item( ({ "column", "columns", "ruined columns" }),
        "The columns are all collapsing on one another and have many "
      + "chips and cracks in them. Yet despite its desolate state, you "
      + "can tell that they were made from the finest marble.\n");
    try_item( ({ "bone", "bones", "many bones" }),
        "There are many bones strewn throughout the ruins here in "
      + "this cave. They appear to be humanoid mostly.\n");
    try_item( ({ "altar" }),
        "You can make nothing out about this ruined altar except that it "
      + "was once an altar.\n");
    try_item( ({ "cave" }),
        "This cave contains a bunch of ruins. You get a strange tingling "
      + "sensation from just being in this place.\n");
      
    add_exit(ROOMS + "tunnel08_05.c", "northwest");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 3, 4);
    if (random(4))
        clone_undead("devourer", 150, 2, 4);
    
    clone_undead("banshee", 130, 1, 1);
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
    return "Ruins";
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
    desc = "You have arrived at a dead end. The only way out of here "+
        "is to the "+COMPOSITE_WORDS(exits)+". Scattered around the "+
        "area are some ancient looking ruins. Strewn throughout the "+
        "ruins are the many bones of the victims of the inhabitants of "+
        "this cave.\n";    
    return desc;
}
