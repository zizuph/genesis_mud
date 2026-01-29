inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_suspect_room()
{
    add_exit(MINAS_DIR+"houses/citizens/h2r2","north",0,0);

    set_door_id("MT_h2_n3crc1");
    set_door_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MINAS_DIR+"n3crc1");
    set_door_desc(BSN("This wooden door is battered from long use. The "
      + "construction is sturdy, but old, and the gouges and chips in the "
      + "door show that it has not been well maintained."));

    set_suspect(1);
    set_wealth(0);
    set_side("north");
    set_circle("First Circle");

    set_short("main room");
    set_long(BSN(
        "This is the main room of the citizen's house. It sports a well used "
      + "dining table in the middle with some chairs arranged around it. "
      + "There is a small wood-stove in the corner and a square window "
      + "cut into the wall. A passage leads north into a darker room, and "
      + "a wooden door leads out of the house to the south."));
    add_item(({"table","dining table"}), BSN(
        "This table is rather old and of mediocre construction. The wood "
      + "bears many stains and is marred by the normal course of years of "
      + "use. This seems to be the only table in the dwelling, so you presume "
      + "that it serves also as a writing surface."));
    add_item(({"chairs","wooden chairs"}),BSN(
        "These chairs are arranged carefully around the table, six in all. "
      + "They are the only visible chairs and double as dining chairs and "
      + "recreational chairs. They, too, are old, but better maintained than "
      + "the table. Two of the chairs have some worn cloth patched over the "
      + "seats."));
    add_item(({"stove","wood stove"}),BSN(
        "This cylindrical metal stove heats the house and provides a "
      + "secondary cooking surface. A woodbox sits next to the stove, and "
      + "some tongs rest against the wall."));
    add_item(({"woodbox","box"}),BSN(
        "This large, iron-bound box holds the wood which fuels the stove. "
      + "The wood is stacked neatly within it and halfway fills the box."));
    add_item(({"tongs","iron tongs"}),BSN(
        "These iron tongs rest casually against the wall. The many scrapes "
      + "in the floor beneath the tongs indicate that this is their keeping "
      + "place, and that they sit here for lack of a rack rather than "
      + "laziness. The tongs have wooden handles to insulate the holder "
      + "from the heat which might conduct up the iron shaft."));
    add_item(({"shutters","wooden shutters","shutter","wooden shutter"}),BSN(
        "These wooden shutters are banded with iron to reinforce them. You "
      + "get the impression that they are as much to keep people out as they "
      + "are to keep the weather out."));

    add_window("There are weathered wooden shutters fastened on hinges " +
        "on the frame of the window to keep the elements at bay.");
    add_walls("The walls bear marks where the dining chairs have scraped " +
        "them.");
    add_ceiling("It is hard to make out in the dim light from the window.");
    add_floor("Upon the floor is some food from a recent meal.");
}
