//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <filter_funs.h>
#include <composite.h>
#include <ss_types.h>

#define SEE_BELOW ({ (ROOM_DIR+"chamber") })

string 
below_view()
{
    object *inv, *live, room;
    int i;
 
    inv = ({ });
    for(i = 0; i < sizeof(SEE_BELOW); i++)
    if((room = find_object(SEE_BELOW[i])))
        inv += all_inventory(room);
 
    if(sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        if(sizeof(live))
            return " From your high vantage point, you can see"+
                   " "+ COMPOSITE_LIVE(live) + ".";
    }
    return "Your heightened senses can detect no signs of "+
           "life in the lower chamber.";
}


public void create_vamp_room()
{

    set_short("Balcony above the central chamber");
    set_long("You are standing on a balcony that encircles a large "+
        "chamber. The staircase that once lead down now lies in ruins "+
        "on the floor below. @@below_view@@\n");

    add_item(({"staircase", "ruined staircase"}), 
        "The staircase once lead from to the balcony down to the room below.\n");
    add_item(({"balcony"}), "There is a balcony encircling and overlooking "+
        "this chamber.\n");
    add_item(({"floor"}), "The floor is level, unpolished and unadorned, the "+
        "same material as the rest of the room.\n");
    add_item(({"ceiling"}), "The ceiling is quite high, about twice "+
        "the height of most of the other ceilings in this place.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "completely unadorned and unpolished.\n");

//  add_prop(VAMP_CAN_START_HERE,1);
    
    add_exit("uppertomb","west");
    add_exit("storage","north");
    add_exit("chamber","down");
    
}

