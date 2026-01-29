/*
* North part of the harbour.
*
* Coded by Porta 971122.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

private object *sailors = allocate(3);

public void
reset_room()
{
    int i = random(3);

    while(i--)
    {
        if(!objectp(sailors[i]))
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

    for(i = 0; i < 2; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("North of a long pier");
    set_long("The road continues along the edge of"+
        " the harbour basin, busy with sailors and workers"+
        " loading and unloading the numerous ships anchored"+
        " by the north pier stretching out far into the"+
        " bay here. Looking out over the water, you can"+
        " see a forest of masts of the ships anchored in"+
        " Gont Port swaying slowly back and forth in the"+
        " rhythm of the small waves. Beyond the way stand two"+
        " high cliffs guarding the narrow canal leading"+
        " between them. Just to the north is a low wooden"+
        " building with a sign over the door. You hear"+
        " laughter and song inside.\n");
    add_item(({"basin","bay","water"}),"The harbour"+
        " basin of the great Port of Gont stretches"+
        " out to the south, with waves rippling its"+
        " grey surface. Anchored by the three big"+
        " piers are numerous ships, with a forest"+
        " of masts swaying back and forth slowly.\n");
    add_item("ships","You see many ships anchored"+
        " by the three major piers coming from all"+
        " over the Archipelago. There are galleys,"+
        " sloops and caravels together with many"+
        " other types, all here for the trading"+
        " opportunities.\n");
    add_item(({"pier","piers"}),
        "There are three major piers"+
        " in this harbour, stretching out into the"+
        " bay from the east, west and north. You are"+
        " standing at the edge of the north pier.\n");
    add_item("cliffs","Two high granite cliffs tower"+
        " up high above the south end of the harbour"+
        " basin, guarding the narrow canal leading"+
        " out to the ocean outside.\n");
    add_item("building","Through the dirty windows"+
        " you can see people moving and the light from"+
        " a fire. You think it must be one of the"+
        " taverns serving the harbour workers and"+
        " sailors frequenting this area of the city.\n");
    add_item(({"sailors","workers"}),"Sailors and"+
        " workers pass by in all directions, busy loading"+
        " and unloading ships anchored by the north pier,"+
        " or just on a leave exploring the harbour of"+
        " Gont City.\n");
    add_item(({"masts","forest"}),"You see hundreds"+
        " of masts of the ships anchored in Gont Port,"+
        " slowly swaying back and forth in the sea"+
        " breeze.\n");
    add_item("sign","The sign reads:\n"+
        " The Seaside tavern.\n");
    add_cmd_item("sign","read","The sign reads:\n"+
        " The Seaside Tavern.\n");
    add_exit("../north_pier1", "south");
    add_exit("../tavern", "north");
    add_exit("city_road18", "east");
    add_exit("city_road16", "west");
    reset_room();
}
