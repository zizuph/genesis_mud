/*
 *  /d/Kalad/common/farmland/farm/rooms/farm1_4
 *
 *  One of the rooms in the farm estates in the Kalad farmlands
 *
 *  Created February 2017, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
#include "../../defs.h"
inherit ROOMS_DIR + "std_farm";


/* Prototypes */
public void         create_std_farm();

/*
 * Function name:        create_room
 * Description  :        constructor for the room
 */
public void
create_std_farm()
{
    set_short("Inside a grand dining hall");
    set_long("Inside a grand dining hall within a large farm estate."
      + " A large wooden table dominates the room, it is filled with"
      + " all sorts of food and drinks, served on exclusive silverware."
      + " This is clearly where the owners of this estate meet and"
      + " socialize with their guests. Several paintings and banners"
      + " hang on the polished wooden walls, candles burn softly in"
      + " candle holders. Several colorful rugs and mats covers the"
      + " wooden floor. The smell of food tells you that the kitchen"
      + " lies to east, to the west there is a bedroom of sorts, south"
      + " leads to the guards barracks, while north will lead back to"
      + " entrance hall of the estate.\n");       

    /* Items for this room */
    add_item( ({ "table", "large table","wooden table","large wooden table"}),
       "A large oaken table, big enough for twenty peoples to sit comfortable"
     + " around. The table is filled with all sorts of food and drinks.\n"); 
    add_item( ({ "chairs", "chair"}),
       "Chairs stand around the table, providing a place to sit.\n");  
    add_item( ({ "food", "drinks", "drink"}),
       "All sorts of food and drinks are being served on exclusive silverware"
     + " and golden goblets.\n");  
    add_item( ({ "silverware", "exclusive siverware", "goblets"}),
       "Exclusive silverware and goblets are standing on the table,"
     + " containing various food and drinks.\n"); 
    add_item( ({ "main hall", "hall"}),
       "The main hall is the entrance to the large farm estate.\n");       
    add_item( ({ "kitchen"}),
       "The kitchen lies directly to the east.\n"); 
    add_item( ({ "bedroom", "large bedroom", "master bedroom"}),
       "A large bedroom, which seems to be the master bedroom,"
     + " lies to the west.\n"); 
    add_item( ({ "barracks", "guards barracks", "guard barrack"}),
       "The guards barracks are very large, taking up a big portion"
     + " of this large farm estate.\n"); 
    
    add_npc(NPC_DIR + "house_guard_p",4,&->arm_me());
    add_npc(NPC_DIR + "noblewoman",random(4),&->arm_me());
    add_npc(NPC_DIR + "nobleman",random(4),&->arm_me());
    add_npc(NPC_DIR + "house_guard_captain_p",1,&->arm_me());     
    add_exit("farm1_5", "west");
    add_exit("farm1_6", "east");
    add_exit("farm1_1", "north");
    add_exit("farm1_7", "south");
 
   
} /* create_std_farm*/


