/* Added a timetable - Tapakah, 05/2009 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define HARBOUR_CAPTAIN "/d/Earthsea/gont/gont_city/liv/harbour_captain"
#define TIMETABLE "/d/Earthsea/gont/gont_city/obj/timetable"

private object harbour_captain;

public void
reset_room()
{
    if(!objectp(harbour_captain))
    {
        harbour_captain = clone_object(HARBOUR_CAPTAIN);
        harbour_captain->move(this_object(), 1);
        harbour_captain->command("emote strolls in.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Harbour Captain's office");
    set_long("This looks like the office of "+
        "someone very busy, as you can see from the heaps of "+
        "paperwork lying on the oak desk that stands in the "+
        "middle of the room with a chair behind. Among the paper "+
        "clutter on the desk you see a sculpture of a dolphin "+
        "carved from driftwood. A map is nailed on the wall "+
        "with different coloured pins denoting ships that come "+
        "regularly to the Port of Gont.\n");
    add_item((({"dolphin", "sculpture", "driftwood sculpture"})),
        "You see a sculpture of a dolphin leaping out of the "+
        "sea, which was perhaps carved by some traveller in "+
        "payment for the harbour captain's services.\n");
    add_item((({"desk", "oak desk", "papers", "paperwork", "heaps"})),
        "Tons of paperwork lie heaped on the harbour captain's desk, "+
        "and you know that this one is a very busy person.\n");
    add_item("chair", "The chair behind the desk is for "+
        "the harbour captain to sit on while he attends to "+
        "the paperwork.\n");
    add_item((({"wall", "map", "map of the docks"})),
        "The map on the wall shows the harbour with coloured "+
        "pins for the different shipping lines.\n");
    add_item("passageway", "It leads west out into the "+
        "busy street.\n"); 
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("city_street/city_road21", "west");
    reset_room();
    add_object(TIMETABLE);
}
