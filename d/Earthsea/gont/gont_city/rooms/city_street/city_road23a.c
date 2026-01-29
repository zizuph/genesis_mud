#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";
inherit "/d/Earthsea/gont/gont_city/rooms/tower_climb";

#include "city_tells.h"

private object sneaker, *smugglers = allocate(4);

public void
reset_room()
{
    object to = this_object();
    int i = random(4);

    while(i--)
    {
        if(!objectp(smugglers[i]))
        {
            smugglers[i] = clone_object(
                "/d/Earthsea/gont/gont_city/liv/smuggler"
            );
            smugglers[i]->move(to);
            smugglers[i]->command("emote sneaks in.");
            smugglers[i]->command("hide");
        }
    }

    if(!sneaker)
    {
        sneaker = clone_object(
            "/d/Earthsea/gont/gont_city/liv/sneaking_smuggler"
        );
        sneaker->move(to);
        sneaker->command("hide");
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
    set_short("Below the steep cliff");
    set_long("The quay ends and the cobbled road"+
        " continues just a few meters from the grey water"+
        " of the secluded bay of Gont Port. Here the beach"+
        " is very rocky, preventing any boats from"+
        " anchoring, making this area feel more peaceful"+
        " compared to the rest of the harbour. Looking"+
        " out over the basin to the northwest you can see"+
        " numerous ships anchored by the three major piers"+
        " and on the other side of the bay the towers and"+
        " stone buildings of the city. A steep cliff is"+
        " blocking your way to the southwest, with a high"+
        " stone tower built on top of it.\n");
    add_item("stairway","The narrow stairway is cut"+
        " out from the rock and seems to be the only"+
        " way to get up to the tower above. You would not"+
        " want to ascend these stairs with hostile archers"+
        " above.\n");
    add_item("beach","The beach is different here, with"+
        " sharp rocks preventing any boat from anchoring."+
        " Just outside the rocks the grey water looks deep"+
        " and cold, with its surface rippled by the fresh"+
        " breeze coming in from the south.\n");
    add_item("rocks","Large rocks make up the beach"+
        " here, most of them sharp and irregular in shape.\n");
    add_item("water","The grey water looks deep and"+
        " very cold, with small waves rippling its surface,"+
        " created by the fresh breeze coming in from the"+
        " south.\n");
    add_item("masts","Looking out over the grey water"+
        " you can see hundreds of masts swaying back and"+
        " forth in the rhytm of the small waves rippling"+
        " the surface.\n");
    add_item(({"harbour","bay","basin"}),
        "The grey water of the harbour of Gont Port is"+
        " stretches out to the northwest, with numerous ships"+
        " and smaller crafts coming from all over the"+
        " Archipelago anchored by the three big piers."+
        " A forest of masts sway gently back and forth"+
        " in the rhytm of the small waves.\n");
    add_item("ships","Anchored by the three major"+
        " piers are many ships of different types. You"+
        " see sloops and caravels, together with long"+
        " boats and galleys.\n");
    add_item("crafts","Smaller crafts lie anchored"+
        " in shallow water close to the side of the"+
        " quay going around the whole bay, or simply"+
        " pulled up on the sandy beach below. These seem"+
        " to be mostly fishing boats.\n");
    add_item(({"entrance","canal"}),"The entrance to the bay is"+
        " a narrow canal leading between the two Armed"+
        " Cliffs towering up high above it.\n");
    add_item("cliff","This steep cliff is one of the"+
        " famous Armed Cliffs, towering up high above"+
        " the narrow canal leading inside"+
        " the secluded bay. You can see a tall stone tower"+
        " built on top of it.\n");
    add_item("tower","The stone tower"+
        " loom over the narrow entrance of the bay, guarding it"+
        " against every intruder. You can see the white"+
        " flag of the lord of Gont flying above them.\n");
    add_item("piers","Numerous ships lie anchored by"+
        " the three major piers stretching out into the"+
        " bay from the north, east and west. The busy"+
        " East Pier is some distance to the north.\n");
    add_exit("city_road23", "north");
    set_next_up("/d/Earthsea/gont/gont_city/rooms/karg_tower/cliff1");
    set_next_down("at_bottom");
    reset_room();
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
