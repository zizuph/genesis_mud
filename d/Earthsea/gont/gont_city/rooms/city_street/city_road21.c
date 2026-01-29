#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

#define CITYPIER1 "/d/Earthsea/ships/avenir_line/east_pier1"

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
    set_short("Just east of a long pier");
    set_long("The road continues along the water's"+
        " edge just east of a long pier stretching out"+
        " far into the grey water of the bay. This is a"+
        " very busy part of the harbour with sailors"+
        " and Gontish harbour workers working hard with"+
        " loading and unloading the numerous ships anchored"+
        " by the pier, and carrying the goods to warehouses"+
        " located to the north and south. To the east is a"+
        " low stone building with a white emblem over"+
        " the door. Northeast a smaller cobbled street"+
        " leads in between the buildings. Looking out over"+
        " the water, you can see many masts swaying back"+
        " and forth in the rhythm of the small waves, and"+
        " further southwards the two high cliffs towering"+
        " above the narrow canal leading into the secluded"+
        " bay. A fresh breeze comes in from the south bringing"+
        " a smell of the sea.\n");
    add_item("building","To the east is a small stone"+
        " building with an official looking white emblem"+
        " over it.\n");
    add_item("emblem","The white emblem is the official"+
        " symbol of the Lord of Gont.\n");
    add_item("masts","Looking out over the grey water"+
        " you can see hundreds of masts swaying back and"+
        " forth in the rhytm of the small waves rippling"+
        " the surface.\n");
    add_item("warehouses","Low wooden buildings line"+
        " the east side of the road north and south of here,"+
        " probably warehouses of some kind. Harbour workers"+
        " and sailors are busy carrying goods to and from"+
        " the warehouses and ships anchored by the East"+
        " Pier.\n");
    add_item(({"harbour","bay","basin","water"}),
        "The grey water of the harbour of Gont Port is"+
        " stretches out to the west, with numerous ships"+
        " and smaller crafts coming from all over the"+
        " Archipelago anchored by the three big piers."+
        " A forest of masts sway gently back and forth"+
        " in the rhytm of the small waves.\n");
    add_item(({"sailors","workers"}),"Sailors dressed"+
        " in exotic clothes together with Gontish harbour"+
        " workers are busy unloading one of the ships"+
        " anchored by the East Pier, passing by you"+
        " carrying boxes and sacks over their shoulders."+
        " They seem to take the goods to buildings north"+
        " and south of here.\n");
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
    add_item("cliffs","These steep cliffs are the"+
        " famous Armed Cliffs, towering up high above"+
        " the narrow canal leading inside"+
        " the secluded bay. Each of the"+
        " cliffs has a stone tower on top.\n");
    add_item(({"tower","towers"}),"The stone towers"+
        " loom over the narrow entrance of the bay, guarding it"+
        " against every intruder. You can see the white"+
        " flag of the Lord of Gont flying above them.\n");
    add_item("piers","Numerous ships lie anchored by"+
        " the three major piers stretching out into the"+
        " bay from the north, east and west. You can step"+
        " out on the East Pier if you go west.\n");
    add_exit("../e_cliff4", "southeast");
    add_exit(CITYPIER1, "west");
    add_exit("../harbour_capt", "east");
    add_exit("city_road33", "south");
    add_exit("city_road20", "north");
    add_exit("city_road28", "northeast");
    reset_room();
}
