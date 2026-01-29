#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <state_desc.h>
#include <const.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/act/action";
inherit M_FILE
inherit "/lib/unique";


string *gAdj1 = ({"cruel", "golden-scaled", "malevolent",
          "black-scaled","evil","merciless", "bloodthirsty"});

#define BLADE       TOBJ + "hornblade"
#define WEP         TOBJ + "spear"
#define QUILL       TOBJ + "sahuagin_quill"
#define GOLD_QUILL  TOBJ + "gold_quill"
#define TRINK       TOBJ + "sahuagin_trinkets"
#define PEARL       "/d/Genesis/gems/obj/pearl"
#define BLACK_PEARL "/d/Genesis/gems/obj/pearl_black"

#define SEA_NET_ID "_sea_net_id"

#define MANA_SHADOW          ("/d/Genesis/specials/guilds/shadows/mana_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define STD_KRYNN_SPELLS     ("/d/Krynn/std/generic_spell_soul")

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

object wep;

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
    add_name("priestess");
    set_race_name("sahuagin");
    set_adj(a1);
    set_gender(G_FEMALE);
    set_short(a1 + " sahuagin priestess");
    set_long("This is a feared sahuagin priestess, a worshipper " +
        "of the malevolent sea goddess known as the Darkling Sea. " +
        "Bloodthirsty and unforgiving, this priestess are responsible " +
        "for calling her people to the surface to slaughter the crews " +
        "of ships and decimating coastal villages in raids.\n");

    // 169 stat average with a 10% variance.
    int sl = SD_AV_CHAMPION;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);
    set_hp(10000);
    set_aggressive(1, 100);

    // Natural armour, decent weapon, powerful harm spell special (150 caid),
    // aggressive, can see in the dark, require swim skill to get to.
    set_exp_factor(160);

    set_alignment(-800);
    set_all_hitloc_unarmed(45); 
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(MAGIC_I_BREATHE_WATER, 100);

    set_skill(SS_WEP_POLEARM, 85 + random(15));
    set_skill(SS_DEFENCE, 80 + random(20));
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75 + random(20));
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_SPELLCRAFT, 85 + random(15));
    set_skill(SS_ELEMENT_WATER, 85 + random(15));
    set_skill(SS_FORM_CONJURATION, 85 + random(15));

    set_cact_time(8);
    add_cact("emote works itself into a blood frenzy!");
    add_cact("emote gurgles a furious battle cry!");
    add_cact("emote calls out to the Darkling Sea for aid!");

    set_default_answer("The sahuagin has no interest in talking with its prey!\n");

    add_leftover(QUILL, "quill", 3, "", 0, 0);
    
    if(a1 == "golden-scaled")
        add_leftover(GOLD_QUILL, "golden quill", 1, "", 0, 0);

    // Set up spells
    clone_object(MANA_SHADOW)->shadow_me(TO);
    add_cmdsoul(STD_KRYNN_SPELLS);
    add_cmdsoul(SPELL_MANAGER_SOUL);
    update_hooks();
}

void
arm_me()
{
    seteuid(getuid(this_object()));

    wep = clone_unique(BLADE, 15, WEP);    
    wep->move(this_object(), 1);
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

/* Function name: special_attack
 * Description  : The priestess special attack spell.
 */
int
special_attack(object enemy)
{
    int attacktype = random(6);

    if(attacktype > 1)
        return 0;

    command("toxicblast");
    return 1;
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
