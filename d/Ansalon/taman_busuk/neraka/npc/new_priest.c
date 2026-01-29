/* Ashlar, 30 Aug 97
 * a priest npc
 *
 * 2004-06-28 - Cotillion
 * Removed the repeating alarm that was used to check if the npc should
 * heal.
 *
 * Louie April 2006 - Granted guardians of the temple see invis/darkness.  
 *      Add ptalon to spells known for priest npcs.  
 *      Boosted stats/skills significantly.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include "/d/Ansalon/guild/pot/spells.h"
#include "/d/Ansalon/guild/pot/obj/living/npc.h"
#include <money.h>

inherit "/d/Ansalon/guild/pot/obj/living/npc";
inherit AUTO_TEAM

#define ARM2 NARM + "crescent_shield"
#define ARM3 NARM + "black_chain_shirt"
#define WEP1 NWEP + "mace1h"

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define ADJ1    ({ "slender", "tall", "weathered", })
#define ADJ2    ({ "dark-haired", "swarthy", "brown-haired", })
#define RACE    ({ "human", "half-elf" })




object pouch, needle, nails, eyes;

void arm_me();

void
create_pot_monster()
{
    if(!IS_CLONE)
	return;

    set_name("priest");
    add_name("_new_priest_");

    set_pick_up_team(({"_new_priest_"}));
    
    set_race_name(ONE_OF(RACE));
    set_adj(ONE_OF(ADJ1));
    add_adj(ONE_OF(ADJ2));
    set_long("This " + query_race() + " seems confident in his own " +
    "abilities, despite the evident lack of fighter training.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({
        115 + random(10),
        140 + random(10),
        150 + random(10),
        115 + random(10),
        115 + random(10),
        200 + random(20)
    }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          85);
    set_skill(SS_DEFENCE,           85);
    set_skill(SS_PARRY,             75);
    set_skill(SS_AWARENESS,         85);
    set_skill(SS_SPELLCRAFT,        100);
    set_skill(SS_ELEMENT_LIFE,      100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_AIR,      100);
    set_skill(SS_FORM_DIVINATION,   75);
    set_skill(SS_FORM_ENCHANTMENT,  100);
    set_skill(SS_FORM_ABJURATION,   75);
    set_skill(SS_FORM_TRANSMUTATION, 75);
    set_skill(SS_HERBALISM, 100);
    add_prop(LIVE_I_SEE_INVIS, 20);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_skill(PS_GUILD_LEVEL, 200 + random(100));
    set_skill(PS_SPELLS, PBLIND_ID | PSLOW_ID | PTALON_ID);

    set_all_hitloc_unarmed(10);

    set_alignment(-950);
    set_knight_prestige(950);
    set_max_team_size_auto_join(3);

    set_aggressive("@@check_for_attack@@");
    set_introduce(0);
}

int
check_for_attack()
{
    return TP->query_prop(NERAKA_I_ATTACKED_TEMPLE);
}


void dispel_me(object me)
{
    if(me->query_attack() || me->query_enemy(-1))
    {
        set_alarm(900.0, 0.0, &dispel_me(me));
        return;
    }
    tell_room(environment(me), QCTNAME(me)+" leaves.\n");
    me->remove_object();
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

void
arm_me()
{

    setuid();
    seteuid(getuid(this_object()));

    clone_object(WEP1)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);


    pouch = clone_object("/d/Ansalon/guild/pot/obj/comp_pouch");

    for(int i = 0; i < 10; i++)
    {
        clone_object("/d/Krynn/common/herbs/bch_willow")->move(pouch, 1);
        clone_object("/d/Krynn/common/herbs/tiger_lily")->move(pouch, 1);
    }

    needle = clone_object("/d/Ansalon/guild/pot/obj/needle");
    needle->add_prop(OBJ_M_NO_STEAL, 1);
    needle->move(this_object(), 1);
 
    nails = clone_object("/std/leftover");
    nails->leftover_init("nail", "human");
    nails->set_heap_size(10);
    nails->move(pouch, 1);

    eyes = clone_object("/std/leftover");
    eyes->leftover_init("eye", "human");
    eyes->set_heap_size(10);
    eyes->move(pouch, 1);

    TO->add_prop("_i_have_money", 1);
    TO->add_prop("_obj_m_has_money", 1);
    MONEY_MAKE_GC(30)->move(pouch, 1);

    pouch->move(this_object(), 1);
 
    command("wear all");
    command("wield all");
    set_alarm(900.0, 0.0, &dispel_me(this_object()));
    ::arm_me();
}

int
is_team_enemy(object o)
{
    if (member_array(o->query_attack(), query_team_others() + ({ TO })) >= 0)
        return 1;
    else
        return 0;
}

int
special_attack(object enemy)
{
    int enemy_health;
    int is_blinded, is_slowed, is_pained;
    object *enemies;

    if (query_prop(LIVE_I_CONCENTRATE))
        return 0;

    is_blinded = objectp(P(BLIND_ID,enemy));
    is_slowed  = objectp(P(SLOW_ID,enemy));
    is_pained  = objectp(P(PAIN_ID,enemy));


    if(!is_blinded)
    {
        command("pblind " + enemy->query_real_name());
        eyes = clone_object("/std/leftover");
        eyes->leftover_init("eye", "human");
        eyes->set_heap_size(10);
        eyes->move(pouch, 1);
        MONEY_MAKE_GC(1)->move(pouch, 1);
        return 0;
    }
    
    if (!is_slowed)
    {
        command("pslow " + enemy->query_real_name());
        clone_object("/d/Krynn/common/herbs/tiger_lily")->move(pouch, 1);
        enemy->add_fatigue(-50);
        return 0;
    }

    command("ptalon " +enemy->query_real_name());
    clone_object("/d/Krynn/common/herbs/bch_willow")->move(pouch, 1);
    nails = clone_object("/std/leftover");
    nails->leftover_init("nail", "human");
    nails->set_heap_size(1);
    nails->move(pouch, 1);
    add_mana(50);
    return 0;
}
