/*
 * farm1a.c
 *
 * Calathin external house.
 * 11/21/1999 -- Tomas
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
    set_short("farm");
    set_long("You are on a dirt road leading southeast from the gate " +
       "to the farmhouse. A snow covered field is on " +
       "either side of you.\n");

    add_item(({"split-railed","fence"}),
       "The fence completely surrounds the farm except for the gate " +
       "before you. It looks sturdy enough to hold even the largest of " +
       "livestock from leaving the farm.\n");

    add_item(("barn"),"The two story red barn stands to the side of the small " +
       "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(({"dirt road","road"}),
       "The dirt road leads from the fenceline to the farmhouse.\n");

    add_item(("field"),"The field looks like it is used to harvest " +
       "crops in the summertime. A lone scarecrow stands guard " +
       "over the snowcovered field.\n");

    add_item(("scarecrow"),"The scarecrow is made of old clothes " +
       "stuffed with straw.\n");
   
    add_item(("house"),"A typical single level range type house.\n");

    add_item(("livestock"),"You dont see any, Yet..\n");
    
    add_exit(CFARMS + "farm1b","southeast",0,1);
    
    room_add_object(CFARMS + "obj/farm1_gate1");

    add_field_herbs();
    add_pebbles();
}
