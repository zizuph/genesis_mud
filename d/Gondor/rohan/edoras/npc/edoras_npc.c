/*
 *	/d/Gondor/rohan/edoras/npc/edoras_npc.c
 *
 *	Standard npc for Edoras
 *	Including citizens and guards
 */
inherit "/std/monster";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/edoras/defs.h"

void
create_edoras_npc()
{
    set_name("citizen");
    set_title("Citizen of Edoras");
}

nomask void
create_monster()
{
    create_edoras_npc();

    add_name("_edoras_npc");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (!interactive(ob))
        return;

    // We only remember the attacks on goodies
    if (query_alignment() > 0)
        ob->add_prop(EDORAS_I_DID_ATTACK,
                     ob->query_prop(EDORAS_I_DID_ATTACK) + 1);
}

/*
 * Function name:   query_nonmet_name
 * Description:     Gives the name of this living to players who have not met
 *                  this living. E.g.: "big fat gnome wizard"
 * Returns:         The name of the living when unmet.
 */
public string
query_nonmet_name()
{
    string *adj, str = "";

    if (sizeof((adj = this_object()->query_adj(1))) > 0)
        if (sizeof(adj) >= 2)
            str = adj[0] + " " + adj[1] + " ";
        else
            str = adj[0] + " ";

    str += this_object()->query_gender_string() + " "
         + this_object()->query_race_name();

    return str;
}

public void
do_die(object killer)
{
    int n;
    if (interactive(killer))
    {
        n = killer->query_prop(LIVE_I_KILLED_ROHIRRIM) + 1;
        killer->add_prop(LIVE_I_KILLED_ROHIRRIM, n);
        if (n > 10)
            EDORAS_MASTER->add_enemy(killer, "several Rohirrim");
    }
    ::do_die(killer);
}
