inherit "/std/key";

#include "../../local.h"

create_key()
{
    ::create_key();

	set_name("key");
	add_name("_green_twitch_common_key");
    set_adj("short");
    add_adj("latch");
    set_short("short latch key");
    set_pshort("short latch keys");
    set_long("This short, iron key is designed to fit into the keyhole "
	+ "of a latch lock that secures cots in the Green Twitch Inn of "
	+ "Palanthas.\n");

	add_prop("_green_twitch_common_key", 1);
    set_key("green_twitch_common_room_key");
}
