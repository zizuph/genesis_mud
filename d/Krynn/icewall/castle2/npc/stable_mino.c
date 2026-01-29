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
      "world you're doing in the same room as him. He is " +
      "one of the White Dragon Highlord's personal bodyguards. " +
      "Today, he has drawn the short straw, and thus, the " +
      "warehouse duty. He doesn't look too pleased about it.\n");

    set_stats(({180, 160, 200, 100, 100, 150}));
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_AXE, 80);


    set_all_hitloc_unarmed(60);
    set_aggressive(1);
    add_prop(LIVE_I_SEE_DARK, 2);

    set_act_time(80);
    add_act("emote snorts violently.");
    add_act("emote unrolls the links of a heavy chain, as if " +
      "preparing it for use.");
    add_act("emote repeatedly hammers a three feet long solid iron " +
      "bolt into the wall. The wall shakes, and echo resounds " +
      "throughout the castle.");
    add_act("emote attaches a heavy chain to a bolt hammered into " +
      "the wall.");
    add_act("emote tugs on a manacle to check the lock.");
    add_act("say The Highlord has a good plan.");
    add_act("say The griffons will prove useful mounts... though " +
      "no minotaur would use magic to subjugate them. Good old " +
      "methods are the best. Club and whip, I say, and we'll get " +
      "them trained and docile as lap dogs.");
    add_act("say I hope the Highlord knows what he's doing... " +
      "If his spells backfire, we'll have a heap of angry feathers " +
      "on our hands.");
    add_act("emote grunts with satisfaction.");
    add_act("Seeing the work here, I wish I was send to actually " +
      "catch the beasts.");

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

