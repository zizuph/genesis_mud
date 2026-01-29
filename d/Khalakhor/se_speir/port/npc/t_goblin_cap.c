/*
 * t_goblin_cap.c
 *
 * The leader of the goblin scouts, not really much more impressive
 * than the others in size or stats, but is the one who holds the most
 * damning piece of evidence against the fishmonger.
 * 
 * Khail - April 4/97
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
#include "../invade_quest.h"

inherit STDGOBLIN;

/*
 * Function name: arm_me
 * Description  : Clones in the goblins's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    seteuid(getuid());

    if (!random(2))
        clone_object(WEP + "poor_axe")->move(TO);
    else
        clone_object(WEP + "poor_dirk")->move(TO);
    command("wield all");
    clone_object(ARM + "poor_targe")->move(TO);
    clone_object("/d/Khalakhor/common/arm/breeches")->move(TO);
    clone_object("/d/Khalakhor/common/arm/bracers_hard_leather")->move(TO);

    command("wear all");
}

/*
 * Function name: setup_adjectives
 * Description  : Generates two random adjectives for the
 *                goblin.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
setup_adjectives()
{
    set_adj(({"large","ugly","flatulent","dull","hairy","imposing",
        "muscular","hideous"})[random(8)]);
    add_adj(({"brutal","nasty","smelly","one-eyed","arrogant",
        "cruel","bruised"})[random(7)]);
}

/*
 * Function name: reset_monster
 * Description  : Makes sure the goblin has the monger warning every
 *                reset.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_khalakhor_goblin()
{
    reset_euid();

    if (!present(INVADE_QUEST_WARN_NAME))
        clone_object(OBJ + "monger_warning")->move(TO, 1);
}

/*
 * Function name: create_monster
 * Description  : Turns this object into a goblin.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_goblin()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name("monster");
    add_name(TUNNEL_GOBLIN);
    setup_adjectives();
    set_long("This goblin doesn't look a whole lot more impressive " +
        "than any of the others down here, but the manner in which " +
        "he carries himself seems to indicate he holds a higher " +
        "status than the others.\n");

    default_config_npc(27 + random(5));
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_WEP_AXE, 30);
    set_skill(SS_WEP_KNIFE, 30);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-(200 + random(200)));

    set_act_time(15);

    set_alarm(0.5, 0.0, reset_monster);
    set_alarm(0.0, 0.0, arm_me);
    set_random_size_descs();
}
