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


string *gAdj1 = ({"mysterious", "silver-skinned", "graceful",
          "heavily-scaled","brooding","suspicious", "black-haired"});

#define WEP         SOBJ + "spear"
#define MAG_WEP     "/d/Ansalon/goodlund/bloodsea/obj/azure_spear"
#define TRINK       SOBJ + "triton_trinkets"
#define PEARL       "/d/Genesis/gems/obj/pearl"
#define BLACK_PEARL "/d/Genesis/gems/obj/pearl_black"

#define SEA_NET_ID "_sea_net_id"
#define ATTACKED_TRITONS "_attacked_courrain_tritons"

#define MANA_SHADOW          ("/d/Genesis/specials/guilds/shadows/mana_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define STD_KRYNN_SPELLS     ("/d/Krynn/std/generic_spell_soul")

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void make_trinket();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    string a1 = ONE_OF(gAdj1);

    set_name("triton");
    add_name("sorcerer");
    add_name("leader");
    set_race_name("triton");
    set_adj(a1);
    set_short(a1 + " triton sorcerer");
    set_gender(random(2));
    set_long("This aquatic creature is a triton sorcerer. Rumoured " +
        "to have originated from the Elemental Plane of Water, " +
        "their torso, head, and arms look like those of " +
        "silvery-skinned humans, with the lower half of their " +
        "bodies scaled and blue and their legs finned. Tritons " +
        "are notoriously protective of their territory, and " +
        "tend to have little love for land dwellers in general.\n");

    // 169 stat average with a 10% variance.
    int sl = SD_AV_CHAMPION;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);
    set_hp(10000);

    // Natural armour, decent weapon, powerful harm spell special (150 caid),
    // aggressive, can see in the dark, require swim skill to get to.
    set_exp_factor(160);

    set_alignment(800);
    set_all_hitloc_unarmed(45); 
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(MAGIC_I_BREATHE_WATER, 100);
    add_prop(OBJ_I_RES_WATER, 75);

    set_skill(SS_WEP_POLEARM, 85 + random(15));
    set_skill(SS_DEFENCE, 80 + random(20));
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 75 + random(20));
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_SPELLCRAFT, 85 + random(15));
    set_skill(SS_ELEMENT_WATER, 85 + random(15));
    set_skill(SS_FORM_CONJURATION, 85 + random(15));

    set_cact_time(18);
    add_cact("emote swims around you in a frenzy!");
    add_cact("emote gestures aggressively towards you.");

    set_default_answer("The triton has no interest in engaging " +
        "with a land dweller!\n");

    equip(({ clone_unique(MAG_WEP, 9, WEP), 
        (random(20) ? PEARL : BLACK_PEARL ) }));

    // Set up spells
    clone_object(MANA_SHADOW)->shadow_me(TO);
    add_cmdsoul(STD_KRYNN_SPELLS);
    add_cmdsoul(SPELL_MANAGER_SOUL);
    update_hooks();

    set_alarm(0.5, 0.0, &make_trinket());
}

void
make_trinket()
{
    seteuid(getuid(this_object()));

    object trinket = clone_object(TRINK);
    trinket->make_the_trinket();
    trinket->move(this_object(), 1);
    command("wear all");
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

    command("steamblast");
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

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_TRITONS))
        ob->add_prop(ATTACKED_TRITONS, 1);
}

void
attack_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    command("kill " +enemy->query_name());
    enemy->add_prop(ATTACKED_TRITONS, 1);

    return;
}

void
warn_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(enemy->id("triton"))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    int message = random(10);

    switch(message)
    {
        case 0:
            command("emote looks at you with alarm.");
            break;
        case 1:
            command("say Leave our waters land dweller!");
            break;
        case 2:
            command("emote raises a hand in warning.");
            break;
        case 3:
            command("emote indicates you should return to " +
                "the surface.");
            break;
    }

    set_alarm(15.0, 0.0, &attack_enemy(enemy));

    return;
}

void
init_living()
{
    if(this_player()->query_prop(ATTACKED_TRITONS))
    {
        set_alarm(1.5, 0.0, &attack_enemy(this_player()));
    }
    else
    {
        set_alarm(1.5, 0.0, &warn_enemy(this_player()));
    }

    ::init_living();
}
