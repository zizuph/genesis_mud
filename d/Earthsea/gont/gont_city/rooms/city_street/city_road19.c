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

    for(i = 0; i < 3; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120); 
    set_short("East part of the harbour");
    set_long("The street continues along the water's"+
        " edge to the east of the harbour basin of Gont"+
        " Port. This is a very busy area with sailors"+
        " and harbour workers passing by carrying boxes"+
        " and sacks from ships on the East Pier to a"+
        " large building on the other side of the road"+
        " looking like a warehouse of some kind. Looking"+
        " out over the grey water of the bay you can see"+
        " numerous ships of all different types"+
        " anchored by the three major piers, together"+
        " with hundreds of smaller crafts anchored by"+
        " the quay side in shallower water. Across"+
        " the bay to the south is the narrow entrance"+
        " to it, guarded by two steep cliffs towering"+
        " up high above it. A smell of sea and fish"+
        " is in the air, and you can feel a salty breeze"+
        " on your skin coming in from the south.\n");
    add_item(({"harbour","bay","basin","water"}),
        "The grey water of the harbour of Gont Port is"+
        " just to the west of you, with numerous ships"+
        " and smaller crafts coming from all over the"+
        " Archipelago anchored by the three big piers."+
        " A forest of masts sway gently back and forth"+
        " in the rhytm of the small waves.\n");
    add_item(({"sailors","workers"}),"Sailors dressed"+
        " in exotic clothes together with Gontish harbour"+
        " workers are busy unloading one of the ships"+
        " anchored by the three piers, passing by you"+
        " carrying boxes and sacks over their shoulders."+
        " They seem to take the goods to a building just"+
        " across the street to the east.\n");
    add_item("ships","Anchored by the three major"+
        " piers are many ships of different types. You"+
        " see sloops and caravels, together with long"+
        " boats and galleys.\n");
    add_item("crafts","Smaller crafts lie anchored"+
        " in shallow water close to the side of the"+
        " quay going around the whole bay, or simply"+
        " pulled up on the sandy beach below. These seem"+
        " to be mostly fishing boats.\n");
    add_item("warehouse","To the east is a warehouse"+
        " built by boards slovenly fit together, leaving"+
        " large gaps between. A constant stream of harbour"+
        " workers and sailors pass through the open"+
        " doors.\n");
    add_item("entrance","The entrance to the bay is"+
        " a narrow canal leading between the two Armed"+
        " Cliffs towering up high above it.\n");
    add_item("cliffs","These steep cliffs are the"+
        " famous Armed Cliffs, towering up high above"+
        " the entrance to the secluded bay. Each of the"+
        " cliffs has a stone tower on top.\n");
    add_item(({"tower","towers"}),"The stone towers"+
        " loom over the narrow entrance, guarding it"+
        " against every intruder. You can see the white"+
        " flag of the lord of Gont flying above them.\n");
    add_item("piers","Numerous ships lie anchored by"+
        " the three major piers stretching out into the"+
        " bay from the north, east and west.\n");
    add_exit("city_road18", "northwest");
    add_exit("city_road20", "south");
    add_exit("../warehouse3", "east");
    reset_room();
}
