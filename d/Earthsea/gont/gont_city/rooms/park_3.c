/*
* Birch grove in the park.
*
* Coded by Porta 971018.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"

#define ASPEN_BARK "/d/Earthsea/herbs/herb_files/aspen_bark"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("In a grove of birch trees");
    set_long("The gravel path ends in the middle of a"+
        " large grove of birch and aspen trees. This part of the park"+
        " seems to be a little less well-tended, with"+
        " undergrowth growing thick between the white stems"+
        " of the older trees. Everything is very peaceful"+
        " and silent except for the many birds singing,"+
        " well-hidden in the lush foliage. The ground is"+
        " wet and covered with a brown mat of fallen"+
        " leaves. A fresh breeze makes the birches sway"+
        " back and forth, rustling the green leaves"+
        " and branches.\n");
    add_item(({"trees","birches"}),"Looking around,"+
        " all you can see"+
        " is a grove of old birch trees with smaller sprouts"+
        " growing thick between the white stems. Some of"+
        " these birches are among the biggest you have seen,"+
        " and must be at least a century old. Among the birches"+
        " you see smaller aspen trees with their quaking leaves.\n");
    add_item("grove","You are standing in the middle of"+
        " a grove of birch and aspen trees, effectivly hiding all"+
        " signs of the city outside the park, except for"+
        " the gravel path leading back to the grass lawns.\n");
    add_item(({"undergrowth","sprouts","foliage"}),
        "Between the"+
        " wide stems is the new generation of birch trees"+
        " growing thick, blocking all view with their"+
        " green leaves.\n");
    add_item(({"mat","fallen leaves"}),"The humid ground"+
        " is covered with a soft mat of decaying leaves, thick"+
        " from the defoliation of many autumns coming and"+
        " going.\n");
    add_item("branches","Leafy branches hang from the stems,"+
        " preventing a great deal of the sunlight from coming"+
        " through.\n");
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_herb_file(ASPEN_BARK);
    add_exit("park_2", "south");
    reset_room();
}
