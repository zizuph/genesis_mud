/*
* Room in the harbour of Gont Port
*
* Coded by Porta 971016
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

    for(i = 0; i < 3; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("West side of the harbour");
    set_long("You are at the west side of the busy"+
        " harbour of Gont Port, with a perfect view over the secluded"+
        " bay and the two large cliffs to the southeast"+
        " guarding the entrance to the basin. Looking out over"+
        " the bay you see a forest of masts of all kinds of"+
        " ships swaying back and forth in rhythm with the"+
        " waves coming in. There are several large wooden"+
        " buildings by the shore, probably warehouses"+
        " belonging to one of the many merchant companies"+
        " located in this city. It is very crowded here,"+
        " with sailors and"+
        " harbour workers working or just walking around"+
        " and a smell of sea is in the air.\n");
    add_item("harbour","This harbour is the largest"+
        " on the whole island of Gont, and where most of"+
        " the imported goods arrive. You see many ships"+
        " coming from all parts of the Archipelago.\n");
    add_item("bay","The harbour is located in a small"+
        " natural bay, with a narrow entrance between"+
        " the fabled Armed Cliffs.\n");
    add_item("cliffs","These two cliffs are the famous"+
        " Armed Cliffs of Gont Port, looming high over each"+
        " side of the narrow entrance to the harbour basin."+
        " There is a tower built on each cliff, adding to"+
        " the impression of a fortress.\n");
    add_item("masts","The many masts of the ships"+
        " anchored in the harbour sway back and forth in"+
        " harmony with the small waves finding their ways in"+
        " through the narrow entrance to the bay.\n");
    add_item(({"tower","towers"}),"There is a high"+
        " tower built on each of the Armed Cliffs, from where"+
        " defendants of the city can easily keep enemy ships"+
        " from entering the harbour.\n");
    add_item("ships","Many ships and boats from all over"+
        " the Archipelago are anchored here. There are large"+
        " galleys, fast sloops and numerous smaller fishing"+
        " boats.\n");
    add_item(({"warehouses","buildings"}),"The buildings"+
        " here are large wooden houses, built from boards. You" +
        " believe they are warehouses for one or another of the"+
        " merchant companies trading with this city. Some of"+
        " the warehouses are currently open, with harbour"+
        " workers walking in and out carrying sacks or heavy"+
        " crates to or from a ship.\n");
    add_item("sailors","The sailors are often dressed in"+
        " exotic clothes, showing they are not originating"+
        " from this city, but you can also see an occasional"+
        " dark-skinned Gontish seafarer.\n");
    add_item("workers","The workers are mostly men from Gont"+
        ", muscular from carrying heavy loads day out and day"+
        " in.\n");
    add_exit("city_road14", "south");
    add_exit("city_road8", "northwest");
    add_exit("city_road10", "northeast");
    add_exit("../warehouse1", "north");
    reset_room();
}
