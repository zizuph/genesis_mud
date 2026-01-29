/*
 *     /d/Gondor/opus/rohan/isengard/guardroom.c
 *
 *     Copyright 1997 by Robert Miller (Opus)
 *
 *     Modification log:
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/open/fireplace/fireplace.h"

#define PATH_WAY "/d/Gondor/rohan/isengard/tunnel3.c"
#define NPC_FILE "/d/Gondor/rohan/isengard/npc/isen_guard"

inherit "/d/Gondor/open/fireplace/fireplace";

// Global Variables
object *Npcs = allocate(3 + random(3));

// Prototypes
public void   reset_room();
public string windowdesc();
public string fire_desc(string arg);

public void
create_isengard()
{
    set_short("guardroom of Isengard");
    set_long(BSN(
        "This appears to be some sort of meeting room for the guards of "+
        "Isengard. A fireplace has been built into the southernmost wall "+
        "while a long, wooden table sits in the center of the room. To "+
        "the east, a doorway leads into the ringwall tunnel and two "+
        "windows allow a view into the tunnel from here. Dark rooms can "+
        "be seen to the northwest as well as to the southwest."));
    
    add_item( ({"table", "wooden table", "long table", "wood table",
        "long wood table", "long wooden table", "table top"}), BSN(
            "The table is so big, it almost takes up the entire room. It "+
            "appears to have taken quite a bit of abuse so it must have "+
            "been crafted from very hard and durable wood. Located around "+
            "the table are chairs that seem to be as worn out as the "+
            "table. Ring marks are noticeable all over the table from "+
            "mugs of ale."));
    add_item( ({"chair", "chairs"}), BSN(
        "A few chairs sit around the table waiting for guards to sit in "+
        "them. They have been crafted out of fine wood, but have begun "+
        "to show signs of heavy use and abuse."));
    add_cmd_item("chair", ({"get", "take"}), BSN(
        "The chair is too heavy to be carried around."));
    add_cmd_item( "chair", ({ "sit" }), BSN(
          "You take a brief rest on the chair, then stand back up."));
    add_item( ({"wall", "walls"}), BSN(
        "A testament to the power of ancient man, the walls have been "+
        "smoothly carved from the strong, black rock that composes this "+
        "entire area. Even a fireplace has been carved into the mighty "+
        "rock wall."));  
    add_item( ({"rock", "black rock", "smooth rock", 
        "smooth black rock"}), BSN(
            "This strange black rock, which makes up the entire, "+
            "has been carved and shaped to form some rooms within the "+
            "ringwall."));
    add_item( ({"fortress", "isengard"}), BSN(
        "You cannot get a better look at Isengard from inside this room."));
    add_item( ({"tunnel", "passage", "passageway"}), BSN(
        "Just beyond the east wall, a tunnel passes through the entire "+
        "length of the ringwall forming the only way in or out of "+
        "Isengard."));
    add_item( ({"ring", "ring wall", "volcanic ring", "ringwall",
        "volcanic ring wall", "volcanic ringwall"}), BSN(
            "Only the black rock, from which this room was constructed, "+
            "is visable from here."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor is relatively smooth considering it had to be carved "+
        "and smoothed by hand."));
    add_item( "ceiling", BSN(
        "High above, the ceiling of the room is perfectly "+
        "rounded making it difficult to tell where the ceiling ends and "+
        "the wall begins."));
    add_item( ({"room", "rooms", "dark room", "dark rooms"}), BSN(
        "The contents on the next room are shadowed by darkness."));
    add_item( ({"marks", "ring marks", "mark", "ring mark"}), BSN(
        "Probably formed from mugs of ale, these marks have stained rings "+
        "all over the table top."));
    add_item( "hearth", BSN(
        "Carved from the same back rock as the walls and fireplace, the "+
        "hearth seems just the perfect height to sit upon."));
    add_cmd_item( ({"hearth", "broad hearth"}),
       ({ "sit" }), BSN(
          "You take a brief rest on the hearth, then stand back up."));
    
    add_item( "fireplace", &fire_desc("fireplace"));
    add_item( ({ "fire" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
                 "firewood in fireplace" }),
        &fire_desc("wood"));
    add_item( ({ "ash", "ashes" }), &fire_desc("ash"));
    add_item( ({"window", "windows"}), windowdesc);

    add_exit(ISEN_DIR + "storerm1", "northwest", 0);
    add_exit(ISEN_DIR + "storerm2", "southwest", 0);
    add_prop(ROOM_I_INSIDE, 1);
    clone_object(ISEN_DIR + "obj/guardrm2")->move(TO);

    reset_room();
}

public void
reset_room()
{
     clone_npcs(Npcs, NPC_FILE, 3.0);
}

public void
init()
{
   ::init();
   init_fire();
}

/*
 * Function name:       fire_desc
 * Descripiton  :       VBFC for fireplace
 * Arguments    :       string arg -- what we're looking at
 * Returns      :       string description
 *
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch ( arg )
    {

    case "fireplace":
        switch ( fire_state )
        {

        case FIRE_BURNING:
            return BSN("The fireplace is quite large, with a "+
                "broad raised hearth. A fire is burning brightly in "+
                "the fireplace.");
        case FIRE_UNLIT_WOOD:
            return BSN("The fireplace is quite large, with a "+
                "broad raised hearth. A pile of wood sits in the "+
                "center of the fireplace.");
        default:        /* FIRE_ASHES */
            return BSN("The fireplace is quite large, with a "+
                "broad raised hearth. Ashes are piled "+
                "in the center of the fireplace.");
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
            return BSN("A fire burns briskly in the fireplace, "+
                "casting a warm light over the room.");
        return BSN("You find no fire.");

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return BSN("The wood in the fireplace burns briskly, casting "+
                "a warm light over the room.");
        case FIRE_UNLIT_WOOD:
           return BSN("Unlit wood is piled in the fireplace.");
        default:        /* FIRE_ASHES */
            return BSN("You find no "+Exa_arg+".");
        }

    case "ash":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return BSN("Beneath the briskly burning fire, "+
                "ashes cover the bottom of the fireplace.");
        case FIRE_UNLIT_WOOD:
            return BSN("Beneath the unlit wood, "+
                "ashes cover the bottom of the fireplace.");
        default:        /* FIRE_ASHES */
            return BSN("Ashes cover the bottom of the fireplace.");
        }
    }
    return "";  /* "cannot" happen */
}



/*
 *  Function name:  windowdesc
 *  Description:    will show the player who examines the window what
 *                  is on the other side, desc and people
 *  Returns:        description of room and who is in it at the time
 */

string
windowdesc()
{
    string tdesc;
    object *lnames;

    tdesc = "Looking through the window that has been cut through the "+
        "wall you see the passage leading through the volcanic ring. ";
    seteuid(getuid(TO));
    (PATH_WAY)->load_me();
    lnames = FILTER_LIVE(all_inventory(find_object(PATH_WAY)));
    if (sizeof(lnames)>0) tdesc += "You can see "+COMPOSITE_LIVE(lnames)+ 
        " as you peer into the tunnel.";
    else tdesc += " The tunnel seems to be empty at this time.";
    return BSN(tdesc);
}
