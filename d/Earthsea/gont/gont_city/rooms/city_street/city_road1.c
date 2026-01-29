#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Narrow cobbled street");
    set_long("You are standing just south of the tunnel"+
        " leading out of the great Port of Gont on a"+
        " narrow cobbled street. The city wall towers"+
        " up above your head, together with numerous"+
        " large three-story stone buildings and high"+
        " towers. The road continues between the buildings"+
        " to the southeast and southwest. Southwards stands"+
        " a tall tower, with a white flag gently flapping"+
        " above it. It is very crowded on the narrow street,"+
        " with people shouting and talking to each other"+
        " as they pass by.\n");
    add_item("tunnel","Looking north you can see the wide"+
      " tunnel leading through the thick city walls, to"+
      " the fields outside.\n");
    add_item("wall","The mighty wall made by cut dark stone"+
      " towers high above your head here.\n");
    add_item(({"buildings","towers"}),"Large stone buildings"+
      " and high narrow towers form the structure of this"+
      " port city, looming over the narrow streets below.\n");
    add_item("street","The street is cobbled, and littered"+
      " by refuse and other traces of many humans walking by.\n");
    add_item("flag","Above the narrow tower to the south is"+
      " a white flag flapping in the breeze; the symbol of the"+
      " Lord of Gont.\n");
    add_item("tower","Southwards is a tall, narrow tower with"+
      " the white flag of the Lord of Gont flapping over it.\n");
    add_exit("../inside_gate", "north");
    add_exit("city_road2", "southwest");
    add_exit("city_road3", "southeast");
    add_exit("city_road1a", "south");
}
