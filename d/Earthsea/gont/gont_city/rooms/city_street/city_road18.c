#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    int i;

    for(i = 0; i < 3; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("Northeast part of the harbour");
    set_long("You are standing just northeast of"+
        " the main part of the harbour of Gont Port,"+
        " some distance away from the major piers."+
        " To the north is a small wooden building,"+
        " probably serving as a storage house of some"+
        " kind. This part of the harbour area is occupied"+
        " by fishermen and their boats, with the"+
        " smaller ones hauled ashore far up on the"+
        " sandy beach. Racks built of sturdy wooden"+
        " poles hold large amounts of fishing nets,"+
        " and you can see several men working on"+
        " repairing them and unloading their catch"+
        " from the small boats. Some distance to the"+
        " south, across the grey water you can see two"+
        " high cliffs towering up, guarding the narrow"+
        " entrance to the secluded bay.\n");
    add_item("cliffs","Across the water to the south you"+
        " can see the two famous Armed Cliffs, guarding the entrance"+
        " to Gont Port with high stone towers built on top of them.\n");
    add_item(({"fishermen","men"}),"Many fishermen"+
        " are at work bringing their catch ashore from"+
        " the boats or repairing nets. Most of them"+
        " seem to be characteristic inhabitants of"+
        " Gont Island, with dark skin.\n");
    add_item("poles","The racks are built by two"+
        " sturdy wooden poles, hammered deep down in the"+
        " sand with a third pole nailed horizontally on"+
        " top of the other two.\n");
    add_item("boats","Many smaller crafts belonging"+
        " to fishermen are anchored in the shallow water"+
        " or simply hauled up on the sandy beach. These"+
        " are small boats built to take at most two or"+
        " three men on shorter fishing expeditions"+
        " outside the coast of Gont.\n");
    add_item("building","Just across the street"+
        " following the water's edge is a small wooden"+
        " building that seems to be a storage house"+
        " of some kind.\n");
    add_item(({"harbour","water"}),"Looking out"+
        " over the busy harbour of Gont Port you can"+
        " see the three major piers with hundreds of"+
        " ships anchored by them, with a forest of masts"+
        " swaying back and forth in the rhytm of the"+
        " small waves rippling the surface of the grey"+
        " water.\n");
    add_item("racks","Sturdy racks of wooden poles"+
        " hold the fishing nets owned by the fishermen."+
        " Some men seems to be busy repairing holes in"+
        " the nets.\n");
    add_item("piers","The three major piers of the"+
        " Gont Port stretches out far into the bay, with"+
        " many ships from all across the Archipelago"+
        " anchored by them. This seems to be a very busy"+
        " trading harbour.\n");
    add_item("nets","A huge amount of fishing nets"+
        " owned by the fishermen hang over the racks,"+
        " probably to dry them and for repairing holes.\n");
    add_exit("city_road19", "southeast");
    add_exit("city_road17", "west");
    add_exit("../storage", "north");
}
