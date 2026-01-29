/*  An npc in the WoHS test.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Krynn/std/monster";
inherit AUTO_TEAM

#define SWORD "/d/Krynn/guilds/wohs/test/obj/steel_shortsword"
#define ARMOUR "/d/Krynn/guilds/wohs/test/obj/wohs_test_chainmail"
#define LEGGINGS "/d/Krynn/guilds/wohs/test/obj/wohs_test_leggings"
#define HELMET "/d/Krynn/guilds/wohs/test/obj/wohs_test_helmet"
#define GLOVES "/d/Krynn/guilds/wohs/test/obj/wohs_test_gauntlets"
#define CAPE "/d/Krynn/guilds/wohs/test/obj/wohs_test_cape"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define DMG_TAKEN   "_wohs_test_damage_taken"
#define INVADING_SOLDIER   "_wohs_test_invading_soldier"

string *gAdj = ({"black-bearded","young","scarred","noble","muscular",
                      "barrel-chested","blue-eyed"});
void get_me_soul();
int soul_id;

int max_hp;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"serl"}));
    set_max_team_size_auto_join(20);

    set_name("scout");
    set_race_name("human");
    set_adj(ONE_OF(gAdj));
    add_adj("Ergothian");
    set_short(implode(query_adjs()," ") + " scout");
    set_gender("G_MALE");
    set_long("Before you stands a scout of the Ergothian imperial "+
        "army, a soldier that preceeds the main force - gathering "+
        "intelligence of the battlefield or enemies.\n");

    set_stats(({80,80,80,80,80,80}));
    set_hp(query_max_hp());
    set_aggressive(1, 100);

    add_prop(CONT_I_WEIGHT, 82000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 90);

    set_all_hitloc_unarmed(20);
    set_alignment(0);
    set_act_time(0);
    add_act("assist");

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    seteuid(getuid());

}

void
get_me_soul()
{
    add_cmdsoul("/d/Krynn/guilds/wohs/test/spells/wohs_test_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul("/d/Genesis/specials/guilds/shadows/mana_shadow");
    update_hooks(); 
    remove_alarm(soul_id);
}

void
arm_me()
{
    equip( ({ SWORD, ARMOUR, LEGGINGS, HELMET, GLOVES, CAPE }));
}


public void
attack_object(object ob)
{
    max_hp = ob->query_hp();

    ::attack_object(ob);
}

public void
do_die(object killer)
{
    int hp = killer->query_hp();
    int dmg_taken = killer->query_prop(DMG_TAKEN);

    dmg_taken = dmg_taken + (max_hp - hp);

    // DEBUG("Max hp: "+ max_hp+ ", hp: "+ hp);
    // DEBUG("Damage taken to "+ killer->query_real_name()+ " "+ dmg_taken);
    killer->add_prop(DMG_TAKEN, dmg_taken);
    SOHM_MANAGER->add_wohs_test_props(killer, DMG_TAKEN, dmg_taken);

    if(TO->query_prop(INVADING_SOLDIER))
    {
      killer->catch_msg("\n\nYou dispatch your foe, but you notice " +
          "there are still more coming you will need to deal with " +
          "before the gargoyles awaken.\n\n");
    }

    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object wep;
    mixed hitres;
    string how, weapon, how1, how2;
    int strength = this_object()->query_stat(SS_STR);

    if(random(6)) /* we do ordinary attack now */
	return 0;

    if(random(3))
    {
       command("blind");
       return 1;
    }

    hitres = query_weapon(-1);
    if(!sizeof(hitres)) /* no weapon wielded */
	return 0;

    wep = hitres[0];
    weapon = hitres[0]->query_short();

    if ( wep->id("mace")  )
        hitres = enemy->hit_me((strength * 2) + random(strength), 
                               W_BLUDGEON, TO,
                               hitres[0]->query_attack_id());
    else
        hitres = enemy->hit_me((strength * 2) + random(strength), 
                               W_SLASH, TO,
             		       hitres[0]->query_attack_id());

    if (hitres[0] < 0)
	hitres[0] = 0;

    switch(hitres[0])
    {
    case 0:
	how1 = "his " + weapon + " just missing";
	how2 = "his " + weapon + " just missing";
	break;
    case 1..10:
        how1 = "his " + weapon + " bruising the skin of";
	how2 = "his " + weapon + " grazing the skin of";
	break;
    case 11..20:
        how1 = "slamming his " + weapon + " hard into";
        how2 = "slicing his " + weapon + " deeply into";
	break;
    case 21..40:
        how1 = "his " + weapon + " crushing";
	how2 = "his " + weapon + " deeply penetrating";
	break;
    case 41..60:
        how1 = "smashing his " + weapon + " powerfully into";
	how2 = "burying his " +weapon+ " deeply into";
	break;
    default:	
        how1 = "his " + weapon + " splattering blood everywhere " +
            "as he almost pulverises";
        how2 = "his " + weapon + " splattering blood everywhere " +
            "as he almost removes";
    }

    if ( wep->id("mace") )
        how = how1;
    else 
        how = how2;
        
    enemy->catch_msg(QCTNAME(TO) + " swings at " +
      "you forcefully, " + how + " your "
      + hitres[1] + ".\n");

    tell_watcher(QCTNAME(TO) + " swings at " + QCTNAME(enemy)
      + " in a forcefully, " +how+ " " +QTNAME(enemy)+ "'s" +
      " " + hitres[1] + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(TO);
    }
    return 1;
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
