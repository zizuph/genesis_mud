#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <state_desc.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/act/action";

inherit M_FILE

string *gAdj1 = ({"huge", "four-armed", "towering",
          "black-scaled","mutated","powerful", "shark-like"});

#define WEP   TOBJ + "trident"
#define QUILL TOBJ + "sahuagin_quill"
#define ARROW TOBJ + "baron_quill"
#define TRINK TOBJ + "sahuagin_trinkets"
#define PEARL "/d/Genesis/gems/obj/pearl"
#define BLACK_PEARL "/d/Genesis/gems/obj/pearl_black"

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
    add_name("baron");
    set_race_name("sahuagin");
    set_adj(a1);
    set_short(a1 + " sahuagin baron");
    set_gender(random(2));
    set_long("This monstrous mutated sahuagin towers over its " +
        "brethren at almost 9 feet in height! But even more " +
        "fearsome is its four functional arms, allowing it " +
        "to easily establish itself physically in the warlike " +
        "hierarchy of these shark-people.\n");

    // 154 stat average with a 10% variance.
    int sl = SD_AV_TITAN;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);
    set_hp(10000);
    set_aggressive(1, 100);

    // Natural armour, decent weapon, 
    // aggressive, can see in the dark, require swim skill to get to.
    set_exp_factor(115);

    set_alignment(-800);
    set_all_hitloc_unarmed(45); 
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(MAGIC_I_BREATHE_WATER, 100);

    set_skill(SS_WEP_POLEARM, 85 + random(15));
    set_skill(SS_DEFENCE, 80 + random(20));
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75 + random(20));
    set_skill(SS_AWARENESS, 85);

    set_cact_time(8);
    add_cact("emote works itself into a blood frenzy!");
    add_cact("emote gurgles a furious battle cry!");

    set_default_answer("The sahuagin has no interest in talking with its prey!\n");

    add_leftover(QUILL, "quill", 2, "", 0, 0);
    add_leftover(ARROW, "long quill", 1, "", 0, 0);
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
    // 5% chance of a black pearl
    if(random(20))
        clone_object(PEARL)->move(this_object(), 1);
    else
        clone_object(BLACK_PEARL)->move(this_object(), 1);
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

