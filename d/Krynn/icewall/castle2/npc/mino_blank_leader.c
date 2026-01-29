/*Created by Macker 10/20/94 */
/* Slight modification by Igneous to include my claws */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>
#include <ss_types.h>

inherit MIN_BASE
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Krynn/std/patrol";
inherit "/d/Krynn/open/auto_teaming";

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

    set_stats(({175, 175, 175, 125, 125, 170}));  
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_WEP_AXE, 90); 
    set_skill(SS_AWARENESS, 100);

    set_all_hitloc_unarmed(45);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a " +
      "red article of clothing.");

    set_alarm(2.0,0.0,"arm_me");
    set_alarm(2.0,0.0,"form_team");
    set_exp_factor(165);
    /*  Exp boost due to highly damaging combat special. Fighting
	a team of minotaurs makes the tanker loose health much 
	more quickly then usual                                    */


    start_patrol();
    set_pick_up_team(({"minotaur"}));
    set_patrol_time(35);
    set_patrol_path(({"n","emote glances out through an outward " +
	"archers' slit.","n","n","e","emote glances out " +
	"through the outward archers' slit.", "emote grumbles: Damn ice.",
	"e", "s", "s", "emote glances out through an outward archers' slit.", 
	"s", "emote stretches his muscular arms, obviously bored", 
	"n", "say After the Highlord fried the " +
	"last courier, the white dragonarmy humans no longer " +
	"come here.", "n","n", "w", "emote curses: Ice " +
	"will soon swallow this castle!", "w", "s", "s",
	"emote yawns: Next shift will be here soon.", "s" }));

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


void
arm_me()
{
    object claw;

    if (!random(2))  
    {
	::arm_me();
	return;
    }

    setuid(); seteuid(getuid());
    set_skill(SS_UNARM_COMBAT, 90);
    map(TO->query_combat_object()->query_attack_id(), TO->cr_reset_attack);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_righthanded();
    claw->move(TO);
    claw = clone_object(PLAINS_O + "claw");
    claw->set_lefthanded();
    claw->move(TO);
    command("wear claws");
}
