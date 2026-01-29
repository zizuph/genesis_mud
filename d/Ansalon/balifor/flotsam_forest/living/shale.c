/*
 * 16.07.2003, Modified by Blizzard.
 * Added dwarven war-mace and blackened kite-shield.
 * 3/15/2012 (Petros) - Use query_attack_id instead of query_hands in hit_me
 */

inherit "/lib/unique";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <wa_types.h>

/* WEP3 is now the guru quest item for Neidar clan - Arman 1/5/2015 */

#define WEP  FOBJ + "weapon/cleaver"
#define WEP2 "/d/Krynn/common/weapons/war-mace"
#define WEP3 FOBJ + "weapon/shale_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "horned_helmet"
#define ARM3 ARMOUR + "shield2"
#define SHLD "/d/Krynn/common/armours/kite-shield"
#define ARM4 ARMOUR + "i_boots"
#define ARM5 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "leggings"
#define ARM7 ARMOUR + "cloak"

inherit AM_FILE

#define PLAYER_I_KILLED_SHALE  "_player_i_killed_neidar_shale"

object  wep;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("shale");
    add_name("dwarf");
    set_living_name("shale");
    set_title("Ironfist, Giantslayer of the Hollowlands");
    set_race_name("hill dwarf");
    set_adj("muscular");
//    add_adj("hill");
//    set_short("muscular male hill dwarf");
    set_gender(G_MALE);
    set_long("This is one of the few Neidar dwarves that makes its home " +
      "in the plains and hills on the border of the Goodlund forest. " +
      "This dwarf is quite rugged and scarred, obviously a veteran of " +
      "many battles.\nHe is a banished member of the Neidar Clan.\n");

    set_stats(({160,119,170,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop("_ranger_m_not_disarm", 1);

    set_alignment(100);
    set_knight_prestige(0);

    set_default_answer("The dwarf stubbornly refuses to answer you.\n");

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
      "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his greying beard lovingly.");

    set_cact_time(0);
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");
    
}

void
arm_me()
{
    seteuid(getuid(TO));
    if (!random(2))
      wep = clone_unique(WEP2, 5, WEP3);
    else
      wep = clone_unique(WEP, 10, WEP3);      

    wep->move(TO, 1);
    command("wield all");
    
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    clone_unique(SHLD, 5, ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    clone_object(ARM5)->move(TO,1);
    clone_object(ARM6)->move(TO,1);
    clone_object(ARM7)->move(TO,1);
    command("wear all");
}

void
return_intro()
{
    command("introduce myself");
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(1.0, 0.0, return_intro);
    }
}

int
special_attack(object enemy)
{
    mixed hitres;
    string how, weapon, how1, how2;

    if(random(5)) /* we do ordinary attack now */
	return 0;

    hitres = query_weapon(-1);
    if(!sizeof(hitres)) /* no weapon wielded */
	return 0;

    weapon = hitres[0]->query_short();

    if ( wep->id("war-mace")  )
        hitres = enemy->hit_me(450 + random(200), W_BLUDGEON, TO,
                               hitres[0]->query_attack_id());
    else
        hitres = enemy->hit_me(450 + random(200), W_SLASH, TO,
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

    if ( wep->id("war-mace") )
        how = how1;
    else 
        how = how2;
        
    enemy->catch_msg(QCTNAME(TO) + " charges at " +
      "you in a furious attack, " + how + " your "
      + hitres[1] + ".\n");

    tell_watcher(QCTNAME(TO) + " charges at " + QCTNAME(enemy)
      + " in a furious rage, " +how+ " " +QTNAME(enemy)+ "'s" +
      " " + hitres[1] + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(TO);
    }
    return 1;
}


public void
do_die(object killer)
{
    killer->add_prop(PLAYER_I_KILLED_SHALE, 1);

    ::do_die(killer);
}
