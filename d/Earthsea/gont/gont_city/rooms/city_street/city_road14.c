/* 
* Just west of the West Pier, in Gont City.
*
* Coded by Porta 971017.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

#define CALIA_PIER "/d/Earthsea/ships/calia_line/west_pier1"

private object *sailors = allocate(3);

public void
reset_room()
{
    int i = random(3);

    while(i--)
    {
        if(!sailors[i])
        {
            sailors[i] = clone_object("/d/Earthsea/gont/gont_city/liv/sailor" + (random(5)+1));
            sailors[i]->move(this_object());
            sailors[i]->command("emote swaggers in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    int i;

    for(i = 0; i < 3; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("At the West Pier");
    set_long("This is the southwest end of the harbour,"+
        " just west of a long pier built with sturdy logs"+
        " stretching far out in the bay. Looking out over"+
        " the grey water you can see many ships anchored"+
        " close together with masts swaying back and"+
        " forth in the rhythm of the small waves coming"+
        " in. Southeast is the narrow opening to the"+
        " harbour basin, guarded by two cliffs rising"+
        " steep up from the sea. This is a very busy"+
        " place with harbour workers and sailors milling"+
        " around you, together with travellers from all"+
        " over the Archipelago.\n");
    add_item("pier","The long pier stretches far out"+
        " into the grey water of the bay, built by sturdy"+
        " timber logs and stone, with many ships anchored"+
        " by it.\n");
    add_item(({"bay","basin"}),"The small bay is secluded"+
        " by the city, with the only entrance safely guarded"+
        " by the Armed Cliffs.\n");
    add_item("cliffs","These cliffs are the famous"+
        " Armed Cliffs, standing post on each side of the"+
        " narrow canal leading between them. A high stone"+
        " tower is built on each of the cliffs, with white"+
        " flags flying from the battlements.\n");
    add_item("water","The sea water looks grey and cold,"+
        " with a surface obscured by small waves coming in"+
        " between the cliffs.\n");
    add_item("ships","There are many ships anchored in the"+
        " harbour, coming to trade from all over the Archipelago."+
        " You see galleys, sloops, longboats and many smaller"+
        " crafts.\n");
    add_item(({"workers","sailors"}),"The harbour workers"+
        " are very busy loading and unloading the ships anchored"+
        " by the west pier, while the sailors do their work on"+
        " the ships or just strolling around enjoying the visit"+
        " in Gont Port.\n");
    add_item("travellers","You see men and women dressed in"+
        " exotic clothes pass by or supervise the loading of their"+
        " ships. Many are merchants but there are some adventurers"+
        " as well, seeking fame and fortune in new lands.\n");
    add_item("logs","The logs look very sturdy, bolted far"+
        " down in the bottom of the sea to give support to the"+
        " pier.\n");
    add_exit(CALIA_PIER, "east");
    add_exit("city_road15", "south");
    add_exit("city_road9", "north");
    add_exit("city_road13", "west");
    reset_room();
}
