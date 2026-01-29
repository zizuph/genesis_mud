/*
*
* Park room.
*
* Coded by Porta 971018.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Within a grove of oak trees");
    set_long("The gravel path leads through a grove of"+
        " oak trees, with the entrance to the park to the"+
        " northeast. Everything is very peaceful here, with"+
        " the wind rustling the leaves of the large tree"+
        " crowns and birds singing. Between the trees the"+
        " ground is covered by a brown mat of fallen leaves,"+
        " but the path is clean and well-tended. To the"+
        " southwest you can leave the grove for a bright"+
        " grass lawn.\n");
    add_item("trees","The trees are old, growing far"+
        " apart from each other, with the mighty crowns"+
        " shadowing the ground below.\n");
    add_item("leaves","The ground is covered by a mat"+
        " of brown fallen leaves, giving an earthy smell of"+
        " decay to the grove.\n");
    add_item("leaves","The breeze rustles the leaves of"+
        " the oak trees, far above your head.\n");
    add_item("path","A well-tended gravel path leading"+
        " northeast to the entrance of the park, and southwest"+
        " through the grove out on a brighter grass lawn.\n");
    add_item("lawn","Southwest the path leads out on a"+
        " brighter grass lawn.\n");
    add_item("grove","Around you is a grove of old oak"+
        " trees, with their mighty crowns shadowing the"+
        " ground.\n");
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_exit("city_street/city_road13", "northeast", "@@leave_park");
    add_exit("park_2", "southwest");
    reset_room();
}

public int
leave_park()
{
    object tp = this_player();
    tp->catch_tell("You leave the park through the gate.\n");
    say(QCTNAME(tp) + " leaves the park through the gate.\n");
    return 0;
}
