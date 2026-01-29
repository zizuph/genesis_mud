/*
 */
#pragma strict_types

inherit "/std/spells";
inherit "/d/Gondor/common/guild/spells/spell_funs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/spells/rest.c"

public void spell_used(object pl);

public void
create_spells()
{
    set_name("Rest_Spell_Object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
    add_spell("rest", "one_rest", "Make someone less fatigued");
}

public int
one_rest(string str)
{
    set_alarm(2.0, 0.0, &spell_used(this_player()));
    do_rest_spell(str);
    return 1;
}

public void
spell_used(object pl)
{
    pl->catch_msg("You feel the words of the spell slipping from your mind.\n");
    this_object()->remove_object();
}

public int
query_skill_needed()
{
    return 15;
}

