/*
* Below the west cliff.
*
* Coded by Porta 971017.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

// #define ORANEA_PIER "/d/Earthsea/ships/oranea_line/west_pier3"
#define THWIL_PIER "/d/Earthsea/ships/thwil_line/west_pier3"
#define SHIRE_PIER "/d/Earthsea/ships/shire_line/shire_pier"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    int i;

    for(i = 0; i < 3; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("Below a high cliff");
    set_long("You are standing by the water's edge at the"+
        " very southwest part of the bay, below a mighty"+
        " cliff towering up far above your head. A broad"+
        " stairway, cut out from the stone, leads steeply"+
        " upwards"+
        " to the top and the stone tower built there to"+
        " guard this side of the entrance to the bay. To the"+
        " northeast is the busy harbour area, with hundreds"+
        " of ships and boats anchored close together and"+
        " surrounding the basin is the large city. It is"+
        " not as crowded here with just a few fishermen"+
        " tending to their boats and nets by the sea."+
        " Just to the south and east you see a narrow wooden pier that"+
        " extends out into the water.\n");
    add_item((({"pier", "wooden pier", "small wooden pier" })),
        "The pier is smaller than those in the central area, "+
        "and there is not as much traffic here.\n");
    add_item(({"bay","basin","harbour"}),"The Port of Gont"+
        " is built around this natural harbour basin, with the"+
        " narrow canal between the two Armed Cliffs as the"+
        " only entrance. The bay is full of anchored boats and"+
        " ships, with hundreds of masts swaying back and forth"+
        " in the wind.\n");
    add_item("cliff","The west Armed Cliff towers up high"+
        " above your head just to the south, with the old stone"+
        " tower built on it's top. A steep stairway cut from the"+
        " rock leads upwards towards the tower.\n");
    add_item("stairway","The stairway is broad and steep,"+
        " and the only way up to the top of the cliff, cut"+
        " straight out from the hard rock. You would think twice"+
        " about ascending it if there were archers on the cliff"+
        " above.\n");
    add_item("tower","At the top of the steep cliff is a"+
        " tower built by black stone, for guarding the west"+
        " side of the narrow canal.\n");
    add_item("city","To the north is the city of Gont Port,"+
        " built around the large harbour.\n");
    add_item("fishermen","A few fishermen are working by"+
        " the shore with repairing their nets or the small"+
        " sailing boats pulled up on the beach.\n");
    add_item("ships","Many ships lie anchored in the"+
        " harbour, loading or unloading goods for the island"+
        " of Gont.\n"); 
    add_exit(THWIL_PIER, "south");
    add_exit(SHIRE_PIER, "east");
    add_exit("../west_stairs", "up");
    add_exit("city_road14", "north");
}
