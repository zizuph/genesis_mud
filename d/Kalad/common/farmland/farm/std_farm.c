/*
 *  /d/Kalad/common/farmland/farm/room/std_farm.c
 *
 *  The standard room for the farm estates in the 
 *  Farmlands west of Kalad.
 *
 *  Created Feb 2017, by Andreas Bergstrom (Zignur)
 */
 
#pragma strict_types

inherit "/std/room";

#include </sys/macros.h>
#include </sys/stdproperties.h>
#include </sys/time.h>
#include "../../defs.h"
#include <stdproperties.h>

/* Definitions */


/* Prototypes */
public nomask void  create_room();
public void         create_std_farm();
public void         add_farm_items();
public void         enter_inv(object ob, object from);


/*
 * Function name:        create_room
 * Description  :        the basic constructor for rooms
 */
public nomask void
create_room()
{
    /* Map file */
   // add_prop(ROOM_S_MAP_FILE, "redfang_trainingcamp.txt");
    //add_name(REDFANG_CAMP_ROOM);
    add_prop(ROOM_I_LIGHT, 1);
    create_std_farm();
    add_farm_items();
    enable_reset(200);  /* make resets as fast as possible for grinding */
    
} /* create_room */


/*
 * Function name:        create_std_farm
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_farm()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} /* create_std_farm */


/*
 * Function name:        add_farm_items
 * Description  :        Adds the standard items for the farms
 *
 */
public void
add_farm_items()
{      
    
    add_item( ({ "floor", "floors", "wooden floor","wooden floors"}),
        "The floors are made by exclusive polished oak wood, that"
      + " are keept stainless by one of the servants in the house.\n");
         
    add_item( ({ "wall", "walls","wooden wall","wooden walls"}),
        "The walls are made by exclusive polished oak wood.\n");
	
    add_item( ({ "wood", "oak wood", "polished wood"}),
        "The walls and floors are made by exclusive polished oak"
      + " wood.\n");
    
    add_item( ({ "painting", "paintings"}),
        "Several paintings hang on the walls, displaying nobles"
      + " in glorious battle.\n");
      
    add_item( ({ "banner", "banners"}),
        "Several banners hang on the walls, proudly showing"
      + " the colors of the Noble House.\n");  

    add_item( ({ "candles", "candle","hole","holes"}),
        "Several candles are placed in candle holders along the"
      + " walls, providing light and a exotic smell.\n");
        
    add_item( ({ "candle holders", "candle holder","holder","holders"}),
        "You see several candel holders with candles mounted on the"
      + " walls.\n");    
    
    add_item( ({ "rugs","mats","colorful mats","colorful rugs","mat","rug"}),
        "You see several colorful rugs and mats lying on the oaken"
      + " floors.\n");    
    
    add_item( ({ "window", "windows"}),
        "The windows provide a view over the wast farmlands outside"
      + " the farm estate.\n");
   
      
} /* add_farm__items */


/*
 * Function name:        enter_inv
 * Description  :        we mask this to set up the room tells.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
} /* enter_inv */

