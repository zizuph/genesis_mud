/*Created by Macker 10/20/94 */
/* Slight modification by Igneous to include my claws */
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

    set_all_hitloc_unarmed(60);
    set_aggressive(1);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");
    add_act("say Noone goes there before Hrun says you can!");
    add_act("say I'll gut whoever breaks Hrun orders first!");
    add_act("Whatever lives up there, we'll get it sooner or later");
    add_act("emote looks expectantly at the stairs and says: Hrun " +
      "should be coming soon now.");
    add_act("command gaze out through outward slit");
    add_act("command gaze out through inward slit");


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
