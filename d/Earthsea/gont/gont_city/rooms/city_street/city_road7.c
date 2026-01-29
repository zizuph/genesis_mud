/* Street in Gont City. Coded by Ciryan 971014 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Below two high towers");
    set_long("The street makes a sharp turn as it passes"+
        " by two tall towers built from cut, black stone and"+
        " rising high up towards the sky. The towers seem"+
        " to be connected at the base with a lower building."+
        " This is probably the home of a very wealthy"+
        " merchant or a Lord of Gont. Surrounding the towers"+
        " is a large garden, filled with grass lawns and"+
        " green birch trees. An iron fence secludes the garden"+
        " from the road. It is a little less crowded here, and"+
        " most of the citizens walking by are dressed in"+
        " expensive, imported clothing.\n");
    add_item("street","The cobbled street is remarkably"+
        " clean here, continuing past the twin towers to the"+
        " northeast and southeast.\n");
    add_item("towers","The towers are of equal height"+
        " and are built from the same cut black stone as"+
        " most other buildings here. Over the towers flaps"+
        " a blue flag in the breeze.\n");
    add_item("building","The two towers are connected"+
        " with a low stone building.\n");
    add_item("garden","The garden is very large, stretching out"+
        " around both towers with well-tended lawns and groves"+
        " of birch trees.\n");
    add_item("fence","The fence is about three meters high and"+
        " made from steel. Each steel rod is formed as a spear, and"+
        " connected with iron cast to resemble the shape of a rope"+
        " tieing them together.\n");
    add_item("citizens","Most of the citizens walking by seem"+
        " to be wealthy merchants, either from Gont or other parts"+
        " of the Archipelago.\n");
    add_exit("city_road6", "northeast");
    add_exit("city_road8", "southeast");
    add_cmd_item((({"fence", "steel fence"})), "climb", "You "+
        "realize the sharp steel spears are too sharp and would "+
        "make climbing the fence very difficult.\n");
}
