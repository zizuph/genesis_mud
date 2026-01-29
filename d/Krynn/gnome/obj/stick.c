/* Created by Dajala
 * Part of the sign-quest
 * This file holds the build-routines
 */ 

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"

create_object()
{
	set_short("stick");
	set_adj("round");
	add_adj("wooden");
	set_long(BS("A round wooden stick. One end is thinner than the "
		+ "other one. Generally it looks quite old. It's about "
		+ "1m in length.", 70));
	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 500);
	add_prop(OBJ_I_VALUE, 0);
	set_name("stick");
	add_name("stick_for_sign");
}

init()
{
	::init();
	ADD("construct_sign", "construct");
	ADD("construct_sign", "build");
	ADD("construct_sign", "fix");
	ADD("assemble_sign", "assemble");
}

void
do_construct()
{
	object obj;
	seteuid(getuid(TO));
	(present("nail_for_sign", TP))->remove_object();
	(present("board_for_sign", TP))->remove_object();
	write(BS("You sit down, nail the board to the stick "
		+ "and get something that resembles a sign. "
		+ "Somehow it looks still incomplete though.", 70));
	say(BS(QCTNAME(TP) + " fabricates something that resembles "
		+ "a sign. But somehow " + PRONOUN(TP) + " doesn't "
		+ "look content with " + POSSESSIVE(TP) 
		+ " work though.", 70));
	obj = clone_object(OBJ + "incomsign");
	obj->move(TP);
}

int
assemble_sign(string str)
{
	NF("What?\n");
	if ((!(P("nail_for_sign", TP))) || (!(P("board_for_sign", TP)))
		|| (!(P("stick_for_sign", TP))))
		return 0;
	NF("Build what with what?\n");
	if(!(P("hammer", TP)))
		return 0;
	NF("Build what?\n");
	if ((str != "parts") && (str != "parts to sign") && (str != "parts of sign"))
		return 0;
	do_construct();
	(P("stick_for_sign", TP))->remove_object();
	return 1;
}

int
construct_sign(string str)
{
	NF("What?\n");
	if ((!(P("nail_for_sign", TP))) || (!(P("board_for_sign", TP)))
		|| (!(P("stick_for_sign", TP))) || (!(P("hammer", TP))))
		return 0;

	NF("Build what?\n");
	if (str != "sign" && str != "sign from parts")
		return 0;
	do_construct();
	(P("stick_for_sign", TP))->remove_object();
	return 1;	
}
