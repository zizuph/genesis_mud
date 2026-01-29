/*
 * tunnel_base.c
 *
 * Baseroom for the tunnels beneath the village that goblins are hiding
 * in.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "../invade_quest.h"

inherit "/d/Khalakhor/std/room";

string extra,
       details_room;
int goblin_num,
    paper_found;
object *gobbos;

public int *
query_local_coords()
{
    return ({17,9});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
reset_room()
{
    int i;

    if (!gobbos)
        gobbos = allocate(goblin_num);

    for (i = 0; i < sizeof(gobbos); i++)
    {
        if (!gobbos[i])
        {
            gobbos[i] = clone_object(NPC + "t_goblin");
            gobbos[i]->move(TO);
            tell_room(environment(gobbos[i]), QCTNAME(gobbos[i]) +
                " charges in from nowhere!\n");
        }
    }

    paper_found = 0;
}
        
public void
create_tunnel()
{
    set_short("a damp tunnel");
    set_long("   You are in a damp tunnel, somewhere beneath the village. " +
        "It looks to have been cut from the surrounding stone, and " +
        "very roughly, as the walls, floor, and ceiling are covered " +
        "in pretty sharp edges. The floor is also covered in a thick " +
        "layer of muck and fish bones. " +
        (stringp(extra) ? extra : "") + "\n");

    INSIDE;
    DARK;

  /* Decide which of the three 'bedrooms' we hid the details */
  /* paper in. */
    if (!details_room)
        details_room = ({ROOM + "tunnel_6",
                         ROOM + "tunnel_7",
                         ROOM + "tunnel_11"})[random(3)];

    if (file_name(TO) == details_room)
    {
        add_prop(OBJ_I_SEARCH_TIME, 5);
        add_prop(OBJ_S_SEARCH_FUN, "find_paper");
    }
}

public string
find_paper(object player, string str)
{
    object *obarr,
           paper;

    if (str != "paddock")
        return "";

    if (paper_found)
        return "";

    if (sizeof(obarr = filter(all_inventory(TO), &->id(TUNNEL_GOBLIN))))
        return obarr[0]->query_The_name(player) + " prevents you from " +
            "completing your search!\n";
    
    paper_found = 1;
    reset_euid();
    paper = clone_object(OBJ + "tunnel_orders");
    if (paper->move(player))
        paper->move(environment(player));
    player->add_prop(LIVE_I_MAC_INV_STATUS, 
        player->query_prop(LIVE_I_MAC_INV_STATUS) | FOUND_DETAILS);
    return "You find a crumpled piece of paper!\n";
}
        