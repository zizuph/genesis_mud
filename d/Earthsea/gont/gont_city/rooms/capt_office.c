#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define CAPTAIN "/d/Earthsea/gont/gont_city/liv/captain"
#define DOOR "/d/Earthsea/gont/gont_city/obj/office_in"

private object captain;

public void
reset_room()
{
    if(!captain)
    {
        captain = clone_object(CAPTAIN);
    }

    captain->command("emote marches off.\n");
    captain->move(this_object(), 1);
    captain->command("emote enters.");
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Office of the Captain of the Guard");
    set_long("You are standing in a room "+
        "enclosed on all four sides by stone walls. "+
        "Narrow slits in the north wall allow some light to enter. "+
        "The walls are made of black stone "+
        "carefully fitted together without mortar. There is "+
        "a large oak desk with a leather padded chair "+
        "in the center of the room loaded "+
        "down with stacks of papers and scrolls. A narrow "+
        "camp cot is set against the west wall. A large map "+
        "of Gont covers the south wall.\n");
    add_item((({"map", "large map"})),
      "You see the map of the island of Gont nailed up on "+
      "the south wall.\n");
    add_item((({"desk", "oak desk", "papers", "scrolls"})),
      "Many papers and scrolls cover the desk, and you know that "+
      "whoever works here is very busy.\n");
    add_item((({"chair", "leather chair", "padded chair"})),
      "The chair is the only item of luxury in this building.\n");
    add_item((({"cot", "camp cot"})),
      "A hard-looking camp cot is where the Captain sleeps.\n");
    add_item((({"beds", "bunk beds"})),
      "These are hard cots that the mercenaries sleep on.\n");
    add_item((({"stone", "black stone", "walls", "floor",
        "granite flagstones", "flagstones"})),
        "The walls and floor are made of the same dark rock as "+
        "the city walls.\n");
    add_prop(ROOM_I_INSIDE, 1);
    setuid();
    seteuid(getuid());
    clone_object(DOOR)->move(this_object());
    reset_room();
}
