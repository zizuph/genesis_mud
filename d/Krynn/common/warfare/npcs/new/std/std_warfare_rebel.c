
/* This is a base file for warfare rebel Solamnian npcs.
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
public string   set_rebel_description(int level, int sublevel,
                    string order);
public void     setup_rebel_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "scarred", "experienced", "veteran", 
                  "merciless", "deadly", "legendary" });

object          gShadow, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting, soul_id;
void            get_me_soul();

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define KNIGHT_WF_MAGIC_WEAPON ({ "/d/Krynn/guilds/knights/guildhall/weapons/kn_lance", \
    "/d/Krynn/guilds/knights/guildhall/weapons/kclaymore", \
    "/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail", \
    "/d/Ansalon/taman_busuk/mountains/obj/greatsword" })

/* Function name: set_rebel_level
 * Description  : Sets the stat level of the rebel soldier.
 * Arguments    : int lev        0 - scarred (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - merciless (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - legendary (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - rebel
 *                               1 - pikeman
 *                               2 - militiaman
 *                               3 - vigilante
 *                               4 - swordsman
 *                               5 - noble
 *                               6 - longbowman
 *                               7 - hedge wizard
 *
 */
varargs void
set_rebel_level(int lev = 0, int sublev = 0, string order = "rebel")
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
    if (gSublevel > 7)
        gSublevel = 7;

    if ( !order )
        gOrder = "rebel";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_rebel_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_rebel_level
 * Description  : Returns the level of the rebel mob.
 */
public int
query_rebel_level()
{
    return gLevel;
}

/* Function name: query_rebel_sublevel
 * Description  : Returns the sublevel of the rebel mob.
 */
public int
query_rebel_sublevel()
{
    return gSublevel;
}

/* Function name: query_rebel_order
 * Description  : Returns the order of the rebel mob.
 */
public string
query_rebel_order()
{
    return gOrder;
}


/* Function name: setup_rebel_soldier
 * Description  : Sets the stats and skills of the rebel soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-7.
 */
public void
setup_rebel_soldier(int level, int sublevel, string order)
{
    string rebel_desc = set_rebel_description(gLevel, 
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
          name_desc = ({ "rebel" });
          break;
       case 1: 
          name_desc = ({ "pikeman" });
          break;
       case 2: 
          name_desc = ({ "militiaman" });
          break;
       case 3: 
          name_desc = ({ "vigilante" });
          break;
       case 4: 
          name_desc = ({ "swordsman" });
          break;
       case 5: 
          name_desc = ({ "noble" });
          break;
       case 6: 
          name_desc = ({ "longbowman" });
          break;
       case 7: 
          name_desc = ({ "wizard" });
          break;
       default: 
          name_desc = ({ "noble" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_warfare_npc_");
    add_name(name_desc);
    add_adj(order);

    if(sublevel == 5)
    {
        set_short(gAdj[gLevel] + " disenfranchised noble");
        add_adj("disenfranchised");
    }
    else if(sublevel == 7)
    {
        set_short(gAdj[gLevel] + " hedge wizard");
        add_adj("hedge");
    }
    else
        set_short(gAdj[gLevel] + " peasant " + name_desc[0]); 

    if(name_desc[0] == "swordsman")
    {
        set_pname("swordsmen");
        set_pshort(gAdj[gLevel] + " peasant swordsmen");
    }

    if(name_desc[0] == "longbowman")
    {
        set_pname("longbowmen");
        set_pshort(gAdj[gLevel] + " peasant longbowmen");
    }

    set_long(rebel_desc);
    set_alignment(0);
    set_knight_prestige(0);

    set_stats(({stat_level + random(5),         // str
                stat_level - random(5),         // dex
                stat_level + random(5),         // con 
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
    set_skill(SS_HIDE,            skill_level);
    set_skill(SS_SNEAK,           skill_level);
    set_skill(SS_ANI_HANDL,       100);

    if(name_desc[0] == "wizard")
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
create_rebel_soldier()
{
    if ( !gLevel )
        set_rebel_level();
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
 * Description  : Adds rebel soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{
    // Wizard gets the SoHM shadow added.
    if (sublevel == 7)
    {
        clone_object(MANA_SHADOW)->shadow_me(TO);

        soul_id = set_alarm(0.5, 0.0, &get_me_soul());
        seteuid(getuid());
        return;
    }
               
}

/* Function name: set_rebel_description
 * Description  : Sets the long description of the rebel, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-7.
 */
public string
set_rebel_description(int level, int sublevel, string order)
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
                        " peasant who has risen up against the feudal " +
                        "Solamnic lords in rebellion. Harsh winters " +
                        "and starving families have driven many to " +
                        "take up arms to take what they can for " +
                        "survival.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " pikeman who has take up arms against the feudal " +
                        "Solamnic lords in rebellion. Harsh winters " +
                        "and famine common in these dark times have driven " +
                        "many to anarchist acts of brutality for survival.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " militiaman who has take up arms against the feudal " +
                        "Solamnic lords in rebellion. Once an authority " +
                        "of law enforcement, this soldier has fallen to acts " +
                        "of banditry and opportunistic brutality during these " +
                        "times of darkness.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " peasant warrior who has risen against his feudal " +
                        "Solamnic lords in vengeance for perceived injustices " +
                        "against the peasants and countrymen of the land. " +
                        "Merciless in his vengeance, this vigilante will " +
                        "stop at nothing to bring the Solamnian Knighthood " +
                        "down.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " peasant swordsman who has risen against his feudal " +
                        "Solamnic lords as much out of opportunistic personal " +
                        "gain as for any perceived injustices. A skilled " +
                        "warrior, he has no qualms equiping himself with " +
                        "the finest Solamnian equipment left by his defeated " +
                        "foes.\n"; 
                break;
                case 5:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " disenfranchised noble who has stirred the fervour " +
                        "of rebellion against his fellow Solamnic lords, " +
                        "taking advantage of famine and harsh winters to " +
                        "cause the countryside to rise against their feudal " +
                        "masters. A skilled tactician and masterful warrior, " +
                        "this foe is not one to be taken lightly.\n";
                break;
                case 6:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " peasant longbowman who has risen against his feudal " +
                        "Solamnic lords as much out of opportunistic personal " +
                        "gain as for any perceived injustices. A skilled " +
                        "archer, he has no qualms in using his skills to take " +
                        "advantage of these chaotic times.\n"; 
                break;
                case 7:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " hedge wizard who has been swept up in the rebellion " +
                        "against the feudal Solamnic lords. Long been persecuted " +
                        "and distrusted by the Knighthood and their followers, this " +
                        "uprising has provided the perfect scenario for " +
                        "past injustices to spellcasters to be avenged.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " disenfranchised noble who has stirred the fervour " +
                        "of rebellion against his fellow Solamnic lords, " +
                        "taking advantage of famine and harsh winters to " +
                        "cause the countryside to rise against their feudal " +
                        "masters. A skilled tactician and masterful warrior, " +
                        "this foe is not one to be taken lightly.\n";
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
    string area = "rebel";
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

    string wep1, wep2, body, helm, greaves, gauntlets, special, shield;
    int hand_type, special_chance;
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
            if(gLevel > 4)
            {
            
                string special = KNIGHT_WF_MAGIC_WEAPON[3];
                special_chance = gLevel;

                if (!random(5))
                    wep1 = KNIGHT_WF_MAGIC_WEAPON[1];
                else
                    wep1 = (WEP_PATH + "std_warfare_sword");
            }
            else if(gLevel > 2)
            {
                special = KNIGHT_WF_MAGIC_WEAPON[1];
                special_chance = 5 + gLevel; 

                wep1 = WEP_PATH + "std_warfare_sword";
            }
            else
                wep1 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_BOTH;
        }
        break;
        case 2..4: // 30% chance 1 handed sword
        {
            wep1 = (WEP_PATH + "std_warfare_sword");

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 5: // 10% chance 2 handed warhammer
        {
            wep1 = (WEP_PATH + "std_warfare_hammer");

            hand_type = W_BOTH;
        }
        break;
        case 6: // 10% chance 1 handed hammer
        {
            special = KNIGHT_WF_MAGIC_WEAPON[2];
            special_chance = (5 + gLevel);
            wep1 = WEP_PATH + "std_warfare_hammer";

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 7: // 10% chance 2 handed polearm
        {
           // WARFARE_DEBUG("2 handed pole called");

            if(gLevel > 2)
            {
                special = KNIGHT_WF_MAGIC_WEAPON[0];
                special_chance = (5 + gLevel);
                wep1 = WEP_PATH + "std_warfare_polearm";
            }
            else
                wep1 = (WEP_PATH + "std_warfare_polearm");

            hand_type = W_BOTH;
        }
        break;
        case 8: // 10% chance 1 handed polearm
        {
           // WARFARE_DEBUG("1 handed pole called");

            wep1 = (WEP_PATH + "std_warfare_polearm");

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        case 9: // 10% chance 2 handed axe
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

    // Pikeman by nature wield pikes!
    if(gSublevel == 1)
    {    
        if(gLevel > 2)
        {
            special = KNIGHT_WF_MAGIC_WEAPON[0];
            special_chance = (5 + gLevel);
            wep1 = WEP_PATH + "std_warfare_polearm";
        }
        else
            wep1 = (WEP_PATH + "std_warfare_polearm");

        hand_type = W_BOTH;
        wep2 = 0;
    }

    // Swordsman by nature wield swords!
    if(gSublevel == 4)
    {    
        if(!random(3))
        {
            if(gLevel > 2)
            {
                special = KNIGHT_WF_MAGIC_WEAPON[1];
                special_chance = (5 + gLevel);
                wep1 = WEP_PATH + "std_warfare_sword";
            }
            else
                wep1 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_BOTH;
        }
        else
        {
            wep1 = (WEP_PATH + "std_warfare_sword");

            if(random(3)) // 66% chance of shield, 33% second weapon
                shield = (ARM_PATH + "std_warfare_shield");
            else
                wep2 = (WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
    }

    // Archers by nature wield bows!
    if(gSublevel == 6)
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
        wep2 = 0;  
        shield = 0;

        add_act("take arrows");     
    }

    // Wizard by nature wield staves!
    if(gSublevel == 7)
    {    
        wep1 = ("/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff");

        hand_type = W_BOTH;
        wep2 = 0;
        shield = 0;

        /* 10% chance of cloning a gravity scroll */
        if(!random(10))
        {
            clone_object("/d/Krynn/common/scrolls/gravity_scroll")->move(TO);
        }
    }


    if (special) {
        equip(clone_unique(special, special_chance, wep1), 1, &init_warfare_item(, gLevel, hand_type));
    } else {
        equip(wep1, 1, &init_warfare_item(, gLevel, hand_type));
    }

    equip(wep2, 1, &init_warfare_item(, gLevel, hand_type));

    equip(ARM_PATH + "std_warfare_armour", 1, &init_warfare_item(, 0, A_TORSO));
    equip(ARM_PATH + "std_warfare_helm", 1, &init_warfare_item(, 0, A_HEAD));
    equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_ARMS));
    equip(ARM_PATH + "std_warfare_grv_gnt", 1, &init_warfare_item(, 0, A_LEGS));

    if (hand_type != W_BOTH)
        equip(shield, 1, &init_warfare_item(, gLevel, A_SHIELD));

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;
    add_prop(OBJ_M_HAS_MONEY, ({ 0, sc, gc, 0 }));
}

public void
update_rebel_soldier()
{
    string rebel_adj = gAdj[gLevel];

    set_pick_up_team(({ "_rebel_warfare_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_rebel_warfare_npc_");
    set_race_name("human");    
    set_adj("rebel");
    add_adj(rebel_adj);    

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
    add_act("say First the gods forsook us, then the knights abandoned us.");
    add_act("say Dark times in Solamnia... the winter was harsh, and the " +
        "land again faces famine.");
    add_act("emote shakes with fury at the thought of the food horded behind " +
        "the castle walls of the Solamnian feudal lords.");
    add_act("say We will drive the Solamnian lords from their castles and " +
        "take their stores of food!");
    add_act("say Honour doesn't fill the belly.");
    add_act("say We worked the fields and paid taxes for the promise " +
        "of protection! The Solamnian lords will pay for their deception!");
    add_act("say Famine and plague we suffer through, but the heavy taxes " +
        "of the Solamnia lords is just banditry! No more I say!");
    add_act("say No longer will we accept their feudal claim to the land! " +
        "We demand the right to our own land, or we will take it from them!");
    add_act("say Castle Brightblade has been razed, and Castle di Caela has " +
        "fallen! Next Vingaard Keep!");

    set_cact_time(45);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote snarls in fury.");
    add_cact("emote attacks with the desperation of one who has nothing to " +
        "lose.");

    arm_me();
}

void
create_krynn_monster()
{
    create_rebel_soldier();
    update_rebel_soldier(); 

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
        command("emote screams: 'Die then scum!'");
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
 * Description  : The code of a rebel special attacks.
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

    // Wizard uses spells
    if (gSublevel == 7) 
    {
        if (attacktype == 0 || attacktype == 1)
        {
           if(!("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(TO)))
           {
             // Cast magic shield if not in effect
              command("arcanfethos");
              return 1;
           }
           if(switchspell == 1)
              command("arcanisvaes"); // magic missile
           else if(switchspell == 2)
              command("xarzithnar"); // ice strike
           else
              command("bakmadaingis"); // prismatic spray

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
  	        "you in a cunning attack, " + how + " your " +
	        hitloc[wloc] + ".\n");
	    tell_watcher(QCTNAME(TO) + " strikes at " + QTNAME(enemy) +
	        " in a cunning attack, " + how + " " + QTPNAME(enemy) + 
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

        if((WAR_CLUB_ADMIN->query_warfare_army(killer) == "Free People"))
        {
            WAR_CLUB_ADMIN->set_time_attacked_own_army(killer);
        }

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
