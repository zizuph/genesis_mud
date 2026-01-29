#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <state_desc.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <files.h>

inherit "/std/act/action";
inherit M_FILE

string *gAdj1 = ({"green-skinned","warlike","webbed-fingered",
          "savage","fish-like","needle-toothed", "black-spined"});

#define WEP   TOBJ + "spear"
#define QUILL TOBJ + "sahuagin_quill"
#define TRINK TOBJ + "sahuagin_trinkets"
#define PEARL "/d/Genesis/gems/obj/pearl"
#define CORAL "/d/Genesis/gems/obj/coral"

#define SEA_NET_ID "_sea_net_id"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif


public void
check_in_combat()
{
    if (TO->query_attack())    
    {
        float timer = itof(5 + random(10));
        set_alarm(timer, 0.0, &check_in_combat());
        return;
    }

    string ship_name = E(TO)->query_name();

    tell_room(environment(TO), "The " +TO->query_short()+ " leaps " +
        "over the rails of the " +ship_name+ " in to the ocean and disappears.\n");

    tell_room(environment(TO)->query_boat_loc(), "A " +TO->query_short()+ 
        " leaps from the deck of the " +ship_name+ " and disappears in to the " +
        "ocean with a splash!\n");

    set_alarm(0.5, 0.0, &remove_object());
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    string a1 = ONE_OF(gAdj1);

    set_name("sahuagin");
    set_race_name("sahuagin");
    set_adj(a1);
    set_short(a1 + " sahuagin");
    set_gender(random(2));
    set_long("This fish-like monstrous humanoid is a sahuagin, the " +
        "scourge of sailors and fisherman across the seas of Krynn. " +
        "Standing over six feet tall this aquatic race has the head " +
        "of a fish with a mouth full of sharp teeth, a powerful tail " +
        "and a dorsal fin that lends to the name they are commonly " +
        "known as, the shark-people.\n");

    // 124 stat average with a 10% variance.
    int sl = SD_AV_RISING_HERO;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);
    set_hp(10000);
    set_aggressive(1, 100);

    set_alignment(-800);
    set_all_hitloc_unarmed(35); 
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(MAGIC_I_BREATHE_WATER, 100);

    set_skill(SS_WEP_POLEARM, 75 + random(20));
    set_skill(SS_DEFENCE, 80 + random(20));
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75 + random(20));
    set_skill(SS_AWARENESS, 85);

    set_cact_time(8);
    add_cact("emote works itself into a blood frenzy!");
    add_cact("emote gurgles a furious battle cry!");

    set_default_answer("The sahuagin has no interest in talking with its prey!\n");

    add_leftover(QUILL, "quill", 3, "", 0, 0);
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    
    clone_object(WEP)->move(this_object(), 1);
    command("wield all");

    object trinket = clone_object(TRINK);
    trinket->make_the_trinket();
    trinket->move(this_object(), 1);
    command("wear all");

    clone_object(PEARL)->move(this_object(), 1);
    if(random(2))
        clone_object(PEARL)->move(this_object(), 1);
    else
        clone_object(CORAL)->move(this_object(), 1);
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    object * players = FILTER_PLAYER_OBJECTS(all_inventory(environment(killer)));
    players -= ({ killer });
    players = ({ killer }) + players; // ensure killer is first

    foreach (object player : players)
    {
        object net = present(SEA_NET_ID, killer);
        if (!objectp(net))
        {
            continue;
        }
        net->sea_creature_do_die_post_actions(killer);
        break;
    }
    
    ::do_die(killer);
}
