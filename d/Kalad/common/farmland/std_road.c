/*
 *  /d/Kalad/common/farmland/std_road
 *
 *  The standard room for the roads in the farmlands
 *
 *  Created Feb 2017, by Andreas Bergstrom (Zignur)
 */
 
#pragma strict_types
inherit "/std/room";
#include </sys/macros.h>
#include </sys/stdproperties.h>
#include </sys/time.h>
#include "defs.h"
#include <stdproperties.h>

/* Definitions */


/* Prototypes */
public nomask void  create_room();
public void         create_std_road();
public void         add_road_items();

/*
 * Function name:        create_room
 * Description  :        the basic constructor for rooms
 */
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    create_std_road();
    add_road_items();
    enable_reset(200);  /* make resets as fast as possible for grinding */
    
} /* create_room */


/*
 * Function name:        create_std_road
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_road()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} /* create_std_road */


/*
 * Function name:        add_road_items
 * Description  :        Adds the standard items for the road
 *
 */
public void
add_road_items()
{      
    add_item( ({ "farmlands", "farmland"}),
        "You see a large fields of hay and various other crops.\n");        
    add_item( ({ "field", "fields","crops","hay"}),
        "Large fields of hay and other crops grows nearby.\n");
    add_item( ({ "road", "gravel road", "ground"}),
        "The road is made of hard packed gravel, you see some holes and"
      + " cracks in it. Most likely caused by the dry hot climate.\n");
    add_item( ({ "crack", "cracks","hole","holes"}),
        "The road has several holes and cracks, caused by the dry climate.\n");
    add_item( ({ "gravel", "small gravel","packed gravel","gravels"}),
        "The road consist of small packed gravels.\n");
         
      
} /* add_road__items */

