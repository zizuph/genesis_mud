/* This is a base file for npcs of Throtyl.
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
public string   set_throtyl_description(int level, int sublevel,
                    string order);
public void     setup_throtyl_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "scarred", "cunning", "brutal", 
                  "fearsome", "deadly", "elite" });

object          gShadow, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting, soul_id;
void            get_me_soul();

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

/* Function name: set_throtyl_level
 * Description  : Sets the stat level of the throtyl soldier.
 * Arguments    : int lev        0 - scarred (112 stat average)
 *                               1 - cunning (125 stat average)
 *                               2 - brutal (140 stat average)
 *                               3 - fearsome (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - elite (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - goblin archer
 *                               1 - hobgoblin looter
 *                               2 - aggressive bugbear
 *                               3 - ogre marauder
 *                               4 - ogre magi
 *
 */
varargs void
set_throtyl_level(int lev = 0, int sublev = 0, string order = "throtyl")
{
    if ( !lev )
    {
        int level = random(100);

        switch(level)
        {  
           case 0..2: 
               gLevel = 0;
               gSublevel = 0;
               break;
           case 3..5: 
               gLevel = 1;
               gSublevel = 0;
               break;
           case 6..10: 
               gLevel = 1;
               gSublevel = 1;
               break;
           case 11..15: 
               gLevel = 2;
               gSublevel = 1;
               break;
           case 16..55: 
               gLevel = 3;
               gSublevel = 1;
               break;
           case 56..70: 
               gLevel = 4;
               gSublevel = 1;
               break;
           case 71..84: 
               gLevel = 3;
               gSublevel = 2;
               break;
           case 85..90: 
               gLevel = 3;
               gSublevel = 3;
               break;
           case 91..95: 
               gLevel = 4;
               gSublevel = 3;
               break;
           case 96..99: 
               gLevel = 5;
               gSublevel = 4;
               break;
           default:
               gLevel = 3;
               gSublevel = 1;
               break;
        }
    }
    else
        gLevel = lev;
    
    if (gLevel < 0)
        gLevel = 0;
    if (gLevel > 5)
        gLevel = 5;
/*
    if ( !sublev )
        gSublevel = 0;
    else
        gSublevel = sublev;
*/    
    if (gSublevel < 0) 
        gSublevel = 0;
    if (gSublevel > 4)
        gSublevel = 4;

    if ( !order )
        gOrder = "throtyl";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_throtyl_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_throtyl_level
 * Description  : Returns the level of the throtyl mob.
 */
public int
query_throtyl_level()
{
    return gLevel;
}

/* Function name: query_throtyl_sublevel
 * Description  : Returns the sublevel of the throtyl mob.
 */
public int
query_throtyl_sublevel()
{
    return gSublevel;
}

/* Function name: query_throtyl_order
 * Description  : Returns the order of the throtyl mob.
 */
public string
query_throtyl_order()
{
    return gOrder;
}


/* Function name: setup_throtyl_soldier
 * Description  : Sets the stats and skills of the throtyl soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-4.
 */
public void
setup_throtyl_soldier(int level, int sublevel, string order)
{
    string throtyl_desc = set_throtyl_description(gLevel, 
        gSublevel, gOrder);
    int skill_level, stat_level;
    string * name_desc;
    string race_desc;

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
          name_desc = ({ "archer" });
          race_desc = "goblin";
          break;
       case 1: 
          name_desc = ({ "marauder" });
          race_desc = "hobgoblin";
          break;
       case 2: 
          name_desc = ({ "bugbear" });
          race_desc = "bugbear";
          break;
       case 3: 
          name_desc = ({ "marauder" });
          race_desc = "ogre";
          break;
       case 4: 
          name_desc = ({ "magi" });
          race_desc = "ogre";
          break;
       default: 
          name_desc = ({ "magi" });
          race_desc = "ogre";
          break;
    }

    add_name(name_desc[0]);
    add_name(name_desc);
    add_name("_throtyl_npc_");
    set_race_name(race_desc);
    add_adj(order);

    if(sublevel == 2)
        set_short(gAdj[gLevel] + " aggressive bugbear");
    else
        set_short(gAdj[gLevel] + " " +race_desc+ " " + name_desc[0]); 
    set_long(throtyl_desc);
    set_alignment(-40 - (gLevel * 100));

    set_stats(({stat_level + (10 * sublevel),   // str
                stat_level - random(5),         // dex
                stat_level + (10 * sublevel),   // con 
                stat_level - random(15),        // int 
                stat_level - random(10),        // wis 
                stat_level + random(5),         // dis
                0, stat_level }));              // racial, occupation

    set_skill(SS_WEP_AXE,         skill_level);
    set_skill(SS_WEP_SWORD,       skill_level);
    set_skill(SS_WEP_POLEARM,     skill_level);
    set_skill(SS_WEP_KNIFE,       skill_level);
    set_skill(SS_WEP_MISSILE,     skill_level + 15);
    set_skill(SS_WEP_CLUB,        skill_level);
    set_skill(SS_DEFENCE,         skill_level);
    set_skill(SS_PARRY,           skill_level);  
    set_skill(SS_2H_COMBAT,       skill_level); 
    set_skill(SS_AWARENESS,       (level * 10) + random(40));
    set_skill(SS_BLIND_COMBAT,    (level * 10) + random(40));
    set_skill(SS_HIDE,            skill_level);
    set_skill(SS_SNEAK,           skill_level);
    set_skill(SS_ANI_HANDL,       100);

    if(name_desc[0] == "magi")
    {
        add_name("_warfare_magus_");
        set_pname("magi");
        set_pshort(gAdj[gLevel] + " ogre magi");
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
create_throtyl_soldier()
{
    if ( !gLevel )
        set_throtyl_level();
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
 * Description  : Adds throtyl soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{

    // Magi gets the SoHM shadow added.
    if (sublevel == 4)
    {
        clone_object(MANA_SHADOW)->shadow_me(TO);

        soul_id = set_alarm(0.5, 0.0, &get_me_soul());
        seteuid(getuid());
        return;
    }

}

/* Function name: set_throtyl_description
 * Description  : Sets the long description of the throtyl, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-3.
 */
public string
set_throtyl_description(int level, int sublevel, string order)
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
                        " goblin archer from one of the tribes that lair " +
                        "in the thick forest of Throtyl. A vicious fighter " +
                        "with no sense of honour or justice, this brute " +
                        "has no interest beyond killing and eating.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " hobgoblin marauder, a larger version of their goblin " +
                        "cousins, with their brutal and vicious traits scaling " +
                        "with its size! Revelling in the chaos of the times, " +
                        "this hobgoblin roams with his tribe, attacking outlying " +
                        "settlements.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " bugbear, a large hulking brute of a creature covered " +
                        "in fur. Aggressive and vicious, this bugbear revels in " +
                        "the fear of its enemies and the death screams of " +
                        "its victims.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " ogre marauder, a massive brute from the Throtyl forest. " +
                        "Slow, but incredibly strong, this is one " +
                        "enemy you do not want to get hit by!\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " ogre magi, a rare ogre spellcaster that combines " +
                        "the strength and constitution of their ogre brethren with " +
                        "the intelligence and cunning of a wizard. They are not a foe " +
                        "to be taken lightly!\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " ogre magi, a rare ogre spellcaster that combines " +
                        "the strength and constitution of their ogre brethren with " +
                        "the intelligence and cunning of a wizard. They are not a foe " +
                        "to be taken lightly!\n";
                break;
            }
            break;
        }
    }  
  
    return str;    
}

void
init_warfare_item(object ob, int level, int slot)
{
    string area = "throtyl";
    if(ob->query_krynn_warfare_weapon())
    {
        ob->set_weapon_level(level, slot, area);
        ob->update_warfare_weapon();
        ob->set_color(area);
    }
    else
    {
        ob->set_armour_level(level, slot, area);
        ob->update_warfare_armour();

        if (slot == A_TORSO)
            ob->set_color(area);
    }
    wield_wear_item(ob);
}


void
arm_me()
{
    setuid();
    seteuid(getuid());

    string wep1, wep2, shield;
    int hand_type;
    int wielding_bow = 0;
    int weapon_type = random(10);

    switch(weapon_type)
    {
        case 0: // 10% chance 2 handed warhammer
        {
            wep1 = (WEP_PATH + "std_warfare_hammer");

            hand_type = W_BOTH;
        }
        break;
        case 1..2: // 20% chance 1 handed hammer
        {
            wep1 = (WEP_PATH + "std_warfare_hammer");

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 3..7: // 50% chance 2 handed axe
        {
            wep1 = (WEP_PATH + "std_warfare_axe");
            hand_type = W_BOTH;
        }
        break;
        default:
        {
            wep1 = (WEP_PATH + "std_warfare_axe");

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
    }

    // Archers by nature wield bows
    if(gSublevel == 0)
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

         wep1 = (WEP_PATH + "std_warfare_bow");

         hand_type = W_BOTH;
         wielding_bow = 1;
         wep2 = 0;
         shield = 0;

         add_act("take arrows");     
    }

    // Magi by nature wield staves!
    if(gSublevel == 4)
    {    
        wep1 = "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff";

        hand_type = W_BOTH;
        wep2 = 0;

        /* 10% chance of cloning a featherweight scroll */
        if(!random(10))
        {
            clone_object("/d/Krynn/common/scrolls/featherweight_scroll")->move(TO);
        }
    }

    equip(ARM_PATH + "std_warfare_armour", 1, &init_warfare_item(, 0, A_TORSO));
    equip(ARM_PATH + "std_warfare_helm", 1, &init_warfare_item(, 0, A_HEAD));
    equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_ARMS));
    equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_LEGS));

    equip(wep1, 1, &init_warfare_item(, gLevel, hand_type));
    equip(wep2, 1, &init_warfare_item(, gLevel, hand_type));
    equip(shield, 1, &init_warfare_item(, 1, A_SHIELD));


    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;
    add_prop(OBJ_M_HAS_MONEY, ({ 0, sc, gc, 0 }));
}

public void
update_throtyl_soldier()
{
    string throtyl_adj = gAdj[gLevel];

    set_pick_up_team(({ "_throtyl_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_throtyl_warfare_npc_");    
    add_adj(throtyl_adj);    

    setuid();
    seteuid(getuid(TO));     
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    set_all_hitloc_unarmed((gLevel * 5));

    // Well armoured with special attack
    set_exp_factor(110 + (gLevel * 10));

    add_prop(CONT_I_WEIGHT, (100000 * gSublevel) + random(10000));
    add_prop(CONT_I_HEIGHT, 160 + (60 * gSublevel));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);

    set_act_time(25);
    add_act("assist");


    set_cact_time(25);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote snarls in fury.");

    arm_me();
}

void
create_krynn_monster()
{
    create_throtyl_soldier();
    update_throtyl_soldier(); 
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
        TO->command("hide");
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
        command("scream angril");
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

    // Magus uses spells
    if (gSublevel == 4) 
    {
        if (attacktype == 0 || attacktype == 1)
        {
           if(!("/d/Krynn/guilds/sohm/spells/blur"->has_spell_object(TO)))
           {
             // Cast blur if not in effect
              command("kadenadon");
              return 1;
           }
           if(switchspell == 1)
              command("apianak"); // fire dart
           else if(switchspell == 2)
              command("bakmadaingis"); // prismatic spray
           else
              command("arcanisvaes"); // magic missile

           return 1;
        }
        return 0;
    }

    if(!sizeof(query_weapon(-1)))
	return 0;

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    my_weapon = query_weapon(-1)[0];
    weapon    = my_weapon->query_short();
    
    if (attacktype == 1)
    {
	pen = query_pen_by_stat(TO->query_average_stat()) * mod;

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


void
init_living()
{
    ::init_living();
    init_team_pickup();      
}
