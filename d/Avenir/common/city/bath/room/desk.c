#pragma strict_types
/*
 * ~/desk.c
 *
 * Desk to obtain keys for the private rooms.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Grace,  Aug 1994: ?.
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h" 
inherit BATH_ROOM;

static void
create_bath_room(void)
{
    set_short("Reception");
    set_long("This is a simple, restful room painted in watery "+
	"tones of blue and green. A strip of carpeting leads "+
	"from double doors to a marble-topped counter behind "+
	"which a doorway can be seen to the north.  The air "+
	"is noticeably warm and moist. There is a sign on the "+
	"east wall.\n"); 
    add_item(({"carpet", "carpeting", "floor"}),
	"A thick sand-coloured carpet stretches across the "+
	"chequered marble floor.\n");
    add_item(({"counter", "marble" }),
	"A long marble counter stretching the length of the room.  "+
	"In order to exit to the north you must go past it.\n");
    add_item("doorway",
	"This opening leads further into the bath house.\n");
    add_item("sign",
	"A heavy wooden sign with ornate script.\n");

    add_cmd_item("sign", "read",
	"Welcome to Melchior's Bath House.\n"+
	"Enjoy the pleasant company and peaceful setting "+
	"at your leisure.\n"+
	"It is stamped with the seal of the Hegemon.\n");
    add_cmd_item("counter", "touch",
	"It is smooth and cool to the touch.\n");

    add_exit(BATHRM + "corr", "north");
    add_exit(BATHRM + "hall", "south");
    add_exit(BATHRM + "post", "west");

    add_npc(BATH + "npc/stos", 1, &->equip_me());
}
