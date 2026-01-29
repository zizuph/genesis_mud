/*Created by Macker 10/20/94 */
// updated by Boron,may 2/03 to give more resistance...

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
      "world you're doing in the same room. He is " +
      "one of the White Dragon Highlord's personal bodyguards.\n");

    set_stats(({160, 160, 200, 110, 110, 150}));
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_WEP_AXE, 80);
    set_skill(SS_AWARENESS, 100);


    set_aggressive(1);
    set_all_hitloc_unarmed(60);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(40);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red article of clothing.");
    add_act("say Hrun will lead an expedition up the glacier. " +
      "There is something living out there...");
    add_act("say They say it sounded like a bird of pray.");
    add_act("say Can't be a bird. The shape was too large.");
    add_act("emote glances out through the slit, impatient.");
    add_act("say I'll kill it quick, whatever it is up there!");
    add_act("Lets go up there ourselves, before Hrun gets around " +
      "to earning all the prestige for the kill again!");
    add_act("command gaze out through outward slit");
    add_act("command gaze out through inward slit");


    set_alarm(2.0,0.0,"arm_me");
    set_exp_factor(165);
}


void
team_up(object leader)
{
    leader->team_join(TO);
}

public void
assist_minotaur(object enemy)
{
    object *friends;
    int    size, i;
    
    friends = filter(all_inventory(environment(TO)),
        &operator(==)("minotaur") @ &->query_race_name());
    friends = filter(friends, not @ &->interactive());    
    friends = filter(friends, not @ &->query_attack());
    
    if ( size = sizeof(friends) )
    {
        for ( i = 0; i < size; i++)
        {
            friends[i]->help_friend(enemy);
        }
    }
    
}

public void
hook_attacked(object enemy)
{
    set_alarm(1.0, 0.0, &assist_minotaur(enemy));    
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

