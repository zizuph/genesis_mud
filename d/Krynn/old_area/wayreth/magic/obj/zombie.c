/*
 * A zombie used by the spells
 */

#include "/d/Krynn/common/defs.h";
#include <language.h>

#define STAT (base_stat + random(base_stat))

inherit "/d/Krynn/wayreth/magic/obj/summoned";

public void
create_summoned()
{
    set_name("zombie");
    add_name("animated");
    set_long("It is a corpse of rotting flesh. The flesh is putrid. " +
	     "Its power of locamotion must come from some unnatural " +
	     "evil magic.\n");

    set_m_in("follows its master");
    set_m_out("goes after its master");

    add_prop(LIVE_I_UNDEAD, 65);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
}

public void
init_spell(object caster, object target, object prev)
{
    object summoned;
    string unique_name;
    int base_stat;

    unique_name = caster->query_real_name() + "_master_animated";

    if (summoned = present(unique_name, E(caster)))
    {
        write("You can't control another animated creature.\n");
	remove_object();
        return;
    }

    if (summoned = present("corpse", E(caster)))
    {
        set_name(summoned->query_name());
	set_short("zombie of " + LANG_ADDART(summoned->query_race()));
    }

    base_stat = caster->query_skill(query_element()) / 2;

    set_stats(({STAT, STAT, STAT, STAT, STAT, STAT}));
    set_hp(query_max_hp());

    clone_object("/d/Krynn/std/follow")->follow(caster, TO);

    ::init_spell(caster, target, prev);
}

