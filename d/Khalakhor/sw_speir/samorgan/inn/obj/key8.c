/**********************************************************************
 * - key8.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>
#include "../inn.h"

inherit "/std/key";

void
create_key()
{
	set_name("key");
	add_name(({"inn key", "key8", "room key"}));
	add_name("_samorgan_room_key");
	set_adj("brass");
	add_adj("small");
	set_short("small brass key");
	set_long("A small brass key.  The numeral '8' is engraved on "+
	"the head of the key. Do not forget to <check out> when done.\n");
	set_key(KEY8);
	add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to do "+
	"that.\n");
	add_prop(OBJ_M_NO_GIVE, "You must return the key to the "+
	"innkeeper.\n");
	add_prop(OBJ_I_WEIGHT, 10);
	add_prop(OBJ_I_VOLUME, 25);
	add_prop(OBJ_I_VALUE, 1000);
}

void
check_environment()
{
	if (!living(environment()))
	{
		tell_room(environment(), "The key drops to the floor "+
		"and is quickly returned to the innkeeper by a "+
		"chambermaid.\n");
		remove_object();
	}
}
