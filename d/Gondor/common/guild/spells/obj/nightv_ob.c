/*
 * The spellobject for the 'nightvision' spell.
 */
#pragma strict_types

inherit "/std/spells.c";
inherit "/d/Gondor/common/guild/spells/spell_funs.c";

#include "/d/Gondor/common/guild/spells/nightvision.c"

public  void    spell_used(object pl);

public void
create_spells()
{
    set_name("Nightvision_Spell_Object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
    add_spell("nightvision", "one_nv", "Gain vision in darkness outside");
}

public int
one_nv(string str)
{
    set_alarm(2.0, 0.0, &spell_used(this_player()));
    do_nightvision_spell(str);
    return 1;
}

public void
spell_used(object pl)
{
    if (!pl->query_prop(RANGER_NIGHTVISION)) 
    {
        pl->catch_msg("You feel the words of the spell slipping from your mind.\n");
	this_object()->remove_object();
    }
    else 
        set_alarm(10.0, 0.0, &spell_used(pl));
}

public int
query_skill_needed()
{
    return 15;
}

