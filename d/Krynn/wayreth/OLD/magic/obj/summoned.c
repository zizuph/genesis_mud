/*
 * This is the standard code for summoned monsters.
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

object gMaster;

public void
create_summoned()
{
}

nomask public void
create_krynn_monster()
{
    create_summoned();
}

public void
notify_dispel_magic(object dispel)
{
    if (TO->id("summoned"))
        tell_room(E(TO), QCTNAME(TO) + " flees...\n");
    else if (TO->id("animated"))
        tell_room(E(TO), QCTNAME(TO) + " crumbles to dust!\n");
    else if (TO->id("conjured"))
        tell_room(E(TO), QCTNAME(TO) + " disappears...\n");
    else
        tell_room(E(TO), QCTNAME(TO) + " fades away...\n");
}

nomask public void
my_heart_beat()
{
    object enemy;

    if (!gMaster)
    {
        dispel_magic();
        return;
    }

    enemy = gMaster->query_attack();

    if (enemy)
    {
        if (enemy == TO)
        {
	    dispel_magic();
            return;
	}
        if (enemy != query_attack())
	    command("kill " + enemy->query_real_name());

	if (enemy->query_attack() == TO)
	    enemy->attack_object(gMaster);
    }
    else
        if (enemy = query_attack())
	{
	    tell_room(E(TO), QCTNAME(TO) + " stops fighting.\n");
	    stop_fight(enemy);
	    enemy->stop_fight(TO);
	}
}

public void
init_spell(object caster, object target, object prev)
{
    gMaster = caster;

    this_object()->move(environment(gMaster));

    if (TO->id("summoned"))
        tell_room(E(TO), QCNAME(TO) + " arrives in a flurry.\n");
    else if (TO->id("animated"))
        tell_room(E(TO), QCTNAME(TO) + " starts to move!\n");
    else if (TO->id("conjured"))
        tell_room(E(TO), QCNAME(TO) + " appears in a flash of light.\n");
    else
        tell_room(E(TO), QCNAME(TO) + " arrives.\n");

    set_alarm(1.0, 1.0, "my_heart_beat");
}






