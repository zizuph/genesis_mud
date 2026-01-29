
/* This is a base file for warfare knight npcs.
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

inherit M_FILE
inherit AUTO_TEAM
inherit "/std/act/add_things";
inherit "/d/Krynn/std/act/actions";
inherit "/lib/unique";

inherit "/d/Genesis/specials/npc/stat_based_specials";

public void    setup_guild_stuff(int level, int sublevel, string colour);
public string   set_knight_description(int level, int sublevel,
                    string order);
public void     setup_knight_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "gallant", "experienced", "veteran", 
                  "fearless", "heroic", "elite" });

object          gShadow, horse, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define KNIGHT_DIR            "/d/Krynn/guilds/knights/"

#define KNIGHT_MAGIC_ARMOUR ({ "/d/Krynn/guilds/knights/guildhall/armours/scalearmour" })

#define KNIGHT_WF_MAGIC_WEAPON ({ "/d/Krynn/guilds/knights/guildhall/weapons/kn_lance", \
    "/d/Krynn/guilds/knights/guildhall/weapons/kclaymore", \
    "/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail" })

/* Function name: set_knight_level
 * Description  : Sets the stat level of the knight soldier.
 * Arguments    : int lev        0 - gallant (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - fearless (155 stat average)
 *                               4 - heroic (170 stat average)
 *                               5 - elite (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - scout / pikeman
 *                               1 - auxillary / nobleman
 *                               2 - footman / Crown knight
 *                               3 - squire / Sword knight
 *                               4 - Crown knight / Rose knight
 *                               5 - archer / longbowman
 *
 */
varargs void
set_knight_level(int lev = 0, int sublev = 0, string order = "crown")
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
        gOrder = "crown";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_knight_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_knight_level
 * Description  : Returns the level of the knight mob.
 */
public int
query_knight_level()
{
    return gLevel;
}

/* Function name: query_knight_sublevel
 * Description  : Returns the sublevel of the knight mob.
 */
public int
query_knight_sublevel()
{
    return gSublevel;
}

/* Function name: query_knight_order
 * Description  : Returns the order of the knight mob.
 */
public string
query_knight_order()
{
    return gOrder;
}

int
query_dragonfear_immunity()
{
    if (gLevel < 2)
        return 1;
    else
        return 0;
}

/* Function name: setup_knight_soldier
 * Description  : Sets the stats and skills of the knight soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-5.
 */
public void
setup_knight_soldier(int level, int sublevel, string order)
{
    string knight_desc = set_knight_description(gLevel, 
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
          if(level > 2)
              name_desc = ({ "pikeman" });
          else
              name_desc = ({ "scout" });
          break;
       case 1: 
          if(level > 2)
              name_desc = ({ "nobleman" });
          else
              name_desc = ({ "auxillary" });
          break;
       case 2: 
          if(level > 2)
              name_desc = ({ "knight", "crown knight" });
          else
              name_desc = ({ "footman" });
          break;
       case 3: 
          if(level > 2)
              name_desc = ({ "knight", "sword knight" });
          else
              name_desc = ({ "squire" });
          break;
       case 4: 
          if(level > 2)
              name_desc = ({ "knight", "rose knight" });
          else
              name_desc = ({ "knight", "crown knight" });
          break;
       default: 
          if(level > 2)
              name_desc = ({ "longbowman" });
          else
              name_desc = ({ "archer" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_warfare_npc_");
    add_name(name_desc);
    add_adj(order);
    set_short(gAdj[gLevel] + " Solamnian " + name_desc[0]); 
    set_long(knight_desc);
    set_alignment(400 + (gLevel * 100));
    set_knight_prestige(- (gLevel * 15));

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
    set_skill(SS_RIDING,          100);
    set_skill(SS_ANI_HANDL,       100);
    set_skill(SS_MOUNTED_COMBAT,  100);

}

public void
create_knight_soldier()
{
    if ( !gLevel )
        set_knight_level();
}


/* Function name: setup_guild_stuff
 * Description  : Adds knight soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{
    if ( level < 3 || sublevel < 1 )
        if(sublevel != 4)
            return;
        
    /* First we remove any old shadow used */
    if(objectp(gShadow))
    {
	gShadow->remove_shadow();
    }

    /* Now we add desired shadow */
    gShadow = clone_object(KNIGHT_DIR + "shadows/occ_shadow");

    if(gShadow->shadow_me(TO, "occupational", "fighter", 
        "Solamnian Knights") != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }
    else
    {
	// gShadow->set_promotion_level(rank);
    }

    /* We add also soul and initialize commands */
    remove_cmdsoul(gSoul);
    gSoul = KNIGHT_DIR + "souls/solamnian_soul";
    add_cmdsoul(gSoul);
    load_command_souls();
        
}

/* Function name: set_knight_description
 * Description  : Sets the long description of the knight, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-5.
 */
public string
set_knight_description(int level, int sublevel, string order)
{
    string str = "";
    
    switch (level) 
    {
        case 0..2:
        {
            switch(sublevel)
            {
                case 0:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " scout of the Solamnian armed forces. Lightly " +
                        "armed and armoured, scouts like this one are " +
                        "commonly used as the vanguard of an advancing " +
                        "army.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " militiaman recruited in as an auxillary for " +
                        "the armed forces commanded by the knights of " +
                        "Solamnia.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " footman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " squire of the order of the Solamnian knights, " +
                        "one who has proven to be honourable enough to " +
                        "be sponsored and begin the military training " +
                        "that will lead to full knighthood.\n"; 
                break;
                case 4:
                    str = "Based on the symbols decorating the tunic of " +
                        "this warrior, you are looking upon " +
                        LANG_ADDART(gAdj[level])+ " knight of Solamnia of " +
                        "the Order of the Crown.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " archer recruited from the provinces by the armed " +
                        "forces of the knights of Solamnia.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " footman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
                break;
            }
            break;
        }
        case 3..5:
        {
            switch(sublevel)
            {
                case 0:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " pikeman of the Solamnian armed forces.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " nobleman fighting for glory and honour with " +
                        "the armed forces commanded by the knights of " +
                        "Solamnia.\n"; 
                break;
                case 2:
                    str = "Based on the symbols decorating the tunic of " +
                        "this warrior, you are looking upon " +
                        LANG_ADDART(gAdj[level])+ " knight of Solamnia of " +
                        "the Order of the Crown.\n"; 
                break;
                case 3:
                    str = "Based on the symbols decorating the tunic of " +
                        "this warrior, you are looking upon " +
                        LANG_ADDART(gAdj[level])+ " knight of Solamnia of " +
                        "the Order of the Sword.\n"; 
                break;
                case 4:
                    str = "Based on the symbols decorating the tunic of " +
                        "this warrior, you are looking upon " +
                        LANG_ADDART(gAdj[level])+ " knight of Solamnia of " +
                        "the Order of the Rose.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " longbowman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " pikeman of the Solamnian armed forces.\n"; 
                break;
            }
            break;
        }
        default:
        {
            switch(sublevel)
            {
                case 0:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " scout of the Solamnian armed forces. Lightly " +
                        "armed and armoured, scouts like this one are " +
                        "commonly used as the vanguard of an advancing " +
                        "army.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " militiaman recruited in as an auxillary for " +
                        "the armed forces commanded by the knights of " +
                        "Solamnia.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " footman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " squire of the order of the Solamnian knights, " +
                        "one who has proven to be honourable enough to " +
                        "be sponsored and begin the military training " +
                        "that will lead to full knighthood.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " footman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " archer recruited from the provinces by the armed " +
                        "forces of the knights of Solamnia.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " footman recruited by the armed forces of the " +
                        "knights of Solamnia.\n"; 
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
        case 0..1: // 20% chance 2 handed sword
        {
            if(gLevel > 2)
                wep1 = clone_unique(KNIGHT_WF_MAGIC_WEAPON[1], (5 + gLevel), 
                    WEP_PATH + "std_warfare_sword");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_BOTH;
        }
        break;
        case 2..4: // 30% chance 1 handed sword
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_sword");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 5: // 10% chance 2 handed warhammer
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_hammer");

            hand_type = W_BOTH;
        }
        break;
        case 6: // 10% chance 1 handed hammer
        {
            wep1 = clone_unique(KNIGHT_WF_MAGIC_WEAPON[2], (5 + gLevel), 
                    WEP_PATH + "std_warfare_hammer");

            if(random(3)) // 66% chance of shield, 33% second weapon
                wep2 = clone_object(ARM_PATH + "std_warfare_shield");
            else
                wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 7: // 10% chance 2 handed polearm
        {
           // WARFARE_DEBUG("2 handed pole called");

            if(gLevel > 2)
                wep1 = clone_unique(KNIGHT_WF_MAGIC_WEAPON[0], 
                    (5 + gLevel), WEP_PATH + "std_warfare_polearm");
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_polearm");

            hand_type = W_BOTH;
        }
        break;
        case 8: // 10% chance 1 handed polearm
        {
           // WARFARE_DEBUG("1 handed pole called");

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

    // Pikeman by nature wield pikes!
    if((gLevel > 2) && (gSublevel == 0))
    {    
        wep1->remove_object();
        wep2->remove_object();

        if(gLevel > 2)
            wep1 = clone_unique(KNIGHT_WF_MAGIC_WEAPON[0], 
                (5 + gLevel), WEP_PATH + "std_warfare_polearm");
        else
            wep1 = clone_object(WEP_PATH + "std_warfare_polearm");

        hand_type = W_BOTH;
        wep2 = 0;
    }

    // Archers by nature wield bows!
    if(gSublevel == 5)
    {
        wep1->remove_object();
        wep2->remove_object();

        object quiver = clone_object(WEP_PATH + "std_quiver");
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

        // Secondary weapon 
        object wep_sec = clone_object(WEP_PATH + "std_warfare_sword");
        wep_sec->set_weapon_level(gLevel, W_ANYH, "knights");
        wep_sec->update_warfare_weapon();
        wep_sec->move(TO, 1);

        add_act("take arrows");     
    }

    if(gLevel > 2)
        body = clone_unique(ONE_OF(KNIGHT_MAGIC_ARMOUR), (5 + gLevel),
            ARM_PATH + "std_warfare_armour");
    else
        body = clone_object(ARM_PATH + "std_warfare_armour");

    helm = clone_object(ARM_PATH + "std_warfare_helm");
    greaves = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    gauntlets = clone_object(ARM_PATH + "std_warfare_grv_gnt");

    body->set_armour_level(gLevel, A_TORSO, "knights");
    body->update_warfare_armour();
    helm->set_armour_level(gLevel, A_HEAD, "knights");
    helm->update_warfare_armour();
    greaves->set_armour_level(gLevel, A_ARMS, "knights");
    greaves->update_warfare_armour();
    gauntlets->set_armour_level(gLevel, A_LEGS, "knights");
    gauntlets->update_warfare_armour();
    
    if(wep1->query_krynn_warfare_weapon())
    {
        wep1->set_weapon_level(gLevel, hand_type, "knights");
        wep1->update_warfare_weapon();
    } 

    if(wep2)
    {
        if(wep2->query_krynn_warfare_weapon())
        {
            wep2->set_weapon_level(gLevel, hand_type, "knights");
            wep2->update_warfare_weapon();
        }
        else
        {
            wep2->set_armour_level(gLevel, A_SHIELD, "knights");
            wep2->update_warfare_armour();
        }
    }

    if(!wep2)
        equip(({ wep1, body, helm, greaves, gauntlets }));
    else
        equip(({ wep1, wep2, body, helm, greaves, gauntlets }));

    wep1->set_color("knights");
    body->set_color("knights");

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;

    MONEY_MAKE_HERE_GC(gc);
    MONEY_MAKE_HERE_SC(sc);
}

public void
update_knight_soldier()
{
    string knight_adj = gAdj[gLevel];

    set_pick_up_team(({ "_knight_warfare_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_knight_warfare_npc_");
    set_race_name("human");    
    set_adj("solamnian");
    add_adj(knight_adj);    

    setuid();
    seteuid(getuid(TO));     
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    set_all_hitloc_unarmed((gLevel * 5));

    // Well armoured with special attack
    set_exp_factor(110 + (gLevel * 10));

    add_prop(CONT_I_WEIGHT, 70000 + random(10000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);

    set_act_time(25);
    add_act("assist");
    add_act("kbrush");
    add_act("kdanger");
    add_act("ksmooth");
    add_act("kchant");
    add_act("kmagic");
    add_act("ksing");
    add_act("ksweat");
    add_act("kstudy");
    add_act("ktend");
    add_act("kswear");

    set_cact_time(25);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote snarls in fury.");
    add_cact("say For Solamnia!");
    add_cact("ksalute2");
    add_cact("kstern");
    add_cact("kdeclare");
    add_cact("kpledge");

    arm_me();
}

void
horse_me(object me)
{
    horse = clone_object("/d/Krynn/common/warfare/npcs/knight/knight_horse"); 
    horse->set_owner(TO);
    horse->move(E(TO));
    shadow = clone_object("/d/Krynn/common/warfare/npcs/knight/cavalry_npc_shadow");
    shadow->shadow_me(this_object(), "layman", "fighter", "Solamnian Cavalry");
    this_object()->command("mount horse");
}

void
create_krynn_monster()
{
    create_knight_soldier();
    update_knight_soldier(); 

    if(gLevel > 2)
        if((gSublevel == 4) || (gSublevel == 3))
            set_alarm(1.0, 0.0, &horse_me(this_object()));
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
        fighting = 0;
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
        command("emote roars 'You fool! Your remains will feed carrion!'");
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
        command("roar");
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


public void
action_attack(object enemy)
{
    // WARFARE_DEBUG("Action attack called in knight_base");

    if (!objectp(enemy))
        return;
    
    command("kill " + OB_NAME(enemy));
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

    attacktype = random(6);   

    if(!sizeof(query_weapon(-1)))
    {
        command("wield sword");
	return 0;
    }

    if(!CAN_SEE_IN_ROOM(TO) && (gLevel > 2))
    {
        if(!random(3))
            command("say Magical darkness! Break out the torches "+
                "and lanterns!");
        setuid();
        seteuid(getuid());
        object torch = clone_object("/d/Krynn/common/warfare/armours/torch");
        torch->move(TO, 1);
        command("light all");

        map(query_team_others(), &->notify_attack_on_team(this_object(),
            enemy));

    }

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
            // WARFARE_DEBUG("Missile check.");

            if(!my_weapon->find_projectiles())
            {
                // WARFARE_DEBUG("Missile check 2.");

                command("gasp");
                command("say I am out of arrows!");
                command("unwield all");

                setuid();
                seteuid(getuid());

                object new_weapon = clone_object(WEP_PATH + "std_warfare_sword");
                new_weapon->set_weapon_level(gLevel, W_BOTH, "knights");
                new_weapon->move(TO, 1);

                command("wield sword");
                return 1;
            }

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

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
    {
        if ( !random(2) )
            command("curse");

	return;
    }

    if(!CAN_SEE_IN_ROOM(TO))
    {
        if(!random(4))
            command("say Magical darkness! Break out the torches "+
                "and lanterns!");
        setuid();
        seteuid(getuid());
        object torch = clone_object("/d/Krynn/common/warfare/armours/torch");
        torch->move(TO, 1);
        command("light all");
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
            gLevel, "knight");

        killer_army = WAR_CLUB_ADMIN->query_warfare_army(killer);
        WAR_CLUB_ADMIN->increase_krynn_war_kills(killer_army, 1);
        WAR_CLUB_ADMIN->increase_krynn_war_player_kills(killer, 1);

        if((WAR_CLUB_ADMIN->query_warfare_army(killer) == "Free People") ||
            (WAR_CLUB_ADMIN->query_warfare_army(killer) == "Neidar Clan"))
        {
            set_alignment(0);
        }

        if((WAR_CLUB_ADMIN->query_warfare_army(killer) == "Knights"))
        {
            WAR_CLUB_ADMIN->set_time_attacked_own_army(killer);
        }
    }

    if(gLevel > 2)
        if((gSublevel == 4) || (gSublevel == 3))
            horse->remove_warfare_warhorse();

    ::do_die(killer);
}

public void
attacked_by(object attacker)
{
    if((WAR_CLUB_ADMIN->query_warfare_army(attacker) == "Knights"))
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
