/* This is a base file for npcs of Throtyl.
 * Based off the barbarian warfare npcs.
 *
 * Arman Sept 2020.  
 */


#pragma  strict_types

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include <options.h>
#include <login.h>
#include <state_desc.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit M_FILE
inherit AUTO_TEAM
inherit "/std/act/add_things";
inherit "/d/Krynn/std/act/actions";
inherit "/lib/unique";

inherit "/d/Genesis/specials/npc/stat_based_specials";

public void    setup_guild_stuff(int level, int sublevel, string colour);
public string   set_barbarian_description(int level, int sublevel,
                    string order);
public void     setup_barbarian_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "canny", "experienced", "veteran", 
                  "hardy", "deadly", "commanding" });

object          gShadow, horse, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting, soul_id;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define BARB_MAGIC_WEAPON ({ "/d/Krynn/icewall/plains/obj/frostreaver" })


/* Function name: set_barbarian_level
 * Description  : Sets the stat level of the barbarian soldier.
 * Arguments    : int lev        0 - canny (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - hardy (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - commanding (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - ?
 *                               1 - ?
 *                               2 - ?
 *                               3 - ?
 *                               4 - ?
 *                               5 - ?
 *                               6 - ?
 *                               7 - outrider / lancer
 *                               8 - horse archer / heavy horse archer
 *
 */
varargs void
set_barbarian_level(int lev = 0, int sublev = 0, string order = "abanasinia")
{
    if ( !lev )
    {
        int level = random(100);

        switch(level)
        {  
           case 0..40: 
               gLevel = 3;
               gSublevel = 7;
               break;
           case 41..80: 
               gLevel = 4;
               gSublevel = 7;
               break;
           case 81..95: 
               gLevel = 5;
               gSublevel = 7;
               break;
           case 96..99: 
               gLevel = 4;
               gSublevel = 8;
               break;
           default:
               gLevel = 3;
               gSublevel = 7;
               break;
        }
    }
    else
        gLevel = lev;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;
    
    if (gSublevel < 0) 
        gSublevel = 0;
    if (gSublevel > 8)
        gSublevel = 8;

    if ( !order )
        gOrder = "throtyl";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_barbarian_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_barbarian_level
 * Description  : Returns the level of the barbarian mob.
 */
public int
query_barbarian_level()
{
    return gLevel;
}

/* Function name: query_barbarian_sublevel
 * Description  : Returns the sublevel of the barbarian mob.
 */
public int
query_barbarian_sublevel()
{
    return gSublevel;
}

/* Function name: query_barbarian_order
 * Description  : Returns the order of the barbarian mob.
 */
public string
query_barbarian_order()
{
    return gOrder;
}


/* Function name: setup_barbarian_soldier
 * Description  : Sets the stats and skills of the barbarian soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 7-8.
 */
public void
setup_barbarian_soldier(int level, int sublevel, string order)
{
    string barbarian_desc = set_barbarian_description(gLevel, 
        gSublevel, gOrder);
    int skill_level, stat_level;
    string * name_desc; 
    string tribe_desc = "moorsman";

    // SD_AV_* provides the highest stat average for a particular
    // level, defined in /sys/state_desc.h 
    switch(level)
    {  
       case 0: 
          skill_level = 60;
          stat_level = SD_AV_VETERAN; // 98 stats
          break;
       case 1: 
          skill_level = 60 + random(20);
          stat_level = SD_AV_EXPERT; // 111 stats
          break;
       case 2: 
          skill_level = 70 + random(20);
          stat_level = SD_AV_RISING_HERO; // 124 stats
          break;
       case 3: 
          skill_level = 80 + random(10);
          stat_level = SD_AV_HERO; // 139 stats
          break;
       case 4: 
          skill_level = 90 + random(10);
          stat_level = SD_AV_CHAMPION; // 169 stats
          break;
       case 5: 
          skill_level = 100;
          stat_level = SD_AV_LEGEND; // 189 stats
          break;
       default:
          skill_level = 100;
          stat_level = SD_AV_LEGEND; // 189 stats
          break;
    }

    switch(sublevel)
    {  
       case 7: 
          name_desc = ({ "outrider", "lancer", "dragoon" });
          break;
       case 8: 
          name_desc = ({ "archer" });
          break;
       default: 
          name_desc = ({ "archer" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_moors_rider_npc_");
    add_name(name_desc);
    add_name("moorsman");
    add_adj(order);
    add_adj(tribe_desc);

    if(sublevel == 1)
    {
        set_pname("moorsmen");
        set_short(gAdj[gLevel] + " " +tribe_desc+ " warrior");
        set_pshort(gAdj[gLevel] + " " +tribe_desc+ " warrior");
    }
    else if(level < 3)
    {
        if(sublevel == 7)
        {
            set_short(gAdj[gLevel] + " " +tribe_desc+ " " + 
                name_desc[random(3)]);
        } 
        else if(sublevel == 8)
        {
            set_short(gAdj[gLevel] + " horse " + name_desc[0]);
            add_adj("horse");
        }
        else
            set_short(gAdj[gLevel] + " " +tribe_desc+ " " + 
                name_desc[0]);
    }
    else
    {
        if(sublevel == 7)
        {
            set_short(gAdj[gLevel] + " " +tribe_desc+ " " + 
                name_desc[random(3)]);
        } 
        else if(sublevel == 8)
        {
            set_short(gAdj[gLevel] + " heavy horse " + name_desc[0]);
            add_adj("horse");
            add_adj("heavy");
        }
        else
            set_short(gAdj[gLevel] + " " +tribe_desc+ " " + 
                name_desc[0]);
    }

    set_long(barbarian_desc);
    set_alignment(0);
    set_knight_prestige(0);

    set_stats(({stat_level + random(10),        // str
                stat_level + random(5),         // dex
                stat_level + random(10),        // con 
                stat_level - random(10),        // int 
                stat_level - random(10),        // wis 
                stat_level + random(5),         // dis
                0, stat_level }));              // racial, occupation

    set_skill(SS_WEP_AXE,         skill_level);
    set_skill(SS_WEP_SWORD,       skill_level);
    set_skill(SS_WEP_POLEARM,     skill_level);
    set_skill(SS_WEP_KNIFE,       skill_level);
    set_skill(SS_WEP_CLUB,        skill_level);
    set_skill(SS_DEFENCE,         skill_level);
    set_skill(SS_PARRY,           skill_level);  
    set_skill(SS_2H_COMBAT,       skill_level); 
    set_skill(SS_AWARENESS,       (level * 10) + random(40));
    set_skill(SS_BLIND_COMBAT,    (level * 10) + random(40));
    set_skill(SS_RIDING,          100);
    set_skill(SS_ANI_HANDL,       100);
    set_skill(SS_MOUNTED_COMBAT,  100);

    if(name_desc[0] == "shaman")
    {
        set_skill(SS_SPELLCRAFT,         skill_level + 15);
        set_skill(SS_FORM_ENCHANTMENT,   skill_level + 15);
        set_skill(SS_FORM_CONJURATION,   skill_level + 15);
        set_skill(SS_FORM_DIVINATION,    skill_level + 15);
        set_skill(SS_FORM_ABJURATION,    skill_level + 15);
        set_skill(SS_FORM_ILLUSION,      skill_level + 15);
        set_skill(SS_FORM_TRANSMUTATION, skill_level + 15);
        set_skill(SS_ELEMENT_FIRE,       skill_level + 15);
        set_skill(SS_ELEMENT_EARTH,      skill_level + 15);
        set_skill(SS_ELEMENT_WATER,      skill_level + 15);
        set_skill(SS_ELEMENT_AIR,        skill_level + 15);
    }

}

public void
create_barbarian_soldier()
{
    if ( !gLevel )
        set_barbarian_level();
}

void
horse_me(object me)
{
    horse = clone_object("/d/Krynn/throtyl/living/moor_horse");
    horse->set_owner(TO);
    horse->move(E(TO));
    this_object()->command("mount horse");
}

/* Function name: setup_guild_stuff
 * Description  : Adds barbarian soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{

    if((sublevel == 7) || (sublevel == 8))
        set_alarm(1.0, 0.0, &horse_me(this_object()));
               
}

/* Function name: set_barbarian_description
 * Description  : Sets the long description of the barbarian, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-8.
 */
public string
set_barbarian_description(int level, int sublevel, string order)
{
    string str = "";
    string tribe_desc = "Throtyl moorlands";

    
    switch (level) 
    {
        default:
        {
            switch(sublevel)
            {
                case 0..7:
                    if(level < 3)
                    {
                        str = "This is " +LANG_ADDART(gAdj[level])+ 
                            " cavalryman of the " +tribe_desc+ ", one " +
                            "of the famed Riders on the Moor that call Throtyl " +
                            "their home. Mounted on a swift moorland " +
                            "steed, this rider can swiftly engage foes or " +
                            "quickly alert nearby Rider warbands.\n";
                        break;
                     }
                    else
                    {
                        str = "This is " +LANG_ADDART(gAdj[level])+ 
                            " cavalryman of the " +tribe_desc+ ", a " +
                            "mounted warrior that is the pride of the " +
                            "moors. Mounted on a powerful moorland " +
                            "stallion, this rider can swiftly ride down " +
                            "unfortunate targets fleeing on foot.\n";
                        break;
                     }
                case 8:
                    if(level < 3)
                    {
                        str = "This is " +LANG_ADDART(gAdj[level])+ 
                            " horse archer of the " +tribe_desc+ ", one " +
                            "of the Riders on the Moor that call Throtyl " +
                            "their home. Mounted on a swift moorland " +
                            "steed, this rider can engage foes at range and keep " +
                            "them at a distance of their choice.\n";
                        break;
                     }
                    else
                    {
                        str = "This is " +LANG_ADDART(gAdj[level])+ 
                            " heavy horse archer of the " +tribe_desc+ ", one " +
                            "of the Riders on the Moor that call Throtyl " +
                            "their home. Mounted on a powerful moorland " +
                            "stallion, this rider can swiftly get in range of a " +
                            "target and rain death upon them.\n";
                        break;
                     }
                break;
                default:
                        str = "This is " +LANG_ADDART(gAdj[level])+ 
                            " cavalryman of the " +tribe_desc+ ", a " +
                            "mounted warrior that is the pride of the " +
                            "moors. Mounted on a powerful moorland " +
                            "stallion, this rider can swiftly ride down " +
                            "unfortunate targets fleeing on foot.\n";
                break;
            }
            break;
        }
    }  
  
    return str;    
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    object wep1, wep2, body, helm, greaves, gauntlets;
    int hand_type;
    int weapon_type = random(10);

    switch(weapon_type)
    {
        case 0..7: // 70% chance 2 handed spear
        {
            wep1 = clone_unique("/d/Krynn/throtyl/weapon/moor_lance", 7,
                WEP_PATH + "std_warfare_polearm");
            hand_type = W_BOTH;
        }
        break;
        default:
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_polearm");

            if(!random(3)) // 33% chance of shield, 66% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_polearm");

            hand_type = W_ANYH;
        }
        break;
    }

    // Archers by nature wield bows!
    if(gSublevel == 8)
    {
        object quiver;

        quiver = clone_object(WEP_PATH + "std_quiver");
        quiver->move(TO, 1);

        if(gLevel > 2)
        {
            clone_object(WEP_PATH + "std_sheaf_arrow")->move(quiver, 1);
            clone_object(WEP_PATH + "std_sheaf_arrow")->move(quiver, 1);
            clone_object(WEP_PATH + "std_sheaf_arrow")->move(quiver, 1);
        }
        else
        {
            clone_object(WEP_PATH + "std_flight_arrow")->move(quiver, 1);
            clone_object(WEP_PATH + "std_flight_arrow")->move(quiver, 1);
            clone_object(WEP_PATH + "std_flight_arrow")->move(quiver, 1);
        }

        wep1 = clone_object(WEP_PATH + "std_warfare_bow");
        hand_type = W_BOTH;
        wep2 = 0;  

        add_act("take arrows");     
    }
  

    body = clone_object(ARM_PATH + "std_warfare_armour");
    helm = clone_object(ARM_PATH + "std_warfare_helm");
    greaves = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    gauntlets = clone_object(ARM_PATH + "std_warfare_grv_gnt");

    body->set_armour_level(0, A_TORSO, "throtyl");
    body->update_warfare_armour();

    // Steel armour is rare.. so barbarians wear a lot of leather
    // but get extra natural protection to make up for it
    helm->set_armour_level(0, A_HEAD, "throtyl");
    helm->update_warfare_armour();
    greaves->set_armour_level(0, A_ARMS, "throtyl");
    greaves->update_warfare_armour();
    gauntlets->set_armour_level(0, A_LEGS, "throtyl");
    gauntlets->update_warfare_armour();
    
    if(wep1->query_krynn_warfare_weapon())
    {
        wep1->set_weapon_level(gLevel, hand_type, "throtyl");
        wep1->update_warfare_weapon();
    } 

    if(wep2)
    {
        if(wep2->query_krynn_warfare_weapon())
        {
            wep2->set_weapon_level(gLevel, hand_type, "throtyl");
            wep2->update_warfare_weapon();
        }
        else
        {
            wep2->set_armour_level(1, A_SHIELD, "throtyl");
            wep2->update_warfare_armour();
        }
    }

    if(!wep2)
        equip(({ wep1, body, helm, greaves, gauntlets }));
    else
        equip(({ wep1, wep2, body, helm, greaves, gauntlets }));

    wep1->set_color("throtyl");
    body->set_color("throtyl");

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;

    MONEY_MAKE_HERE_GC(gc);
    MONEY_MAKE_HERE_SC(sc);
}

public void
update_barbarian_soldier()
{
    string barbarian_adj = gAdj[gLevel];

    set_pick_up_team(({ "_moors_rider_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_moors_rider_npc_");
    set_race_name("human");    
    set_adj("barbarian");
    add_adj(barbarian_adj);    

    setuid();
    seteuid(getuid(TO));     
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    // barbarians get an extra 20 hitloc to make up for
    // not getting access to metal armours
    set_all_hitloc_unarmed(20 + (gLevel * 5));

    // Well armoured with special attack
    set_exp_factor(110 + (gLevel * 10));

    add_prop(CONT_I_WEIGHT, 70000 + random(10000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);

    set_act_time(25);
    add_act("assist");
    add_act("emote eyes you distrustfully.");
    add_act("emote studies your every move.");
    add_act("say A storm is coming... I can feel it in my bones.");
    add_act("say A group of hobgoblins passed this way. We " +
        "should try and ambush them.");
    add_act("emote raises a weathered hand to the wind.");
    add_act("emote gazes sternly across the moors.");

    set_cact_time(25);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote snarls in fury.");

    arm_me();
}

void
create_krynn_monster()
{
    create_barbarian_soldier();
    update_barbarian_soldier(); 

}

public int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
        return 1;
}

public void
calm_me()
{
    if ( !query_attack() )
    {
        fighting = 0;
    }
    else
        calm_alarm = set_alarm(10.0, 0.0, calm_me);
}

/* Function name: hook_attacked
 * Description  : Hook called when the npc is attacked by someone.
 */
public void
hook_attacked(object enemy)
{    
    if ( fighting == 1 )
        return;
    
    switch ( random(3) )
    {
    case 0:
        command("say Fool! You will die now!");
    break;
    case 1:
        command("roar");
    break;
    case 2:
        command("emote screams: 'You fool! You'll soon be a corpse " +
            "for the crows!'");
    break;
    }
    
    fighting = 1;
    calm_alarm = set_alarm(8.0, 0.0, calm_me);
}

public void
hook_friend_killed(object friend, object killer)
{
    switch ( random(3) )
    {
    case 0:
        command("grimace");
    break;
    case 1:
        command("emote screams: 'You'll pay for that!'");
    break;
    default:
        command("curse");
    break; 
    }
   
    command("kill " + OB_NAME(killer));
}


/* Function name: special_attack
 * Description  : The code of a knight special attacks.
 */
int
special_attack(object enemy)
{
    int    attacktype, pen, wloc;
    mixed  hitres;
    string *hitloc, how, how0, how1, how2, how3, weapon;
    object my_weapon;

    attacktype = random(6);   

    if(!sizeof(query_weapon(-1)))
	return 0;

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    my_weapon = query_weapon(-1)[0];
    weapon    = my_weapon->query_short();
    
    if (attacktype == 1)
    {
	pen = query_pen_by_stat(TO->query_average_stat()) * 2;

        hitres = enemy->hit_me(pen, my_weapon->query_dt(), TO, -1);

	wloc = random(5);

        if (hitres[0] < 0)
            hitres[0] = 0;

        switch(hitres[0])
        {
            case 0:
                how0 = "which just miss";
	        how1 = "his " + weapon + " just missing";
	        how2 = "his " + weapon + " just missing";
	        how3 = "his " + weapon + " just missing";
	    break;
            case 1..10:
                how0 = "grazing the skin of";
                how1 = "his " + weapon + " bruising the skin of";
	        how2 = "his " + weapon + " grazing the skin of";
	        how3 = "his " + weapon + " scratching the skin of";
	    break;
            case 11..20:
                how0 = "which pierce deeply into";
                how1 = "slamming his " + weapon + " hard into";
                how2 = "slicing his " + weapon + " deeply into";
                how3 = "piercing his " + weapon + " deeply into";
	    break;
            case 21..40:
                how0 = "which deeply penetrate";
                how1 = "his " + weapon + " crushing";
	        how2 = "his " + weapon + " deeply penetrating";
	        how3 = "his " + weapon + " deeply penetrating";
	    break;
            case 41..60:
                how0 = "which bury deeply into";
                how1 = "smashing his " + weapon + " powerfully into";
	        how2 = "burying his " +weapon+ " deeply into";
	        how3 = "burying his " +weapon+ " deeply into";
	    break;
            default:	
                how0 = "which nastily impale";
                how1 = "his " + weapon + " splattering blood everywhere " +
                       "as he almost pulverises";
                how2 = "his " + weapon + " splattering blood everywhere " +
                       "as he almost removes";
                how3 = "his " + weapon + " splattering blood everywhere " +
                       "as he impales";
            break;
        }

        if ( my_weapon->query_wt() == W_MISSILE )
            how = how0;
        else if ( my_weapon->query_dt() == W_BLUDGEON )
            how = how1;
        else if( my_weapon->query_dt() == W_IMPALE )
            how = how3;
        else
            how = how2;

        if ( my_weapon->query_wt() == W_MISSILE )
        {
	    enemy->catch_msg(QCTNAME(TO) + " launches a " +
  	        "barrage of arrows " + how + " your " +
	        hitloc[wloc] + ".\n");
	    tell_watcher(QCTNAME(TO) + " launches a barrage of arrows, " +
                how + " " + QTPNAME(enemy) + " " + hitloc[wloc] + ".\n", enemy);
        }
        else
        {            
	    enemy->catch_msg(QCTNAME(TO) + " strikes out at " +
  	        "you in a powerful attack, " + how + " your " +
	        hitloc[wloc] + ".\n");
	    tell_watcher(QCTNAME(TO) + " strikes at " + QTNAME(enemy) +
	        " in a powerful attack, " + how + " " + QTPNAME(enemy) + 
	        " " + hitloc[wloc] + ".\n", enemy);
        }

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    
    return 0;
}

public void
action_attack(object enemy)
{
    if (!objectp(enemy))
        return;
    
    command("kill " + OB_NAME(enemy));
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

    if(random(2))    
        command("shout Scum! Die bastard!");
    else
        command("shout Riders of the Moor! To battle!");
    action_attack(enemy);
}

public void
do_die(object killer)
{
    if((gSublevel == 7) || (gSublevel == 8))
        horse->remove_warfare_warhorse();

    ::do_die(killer);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();      
}
