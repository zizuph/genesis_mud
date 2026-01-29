/*Created by Macker 10/20/94 */
/* Slight modification by Igneous to include my claws */

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
      "world you're doing in the same room as him.\n");
    set_monster_home(ICE_PLAINS + "plain_1.c");
    set_restrain_path("/d/Krynn/icewall/");
    set_random_move(20 + random(10));

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");

    set_alarm(2.0,0.0,"arm_me");
}

object
query_folk_here()
{
    int i = 0;
    object *allhere;
    allhere = FILTER_LIVE(all_inventory(E(TO)));
    while(implode((allhere[i])->query_adj(1), " ") != "ice folk")
    {
	if((i+1)>= sizeof(allhere))
	    return 0;
	else
	    i += 1;
    }
    return(allhere[i]);
}


public void
init_attack()
{
    object folk;

    if((implode(TP->query_adj(1), " ") == "ice folk")&&
      (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
	set_alarm(1.5, 0.0, "aggressive_attack", TP);
    folk = query_folk_here();
    if((interactive(TP))&&(folk))
	set_alarm(1.5, 0.0, "aggressive_attack", folk);

    return(::init_attack());
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
    set_skill(SS_UNARM_COMBAT, 75);
    map(TO->query_combat_object()->query_attack_id(), TO->cr_reset_attack);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_righthanded();
    claw->move(TO);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_lefthanded();
    claw->move(TO);
    command("wear claws");
}
