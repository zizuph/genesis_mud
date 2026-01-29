/* Ashlar, 19 Jul 97
   This is a spellcasting medallion worn by spellcasting NPC's -
   it cannot be used by players, for them it is just a medallion
   of evil
*/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>

inherit "/std/armour" armourObj;
inherit "/d/Krynn/open/spellsystem/spellcasting.c" spellObj;

/*
 * special functions usable by npc spells
 */

public object *
find_dead_object(string str)
{
    object *targets;

    targets = FIND_STR_IN_OBJECT(str, query_caster()) +
              FIND_STR_IN_OBJECT(str, E(query_caster()));

    targets = targets - filter(targets, living);

    if (!sizeof(targets))
    {
        write("You can't seem to locate " + str + " here.\n");
        return 0;
    }
    return ({ targets[0] });
}

#include "spells/pidentify.c"

int
query_spell_mess(string verb, string arg)
{
    if (!TP->query_npc())
        return 0;

    write("You clutch your " + short() + " in your hand.\n");
    tell_room(E(TP),QCTNAME(TP) + " clutches " + HIS(TP) + " " +
        short() + " in " + HIS(TP) + " hand.\n", TP);
    return 1;
}

int
spell_fail()
{
	object c;
	c = query_caster();
	if (c && c->query_npc())
		c->spell_failed();
	return 0;
}

void
create_armour()
{
    set_name("medallion");
    add_name("takhisis_medallion");
    add_adj("black");
    set_long("The medallion is a plain disc of metal, blackened, and " +
        "inscribed with a life-like carving of a five-headed dragon.\n");
    set_ac(1);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,850);

    add_spell("pidentify",do_pidentify,"Identify");
}


void
leave_env(object env, object to)
{
    armourObj::leave_env(env, to);
    spellObj::leave_env(env, to);

    remove_spell("pidentify");
}

void
enter_env(object env, object from)
{
    armourObj::enter_env(env, from);
    spellObj::enter_env(env, from);
}
