/*
 * calathin1/living.c
 *
 * Lilith - March 2022
 *
 */
#pragma strict_types

#include "h1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit H1 +"housebase";

#define SEE_NORTH	({ H1 + "kitchen" })
#define SEE_ENTRY   ({ JUNK_ROOM })

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";
    else
    return " where you can see "+ COMPOSITE_LIVE(live) + ",";
}

public string
window_view(void)
{
    object *live = get_view(SEE_ENTRY);

    if (!sizeof(live))
	return " Through the windows you can see the front stoop and "+
        "the townhouses across the street. It looks like a cold "+
        "day out there.\n";
    else
    return " Through the windows you can see "+
        COMPOSITE_LIVE(live) + " standing on the front stoop. "+
        "It looks pretty cold out there, perhaps you should invite "+
        "them inside?\n";
}


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{

    add_exit("kitchen", "north");

    room_add_object(DOOR +"h1_in", 1);
    room_add_object(HOBJ +"table1_living", 1);
    room_add_object(HOBJ +"couch1_e", 1);
    room_add_object(HOBJ +"couch1_w", 1);

    set_short("townhouse living room");
    set_long(
        "This a comfortable living room in one of the townhouses "+ 
        "in western Calathin. "+
        "The ceiling is open all the way to the roof, making "+
        "the space light and airy. "+
        "You can see a railing above, where the floor of the "+
        "loft ends. "+
        "The walls are made of pine logs that have been peeled "+
        "and sanded smooth. Bands of white chinking fills "+
        "the spaces between the logs and brightens up the "+
        "interior. "+
        "The large south-facing windows shed light on two "+
        "couches piled with cushions, "+
        "and between them is a low table resting on a large "+
        "bearskin. "+
        "North is a kitchen,@@north_view@@ while the way "+ 
        "south leads out of the townhouse. "+
        "\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_help_topic("here",   HELP +"living_help");
    add_help_topic("room",   HELP +"living_help"); 
	add_help_topic("living", HELP + "living_help");
	
    set_items_living();
    
    add_item(({"bearskin", "bear skin", "rug", "bearskin run"}),
        "A very large bear gave up its skin so you could have "+
        "a warm rug underfoot.\n");
    add_item(({"cushions", "cushion"}), 
      "There are crimson satin cushions on the east "+		
      "couch and maroon silk cushions on the west one.\n");  
    add_cmd_item("sign", "read", "@@sign_desc@@");
    add_item("sign", "@@sign_desc@@");
    add_item(({ "window", "window in door", "doorwindow", "windows"}), 
      "@@window_view@@");
    add_item(({"loft", "railing"}), "There is a loft above part "+
        "of this room, and the next one south of here. A safety "+
        "railing prevents people from falling over the edge.\n");		
	  
    start_room_tells();		
    add_tell("You hear a commotion on the road outside.\n");
	add_tell("A stray beam of light illuminates the floor.\n");
    add_tell("You hear a loud pop from the wood burning "+
        "in the fireplace in the kitchen.\n");
    add_tell("The scent of stew wafts in from the kitchen.\n");
    add_tell("A strong gust of air rattles the door.\n");	
    add_tell("A feeling of peace and comfort settles upon you.\n");
    add_tell("The warmth of this home is a welcome respite from "+
        "the bitter cold outside.\n");
}

string
sign_desc()
{
    return
    "     Welcome! Please try <help house>.\n"+
    "                      -The Management.\n";
}
