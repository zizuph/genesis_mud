/* Adapted by Mortis 10.2005
 *
 * Ashlar, 25 Jul 97 - The place where stabled horses are kept.
 */

#include "../local.h"

inherit NOBLE_BASE;

create_palan_room()
{
	set_short("The livery's stable");
	set_long("This is where horses are kept.\n");

	add_prop(ROOM_I_ALLOW_STEED,1);
	add_exit(NOBLE + "livery.c","out");
}

