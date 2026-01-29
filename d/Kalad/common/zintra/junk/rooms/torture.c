inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short("Torture Chamber");
    set_long(BS(
"This room in itself is not very impressive.  What is impressive, however, " +
"is the collection of torture devices here, all in very good condition.  " +
"There is a rack, an iron maiden, and many shackles designed to keep victims" +
" from running away.  There is also a forge here, used to heat branding " +
"irons.  The dungeon proper lies to the south.\n"));

    add_exit(G_ROOMS + "dungeon", "south", 0);

    add_item(({"iron maiden", "maiden"}), BS("The iron maiden is closed.\n"));

    add_item("rack", BS(
"A simple device, but effective.  An individual is strapped to the rack, " +
"and is literally pulled apart by turning a wheel attached to the straps.  " +
"On the rack at this moment is a very strong-looking elf.  Heh heh heh.  " +
"Now's your chance to have some fun.\n"));

    add_item("wheel", BS(
"This wheel is very large, to provide the touque needed to stretch an " +
"individual strapped to the rack.  It looks as if it turns very " +
"easily.\n"));

    add_item("shackles", BS(
"Some are empty, some are not.  There is a skeleton hanging from one set, " +
"on the eastern wall.\n"));

    add_item("skeleton", BS(
"One of the more fortunate victims in the room.  Someone must have forgot " +
"to remove it.  It seems to provide hope for the others in the room who " +
"long for the release of death.\n"));

    add_item("forge", BS(
"This forge is used to heat irons.  There are a couple in the forge at this " +
"moment.  Im sure you could use them to 'burn' one of the victims in the " +
"room.\n"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "No, no, no!  Play a bit, first.\n");
    add_prop(ROOM_M_NO_ATTACK, "But there are better ways to hurt your " +
        "victims.\n");
    room_add_object(G_MON + "mystic");
    room_add_object(G_MON + "calian");
    room_add_object(G_MON + "knight");
}








