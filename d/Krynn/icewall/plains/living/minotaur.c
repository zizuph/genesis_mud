/*Created by Macker 10/20/94 */

#include "/d/Krynn/icewall/local.h";
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
    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_adj(adjlist[(random(sizeof(adjlist)))]);
    set_long("This minotaur is as strong and evil-looking as any. " +
	     "His sharp curved horns make you wonder what in the " +
	     "world you're doing in the same room as him.\n");
    set_stats(({100, 80, 95, 80, 40, 100}));
    set_skill(SS_WEP_AXE, 70);
    set_all_hitloc_unarmed(30);
    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");
    
    set_alarm(2.0,0.0,"arm_me");
}


void
team_up(object leader)
{
    leader->team_join(TO);
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

