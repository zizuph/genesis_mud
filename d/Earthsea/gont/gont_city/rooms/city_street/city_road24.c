#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Narrow street");
    set_long("The cobbled street leads in"+
          " between the wooden warehouses and other"+
          " two-story buildings further eastwards."+
          " This seems to be living quarters for the"+
          " less well-standing part of the population"+
          " of Gont Port with small apartments packed"+
          " closely together, and piles of trash in the"+
          " narrow alleys. The sides of the tall buildings"+
          " lean in over your head, casting dark"+
          " shadows over the street. Looking through"+
          " one of the narrow alleys you can see the"+
          " high city wall close behind to the"+
          " southeast. People dressed like fishermen"+
          " and harbour workers pass by now and then,"+
          " on their way to other parts of the city.\n");
    add_item("warehouses","Westwards, closer to"+
        " the harbour area the living quarters change"+
        " to wooden warehouses where goods traded"+
        " through Gont Port are stored.\n");
    add_item(({"quarters","wooden buildings", "buildings"}),
        "Two-story wooden buildings"+
        " containing several apartments for the less"+
        " well-standing of the population make up the"+
        " bulk of this part of the city. They contain"+
        " small apartments packed closely together.\n");
    add_item("trash","This is household refuse"+
        " that noone bothered to take further away."+
        " It was probably dumped on the street from"+
        " the windows.\n");
    add_item("street","The cobbled street is"+
        " narrow and littered with trash here, as"+
        " it winds on towards the northeast between"+
        " the high wooden buildings.\n");
    add_item("alleys","Dark alleys lead in between"+
        " the two-story wooden buildings, most of"+
        " them filled with piles of trash and refuse.\n");
    add_item("wall","Through one of the alleys"+
        " you can see the high crenelated city wall"+
        " close to the southeast.\n");
    add_item("apartments","The apartments look"+
        " very small and closely packed together,"+
        " to provide room for as many as possible.\n");
    add_item(({"people","fishermen", "harbour workers"}),
        "People pass by you"+
        " now and then but most of the time the street"+
        " is calm and peaceful. Most of them are"+
        " dressed as harbour workers or fishermen,"+
        " smiling and laughing as they walk by.\n");
    add_exit("city_road22", "west");
    add_exit("city_road25", "northeast");
}
