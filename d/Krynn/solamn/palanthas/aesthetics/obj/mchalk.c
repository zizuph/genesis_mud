/* 
 * Taken from the piece of chalk for the Cabal of Hiddukel.
 * Adapted for sale in large, commercial form at general
 * EQ store in Aesthetics quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/object";
inherit "/lib/keep"; 

#include "../../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>

#define CH_MAX_WRITING      100
#define CH_MAX_LENGTH       120
#define CHALK_MESSAGE       "There is writing on the " + where + " here.\n"

int ch_length;

void
create_object()
{
   set_name("stick of chalk");
   set_pname("sticks of chalk");
   add_name("chalk");
   add_name("stick");
   set_short("stick of chalk");
   set_pshort("sticks of chalk");
   set_long("@@my_long");
   
   ch_length = CH_MAX_LENGTH;

   add_prop(OBJ_I_VALUE, "@@my_value");
   add_prop(OBJ_I_WEIGHT, 40);
   add_prop(OBJ_I_VOLUME, 150);
   set_keep(1);
}

void
init()
{
	ADA("write");
}

int
my_value()
{
	return ch_length + 30;
}

string
my_long()
{
	string str;

	if (ch_length == CH_MAX_LENGTH)
		str = "It looks brand new";

	else if (ch_length > CH_MAX_LENGTH * 13 / 15)
		str = "It looks almost unused";

	else if (ch_length > CH_MAX_LENGTH * 10 / 15)
		str = "It looks used";

	else if (ch_length > CH_MAX_LENGTH * 6 / 15)
		str = "It looks well used";

	else if (ch_length > CH_MAX_LENGTH * 2 / 15)
		str = "It is rather short";

	else if (ch_length > 0)
		str = "It is merely a stub";

	else
		str = "There is nothing left to write with, just a chalk holder "
		+ "ring";
	
	return "Held in a small, flat wooden ring at its base is a large stick "
	+ "of chalk with which you may <write>.  " + str + ".\n";
}

// The chalk is there to write.  We write something.
int
write(string str)
{
	int dummy;
	string where;
	object writing_obj;
	object here = E(TP);

	NF("You must be holding the chalk in order to write with it.\n");
	if (E(TO) != TP)
		return 0;

	NF("It is too dark to see.\n");
	if (!CAN_SEE_IN_ROOM(TP))
		return 0;

	NF("Write what?\n");
	if (!str)
		return 0;

	NF("You are not able to write here.  If there is already a message "
	+ "here, try erasing it first.\n");
	if (!here)
		return 0;
 
	where = (here->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");

	if (member_array(CHALK_MESSAGE, here->query_desc()) != -1)
		return 0;

	if (here->query_prop(ROOM_I_NO_EXTRA_DESC))
		return 0;

	NF("There isn't enough space here to write such a long message.\n");
	if (strlen(str) > CH_MAX_WRITING)
		return 0;

	if (strlen(str) > ch_length)
		str = extract(str,0,ch_length);

	seteuid(getuid(TO));

	ch_length -= strlen(str);
	where = (here->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");

	TP->catch_msg("You write a message on the " + where + ".\n");
	
	dummy = random(CH_MAX_LENGTH * 3) - ch_length + (CH_MAX_LENGTH / 4);

	if (ch_length <= 0)
		TP->catch_msg("Hmmm, you used all the chalk, there is nothing left "
		+ "but the chalk holder.\n");

	else if (dummy < 0)
	{
		TP->catch_msg("Oops! The stick of chalk breaks. It is much shorter "
		+ "now.\n");

		ch_length += dummy;

		if (ch_length <= 0)
			TP->catch_msg("Hmmm, in fact there is nothing left anymore.\n");
	}

	writing_obj = clone_object(MONKS + "obj/mwriting_obj");
	writing_obj->set_writing_text(str, where);
	writing_obj->move(here);
	writing_obj->initiate_self_destruct();

	say(QCTNAME(TP) + " bends down and writes something on the "
	+ where + ".\n");

	here->add_my_desc(CHALK_MESSAGE, writing_obj);

	if (ch_length <= 0)
		set_alarm(3.0,0.0,"remove_object");

	return 1;
}
