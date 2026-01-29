#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../bat_manager.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <files.h>
#include <const.h>


void create_delivery_bat() { }

nomask void
create_creature()
{
    setuid();
    seteuid(getuid());

    set_name("bat");
    set_race_name("bat");
    set_adj("black");
    set_gender(G_NEUTER);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
             "anything else but small messages.\n");
    remove_prop(OBJ_M_NO_GET);

    set_attack_unarmed(1, 5, 5, W_BLUDGEON, 100, "wings");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");

    create_delivery_bat();
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
            "The black bat flies away.\n",
            "The black bat flies away.\n",
            "" }));
    }

    destruct();
}

void leave_env(object env, object to)
{
    int id;

    ::leave_env(env, to);

    if (env)
    {
        if ((id = query_messenger_id()) >= 0)
	{
	    BAT_MANAGER->remove_message(id);
	}

        set_alarm(0.0, 0.0, remove_messenger);
    }
}

varargs void write_message(function f, string who)
{
#if 0
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You can't send out the bat when you're not " +
                "out in open air.\n");
        return;
    }
#endif

    write("Enter your message.\n"
        + "On any line you can give ** to end, or ~q to abort the message.\n");

    clone_object(EDITOR_OBJECT)->edit((who ? &f(, who) : &f()));
}

void
remove_object()
{
    int id;

    if ((id = query_messenger_id()) >= 0)
    {
    	BAT_MANAGER->remove_message(id);
    }

    ::remove_object();
}
