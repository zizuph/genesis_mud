
/* This is a base file for warfare qualinesti elf npcs.
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
public string   set_elf_description(int level, int sublevel,
                    string order);
public void     setup_elf_soldier(int level, int sublevel, 
                    string order);

string *gAdj = ({ "skillful", "experienced", "veteran", 
                  "heroic", "deadly", "elite" });

object          gShadow, shadow;
string          gSoul, gOrder;
int             gLevel, gSublevel, calm_alarm, fighting, soul_id;
void            get_me_soul();

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

#define ARCHER_DIR      "/d/Krynn/guilds/elven_archers/"
#define SS_FOCUS        108500
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define ELF_MAGIC_ARMOUR ({ "/d/Krynn/qualinesti/arm/ashchain" })

#define ELF_MAGIC_WEAPON ({ "/d/Krynn/qualinesti/wep/silver_bow", \
    "/d/Krynn/qualinesti/wep/ash_bow" })

/* Function name: set_elf_level
 * Description  : Sets the stat level of the elf soldier.
 * Arguments    : int lev        0 - skillful (112 stat average)
 *                               1 - experienced (125 stat average)
 *                               2 - veteran (140 stat average)
 *                               3 - heroic (155 stat average)
 *                               4 - deadly (170 stat average)
 *                               5 - elite (190 stat average)
 *                               If not given, level is scarred (0).
 *
 *              : int sublev     0 - scout
 *                               1 - ranger
 *                               2 - skirmisher
 *                               3 - archer
 *                               4 - magus
 *
 */
varargs void
set_elf_level(int lev = 0, int sublev = 0, string order = "qualinesti")
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
        gOrder = "qualinesti";
    else
        gOrder = order;
        
    setup_guild_stuff(gLevel, gSublevel, gOrder);
    setup_elf_soldier(gLevel, gSublevel, gOrder);

}

/* Function name: query_elf_level
 * Description  : Returns the level of the elf mob.
 */
public int
query_elf_level()
{
    return gLevel;
}

/* Function name: query_elf_sublevel
 * Description  : Returns the sublevel of the elf mob.
 */
public int
query_elf_sublevel()
{
    return gSublevel;
}

/* Function name: query_elf_order
 * Description  : Returns the order of the elf mob.
 */
public string
query_elf_order()
{
    return gOrder;
}


/* Function name: setup_elf_soldier
 * Description  : Sets the stats and skills of the elf soldier
 *                depending on his level.
 * Arguments    : int level           - range 0-5.
 *              : int sublevel        - range 0-4.
 */
public void
setup_elf_soldier(int level, int sublevel, string order)
{
    string elf_desc = set_elf_description(gLevel, 
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
          name_desc = ({ "scout" });
          break;
       case 1: 
          name_desc = ({ "ranger" });
          break;
       case 2: 
          name_desc = ({ "skirmisher" });
          break;
       case 3: 
          name_desc = ({ "archer" });
          break;
       default: 
          name_desc = ({ "magus" });
          break;
    }

    add_name(name_desc[0]);
    add_name("_warfare_npc_");
    add_name(name_desc);
    add_adj(order);
    set_short(gAdj[gLevel] + " elven " + name_desc[0]); 
    set_long(elf_desc);
    set_alignment(400 + (gLevel * 100));
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
    set_skill(SS_WEP_MISSILE,     skill_level + 15);
    set_skill(SS_WEP_CLUB,        skill_level);
    set_skill(SS_DEFENCE,         skill_level);
    set_skill(SS_PARRY,           skill_level);  
    set_skill(SS_2H_COMBAT,       skill_level); 
    set_skill(SS_AWARENESS,       (level * 10) + random(40));
    set_skill(SS_BLIND_COMBAT,    (level * 10) + random(40));
    set_skill(SS_HIDE,            skill_level);
    set_skill(SS_SNEAK,           skill_level);
    set_skill(SS_FOCUS,           skill_level);
    set_skill(SS_ANI_HANDL,       100);

    if(name_desc[0] == "magus")
    {
        add_name("_warfare_magus_");
        set_pname("magi");
        set_pshort(gAdj[gLevel] + " elven magi");
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
create_elf_soldier()
{
    if ( !gLevel )
        set_elf_level();
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
 * Description  : Adds elf soul and shadow if neccessary.
 */
public void
setup_guild_stuff(int level, int sublevel, string colour)
{

    // Magus gets the SoHM shadow added.
    if (sublevel == 4)
    {
        clone_object(MANA_SHADOW)->shadow_me(TO);

        soul_id = set_alarm(0.5, 0.0, &get_me_soul());
        seteuid(getuid());
        return;
    }
        
    /* First we remove any old shadow used */
    if(objectp(gShadow))
    {
	gShadow->remove_shadow();
    }

    /* Now we add desired shadow */
    gShadow = clone_object(ARCHER_DIR + "lib/occ_shadow");

    if(gShadow->shadow_me(TO, "occupational", "ranger", 
        "Ansalon Elvish Archers") != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }
    else
    {
        gShadow->init_guild_member();
    }

    /* We add also soul and initialize commands */
    remove_cmdsoul(gSoul);
    gSoul = ARCHER_DIR + "lib/archer_soul";
    add_cmdsoul(gSoul);
    load_command_souls();
        
}

/* Function name: set_elf_description
 * Description  : Sets the long description of the elf, depending 
 *                on his level.
 * Arguments    : int level        - range 0-5
 *              : int sublevel     - range 0-4.
 */
public string
set_elf_description(int level, int sublevel, string order)
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
                        " elven scout of the Qualinesti elves. Lightly " +
                        "armed and armoured, scouts like this one " +
                        "range through their sylvan forests and are only " +
                        "seen if they choose to be.\n"; 
                break;
                case 1:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " elven ranger of the Qualinesti elves. Both " +
                        "hunters and protectors of the sylvan forests, " +
                        "they are experts with the bow.\n"; 
                break;
                case 2:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " elven skirmisher of the Qualinesti elves. " +
                        "A trained warrior, this elf is proficient in " +
                        "the art of ambush and hit-and-run tactics against " +
                        "uninvited forces that enter their sylvan forests.\n"; 
                break;
                case 3:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " elven archer of the Qualinesti elves. Renown " +
                        "throughout the realms as the most deadly of " +
                        "user of the longbow, these elves are capable of " +
                        "raining death upon their enemies from great " +
                        "range.\n"; 
                break;
                case 4:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " elven magi of the Qualinesti elves. Revered " +
                        "amongst the elven people as masters of magic, " +
                        "they are foes not to be taken lightly.\n"; 
                break;
                default:
                    str = "This is " +LANG_ADDART(gAdj[level])+ 
                        " elven magus of the Qualinesti elves. Revered " +
                        "amongst the elven people as masters of magic, " +
                        "they are foes not to be taken lightly.\n";
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

    object wep1, wep2, body, helm, greaves, gauntlets, cloak;
    int hand_type;
    int wielding_bow = 0;
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
        case 0: // 10% chance 2 handed sword
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_sword");
            wep2 = 0;

            hand_type = W_BOTH;
        }
        break;
        case 1: // 10% chance 1 handed sword
        {
            wep1 = clone_object(WEP_PATH + "std_warfare_sword");
            wep2 = clone_object(WEP_PATH + "std_warfare_sword");

            hand_type = W_ANYH;
        }
        break;
        default: // 80% chance of bow
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

            if(gLevel > 2)
                wep1 = clone_unique(ONE_OF(ELF_MAGIC_WEAPON), (5 + gLevel), 
                    WEP_PATH + "std_warfare_bow");  
            else
                wep1 = clone_object(WEP_PATH + "std_warfare_bow");

            hand_type = W_BOTH;
            wielding_bow = 1;
            wep2 = 0;

            add_act("take arrows");     
        }
        break;
    }

    // Archers by nature wield bows
    if((gSublevel == 3) && !(wielding_bow))
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

         if(gLevel > 2)
             wep1 = clone_unique(ONE_OF(ELF_MAGIC_WEAPON), (5 + gLevel), 
                 WEP_PATH + "std_warfare_bow");  
         else
             wep1 = clone_object(WEP_PATH + "std_warfare_bow");

         hand_type = W_BOTH;
         wielding_bow = 1;
         wep2 = 0;

         add_act("take arrows");     
    }

    // Magi by nature wield staves!
    if(gSublevel == 4)
    {    
        wep1 = clone_object("/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff");

        hand_type = W_BOTH;
        wep2 = 0;

        /* 10% chance of cloning a featherweight scroll */
        if(!random(10))
        {
            clone_object("/d/Krynn/common/scrolls/featherweight_scroll")->move(TO);

        }
    }

    if(gLevel > 2)
        body = clone_unique(ONE_OF(ELF_MAGIC_ARMOUR), (5 + gLevel),
            ARM_PATH + "std_warfare_armour");
    else
        body = clone_object(ARM_PATH + "std_warfare_armour");

    helm = clone_object(ARM_PATH + "std_warfare_helm");
    greaves = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    gauntlets = clone_object(ARM_PATH + "std_warfare_grv_gnt");
    cloak = clone_object("/d/Krynn/qualinesti/arm/cloak");

    body->set_armour_level(gLevel, A_TORSO, "qualinesti");
    body->update_warfare_armour();
    helm->set_armour_level(gLevel, A_HEAD, "qualinesti");
    helm->update_warfare_armour();
    greaves->set_armour_level(gLevel, A_ARMS, "qualinesti");
    greaves->update_warfare_armour();
    gauntlets->set_armour_level(gLevel, A_LEGS, "qualinesti");
    gauntlets->update_warfare_armour();


    
    if(wep1->query_krynn_warfare_weapon())
    {
        if(wielding_bow && (gLevel < 3)) // elves use longbows
            wep1->set_weapon_level(3, hand_type, "qualinesti");
        else
            wep1->set_weapon_level(gLevel, hand_type, "qualinesti");

        wep1->update_warfare_weapon();
    } 

    if(wep2)
    {
        if(wep2->query_krynn_warfare_weapon())
        {
            wep2->set_weapon_level(gLevel, hand_type, "qualinesti");
            wep2->update_warfare_weapon();
        }
        else
        {
            wep2->set_armour_level(gLevel, A_SHIELD, "qualinesti");
            wep2->update_warfare_armour();
        }
    }

    if(!wep2)
        equip(({ wep1, body, helm, greaves, gauntlets, cloak }));
    else
        equip(({ wep1, wep2, body, helm, greaves, gauntlets, cloak }));

    wep1->set_color("qualinesti");
    body->set_color("qualinesti");

    // mobs drop 0-5 gold coins and 5-9 silver coins
    int gc = min(6, (random(gLevel) + gLevel));
    int sc = random(gLevel) + 5;

    MONEY_MAKE_HERE_GC(gc);
    MONEY_MAKE_HERE_SC(sc);
}

public void
update_elf_soldier()
{
    string elf_adj = gAdj[gLevel];

    set_pick_up_team(({ "_qualinesti_warfare_npc_" }));
    set_max_team_size_auto_join(8);
        
    add_name("_qualinesti_warfare_npc_");
    set_race_name("elf");    
    set_adj("elven");
    add_adj(elf_adj);    

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
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(OBJ_I_HIDE, 30); // elves start hidden

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
    create_elf_soldier();
    update_elf_soldier(); 

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
        command("emote screams: 'You fool! Your remains will feed the forest!'");
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
    command("dfear");
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
