
/* This is a base file for hill dwarf warfare npcs.
 *
 *
 * Usage: inherit this file and define function:
 *
 * public void
 * create_hill_dwarf()
 * {
 *     set_dwarf_level(level);
 * }
 *
 *   Where level is number from range 1-4.
 *
 *   1 - dwarven clansmen 
 *   2 - dwarven warrior
 *   3 - dwarven battlerager
 *   4 - elite dwarven battlerager
 *
 * Dwarves of level 2-4 are also Shieldbearers.
 *
 * 6.01.2004, Blizzard.
 *   
 */

#pragma  strict_types

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/guild/shieldbearers/guild.h"
#include <wa_types.h>
#include <options.h>
#include <login.h>

#define WEP      "/d/Ansalon/estwilde/obj/weapon/"
#define ARMOUR   "/d/Ansalon/estwilde/obj/armour/"
#define KRSTUFF  "/d/Krynn/haven/dwarf_camp/"

#define ARM1        ARMOUR + "leggings"
#define ARM2        ARMOUR + "i_gauntlets"
#define ARM3        ARMOUR + "i_boots"
#define HELMS    ({ ARMOUR + "horned_helmet", KRSTUFF + "arm/helm" })
#define SHIELDS  ({ ARMOUR + "shield", ARMOUR + "shield2", \
                    KRSTUFF + "arm/shield" })
#define WPS      ({ WEP + "iron_axe", WEP + "warhammer", \
                    KRSTUFF + "wep/waraxe", KRSTUFF + "wep/sword", \
                    KRSTUFF + "wep/mace" })
#define ARMS     ({ ARMOUR + "chainmail", KRSTUFF + "arm/chainmail", \
                    KRSTUFF + "arm/leather_armour" })

#define HILL_DWARF_ENEMY  "_hill_dwarf_enemy_"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/equip";
inherit "/d/Krynn/std/act/actions";

string *gAdj1 = ({ "grumpy", "gruff", "scarred", "jovial", "friendly",
                   "stout", "old", "young", "gnarled", "angry", 
                   "muscular" });
string *gAdj2 = ({ "black-bearded", "fork-bearded", "red-bearded",
                   "brown-bearded", "long-bearded", "grey-bearded" });

varargs void    setup_guild_stuff(int level);
public string   set_dwarf_description(int level);
public void     setup_hill_dwarf(int level);

object          gShadow;
string          gSoul;
int             gLevel, calm_alarm, fighting;


/* Function name: set_dwarf_level
 * Description  : Sets the level of the dwarf guard.
 * Arguments    : int lev        1 - clansman
 *                               2 - warior
 *                               3 - battlerager
 *                               4 - elite battlerager
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
    (gLevel > 4) ? 4 : gLevel;
        
    setup_guild_stuff(gLevel);
    setup_hill_dwarf(gLevel);

}

/* Function name: query_dwarf_level
 * Description  : Returns the level of the dwarf.
 */
public int
query_dwarf_level()
{
    return gLevel;
}

/* Function name: setup_hill_dwarf
 * Description  : Sets the stats and skills of the dwarf guard
 *                depending on his level.
 * Arguments    : int level           - range 1-4.
 */
public void
setup_hill_dwarf(int level)
{
    string dwarf_desc = set_dwarf_description(gLevel);

    set_long(dwarf_desc);

    set_base_stat(SS_STR, 75 + (level * 20) + random(level * 10));
    set_base_stat(SS_DEX, 65 + (level * 10) + random(level * 5));
    set_base_stat(SS_CON, 75 + (level * 20) + random(level * 10));
    set_base_stat(SS_INT, 65 + (level * 10) + random(level * 5));
    set_base_stat(SS_WIS, 65 + (level * 10) + random(level * 5));
    set_base_stat(SS_DIS, 75 + (level * 20) + random(level * 8));
    
    set_skill(SS_WEP_SWORD,       60 + (level * 10));
    set_skill(SS_WEP_AXE,         60 + (level * 10));
    set_skill(SS_WEP_CLUB,        60 + (level * 10));
    set_skill(SS_UNARM_COMBAT,    60 + (level * 10));
    set_skill(SS_DEFENCE,         60 + (level * 10));
    set_skill(SS_PARRY,           60 + (level * 10));
    set_skill(SS_AWARENESS,       20 + (level * 10));
    set_skill(SS_BLIND_COMBAT,    30 + (level * 10));
    set_skill(SS_APPR_MON,        40 + (level * 10));
 
    if ( level < 2 )
        return;
 
    set_skill(SHIELDSLAM_SPECIAL, 84 + (level * 4));

}

public void
create_hill_dwarf()
{
    if ( !gLevel )
        set_dwarf_level();
}

/* Function name: setup_guild_stuff
 * Description  : Adds Shieldbearers soul and shadow if neccessary.
 * Arguments    : int level          - range 1-4.
 */
public void
setup_guild_stuff(int level)
{
    if ( level < 2 )
        return;
    
    level = 20 + level * 30;
    
    if ( objectp(gShadow) )
    {
        TO->clear_guild_stat(SS_LAYMAN);
    }
    
    gShadow = clone_object(GUILD_SHADOW);
    
    if ( gShadow->shadow_me(TO, "layman", GUILD_STYLE, GUILD_NAME) != 1 )
    {
        "secure/master"->do_debug("destroy", gShadow);
    }
    else
    {
        TO->set_base_stat(SS_LAYMAN, level, 10);
    }

    remove_cmdsoul(gSoul);
    gSoul = GUILD_CMDSOUL;
    add_cmdsoul(gSoul);
    load_command_souls();
        
}

/* Function name: set_dwarf_description
 * Description  : Sets the long description of the dwarf, depending on
 *                his level.
 * Arguments    : int level        - range 1-4.
 */
public string
set_dwarf_description(int level)
{
    string str = "";
    
    switch (level) 
    {
    case 0..1:
        str = "This lightly-armoured dwarf does not look happy to be " +
              "sent here, as he probably would prefer to sit in a tavern " +
              "and drink an ale or two. However, at his side swings a " +
              "well-used weapon - after all, even a regular dwarven " +
              "clansman is a decent warrior.\n"; 
    break;
    case 2:
        str = "This tough dwarf is well equipped and from beneath " +
              "his helmet dark eyes peer out watchfully. " +
              "Being a skilled warrior of the Clan he takes his " +
              "job seriously, and everyone who dare to attack this " +
              "land should be prepared for a hard fight.\n"; 
    break;
    case 3:
        str = "When you look at this well-built dwarf you understand " +
              "why his kin are considered by people as great warriors. " +
              "Skilled and powerful battleragers, the dwarven folk of " +
              "Iron Delving are not to be made enemies of lightly.\n";
    break;
    default:
        str = "This powerfully-built dwarf looks like the hardest and " +
              "most dangerous opponent. He must be an elite guard of " +
              "the hill dwarf clan and a survivor of many battles. " +
              "You really should think twice before messing with him.\n";
    break;
    }
    
    return str;
    
}

void
create_krynn_monster()
{
    create_hill_dwarf();
        
    set_pick_up_team(({ "hill_dwarf", "boar" }));
    set_max_team_size_auto_join(4);

    set_race_name("hill dwarf");
    set_name("clan_guard");
    add_name(({ "hill_dwarf", "dwarf" }));
    
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    
    set_gender("G_MALE");
    
    set_hp(query_max_hp());
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 4);
    
    set_alignment(100);
    set_knight_prestige(-1);
    set_exp_factor(100 + (TO->query_dwarf_level() * 10));

    set_default_answer("The dwarf looks at you funnily, as if " +
      "you should already know the answer to that.\n");

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
      "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his greying beard lovingly.");
    
    if ( gLevel > 1 )
    {
        add_act("shhide");
        add_act("shpolish");
        add_act("shrest");
        add_act("shtrust");
        add_act("shgrin");
        add_act("shadjust");
        add_act("shinspect");
        add_act("shready");
    }

    set_cact_time(0);
    add_cact("assist");
    add_cact("assist");
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");

    seteuid(getuid(TO));
    equip(({ ONE_OF(WPS), ONE_OF(ARMS), ONE_OF(SHIELDS), ONE_OF(HELMS), 
             ARM1, ARM2, ARM3 }));
    
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
    if ( !enemy->query_prop(HILL_DWARF_ENEMY) )
        enemy->add_prop(HILL_DWARF_ENEMY, 1);
    
    if ( fighting == 1 )
        return;
    
    switch ( random(3) )
    {
    case 0:
        command("say Ye doorknob! Ye gonna die now!");
    break;
    case 1:
        command("roar");
        command("shready");
    break;
    case 2:
        command("emote roars 'Ye stupid maggot! Yer remains will rot here!'");
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
        command("emote roars 'Ye dorknoob! Ye 'll pay for that!'");
    break;
    default:
        command("curse dwarvishly");
    break; 
    }
    
    command("kill " + OB_NAME(killer));
}

/* Function name: special_attack
 * Description  : The code of a dwarven special attacks.
 */
int
special_attack(object enemy)
{
    int    attacktype, pen, wloc;
    mixed  hitres;
    string *hitloc, how, how1, how2, weapon;
    object my_weapon;

    if(!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(6);

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    my_weapon = query_weapon(-1)[0];
    weapon    = my_weapon->query_short();

    if ( objectp(gShadow) && !TO->query_slam() )
    {
      /* The guild code takes care of the rest. 
       */  
        command("slam");
    }
    
    if (attacktype == 1)
    {
	pen = 350 + (gLevel * 50);

	if ( my_weapon->query_wt() == W_CLUB )
   	    hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);
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
        break;
        }

        if ( my_weapon->query_wt() == W_CLUB )
            how = how1;
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
warn_gobbo(object enemy)
{
    if ( !CAN_SEE(TO,enemy) )
    {
        if ( !random(2) )
            command("curse dwarvishly");
	
	return;
    }

    command("spit");
    command("say The only good gobbo is a dead one.");

}

void
greet_func(object enemy)
{
    object *my_weapons, weapon;
    
    my_weapons = query_weapon(-1);
    
    if ( sizeof(my_weapons) )
        weapon = my_weapons[0];
        
    if (!objectp(enemy) || environment(enemy) != environment())
        return;
        
    if ( !CAN_SEE(TO, enemy) )
	return;

    if ( random(3) )
    {
	if ( random(2) == 1 )
	{
            command("say to " + OB_NAME(enemy) + " Greetins to ya!");
	   
	    if ( !objectp(weapon) )
	        return;
	    
   	    command("emote raises his " + weapon->query_short() +
               " in greetings.");
	}
	else
	{
   	    command("smile dwarvish " + OB_NAME(enemy));

	    if ( !objectp(weapon) )
	        return;
	    
	    command("emote raises his " + weapon->query_short() +
	        ", saying: Axes high friend!");
	}
    }

}

void
init_living()
{
    ::init_living();
    init_team_pickup();
    

    if ( TP->query_prop(HILL_DWARF_ENEMY) )
    {
	set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }
    
    if ( TP->query_race_name() == "goblin" )
    {
        set_alarm(0.5, 0.0, &warn_gobbo(TP));
        return;
    }
    if ( TP->query_guild_member("Dwarven Warriors of the Neidar Clan" ) ||
        (TP->query_race_name() == "dwarf" && !TP->query_npc()) || 
        P("ansalon_rune_object", TP) )
    {
        set_alarm(0.5, 0.0, &greet_func(TP));
        return;
    }
}
