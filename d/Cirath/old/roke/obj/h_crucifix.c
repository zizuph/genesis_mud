/*
 * h_crucifix.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  A nice crucifix belonging to van Helsing.
    coded by Calonderiel 930906               */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

void
create_object()
{
    set_name("crucifix");
    set_adj("small");
    set_short("small crucifix");
    set_long("This is a most holy crucifix.\n");

    seteuid(getuid(TO));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, "@@steal_me");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 5000);
}

string
query_recover()
{
    return MASTER;
}

void
init()
{
    add_action("brandish", "brandish");
}

int
brandish(string str)
{

    object *enemys = environment(TO)->query_enemy(-1);
    object holy;
    int i;
    notify_fail("Brandish what?\n");
    if (str == "crucifix")
    {
        for (i = 0; i < sizeof(enemys); i++)
            if (enemys[i]->query_guild_name_occ() == "Vampyr guild")
            {
                if (!present("crucifix", enemys[i]))
                {
                    holy = clone_object(ROKEDIR + "obj/h_scare_him");
                    holy->move(enemys[i]);
                    holy->activate();
                }
                if (present(enemys[i], environment(environment(TO))))
                {
                    tell_room(environment(enemys[i]),
                              QCTNAME(environment(TO)) +
                              " brandishes a small crucifix!\n", enemys[i]);
                    enemys[i]->catch_msg("Suddenly " +
                                         QCTNAME(environment(TO)) +
                                         " reaches out and touches your " +
                                         "forehead with something.\n");
                    enemys[i]->add_panic(400);
                    enemys[i]->run_away();
                }
            }
        return 1;
    }
    return 0;
}

string
steal_me()
{
    write("Someone is trying to steal your crucifix. \n");
    return "The crucifix resists all your clumsy attempts to steal it!\n";
}
