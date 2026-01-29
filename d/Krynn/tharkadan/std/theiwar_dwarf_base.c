
/* This is a base file for dark dwarf npcs.
 *
 *
 * Usage: inherit this file and define function:
 *
 * public void
 * create_dark_dwarf()
 * {
 *     set_dwarf_level(level);
 * }
 *
 *   Where level is number from range 1-3.
 *
 *   1 - Theiwar miner 
 *   2 - dwarven axeman
 *   3 - dwarven dark savant
 *
 * Dark savants are magic using dwarves and inherit SoHM guild spells.
 *
 * Arman July 2017.  
 */

#pragma  strict_types

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <options.h>
#include <login.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/sohm/defs.h"
#include "/d/Genesis/gems/gem.h"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define WEAPON   ({ WEP + "theiwar_pickaxe", WEP + "theiwar_waraxe", \
                    WEP + "theiwar_hammer" })

#define ARM1     ARMOUR + "theiwar_chainmail"
#define ARM2     ARMOUR + "theiwar_gauntlets"
#define ARM3     ARMOUR + "theiwar_greaves"
#define ARM4     ARMOUR + "theiwar_helm"
#define ARM5     ARMOUR + "theiwar_leather"
#define SHIELD   ARMOUR + "theiwar_shield"

#define WAND     "/d/Krynn/solace/poolbottom/obj/wand"
#define ROBE     ARMOUR + "grey_robe"
#define SCROLL   "/d/Krynn/common/scrolls/ballistic_spray_scroll"

#define DARK_DWARF_ENEMY  "_dark_dwarf_enemy_"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/equip";
inherit "/d/Krynn/std/act/actions";

varargs void    setup_guild_stuff(int level);
public string   set_dwarf_description(int level);
public void     setup_dark_dwarf(int level);

string *gAdj = ({ "pale", "grey-bearded", "scarred", "intolerant",
                   "unfriendly", "dour", "grim", "gnarled", "angry", 
                   "wild-eyed" });

object          gShadow;
string          gSoul;
int             gLevel, calm_alarm, fighting;


/* Function name: set_dwarf_level
 * Description  : Sets the level of the dwarf guard.
 * Arguments    : int lev        1 - miner
 *                               2 - axeman
 *                               3 - savant
 *                               If not given, level is random (1-3).
 *
 */
varargs void
set_dwarf_level(int lev = 0)
{
    if ( !lev )
        gLevel = 1 + random(3);
    else
        gLevel = lev;
    
    (gLevel < 1) ? 1 : gLevel;
    (gLevel > 3) ? 3 : gLevel;
        
    setup_guild_stuff(gLevel);
    setup_dark_dwarf(gLevel);

}

/* Function name: query_dwarf_level
 * Description  : Returns the level of the dwarf.
 */
public int
query_dwarf_level()
{
    return gLevel;
}

/* Function name: setup_dark_dwarf
 * Description  : Sets the stats and skills of the dwarf guard
 *                depending on his level.
 * Arguments    : int level           - range 1-3.
 */
public void
setup_dark_dwarf(int level)
{
    string dwarf_desc = set_dwarf_description(gLevel);

    set_name("dark_dwarf");
    set_long(dwarf_desc);

    switch(level)
    {
       case 1:
          set_stats(({120, 90, 120, 95, 95, 110 }));
          break;
       case 2:
          set_stats(({140, 110, 140, 115, 115, 145 }));
          break;
       default:
          set_stats(({120, 110, 140, 140, 140, 145 }));
          break;
    }
 
    switch(level)
    {  
       case 1..2: 
          set_skill(SS_WEP_AXE,         80 + random(20));
          set_skill(SS_WEP_CLUB,        80 + random(20));
          set_skill(SS_DEFENCE,         80 + random(20));
          set_skill(SS_PARRY,           80 + random(20));
          set_skill(SS_AWARENESS,       30 + random(40));
          set_skill(SS_BLIND_COMBAT,    30 + random(40));
          break;
       default:
          set_skill(SS_SPELLCRAFT, 75 + random(20));
          set_skill(SS_FORM_ENCHANTMENT, 75 + random(20));
          set_skill(SS_FORM_CONJURATION, 75 + random(20));
          set_skill(SS_FORM_DIVINATION, 75 + random(20));
          set_skill(SS_FORM_ABJURATION, 75 + random(20));
          set_skill(SS_FORM_ILLUSION, 75 + random(20));
          set_skill(SS_FORM_TRANSMUTATION, 75 + random(20));
          set_skill(SS_ELEMENT_FIRE, 75 + random(20));
          set_skill(SS_ELEMENT_EARTH, 75 + random(20));
          set_skill(SS_ELEMENT_WATER, 75 + random(20));
          set_skill(SS_ELEMENT_AIR, 75 + random(20));
          set_skill(SS_DEFENCE,         40 + random(20));
          set_skill(SS_PARRY,           40 + random(20));
          set_skill(SS_AWARENESS,       30 + random(40));
          break;
    }

    // resistance to magic and poison
    add_prop(OBJ_I_RES_MAGIC, 5);
    add_prop(OBJ_I_RES_POISON, 5);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);

    add_prop(LIVE_I_ATTACK_THIEF, 1);
 
    if ( level < 2 )
        return;

}

public void
create_dark_dwarf()
{
    if ( !gLevel )
        set_dwarf_level();
}

/* Function name: setup_guild_stuff
 * Description  : Adds SoHM soul and shadow if neccessary.
 * Arguments    : int level          - range 1-3.
 */
public void
setup_guild_stuff(int level)
{
    if ( level < 3 )
        return;
        
    clone_object(MANA_SHADOW)->shadow_me(TO);
    add_cmdsoul(SOHM_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul("/d/Genesis/specials/guilds/shadows/mana_shadow");
    update_hooks(); 
        
}

/* Function name: set_dwarf_description
 * Description  : Sets the long description of the dwarf, depending on
 *                his level.
 * Arguments    : int level        - range 1-3.
 */
public string
set_dwarf_description(int level)
{
    string str = "";
    
    switch (level) 
    {
    case 0..1:
        str = "This stocky pale-skinned dwarf is a miner of the Theiwar " +
              "clan - known for their xenophobia and intolerance of " +
              "other races, including other dwarf clans!\n"; 
    break;
    case 2:
        str = "This stocky pale-skinned dwarf is a warrior of the " +
              "Theiwar clan - known for their xenophobia and " +
              "intolerance of other races, including other dwarf clans!\n"; 
    break;
    default:
        str = "This robed figure is a dark savant - a magic-using " +
              "dwarf! While magic isn't tolerated amongst the majority " +
              "of dwarven clans, the Theiwar clans have embraced it " +
              "and are very skilled at the Dark Arts.\n";
    break;
    }
    
    return str;
    
}

// To avoid cloning a gem that wouldn't be found through mining

object
clone_dwarf_gem()
{
    object gem = RANDOM_GEM_BY_RARITY(GEM_EXTREMELY_RARE);

    if(gem->query_name() == "coral")
      gem = clone_object("/d/Genesis/gems/obj/agate");
    if(gem->query_name() == "pearl")
      gem = clone_object("/d/Genesis/gems/obj/peridot");
    if(gem->query_name() == "black_pearl")
      gem = clone_object("/d/Genesis/gems/obj/topaz_yellow");

    return gem;
}

void
create_krynn_monster()
{
    string dwarf_adj = ONE_OF(gAdj);

    create_dark_dwarf();
        
    set_pick_up_team(({ "dark_dwarf" }));
    set_max_team_size_auto_join(8);

    set_race_name("dwarf");    
    set_adj("theiwar");
    add_adj("dark");
    add_adj("dwarven");
    add_adj(dwarf_adj);

    setuid();
    seteuid(getuid(TO));

    switch(TO->query_dwarf_level())
    {
       case 0..1:
         equip(({ WEAPON[0], ARM1, ARM2, ARM3, clone_dwarf_gem(), 
             clone_dwarf_gem() }));
         add_name("miner");
         set_short(dwarf_adj + " dwarven miner");
         set_act_time(15);
         add_act("rsay Neidar dwarves are barely better than gully " +
             "dwarves. They smell as bad!");
         add_act("emote expertly inspects the wall of the tunnel " +
              "for mineral veins.");
         add_act("emote tirelessly strikes the wall of the tunnel " +
              "with his pickaxe.");
         break;
       case 2:
         equip(({ WEAPON[1], ARM1, ARM2, ARM3, ARM4, SHIELD, 
             clone_dwarf_gem(), clone_dwarf_gem(), clone_dwarf_gem() }));
         add_name("axeman");
         add_pname("axemen");
         set_short(dwarf_adj + " dwarven axeman");
         set_pshort(dwarf_adj + " dwarven axemen");
         set_act_time(35);
         add_act("rsay Curse the Hylar clan!");
         add_act("rsay We must ensure a Theiwar is the next High King " +
             "of Thorbardin.");
         add_act("emote inspects his waraxe carefully.");
         add_act("emote looks at you with deep suspicion and distrust.");
         break;
       default:
         equip(({ WAND, ROBE, ARM2, ARM3, ARM4, ARM5, clone_dwarf_gem(),
                  clone_dwarf_gem(), clone_dwarf_gem() }));
         if(random(5) == 1)
            equip(({ SCROLL }));
         add_name("savant");
         set_short(dwarf_adj + " dark savant");
         set_act_time(25);
         add_act("rsay We must ensure a Theiwar is the next High King " +
              "of Thorbardin.");
         add_act("sstudy");
         add_act("emote looks at you with deep suspicion and distrust.");
         add_act("rsay I waste my time here. Take me to the altar " +
                 "where I can make a sacrifice to Nuitari the Ungod!");
         break;
    }         
    
    set_gender("G_MALE");    
    set_hp(query_max_hp());
    set_alignment(-900);
    set_aggressive(0, 100);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 10);  

    set_default_answer("The dark dwarf has no interest in conversing " +
         "with you.\n");

    set_cact_time(25);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote roars 'By the Nightreaver!' in fury!");
    add_cact("say The tortures I will put you through!");
    add_cact("say Slay the intruder!");    
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
    if ( !enemy->query_prop(DARK_DWARF_ENEMY) )
        enemy->add_prop(DARK_DWARF_ENEMY, 1);
    
    if ( fighting == 1 )
        return;
    
    switch ( random(3) )
    {
    case 0:
        command("say Fool! Ye shall die now!");
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
        command("emote roars 'Curses! You'll pay for that!'");
    break;
    default:
        command("curse dwarvishly");
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
 * Description  : The code of a dwarven special attacks.
 */
int
special_attack(object enemy)
{
    int    attacktype, pen, wloc, light_level;
    mixed  hitres;
    string *hitloc, how, how1, how2, how3, weapon;
    object my_weapon;

    attacktype = random(6);
    light_level = E(TO)->query_prop(OBJ_I_LIGHT);

    // Savant casts spells here... to add
    if(gLevel == 3)
    {
       if(!("/d/Krynn/guilds/sohm/spells/blur"->has_spell_object(TO)))
       {
         // Cast the blur spell if not in effect
          command("kadenadon");
          return 1;
       }

       if(!P("_SoHM_gloom_object", E(TO)))
       {
         // Cast the gloom spell if not in effect
          command("whedabra");
          return 1;
       }

        if(attacktype > 1)
          return 0;

        if(random(4) == 1)
          command("okiai");  // Dazzle spell
        else
          command("tonashingis"); // Ballistic spray spell

        return 1;
    }

    if(!sizeof(query_weapon(-1)))
	return 0;

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    my_weapon = query_weapon(-1)[0];
    weapon    = my_weapon->query_short();
    
    if (attacktype == 1)
    {
       if(light_level > 0)
       {
           if(light_level > random(10))
           {
              command("emote is dazzled by the bright light and " +
                  "aborts his attack.");
              return 0;
           }
       }

	pen = 350 + (gLevel * 50);

	if ( my_weapon->query_wt() == W_CLUB )
   	    hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);
        else if( my_weapon->query_dt() == W_IMPALE )
   	    hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);
        else
            hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

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

        if ( my_weapon->query_wt() == W_CLUB )
            how = how1;
        else if( my_weapon->query_dt() == W_IMPALE )
            how = how3;
        else
            how = how2;
            
	enemy->catch_msg(QCTNAME(TO) + " charges at " +
  	    "you in a furious attack, " + how + " your " +
	    hitloc[wloc] + ".\n");

	tell_watcher(QCTNAME(TO) + " charges at " + QTNAME(enemy) +
	    " in a furious rage, " + how + " " + QTNAME(enemy) + "'s" +
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
