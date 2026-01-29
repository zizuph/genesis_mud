
/* This is a base file for warfare Neidar npcs.
 *
 * Arman Sept 2018.  
 * 
 * Cotillion - 2020-05-12
 * - Fixed cloning of weapons into the void
 */
#pragma strict_types

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
public string   set_neidar_description(int level, int sublevel,
                    string order);
public void     setup_neidar_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "scarred", "experienced", "veteran", 
                  "grizzled", "deadly", "legendary" });

object          gShadow, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define NEIDAR_RACIAL_ENEMIES \
    ({ "goblin", \
        "troll", \
        "giant", \
        "orc", \
        "hill giant", \
        "minotaur", \
        "ogre", \
        "half-ogre", \
        "ogre-magi", \
        "uruk", \
        "hobgoblin" \
    })


/* Function name: set_neidar_level
 * Description  : Sets the stat level of the neidar soldier.
 * Arguments    : int lev        0 - scarred (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - grizzled (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - legendary (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - wayfinder / hammerer
 *                               1 - trailblazer / longbeard
 *                               2 - adventurer / slayer
 *                               3 - clansman / battlerager
 *                               4 - axeman / chieftain
 *                               5 - sniper / sharpshooter
 *
 */
varargs void
set_neidar_level(int lev = 0, int sublev = 0, string order = "neidar")
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
        gOrder = "neidar";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_neidar_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_neidar_level
 * Description  : Returns the level of the neidar mob.
 */
public int
query_neidar_level()
{
    return gLevel;
}

/* Function name: query_neidar_sublevel
 * Description  : Returns the sublevel of the neidar mob.
 */
public int
query_neidar_sublevel()
{
    return gSublevel;
}

/* Function name: query_neidar_order
 * Description  : Returns the order (in this case clan) of the neidar mob.
 */
public string
query_neidar_order()
{
    return gOrder;
}

/* Function name: setup_neidar_soldier
 * Description  : Sets the stats and skills of the neidar soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-5.
 */
public void
setup_neidar_soldier(int level, int sublevel, string order)
{
    string neidar_desc = set_neidar_description(gLevel, 
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
              name_desc = ({ "hammerer" });
          else
              name_desc = ({ "wayfinder" });
          break;
       case 1: 
          if(level > 2)
              name_desc = ({ "longbeard" });
          else
              name_desc = ({ "trailblazer" });
          break;
       case 2: 
          if(level > 2)
              name_desc = ({ "slayer" });
          else
              name_desc = ({ "adventurer" });
          break;
       case 3: 
          if(level > 2)
              name_desc = ({ "battlerager" });
          else
              name_desc = ({ "clansman" });
          break;
       case 4: 
          if(level > 2)
              name_desc = ({ "chieftain" });
          else
              name_desc = ({ "axeman" });
          break;
       default: 
          if(level > 2)
              name_desc = ({ "sharpshooter" });
          else
              name_desc = ({ "sniper" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_warfare_npc_");
    add_name(name_desc);

    if(name_desc[0] == "clansman")
        set_pname("clansmen");
    if(name_desc[0] == "axeman")
        set_pname("axemen");

    add_adj(order);
    set_short(gAdj[gLevel] + " dwarven " + name_desc[0]); 

    if(name_desc[0] == "clansman")
        set_pshort(gAdj[gLevel] + " dwarven clansmen");
    if(name_desc[0] == "axeman")
        set_pshort(gAdj[gLevel] + " dwarven axemen");

    set_long(neidar_desc);
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
create_neidar_soldier()
{
    if ( !gLevel )
        set_neidar_level();
}


/* Function name: setup_guild_stuff
 * Description  : Adds neidar soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{
    if ( level < 3 || sublevel < 1 )
        if(sublevel != 4)
            return;
        
    // This is where we add guild souls if we desire 

    /* First we remove any old shadow used */
    if(objectp(gShadow))
    {
	gShadow->remove_shadow();
    }

    /* Now we add desired shadow */
    gShadow = clone_object("/d/Ansalon/guild/neidar/shadows/occ_shadow");

    if(gShadow->shadow_me(TO, "occupational", "fighter", 
        "Dwarven Warriors of the Neidar Clan") != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }

    /* We add also soul and initialize commands */
    remove_cmdsoul(gSoul);
    gSoul = "/d/Ansalon/guild/neidar/souls/cmdsoul";
    add_cmdsoul(gSoul);
    load_command_souls();
        
}

/* Function name: set_neidar_description
 * Description  : Sets the long description of the neidar, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-5.
 */
public string
set_neidar_description(int level, int sublevel, string order)
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
                        " wayfinder of the Neidar Clan. Lightly " +
                        "armed and armoured, hill dwarves like this one are " +
                        "often explorers, guides and spies.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " trailblazer of the Neidar Clan. Lightly " +
                        "armed and armoured - for a dwarf - this warrior " +
                        "commonly scouts ahead for advancing dwarven war " +
                        "throngs.\n";
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " adventurer of the Neidar Clan. Young and keen to " +
                        "make a name for himself, this hill dwarf seeks " +
                        "battle and glory against the armies across the realm.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " clansman of the Neidar Clan. Well " +
                        "armed and armoured, these fearless hill dwarf warriors " +
                        "form the backbone of dwarven war throngs.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " axeman of the Neidar Clan. Armed with sharp " +
                        "dwarven axes, these fearless hill dwarf warriors " +
                        "are dangerous in battle and are at the forefront " +
                        "of dwarven war throngs in any clash.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " sniper of the Neidar Clan. Uncommon amongst the hill " +
                        "dwarves - who consider archers a little queer - these experts " +
                        "with shortbows play an important part in engaging at range " +
                        "with enemies before dwarven war throngs march in to range.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " axeman of the Neidar Clan. Armed with sharp " +
                        "dwarven axes, these fearless hill dwarf warriors " +
                        "are dangerous in battle and are at the forefront " +
                        "of dwarven war throngs in any clash.\n"; 
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
                        " hammerer of the Neidar Clan. Armed with great " +
                        "dwarven warhammers and heavily armoured, these " +
                        "respected hill dwarf warriors are feared for crushing " +
                        "holes through the ranks of their enemies.\n";  
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " longbeard of the Neidar Clan, a highly respected " +
                        "hill dwarf elder and a veteran of many battles.\n";  
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " slayer of the Neidar Clan, one who has taken an " +
                        "oath to die gloriously in battle. As fearless as " +
                        "he is armourless, this dwarven berserker is covered " +
                        "with glorious tattoos and long scars, and fights " +
                        "with an almost mystical hardiness.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " battlerager of the Neidar Clan. Held in reverence " +
                        "and no small amount of nervousness by his fellow " +
                        "dwarven warriors, battleragers are renown for their " +
                        "madness and irrational behaviour. Believing that if " +
                        "killed in battle they return to the earth to be reborn " +
                        "even stronger, they have no fear of death.\n"; 
                break;
                case 4:
                    str = "Before you stands " +LANG_ADDART(gAdj[level])+ 
                        " chieftain of the Neidar Clan, a mighty dwarven " +
                        "warrior who leads his people with a wise hand in " +
                        "their hillborn strongholds as well as with a " +
                        "implacable fury on the battlefield. Not one to " +
                        "be crossed, as a grievance against a dwarf such as " +
                        "this is a grudge only appeased with blood.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " sharpshooter of the Neidar Clan. Uncommon amongst the hill " +
                        "dwarves - who consider archers a little queer - these experts " +
                        "with shortbows have the patience of the mountains when " +
                        "seeking out a mark on the battlefield and an accuracy " +
                        "unrivalled amongst their kin.\n"; 
                break;
                default:
                    str = "Before you stands " +LANG_ADDART(gAdj[level])+ 
                        " chieftain of the Neidar Clan, a mighty dwarven " +
                        "warrior who leads his people with a wise hand in " +
                        "their hillborn strongholds as well as with a " +
                        "implacable fury on the battlefield. Not one to " +
                        "be crossed, as a grievance against a dwarf such as " +
                        "this is a grudge only appeased with blood.\n"; 
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
                        " wayfinder of the Neidar Clan. Lightly " +
                        "armed and armoured, hill dwarves like this one are " +
                        "often explorers, guides and spies.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " trailblazer of the Neidar Clan. Lightly " +
                        "armed and armoured - for a dwarf - this warrior " +
                        "commonly scouts ahead for advancing dwarven war " +
                        "throngs.\n";
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " adventurer of the Neidar Clan. Young and keen to " +
                        "make a name for himself, this hill dwarf seeks " +
                        "battle and glory against the armies across the realm.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " clansman of the Neidar Clan. Well " +
                        "armed and armoured, these fearless hill dwarf warriors " +
                        "form the backbone of dwarven war throngs.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " axeman of the Neidar Clan. Armed with sharp " +
                        "dwarven axes, these fearless hill dwarf warriors " +
                        "are dangerous in battle and are at the forefront " +
                        "of dwarven war throngs in any clash.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " sniper of the Neidar Clan. Uncommon amongst the hill " +
                        "dwarves - who consider archers a little queer - these experts " +
                        "with shortbows play an important part in engaging at range " +
                        "with enemies before dwarven war throngs march in to range.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " axeman of the Neidar Clan. Armed with sharp " +
                        "dwarven axes, these fearless hill dwarf warriors " +
                        "are dangerous in battle and are at the forefront " +
                        "of dwarven war throngs in any clash.\n"; 
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
    string area = "neidar";
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

    string shield, wep1, wep2, body, helm, greaves, gauntlets;
    int hand_type;
    int weapon_type = random(20);

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
        case 0: // 5% chance 2 handed sword
        {
            wep1 = (WEP_PATH + "std_warfare_sword");
            hand_type = W_BOTH;
        }
        break;
        case 1: // 5% chance 1 handed sword
        {
            wep1 = (WEP_PATH + "std_warfare_sword");
            shield = (ARM_PATH + "std_warfare_shield");
            hand_type = W_ANYH;
        }
        break;
        case 2..5: // 20% chance 2 handed club
        {
            wep1 = (WEP_PATH + "std_warfare_hammer");
            hand_type = W_BOTH;
        }
        break;
        case 6..9: // 20% chance 1 handed hammer
        {
            wep1 = (WEP_PATH + "std_warfare_hammer");
            shield = (ARM_PATH + "std_warfare_shield");
            hand_type = W_ANYH;
        }
        break;
        case 10..14: // 25% chance 2 handed axe
        {
            wep1 = (WEP_PATH + "std_warfare_axe");
            hand_type = W_BOTH;
        }
        break;
        default:
        {
            wep1 = (WEP_PATH + "std_warfare_axe");
            shield = (ARM_PATH + "std_warfare_shield");
            hand_type = W_ANYH;
        }
        break;
    }

    // Axemen by nature wield axes!
    if((gLevel < 3) && (gSublevel == 4))
    {    
        wep1 = (WEP_PATH + "std_warfare_axe");
        hand_type = W_BOTH;
        wep2 = 0;
        shield = 0;
    }

    // Hammerers by nature wield hammers!
    if((gLevel > 2) && (gSublevel == 0))
    {    
        wep1 = (WEP_PATH + "std_warfare_hammer");
        hand_type = W_BOTH;
        wep2 = 0;
        shield = 0;
    }

    // Archers by nature wield bows!
    if (gSublevel == 5)
    {
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

        wep1 = (WEP_PATH + "std_warfare_bow");
        hand_type = W_BOTH;
        wep2 = 0;  
        shield = 0;

        add_act("take arrows");     
    }

    equip(wep1, 1, &init_warfare_item(, gLevel, hand_type));
    equip(wep2, 1, &init_warfare_item(, gLevel, hand_type));

    // If a slayer they have no armour, but natural AC
    if((gLevel > 2) && (gSublevel == 2))
    {
        set_all_hitloc_unarmed((gLevel * 12));
    } 
    else 
    { 
        equip(ARM_PATH + "std_warfare_armour", 1, &init_warfare_item(, 0, A_TORSO));
        equip(ARM_PATH + "std_warfare_helm", 1, &init_warfare_item(, 0, A_HEAD));
        equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_ARMS));
        equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_LEGS));

        if (hand_type != W_BOTH)
            equip(shield, 1, &init_warfare_item(, gLevel, A_SHIELD));
    }

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;

    add_prop(OBJ_M_HAS_MONEY, ({ 0, sc, gc, 0 }));
}

public void
update_neidar_soldier()
{
    string neidar_adj = gAdj[gLevel];

    set_pick_up_team(({ "_neidar_warfare_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_neidar_warfare_npc_");
    set_race_name("dwarf");    
    set_adj("dwarf");
    add_adj(neidar_adj);    

    setuid();
    seteuid(getuid(TO));     
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    set_all_hitloc_unarmed((gLevel * 5));

    // Well armoured with special attack
    set_exp_factor(110 + (gLevel * 10));

    add_prop(CONT_I_WEIGHT, 70000 + random(10000));
    add_prop(CONT_I_HEIGHT, 110 + random(40));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_act_time(25);
    add_act("drest");
    add_act("dlaugh");
    add_act("dbang");
    add_act("dsong");
    add_act("dsong2");
    add_act("dsmirk");
    add_act("dstare");

    set_cact_time(25);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote snarls in fury.");
    add_cact("dfury");
    add_cact("doutrage");
    add_cact("dcrouch");
    add_cact("say By Reorx's beard!");

    arm_me();
}

void
create_krynn_monster()
{
    create_neidar_soldier();
    update_neidar_soldier(); 
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

/* Function name: special_attack
 * Description  : The code of a neidar special attacks.
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

    string enemy_race = enemy->query_race();
    string enemy_race_name = enemy->query_race_name();

    foreach (string race : NEIDAR_RACIAL_ENEMIES)
    {
        if (wildmatch("*" + race, enemy_race) || 
            wildmatch ("*" + race, enemy_race_name))
        {
	    tell_watcher(QCTPNAME(TO) + " eyes burn with racial " +
                "hatred!\n");

            // Hill dwarves do more damage against racial enemies.            
            pen = pen * 100 / 80;

            // WARFARE_DEBUG("Special pen post racial check: " +pen+ ".");
        }
    }

        hitres = enemy->hit_me(pen, my_weapon->query_dt(), TO, -1);

	wloc = random(5);

        if (hitres[0] < 0)
            hitres[0] = 0;

        switch(hitres[0])
        {
            case 0:
                how0 = "just missing";
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
                how0 = "piercing deeply into";
                how1 = "slamming his " + weapon + " hard into";
                how2 = "slicing his " + weapon + " deeply into";
                how3 = "piercing his " + weapon + " deeply into";
	    break;
            case 21..40:
                how0 = "deeply penetrating";
                how1 = "his " + weapon + " crushing";
	        how2 = "his " + weapon + " deeply penetrating";
	        how3 = "his " + weapon + " deeply penetrating";
	    break;
            case 41..60:
                how0 = "burying deeply into";
                how1 = "smashing his " + weapon + " powerfully into";
	        how2 = "burying his " +weapon+ " deeply into";
	        how3 = "burying his " +weapon+ " deeply into";
	    break;
            default:	
                how0 = "nastily impaling";
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
  	        "barrage of arrows at you, " + how + " your " +
	        hitloc[wloc] + ".\n");
	    tell_watcher(QCTNAME(TO) + " launches a barrage of arrows " +
                "at " + QTNAME(enemy) + ", " + how + " " + QTPNAME(enemy) + 
	        " " + hitloc[wloc] + ".\n", enemy);
        }
        else
        {            
	    enemy->catch_msg(QCTNAME(TO) + " charges into you in " +
  	        "a dwarven rage, " + how + " your " +
	        hitloc[wloc] + ".\n");
	    tell_watcher(QCTNAME(TO) + " charges into " + QTNAME(enemy) +
	        " in a dwarven rage, " + how + " " + QTPNAME(enemy) + 
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
            gLevel, "neidar");

        killer_army = WAR_CLUB_ADMIN->query_warfare_army(killer);
        WAR_CLUB_ADMIN->increase_krynn_war_kills(killer_army, 1);
        WAR_CLUB_ADMIN->increase_krynn_war_player_kills(killer, 1);

    }

    if((WAR_CLUB_ADMIN->query_warfare_army(killer) == "Free People") ||
        (WAR_CLUB_ADMIN->query_warfare_army(killer) == "Knights"))
    {
        set_alignment(0);
    }

    ::do_die(killer);
}

public void
attacked_by(object attacker)
{
    if((WAR_CLUB_ADMIN->query_warfare_army(attacker) == "Neidar Clan"))
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
