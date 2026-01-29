/*
 * DEBUGGING COPY!
 *  /d/Gondor/rohan/edoras/stallion_dining.c
 *
 *  Opus, Feb 1998
 *
 *  Copyright (c) 1998 by Robert Miller
 *
 * Modification log:
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

inherit "/d/Gondor/open/fireplace/fireplace";

#define PATH_WAY     "/d/Gondor/rohan/edoras/DBGstairs2.c"        

// Prototypes
public void    reset_room();
public string  windowdesc();
public string  archdesc();
public int     can_pass();
public string  fire_desc(string arg);

public void
create_gondor()
{
    set_short("dining room of the stallion inn.");
    set_long(BSN(
       "This is a large gathering room that also doubles as a dining "+
       "room for the Sleeping Stallion Inn. Tables litter the room "+
       "waiting to be used by locals or travelers wishing to sit down "+
       "to enjoy a fine meal searved by the inn. A fireplace has been "+
       "placed in the corner to provide a nice atmosphere. Every table "+
       "has a small lamp providing personal light while the entire room "+
       "is lit by a few large lamps hanging from the ceiling. A large rug "+
       "covers most of the floor. Fresh air fills the room from a window "+
       "on the west wall. To the north a wooden archway leads back into "+
       "the main area of the inn."));
    
    add_item( ({"tables", "table", "wood table", "wood tables",
                "wooden table", "wooden tables"}), BSN(
        "These wooden tables are sturdy despite thier dilapidated "+
        "appearance from years of use and abuse. Many of the tables "+
        "are currently occupied by folks feasting on a hearty meal from "+
        "the inn. Small lamps, located in the middle of each table, "+
        "provide enough light to eat by."));
    add_item( ({"lamp", "small lamp", "lamps", "small lamps",
                "large lamp", "large lamps"}), BSN(
        "Large lamps hang from the ceiling provide the room with light. "+
        "In the middle of each table, a small lamp provides just enough "+
        "light to be able to eat."));
    add_item( ({"rug", "large rug", "reminants"}), BSN(
        "The reminants of what once was an elegant rug lies beneath your "+
        "feet. The color has faded and various parts have worn through to "+
        "the floor below."));
    add_item( "window", windowdesc()); 
    add_item( ({"arch", "archway", "wooden arch", "wooden archway"}), 
                archdesc());
    add_item( ({"wall", "walls"}), BSN(
        "The smooth plaster walls gleam in the oil lamp's light.")); 
    add_item( ({"floor", "ground"}), BSN(
        "The floor is covered by a large, worn out rug."));
    add_item( "ceiling", BSN(
        "Just above your head, the ceiling has been constructed out of "+
        "wood."));
    
    add_item( "hearth", BSN(
        "Built of stone, the hearth is about knee high."));
    add_cmd_item( ({"hearth", "stone hearth"}),
       ({ "sit" }), BSN(
          "You take a brief rest on the hearth, then stand back up."));
    
    add_item( "fireplace", &fire_desc("fireplace"));
    add_item( ({ "fire" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
                 "firewood in fireplace" }),
        &fire_desc("wood"));
    add_item( ({ "ash", "ashes" }), &fire_desc("ash"));
    add_item( ({"window", "windows"}), windowdesc);
    

    add_exit(EDORAS_DIR + "DBGstallion.c", "north",  can_pass);
    add_exit(EDORAS_DIR + "DBGstairs2.c",  "window", 0, 0, 1); 
    
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

public void
reset_room()
{
   

}

public void
init()
{
   ::init();
   init_fire();
}

/*
 *  Function:    windowdesc()
 *  Description: Gives the player the description of the room that is 
 *               beyond the window.
 *  Returns:     wdesc
 */

string
windowdesc()
{
    string wdesc, time;
    object *wnames;

    wdesc = "Outside the window is a busy area of Edoras. Across the "+
        "way is the local bank. "; 
    
    switch (tod())
    {
    case "night":
        wdesc += "Darkness fills the air outside. ";
        break;
    case "noon":
        wdesc += "The sun is beating down from high in the sky. ";
        break;
    case "early morning":
    case "morning":
        wdesc += "Shadows are cast across the town from the rising sun. ";
        break;
    case "afternoon":
    case "evening":
        wdesc += "Shadows are cast across the town from the "+
            "setting sun. ";
        break;
    default:
        wdesc += "Something is wrong, please notify a wizard. ";
        break;
    }
    
    seteuid(getuid(TO));
    (PATH_WAY)->load_me();
    wnames = FILTER_LIVE(all_inventory(find_object(PATH_WAY)));
    if (sizeof(wnames)>0) wdesc += "You see " +COMPOSITE_LIVE(wnames)+ 
        " outside.";
    else wdesc += " No one seems to be outside at this moment.";
    return BSN(wdesc);
    
}

/*
 *  Function:    archdesc()
 *  Description: Gives the player the description of the room that is
 *               beyond the arch.
 *  Returns:     adesc
 */

string
archdesc()
{
    string adesc;
    object *anames;

    return "";
}

int
can_pass()
{
   return 0;
}

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
                "stone hearth. A fire is burning brightly in "+
                "the fireplace.");
        case FIRE_UNLIT_WOOD:
            return BSN("The fireplace is quite large, with a "+
                "stone hearth. A pile of wood sits in the "+
                "center of the fireplace.");
        default:        /* FIRE_ASHES */
            return BSN("The fireplace is quite large, with a "+
                "stone hearth. Ashes are piled "+
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
