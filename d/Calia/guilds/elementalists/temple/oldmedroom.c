

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

void
create_room()
{
    set_short("Old focus and contemplation chamber");
    set_long("You have entered the old focus chamber of the temple. "+
        "A single white candle inside of a candle box still provides "+
        "a dim soft glow for the entire room even though it was "+
        "abandoned long ago. Here in the centre of the room you "+
        "see a single silver altar, much like the one in the main "+
        "chamber. The walls are a pale white colour and appear to "+
        "be solid blocks of stone. The ground is covered in soft, "+
        "evenly cut green grass. There is a small archway in the "+
        "north wall heading back out to the old bed chamber, "+
        "and an exit leading southwards.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);

    add_item(({"candle","box"}),"It is a small white candle inside of "+
        "a candle box. The light from the candle bathes the room with "+
        "a soft white glow.\n");

    add_item("altar","A small silver altar rests in the middle of this "+
        "chamber.\n");

    add_item(({"walls","wall","stone","stones","block","blocks"}),
        "The walls are made from large blocks of perfect, evenly "+
        "cut pieces of pale white coloured stones.\n");

    add_item(({"grass","ground"}),"The entire ground of this chamber "+
        "is covered by a soft green grass.\n");

    add_item("archway","The archway is carved into the north wall, and "+
        "leads back into the old bed chamber.\n");

    add_exit(ELEMENTALIST_TEMPLE+"oldstartroom", "north",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldestiroom","south",0,1);
}
