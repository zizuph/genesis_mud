/*
* In a birch grove of the park.
*
* Coded by Porta 971018.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Birch grove under the city wall");
    set_long("The gravel path continues through a thick"+
        " grove of birch and aspen trees, forming a roof over your"+
        " head with many leafy branches. The old stems"+
        " stand wide apart, with new sprouts and other"+
        " green vegetation growing beneath. To the west"+
        " you can just barely catch a glimpse of the"+
        " high city wall through the foliage. Under your"+
        " feet the ground is covered with a thick mat of"+
        " brown fallen leaves. Northwards"+
        " the gravel path leads further into the"+
        " grove.\n");
    add_item("trees","The old birch trees stand wide"+
        " apart here, with their leafy entangled branches"+
        " forming a roof over your head.\n");
    add_item("grove","This is a large grove of birch"+
        " trees in the park of Gont Port, spreading out"+
        " in every direction except to the south where"+
        " the gravel path leads out on a bright grass"+
        " lawn.\n");
    add_item("branches","Leafy branches hang over the"+
        " path, forming a roof over your head, shadowing"+
        " from most of the sunlight.\n");
    add_item("stems","The stems are thick with the"+
        " characteristic white birch bark.\n");
    add_item("leaves","Green leaves prevent you from"+
        " looking further in any direction except to the"+
        " south.\n");
    add_item(({"mat","fallen leaves"}),
        "The ground is covered with"+
        " a thick mat of fallen leaves, smelling of decay"+
        " and earth.\n");
    add_item("foliage","New birch sprouts together with"+
        " other kinds of plants form a thick foliage lining"+
        " the sides of the path, making it difficult to see"+
        " further into the grove.\n");
    add_item("wall","The city wall is hardly visible through"+
        " the thick foliage, but stands just west of here.\n");
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_exit("park_2", "southeast");
    add_exit("park_5", "north");
    reset_room();
}
