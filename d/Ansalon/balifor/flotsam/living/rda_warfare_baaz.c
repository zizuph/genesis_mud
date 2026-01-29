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

inherit "/d/Krynn/std/baaz";
inherit "/lib/unique";
inherit AUTO_TEAM
inherit "/std/act/add_things";
inherit "/d/Krynn/std/act/actions";
inherit "/lib/unique";

inherit "/d/Genesis/specials/npc/stat_based_specials";

varargs void    setup_guild_stuff(int level, int sublevel, string colour);
public void     setup_dragonarmy_soldier(int level, int sublevel, 
                    string colour);

string *gAdj = ({ "scarred", "experienced", "veteran", 
                  "fearsome", "deadly", "elite" });

object          gShadow, uniform;
string          gSoul, gColour;
int             gLevel, gSublevel, calm_alarm, fighting;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define D_ARMY_DIR            "/d/Ansalon/guild/dragonarmy/"

#define DA_MAGIC_ARMOUR ({ "/d/Krynn/solamn/splains/obj/bdragonarm", \
     "/d/Krynn/common/armours/elite_chain" })

#define DA_MAGIC_WEAPON ({ "/d/Krynn/solamn/splains/obj/bclaymore", \
     "/d/Krynn/icewall/castle2/obj/weapons/wknife", \
     "/d/Krynn/solamn/splains/obj/bbattleaxe", \
     "/d/Krynn/common/weapons/flame_glaive", \
     "/d/Ansalon/common/wep/pole/aurak_halberd", \
     "/d/Ansalon/common/wep/pole/roncone" })

/* Function name: set_dragonarmy_level
 * Description  : Sets the stat level of the dragonarmy soldier.
 * Arguments    : int lev        0 - scarred (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - fearsome (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - elite (190 stat average)
 *                               If not given, level is scarred (0).
 *
 */
varargs void
set_dragonarmy_level(int lev = 0, int sublev = 0, string colour = "black")
{
    if ( !lev )
        gLevel = 0;
    else
        gLevel = lev;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;

    if ( !sublev )
        gSublevel = 0;
    else
        gSublevel = sublev;
    
    if (gSublevel < 0) 
        gSublevel = 0;
    if (gSublevel > 3)
        gSublevel = 3;

    if ( !colour )
        gColour = "black";
    else
        gColour = colour;
        
    setup_guild_stuff(gLevel, gSublevel, gColour);
    setup_dragonarmy_soldier(gLevel, gSublevel, gColour);

}

/* Function name: query_dragonarmy_level
 * Description  : Returns the level of the dragonarmy mob.
 */
public int
query_dragonarmy_level()
{
    return gLevel;
}

/* Function name: query_dragonarmy_sublevel
 * Description  : Returns the sublevel of the dragonarmy mob.
 */
public int
query_dragonarmy_sublevel()
{
    return gSublevel;
}

/* Function name: query_dragonarmy_colour
 * Description  : Returns the colour of the dragonarmy mob.
 */
public string
query_dragonarmy_colour()
{
    return gColour;
}

int
query_dragonfear_immunity()
{
    // All draconians are immune to dragonfear
    return 1;
}

/* Function name: setup_dragonarmy_soldier
 * Description  : Sets the stats and skills of the dragonarmy soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-2.
 */
public void
setup_dragonarmy_soldier(int level, int sublevel, string colour)
{
    int skill_level, stat_level;
    string * name_desc;

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

    add_name("_warfare_npc_");
    add_adj(colour);
    set_alignment(-400 - (gLevel * 100));
    set_knight_prestige(400 + (gLevel * 150));

    set_stats(({stat_level + random(15),        // str
                stat_level - random(5),         // dex
                stat_level + random(10),        // con 
                stat_level - random(15),        // int 
                stat_level - random(10),        // wis 
                stat_level + random(5),         // dis
                0, stat_level }));              // racial, occupation

    set_skill(SS_WEP_AXE,         skill_level);
    set_skill(SS_WEP_SWORD,       skill_level);
    set_skill(SS_WEP_POLEARM,     skill_level);
    set_skill(SS_WEP_KNIFE,       skill_level);
    set_skill(SS_WEP_MISSILE,     skill_level);
    set_skill(SS_WEP_CLUB,        skill_level);
    set_skill(SS_DEFENCE,         skill_level);
    set_skill(SS_PARRY,           skill_level);  
    set_skill(SS_2H_COMBAT,       skill_level); 
    set_skill(SS_AWARENESS,       (level * 10) + random(40));
    set_skill(SS_BLIND_COMBAT,    (level * 10) + random(40));
    set_skill(SS_ANI_HANDL,       (level * 20));

}

public void
create_dragonarmy_soldier()
{
    if ( !gLevel )
        set_dragonarmy_level();
}

/* Function name: setup_guild_stuff
 * Description  : Adds dragonarmy soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{
    if ( level < 3 || sublevel < 1 )
        return;
        
    // add guild soul command stuff here
    int rank = (sublevel + 1);

    /* First we remove any old shadow used */
    if(objectp(gShadow))
    {
	gShadow->remove_da_shadow();
    }

    /* Now we add desired shadow */
    gShadow = clone_object(D_ARMY_DIR + "shadow/dragonarmy_" + colour +
        "_sh");

    if(gShadow->shadow_me(TO, "occupational", "fighter", "Dragonarmy") != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }
    else
    {
	gShadow->set_promotion_level(rank);
    }

    /* We add also soul and initialize commands */
    remove_cmdsoul(gSoul);
    gSoul = D_ARMY_DIR + "soul/dragonarmy_" +colour+ "_soul";
    add_cmdsoul(gSoul);
    load_command_souls();
    /* Finaly color all inventory also */
    all_inventory()->set_color(colour);
    all_inventory()->set_colour(colour);
        
}

void
create_baaz()
{
    if (!IS_CLONE)
	return;

    arm_draconian_called = 1;
    /* Necessary so that draconian does not automatically wield
       standard draconian equipment */

    create_dragonarmy_soldier();
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object enemy)
{
    int    attacktype, pen, wloc, mitigation, mod;
    mixed  hitres;
    string *hitloc, how, how1, how2, how3, weapon;
    object my_weapon;

    attacktype = random(6); 

    if(!sizeof(query_weapon(-1)))
	return 0;

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    my_weapon = query_weapon(-1)[0];
    weapon    = my_weapon->query_short();

    // ogres can't mitigate damage with armour, so providing base 50% 
    // resistance to warfare special attacks.
    if(enemy->query_race_name() == "ogre")
        mod = 1;
    else
        mod = 2;
    
    if (attacktype == 1)
    {
	pen = query_pen_by_stat(TO->query_average_stat()) * mod;
        WARFARE_DEBUG("Special pen: " +pen+ ".");

        // Some warfare armours provide mitigation against the special
        // attacks of the npcs through a prop value, equating to x %
        // mitigation.
        mitigation = enemy->query_prop(WARFARE_ARMOUR_PROP);

        if(mitigation)
        {
            pen = pen * (100 - mitigation) / 100;
            WARFARE_DEBUG("Special pen post mitigation: " +pen+ ".");
        }

        hitres = enemy->hit_me(pen, my_weapon->query_dt(), TO, -1);

	wloc = random(5);

        if (hitres[0] < 0)
            hitres[0] = 0;

        switch(hitres[0])
        {
            case 0:
	        how1 = "his " + weapon + " just missing";
	        how2 = "his " + weapon + " just missing";
	        how3 = "his " + weapon + " just missing";
	    break;
            case 1..10:
                how1 = "his " + weapon + " bruising the skin of";
	        how2 = "his " + weapon + " grazing the skin of";
	        how3 = "his " + weapon + " scratching the skin of";
	    break;
            case 11..20:
                how1 = "slamming his " + weapon + " hard into";
                how2 = "slicing his " + weapon + " deeply into";
                how3 = "pierces his " + weapon + " deeply into";
	    break;
            case 21..40:
                how1 = "his " + weapon + " crushing";
	        how2 = "his " + weapon + " deeply penetrating";
	        how3 = "his " + weapon + " deeply penetrating";
	    break;
            case 41..60:
                how1 = "smashing his " + weapon + " powerfully into";
	        how2 = "burying his " +weapon+ " deeply into";
	        how3 = "burying his " +weapon+ " deeply into";
	    break;
            default:	
                how1 = "his " + weapon + " splattering blood everywhere " +
                       "as he almost pulverises";
                how2 = "his " + weapon + " splattering blood everywhere " +
                       "as he almost removes";
                how3 = "his " + weapon + " splattering blood everywhere " +
                       "as he impales";
            break;
        }

        if ( my_weapon->query_dt() == W_BLUDGEON )
            how = how1;
        else if( my_weapon->query_dt() == W_IMPALE )
            how = how3;
        else
            how = how2;
            
	enemy->catch_msg(QCTNAME(TO) + " strikes at " +
  	    "you in a furious attack, " + how + " your " +
	    hitloc[wloc] + ".\n");

	tell_watcher(QCTNAME(TO) + " strikes at " + QTNAME(enemy) +
	    " in a furious attack, " + how + " " + QTPNAME(enemy) + 
	    " " + hitloc[wloc] + ".\n", enemy);

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    
    return 0;

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
        case 0..1: // 20% chance 2 handed sword
        {
            if(gLevel > 2)
                wep1 = clone_unique(DA_MAGIC_WEAPON[0], (5 + gLevel), 
                    WEP_PATH + "std_warfare_sword");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_BOTH;
        }
        break;
        case 2..4: // 30% chance 1 handed sword
        {
            if(gLevel > 2)
                wep1 = clone_unique(DA_MAGIC_WEAPON[1], (5 + gLevel), 
                    WEP_PATH + "std_warfare_sword");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_sword");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 5..6: // 20% chance 2 handed polearm
        {
           WARFARE_DEBUG("2 handed pole called");

            int pole_type = random(3) + 3;

            if(gLevel > 2)
                wep1 = clone_unique(DA_MAGIC_WEAPON[pole_type], 
                    (5 + gLevel), WEP_PATH + "std_warfare_polearm");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_polearm");

            hand_type = W_BOTH;
        }
        break;
        case 7..8: // 20% chance 1 handed polearm
        {
           WARFARE_DEBUG("1 handed pole called");

            wep1 = clone_object(WEP_PATH + "std_warfare_polearm");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 9: // 10% chance 2 handed axe
        {
            if(gLevel > 2)
                wep1 = clone_unique(DA_MAGIC_WEAPON[2], 
                    (5 + gLevel), WEP_PATH + "std_warfare_axe");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_axe");

            hand_type = W_BOTH;
        }
        break;
        default:
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_axe");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
    }

    if(gLevel > 2)
        body = clone_unique(ONE_OF(DA_MAGIC_ARMOUR), (5 + gLevel),
            ARM_PATH + "std_warfare_armour");
    else
        body = clone_object(ARM_PATH + "std_warfare_armour");

    helm = clone_object(ARM_PATH + "std_warfare_helm");
    greaves = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    gauntlets = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    uniform = clone_object(D_ARMY_DIR + "obj/uniform");

    body->set_armour_level(gLevel, A_TORSO, gColour);
    body->update_warfare_armour();
    helm->set_armour_level(gLevel, A_HEAD, gColour);
    helm->update_warfare_armour();
    greaves->set_armour_level(gLevel, A_ARMS, gColour);
    greaves->update_warfare_armour();
    gauntlets->set_armour_level(gLevel, A_LEGS, gColour);
    gauntlets->update_warfare_armour();
    
    if(wep1->query_krynn_warfare_weapon())
    {
        wep1->set_weapon_level(gLevel, hand_type, gColour);
        wep1->update_warfare_weapon();
    } 

    if(wep2)
    {
        if(wep2->query_krynn_warfare_weapon())
        {
            wep2->set_weapon_level(gLevel, hand_type, gColour);
            wep2->update_warfare_weapon();
        }
        else
        {
            wep2->set_armour_level(gLevel, A_SHIELD, gColour);
            wep2->update_warfare_armour();
        }
    }

    if(!wep2)
        equip(({ wep1, body, helm, greaves, gauntlets, uniform }));
    else
        equip(({ wep1, wep2, body, helm, greaves, gauntlets, uniform }));

    wep1->set_color(gColour);
    body->set_color(gColour);
    uniform->set_color(gColour);

    uniform->set_dalevel(TO->query_dragonarmy_promotions());
    uniform->set_condition(random(5));
    uniform->set_repair(random(2));

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;

    MONEY_MAKE_HERE_GC(gc);
    MONEY_MAKE_HERE_SC(sc);
}

public void
do_die(object killer)
{
    string killer_army;

    if(WAR_CLUB_ADMIN->query_is_member(killer))
    {
        WAR_CLUB_ADMIN->add_warfare_enemy_vanquished(killer, 
            gLevel, gColour);

        killer_army = WAR_CLUB_ADMIN->query_warfare_army(killer);
        WAR_CLUB_ADMIN->increase_krynn_war_kills(killer_army, 1);
        WAR_CLUB_ADMIN->increase_krynn_war_player_kills(killer, 1);
    }

    ::do_die(killer);
}
