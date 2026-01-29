// updated by Boron,may 2/03 to give more resistance...

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>
#include <ss_types.h>

inherit MIN_BASE

void
create_minotaur()
{
    string str;
    string * adjlist = ({ "savage", "brutal", "mean", "violent",
      "ugly", "wild", "ruthless", "deadly", "devastating",
      "destructive", "aggressive", "mutilating", "large", "massive",
      "hulking", "scarred", "stalky", "hairy", "muscular",
      "huge" });


    remove_adj("huge");
    set_adj("dominant");
    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_long("This minotaur is as strong and evil-looking as any. " +
      "His sharp curved horns make you wonder what in the " +
      "world you're doing in the same room. This warrior " +
      "had proven his skill and loyalty repeatedly, and thus was " +
      "chosen to serve in the castle of the White Dragon Highlord, " +
      "and ranks over the other minotaurs.\n");

    set_stats(({175, 175, 200, 125, 125, 170}));
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_AWARENESS, 100);

    set_aggressive(1);

    set_all_hitloc_unarmed(60);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");

    set_alarm(2.0,0.0,"arm_me");
    set_alarm(2.0,0.0,"form_team");
    set_exp_factor(170);
}


void
form_team()
{
    object *others;
    others = FILTER_OTHER_LIVE(all_inventory(E(TO)));
    others = others - ({TO});
    others->team_up(TO);
    return;
}


string
query_crash()
{
    return("snowdrift");
}

void
arm_me()
{
    object claw;

    if (!random(3))  // 33% chance an axe is cloned.
    {
	::arm_me();
	return;
    }

    setuid(); seteuid(getuid());
    set_skill(SS_UNARM_COMBAT, 100);
    map(TO->query_combat_object()->query_attack_id(), TO->cr_reset_attack);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_righthanded();
    claw->move(TO);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_lefthanded();
    claw->move(TO);
    command("wear claws");
}
