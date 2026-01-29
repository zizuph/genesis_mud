/**********************************************************************
 * - messenger_base.c                                               - *
 * - This is the base for the messenger                             - *
 * - A Tiny Elven Nymph Dragon                                      - *
 * - There are three messengers, messenger.c, reply_messenger.c,    - *
 * - resend_messenger.c                                             - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "messenger_manager.h"
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_delivery_messenger()
{}
nomask void
create_creature()
{
	set_name(({"dragon", "messenger"}));
	set_race_name("nymph dragon");
	set_adj(({"tiny", "elven", "dragon", "nymph"}));
	set_short("tiny elven nymph dragon");
	set_gender(G_FEMALE);
	add_item(({"tail", "dragon tail", "nymph tail"}),
	"The tiny elven nymph dragon has a nice long tail, "+
	"which she enjoys tickling necks with.\n");
	add_item(({"tail"}), "It is long and had belongs to the "+
	"" + short() + " and she is tickling you with it.\n");
	set_appearance_offset(-150);
	add_prop(CONT_I_WEIGHT, 350);
	add_prop(CONT_I_VOLUME, 350);
	add_prop(LIVE_I_NON_REMEMBER, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able "+
	"to carry anything else but small scrolls.\n");
	create_delivery_messenger();
}

public int
query_knight_prestige()
{
	return -1000;
}

int
query_messenger_id()
{
	return -1;
}

void
remove_messenger()
{
	object env = environment();
	if (env && living(env))
	{
		env = environment(env);
	}
	
	if (env)
	{
		tell_room(env, ({
			"The tiny elven nymph dragon mysteriously "+
			"disappears.\n",
			"The tiny elven nymph dragon mysteriously "+
			"disappears.\n", "" }));
	}
        remove_object();
}

void leave_env(object env, object to)
{
	int id;
	::leave_env(env, to);
	if (env)
	{
		if ((id = query_messenger_id()) >= 0)
		{
			setuid();
			seteuid(getuid());
			MESSENGER_MANAGER->remove_message(id);
		}
		set_alarm(0.0, 0.0, remove_messenger);
	}
}

varargs void write_message(function f, string who)
{
	write("Enter your message.\nOn any line you can give ** "+
	"to end, or ~q to abort the scroll.\n");
	setuid();
	seteuid(getuid());
	clone_object(EDITOR_OBJECT)->edit((who ? &f(, who) : &f()));
}

void
remove_object()
{
	int id;
	if ((id = query_messenger_id()) >= 0)
	{
		setuid();
		seteuid(getuid());
		MESSENGER_MANAGER->remove_message(id);
	}
	::remove_object();
}
