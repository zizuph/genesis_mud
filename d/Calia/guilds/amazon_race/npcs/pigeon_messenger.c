/*
 *    pigeon_messenger.c  
 *
 * A pigeon messenger. Inheriting the Genesis standard one
 * and altering the description slightly
 *
 * Baldacin@Genesis, Feb 2004
 *
 */

inherit "/d/Genesis/obj/pigeon";

void
create_creature()
{
	::create_creature();
	set_short("grey carrier pigeon");
	remove_adj("white");
	add_adj("grey");
}