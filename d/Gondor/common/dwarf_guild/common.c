/*
 * /d/Gondor/common/dwarf_guild/common.c
 *
 * This is the common board cave. You will find the common board here.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define BOARD "/d/Genesis/obj/board"

void
create_room()
{
    set_short("the common board cave of the " + DWARVEN_RACE_GUILD_NAME);
    set_long(BSN("This cave is rather small. There is a small opening " +
	"in which you can see some strange beams of light. These beams " +
	"seem to connect the bulletin board in this cave with the rest " +
	"of the world. The construction was crafted by magic a long time " +
	"ago. It makes sure that this board always contains the most " +
	"recent postings. To the east is the exit of this cavern."));

#include "cavedesc.h"

    add_item( ({ "chimney", "opening" }),
	BSN("The opening is the beginning of a chimney. The chimney is " +
	"only two inches in diameter and in it you see the white light."));
    add_item( ({ "beam", "beams", "light", "beams of light", "white light" }),
	BSN("In the chimney you see beams of white light. The light is " +
	"rather strong and you do not peer straight into the light for it " +
	"might do harm to your eyes."));

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "east");

    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_NO_ATTACK,       1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    clone_object(BOARD)->move(TO, 1);
}
