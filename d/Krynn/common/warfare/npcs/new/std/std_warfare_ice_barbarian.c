
/* This is a base file for warfare Icewall barbarian npcs.
 *
 * Arman Sept 2018.  
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

string *gAdj = ({ "scarred", "experienced", "veteran", 
                  "hardy", "deadly", "legendary" });

object          gShadow, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting, soul_id;
void            get_me_soul();

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define BARB_MAGIC_WEAPON ({ "/d/Krynn/icewall/plains/obj/frostreaver" })


/* Function name: set_barbarian_level
 * Description  : Sets the stat level of the barbarian soldier.
 * Arguments    : int lev        0 - scarred (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - hardy (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - legendary (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - wanderer
 *                               1 - hunter
 *                               2 - barbarian
 *                               3 - reaver
 *                               4 - chieftain
 *                               5 - winternorn
 *
 */
varargs void
set_barbarian_level(int lev = 0, int sublev = 0, string order = "ice")
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
    if (gSublevel > 5)
        gSublevel = 5;

    if ( !order )
        gOrder = "ice";
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
 *              : int sublevel        - range 0-5.
 */
public void
setup_barbarian_soldier(int level, int sublevel, string order)
{
    string barbarian_desc = set_barbarian_description(gLevel, 
        gSublevel, gOrder);
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

    switch(sublevel)
    {  
       case 0: 
          name_desc = ({ "wanderer" });
          break;
       case 1: 
          name_desc = ({ "hunter" });
          break;
       case 2: 
          name_desc = ({ "barbarian" });
          break;
       case 3: 
          name_desc = ({ "reaver" });
          break;
       case 4: 
          name_desc = ({ "chieftain" });
          break;
       default: 
          name_desc = ({ "winternorn" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_warfare_npc_");
    add_name(name_desc);
    add_adj(order);

    if(sublevel < 4)
        set_short(gAdj[gLevel] + " ice " + name_desc[0]); 
    else if(sublevel == 4)
        set_short(gAdj[gLevel] + " barbarian " + name_desc[0]);
    else
        set_short(gAdj[gLevel] + " " + name_desc[0]);

    set_long(barbarian_desc);
    set_alignment(0);
    set_knight_prestige(0);

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
    set_skill(SS_WEP_CLUB,        skill_level);
    set_skill(SS_DEFENCE,         skill_level);
    set_skill(SS_PARRY,           skill_level);  
    set_skill(SS_2H_COMBAT,       skill_level); 
    set_skill(SS_AWARENESS,       (level * 10) + random(40));
    set_skill(SS_BLIND_COMBAT,    (level * 10) + random(40));
    set_skill(SS_ANI_HANDL,       100);

    if(name_desc[0] == "winternorn")
    {
        add_name("_warfare_winternorn_");
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
get_me_soul()
{
    add_cmdsoul(SOHM_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul("/d/Genesis/specials/guilds/shadows/mana_shadow");
    update_hooks(); 
    remove_alarm(soul_id);
}

/* Function name: setup_guild_stuff
 * Description  : Adds barbarian soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{
    // Winternorn gets the SoHM shadow added.
    if (sublevel == 5)
    {
        clone_object(MANA_SHADOW)->shadow_me(TO);

        soul_id = set_alarm(0.5, 0.0, &get_me_soul());
        seteuid(getuid());
        return;
    }
               
}

/* Function name: set_barbarian_description
 * Description  : Sets the long description of the barbarian, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-4.
 */
public string
set_barbarian_description(int level, int sublevel, string order)
{
    string str = "";
    
    switch (level) 
    {
        default:
        {
            switch(sublevel)
            {
                case 0:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " wanderer of the Icereach Glacier.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " hunter of the Icereach Glacier.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " ice barbarian of the Icereach Glacier. " +
                        "Constantly exposed to freezing winds have " +
                        "made this tribesman's features grim and " +
                        "weathered, although in battle the cold can " +
                        "do little to quell the fire of his fury!\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " ice reaver of the Ice Folk, a mighty " +
                        "warrior of the barbarian tribes that make " +
                        "Icereach Glacier their home.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " barbarian chieftain of the tribes of the Icereach " +
                        "Glacier. Chosen from the wisest, strongest, and " +
                        "hardiest of the warriors, this tribesman is one " +
                        "to fear raising the ire of!\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " winternorn, an ice wizard of the Ice Folk of " +
                        "the Icereach Glacier. Respected and feared by " +
                        "the local barbarian tribes, they are invaluable " +
                        "allies in times of trouble and in battle.\n";
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

    int gem_spawn_chance = GEM_SPAWN_CHANCE - (gLevel * 2);
    string * gem_array;
    string gem_string;
    object gem;

    // chance of spawning an augmentation crystal
    if(!random(gem_spawn_chance))
    {
        // Make it harder to steal-farm gems, but not
        // impossible.
        set_skill(SS_AWARENESS, (gLevel * 10) + 50);

        switch(random(10))
        {
            case 0..2:
            {
                if(gLevel > 2)
                    gem_array = KRYNN_WAR_GEM_TIER2_SPAWN["ellipse"];
                else
                    gem_array = KRYNN_WAR_GEM_TIER1_SPAWN["ellipse"];

                gem_string = ONE_OF(gem_array);
                gem = clone_object(gem_string);
                gem->move(TO, 1);
            }
            break;
            case 3..5:
            {
                if(gLevel > 2)
                    gem_array = KRYNN_WAR_GEM_TIER2_SPAWN["tear"];
                else
                    gem_array = KRYNN_WAR_GEM_TIER1_SPAWN["tear"];

                gem_string = ONE_OF(gem_array);
                gem = clone_object(gem_string);
                gem->move(TO, 1);
            }
            break;
            case 6..8:
            {
                if(gLevel > 2)
                    gem_array = KRYNN_WAR_GEM_TIER2_SPAWN["oval"];
                else
                    gem_array = KRYNN_WAR_GEM_TIER1_SPAWN["oval"];

                gem_string = ONE_OF(gem_array);
                gem = clone_object(gem_string);
                gem->move(TO, 1);
            }
            break;
            default:
            {
                if(gLevel > 2)
                    gem_array = KRYNN_WAR_GEM_TIER2_SPAWN["triangular"];
                else
                    gem_array = KRYNN_WAR_GEM_TIER1_SPAWN["triangular"];

                gem_string = ONE_OF(gem_array);
                gem = clone_object(gem_string);
                gem->move(TO, 1);
            }
            break;
        }
    }

    switch(weapon_type)
    {
        case 0: // 10% chance 2 handed warhammer
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_hammer");

            hand_type = W_BOTH;
        }
        break;
        case 1..2: // 20% chance 1 handed hammer
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_hammer");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 3..7: // 50% chance 2 handed axe
        {
            wep1 = clone_unique(BARB_MAGIC_WEAPON[0], (5 + gLevel), 
                WEP_PATH + "std_warfare_axe");

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

    // Winternorns by nature wield staves!
    if(gSublevel == 5)
    {    
        wep1 = clone_object("/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff");

        hand_type = W_BOTH;
        wep2 = 0;

        /* 10% chance of cloning a gravity scroll */
        if(!random(10))
        {
            clone_object("/d/Krynn/common/scrolls/gravity_scroll")->move(TO);

        }
    }

    // Chieftains have a greater chance of carrying a frostreaver
    if(gSublevel == 4)
    { 
        if(random(10) < gLevel)   
            wep1 = clone_object(BARB_MAGIC_WEAPON[0]);
        else
            wep1 = clone_object(WEP_PATH + "std_warfare_axe");

        hand_type = W_BOTH;
        wep2 = 0;
    }    

    body = clone_object(ARM_PATH + "std_warfare_armour");
    helm = clone_object(ARM_PATH + "std_warfare_helm");
    greaves = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    gauntlets = clone_object(ARM_PATH + "std_warfare_grv_gnt");

    body->set_armour_level(gLevel, A_TORSO, "ice");
    body->update_warfare_armour();

    // Steel armour is rare.. so barbarians wear a lot of leather
    // but get extra natural protection to make up for it
    helm->set_armour_level(0, A_HEAD, "ice");
    helm->update_warfare_armour();
    greaves->set_armour_level(0, A_ARMS, "ice");
    greaves->update_warfare_armour();
    gauntlets->set_armour_level(0, A_LEGS, "ice");
    gauntlets->update_warfare_armour();
    
    if(wep1->query_krynn_warfare_weapon())
    {
        wep1->set_weapon_level(gLevel, hand_type, "ice");
        wep1->update_warfare_weapon();
    } 

    if(wep2)
    {
        if(wep2->query_krynn_warfare_weapon())
        {
            wep2->set_weapon_level(gLevel, hand_type, "ice");
            wep2->update_warfare_weapon();
        }
        else
        {
            wep2->set_armour_level(1, A_SHIELD, "ice");
            wep2->update_warfare_armour();
        }
    }

    if(!wep2)
        equip(({ wep1, body, helm, greaves, gauntlets }));
    else
        equip(({ wep1, wep2, body, helm, greaves, gauntlets }));

    wep1->set_color("ice");
    body->set_color("ice");

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

    set_pick_up_team(({ "_ice_barbarian_warfare_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_barbarian_warfare_npc_");
    set_race_name("human");    
    set_adj("barbarian");
    add_adj(barbarian_adj);    

    setuid();
    seteuid(getuid(TO));     
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    // barbarians get an extra 16 hitloc to make up for
    // not getting access to metal armours
    set_all_hitloc_unarmed(16 + (gLevel * 5));

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
    add_act("say A snowstorm is coming... I can feel it in my bones.");
    add_act("say A patrol of thanoi and minotaurs passed this way. We " +
        "should try and ambush them.");
    add_act("emote raises a weathered hand to the wind.");
    add_act("emote gazes sternly across the icy plains.");

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
        command("emote screams: 'You fool! You'll soon be an icy corpse " +
            "for the thanoi to chew on!'");
    break;
    }

    // Charlatan uses spells
    if (gSublevel == 5) 
    {
           if(!("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(TO)))
           {
             // Cast greater magic shield if not in effect
              command("jennufethos");
           }
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

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

/* Function name: special_attack
 * Description  : The code of a knight special attacks.
 */
int
special_attack(object enemy)
{
    int    attacktype, pen, wloc, mitigation, mod;
    mixed  hitres;
    string *hitloc, how, how0, how1, how2, how3, weapon;
    object my_weapon;
    int    switchspell = random(4);

    attacktype = random(6);   

    // Winternorn uses spells
    if (gSublevel == 5) 
    {
        if (attacktype == 0 || attacktype == 1)
        {
           if(!("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(TO)))
           {
             // Cast greater magic shield if not in effect
              command("jennufethos");
              return 1;
           }
           if(switchspell == 1)
              command("arcanisvaes"); // magic missile
           else if(switchspell == 2)
              command("haddross"); // gravity
           else
              command("xarzithnar"); // ice strike

           return 1;
        }
        return 0;
    }

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
        // WARFARE_DEBUG("Special pen: " +pen+ ".");

        // Some warfare armours provide mitigation against the special
        // attacks of the npcs through a prop value, equating to x %
        // mitigation.
        mitigation = enemy->query_prop(WARFARE_ARMOUR_PROP);

        if(mitigation)
        {
            pen = pen * (100 - mitigation) / 100;
            // WARFARE_DEBUG("Special pen post mitigation: " +pen+ ".");
        }

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
    
    command("shout Scum! Die bastard!");
    action_attack(enemy);
}

public void
do_die(object killer)
{
    string killer_army;

    if(WAR_CLUB_ADMIN->query_is_member(killer))
    {
        WAR_CLUB_ADMIN->add_warfare_enemy_vanquished(killer, 
            gLevel, "free");

        killer_army = WAR_CLUB_ADMIN->query_warfare_army(killer);
        WAR_CLUB_ADMIN->increase_krynn_war_kills(killer_army, 1);
        WAR_CLUB_ADMIN->increase_krynn_war_player_kills(killer, 1);

    }

    ::do_die(killer);
}

public void
attacked_by(object attacker)
{
    if((WAR_CLUB_ADMIN->query_warfare_army(attacker) == "Free People"))
    {
        WAR_CLUB_ADMIN->set_time_attacked_own_army(attacker);
    }

    ::attacked_by(attacker);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();      
}
