/*Created by Macker 10/20/94 */

#include "/d/Krynn/icewall/local.h";
#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>
#include <ss_types.h>

inherit "/std/act/domove";
inherit "/std/act/action";

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
    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_long("This minotaur is as strong and evil-looking as any. " +
      "His sharp curved horns make you wonder what in the " +
      "world you're doing in the same room. He is " +
      "one of the White Dragon Highlord's personal bodyguards, " +
      "and right now keeps watch on the battlements.\n");

    set_stats(({160, 160, 160, 110, 110, 150}));  
    set_skill(SS_PARRY, 65);
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_WEP_AXE, 80); 


    set_all_hitloc_unarmed(35);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");
    add_act("emote peers out through an archers' slit.");
    add_act("emote yawns, bored.");

    set_alarm(2.0,0.0,"arm_me");
    set_exp_factor(165);
    /*  Exp boost due to highly damaging combat special. Fighting
	a team of minotaurs makes the tanker loose health much 
	more quickly then usual                                    */

}


void
team_up(object leader)
{
    leader->team_join(TO);
}


arm_me()
{
    string * weplist = (({PLAINS_O + "taxe",
	LAKE_O + "minoaxe"}));

    object wep;
    seteuid(getuid(TO));
    wep = clone_object(weplist[(random(sizeof(weplist)))]);
    wep->move(this_object());
    command("wield weapon");
}


string
query_crash()
{
    return("snowdrift");
}

