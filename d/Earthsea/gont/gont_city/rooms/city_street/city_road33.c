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
    set_short("East part of the harbour area");
    set_long("The cobbled road continues along the"+
        " water's edge just east of the grey water of"+
        " the harbour basin, where numerous ships are"+
        " anchored by the three major piers. A forest"+
        " of masts sway back and forth in the small"+
        " waves created by the fresh breeze coming in"+
        " from the south. This is a busy street, with"+
        " dark-skinned harbour workers and sailors"+
        " dressed in exotic clothes carrying sacks and"+
        " crates to a wooden warehouse to the east from"+
        " a large trader anchored by the pier just north"+
        " of here. Fairly close to the south you can see"+
        " two steep cliffs towering high above the narrow"+
        " canal leading inside the secluded bay.\n");
    add_item("waves","The water surface is rippled"+
        " with small waves, created by the fresh breeze"+
        " blowing in from the south.\n");
    add_item("warehouse","Just to the east is a busy"+
        " warehouse with its wide double doors standing"+
        " open to allow the sailors and harbour workers"+
        " passage through with heavy sacks and crates on"+
        " their shoulders. It is built by boards slovenly"+
        " fitted together to leave large gaps open.\n");
    add_item("masts","Looking out over the grey water"+
      " you can see hundreds of masts swaying back and"+
      " forth in the rhythm of the small waves rippling"+
      " the surface.\n");
    add_item("trader","The boat being unloaded is a"+
      " large galley, probably coming from the west"+
      " part of the Archipelago. It has at least one"+
      " hundred openings for oars on each side.\n");
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
      " flag of the lord of Gont flying above them.\n");
    add_item("piers","Numerous ships lie anchored by"+
      " the three major piers stretching out into the"+
      " bay from the north, east and west. The busy"+
      " East Pier is just to the north.\n");
    add_exit("../warehouse4", "east");
    add_exit("city_road22", "south");
    add_exit("city_road21", "north");
    reset_room();
}
