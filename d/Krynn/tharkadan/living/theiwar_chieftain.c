/*
 * Theiwar chieftain
 * 
 */

inherit "/lib/unique";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <wa_types.h>

#define AXE1    WEP + "mag_theiwar_waraxe"
#define AXE2    WEP + "theiwar_waraxe"
#define HAMMER1 WEP + "mag_theiwar_hammer"
#define HAMMER2 WEP + "theiwar_hammer"
#define BODY1   ARMOUR + "theiwar_fullplate"
#define BODY2   ARMOUR + "theiwar_chainmail"
#define SHIELD1 ARMOUR + "theiwar_mag_shield"
#define SHIELD2 ARMOUR + "theiwar_shield"
#define HELM    ARMOUR + "theiwar_helm"
#define GREAVES ARMOUR + "theiwar_greaves"
#define GAUNT   ARMOUR + "theiwar_gauntlets"
#define ROBE    ARMOUR + "grey_robe"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/act/actions";

object  wep;

#define DARK_DWARF_ENEMY  "_dark_dwarf_enemy_"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({ "dark_dwarf" }));
    set_max_team_size_auto_join(8);

    set_name("krothgar");
    add_name("dwarf");
    add_name("warleader");
    add_name("dark_dwarf");
    set_living_name("krothgar");
    set_title("Grimscarr, Warleader of the Theiwar Clan");
    set_race_name("dwarf");
    set_adj("powerful");
    add_adj("dwarven");
    set_short("powerful dwarven warleader");
    set_gender(G_MALE);
    set_long("Before you stands a powerful dark dwarven warrior, " +
        "a seasoned leader of many battles. He is heavily armed and " +
        "armoured, and you have no doubt he would be a difficult foe!\n");

    set_stats(({360,280,360,220,220,300}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop("_ranger_m_not_disarm", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 10);

    set_alignment(-1000);
    set_knight_prestige(300);

    set_default_answer("The dark dwarf warleader has no interest in " +
        "answering your questions.\n");

    set_act_time(25);
    add_act("rsay A Theiwar should be the next High King of Thorbardin, " +
            "namely me!");
    add_act("emote looks at you with deep suspicion and distrust.");
    add_act("rsay Curse the Hylar clan!");
    add_act("rsay Neidar dwarves are barely better than gully dwarves. " +
                 "They smell as bad!");

    set_cact_time(25);
    add_cact("rsay By the Devouring Darkness, you will not walk away " +
             "from this battle!");
    add_cact("rsay The tortures I will put you through!");
    add_cact("rsay Slay the intruder!"); 
    
}

void
arm_me()
{
    seteuid(getuid(TO));
    if (!random(2))
      wep = clone_unique(AXE1, 10, AXE2);
    else
      wep = clone_unique(HAMMER1, 10, HAMMER2);      

    wep->move(TO, 1);
    command("wield all");
    
    clone_unique(BODY1, 10, BODY2)->move(TO, 1);
    clone_unique(SHIELD1, 10, SHIELD2)->move(TO, 1);
    clone_object(HELM)->move(TO, 1);
    clone_object(ROBE)->move(TO, 1);

    if(!P("_theiwar_magic_fullplate", TO))
    {
       clone_object(GREAVES)->move(TO, 1);
       clone_object(GAUNT)->move(TO, 1);
    }
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

    if ( wep->id("warhammer")  )
        hitres = enemy->hit_me(850 + random(500), W_BLUDGEON, TO,
                               hitres[0]->query_attack_id());
    else
        hitres = enemy->hit_me(850 + random(500), W_SLASH, TO,
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

    if ( wep->id("warhammer") )
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

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
    {
        if ( !random(2) )
            command("curse");

	return;
    }
    
    command("shout Scum! Die ye bastard!");
    action_attack(enemy);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();  

    int light_level = E(TO)->query_prop(OBJ_I_LIGHT);

    if(light_level > 0)
    {
        if(light_level > random(10))
        {
           if(random(2))
             command("emote is dazzled by the bright light.");
           else
             command("emote winces in pain at the light.");
        }
    }

    if ( TP->query_prop(DARK_DWARF_ENEMY) )
    {
	set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }
    
}
