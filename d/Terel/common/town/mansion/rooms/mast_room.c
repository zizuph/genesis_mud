/* This is the long gone master's chamber. Mortricia 920909 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define BSN(message)   break_string(message + "\n", 70)
#define TP             this_player()
#define TO             this_object()

void
create_room()
{
    object door_w, door_n;
    object key, desk;

    set_short("Master's chamber");
    set_long(BSN(
        "This is the chamber where the long gone master of this " +
	"mansion used to go when he wanted some privacy. It's " +
	"rather empty. There is a closet on the northern wall. " +
	"You can go south into another room. On the eastern " +
	"wall a large and bombastic shield has been mounted."
    ));
    add_item(({"shield"}), BSN(
	"The person who wanted this piece of armour nailed to " +
	"the wall most likely lacked sophisticated taste. You " +
	"notice some letters on it: Marquis Avenchir."
    ));
    add_cmd_item("shield", "get", BSN(
	"It's out of reach for you."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "rooms/mast_bed", "south", 0);

    door_n = clone_object(MANSION + "rooms/closet_door2");
    door_n -> move(TO);
    door_n -> set_key(77102);

    door_w = clone_object(MANSION + "rooms/m_door1");
    door_w -> move(TO);
    key = clone_object(MANSION + "rooms/gold_key");
    door_w -> set_key(key -> query_key());

    desk = clone_object(MANSION + "rooms/desk");
    desk -> move(TO);

    key -> move(desk);
}
