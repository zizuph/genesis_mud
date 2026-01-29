/*
 *	/d/Gondor/pelargir/npc/pelargir_npc.c
 *
 *	Standard npc for Pelargir
 *	Including citizens and guards
 */
inherit "/std/monster";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/defs.h"

void
create_pelargir_npc()
{
    set_name("citizen");
    set_title("Citizen of Pelargir");
}

nomask void
create_monster()
{
    create_pelargir_npc();

    add_name("_pelargir_npc");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (!interactive(ob))
        return;

    // We only remember the attacks on goodies
    if (query_alignment() > 0)
        ob->add_prop(PEL_I_DID_ATTACK,
                     ob->query_prop(PEL_I_DID_ATTACK) + 1);
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

