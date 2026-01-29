/*
 * Envenom combat special for the Fire Knives
 *
 * Nerull 2019
 *
 */

#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"

// 
// Disabled, should use log_file 
//
// #define ENVENOM_LOG(x,y)  write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
//                       4, 15) +" "+ y )
//					   
//#define ENVENOM_CRIPPLE_LOG(x,y)  write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
//                       4, 15) +" "+ y )
#define ENVENOM_LOG(x, y)
#define ENVENOM_CRIPPLE_LOG(x, y)                       

#define ACTIVITY_POINT_CHANGE  5

int weapon_oil_type = 0;
string weapon_oil_type_string = "";


public void config_ability()
{
    ::config_ability();
    set_combat_aid(33);
    set_tohit(95);  // 84% chance of hitting

    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
    SKILL_WEIGHT, 20, TS_WIS }) );

    set_skills(({ SS_ART }) );

    set_guild_stat_modifier(SS_OCCUP, 20, 100);

    set_ability_prep_time(4);
    set_ability_cooldown_time(5);
    set_dt(W_SLASH | W_IMPALE);
    set_ability_name("envenom");
}


/*
* Function name: check_valid_action
* Description:   Perform ability-specific checks
* Arguments:     1. (object) The player
*                2. (mixed *) The targets
*                3. (string) Arguments passed to the command
*                4. (int) Actual spell execution
* Returns:       (int) 1 if we can continue, 0 if failure
*/
static int
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;
    object * enemies;
    
    object weaponob2;
    
    weaponob2 = this_player()->query_weapon(W_LEFT);
    
    string weapon2 = weaponob2->query_short();

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(player->query_name()) < AB1)
    {
        player->catch_tell("You are not qualified to use this ability.\n");
        
        return 0;
    }
    
    if (player->query_alignment() > -10)
    {
        player->catch_msg("You struggle with your conscience to execute "
        +"such an action!\n");
        return 0;
    }

    if (!player->query_skill(SS_ART))
    {
        player->catch_tell("You are not skilled the arts of Assassination!\n");

        return 0;
    } 
    
    if(!objectp(weaponob2))
    {
        player->catch_tell("Envenom requires a wielded "
        +"blade in the left hand in "
        +"order to work!\n");
        
        return 0;
    }
    
    if (weaponob2->query_wt() != W_KNIFE)
    {
        player->catch_tell("Your weapon in your left hand is not a dagger "
        +"or a knife!\n");
        
        return 0;
    }
	
	
	// Crippling oil
    if (weaponob2->query_prop(CRIPPLINGOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = CRIPPLING_FLAME;
        
        return 1;
    }
    
    // Manslayer
    if (weaponob2->query_prop(MANSLAYEROIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = MANSLAYER_FLAME;
        
        if (targets[0]->query_race_name() == "human" 
        || targets[0]->query_race_name() == "half-elf"
        || targets[0]->query_race_name() == "triton"
        || targets[0]->query_race_name() == "kroug"
        || targets[0]->query_race_name() == "water-kroug"
		|| targets[0]->query_race_name() == "priestess"
		|| targets[0]->query_race_name() == "priest"
		|| targets[0]->query_race_name() == "witch"
        || targets[0]->query_race_name() == "sahuagin"
        || targets[0]->query_race_name() == "dummy")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against mankind!\n");
            
        return 0;
    }
    
    // Eldarbane
    if (weaponob2->query_prop(ELDARBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = ELDARBANE_FLAME;
        
        if (targets[0]->query_race_name() == "elf" 
        || targets[0]->query_race_name() == "drow"
        || targets[0]->query_race_name() == "half-elf"
        || targets[0]->query_race_name() == "dark elf"
        || targets[0]->query_race_name() == "dark-elf"
        || targets[0]->query_race_name() == "shadow-elf"
        || targets[0]->query_race_name() == "shadow elf")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against elvenkind!\n");
            
        return 0;
    }
    
    // Dwarfbane
    if (weaponob2->query_prop(DWARFBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = DWARFBANE_FLAME;
        
        if (targets[0]->query_race_name() == "dwarf")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against dwarvenkind!\n");
            
        return 0;
    }
    
    // Gnomeslayer
    if (weaponob2->query_prop(GNOMESLAYEROIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = GNOMESLAYER_FLAME;
        
        if (targets[0]->query_race_name() == "gnome")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against gnomekind!\n");
            
        return 0;
    }
    
    // Halflingbane
    if (weaponob2->query_prop(HALFLINGBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = HALFLINGBANE_FLAME;
        
        if (targets[0]->query_race_name() == "hobbit" 
        || targets[0]->query_race_name() == "kender"
        || targets[0]->query_race_name() == "halfling")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against halflings!\n");
            
        return 0;
    }
    
    // Giantsbane
    if (weaponob2->query_prop(GIANTSBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = GIANTSBANE_FLAME;
        
        if (targets[0]->query_race_name() == "troll" 
        || targets[0]->query_race_name() == "ogre"
        || targets[0]->query_race_name() == "giant"
        || targets[0]->query_race_name() == "centaur"  
        || targets[0]->query_race_name() == "huorn"
        || targets[0]->query_race_name() == "unicorn"
        || targets[0]->query_race_name() == "bicorn"	
        || targets[0]->query_race_name() == "yeti"	
        || targets[0]->query_race_name() == "thanoi"			
        || targets[0]->query_race_name() == "minotaur"
		|| targets[0]->query_race_name() == "demonic deity"
        || targets[0]->query_race_name() == "abomination"
        || targets[0]->query_race_name() == "ent")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against giants and similar creatures!\n");
            
        return 0;
    }
    
    // Dragonbane
    if (weaponob2->query_prop(DRAGONBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = DRAGONBANE_FLAME;
        
        if (targets[0]->query_race_name() == "dragon" 
        || targets[0]->query_race_name() == "wyrm"
        || targets[0]->query_race_name() == "draconian"
        || targets[0]->query_race_name() == "wyvern"
        || targets[0]->query_race_name() == "baaz"
        || targets[0]->query_race_name() == "bozak"
        || targets[0]->query_race_name() == "kapak"
        || targets[0]->query_race_name() == "sivak"
        || targets[0]->query_race_name() == "aurak"
        || targets[0]->query_race_name() == "half-dragon")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against dragonkind!\n");
            
        return 0;
    }
    
    // Greenslayer
    if (weaponob2->query_prop(GREENSLAYEROIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = GREENSLAYER_FLAME;
        
        if (targets[0]->query_race_name() == "goblin" 
        || targets[0]->query_race_name() == "orc"
        || targets[0]->query_race_name() == "hobgoblin"
        || targets[0]->query_race_name() == "lizardman"
        || targets[0]->query_race_name() == "bullywug"
        || targets[0]->query_race_name() == "uruk-hai"
        || targets[0]->query_race_name() == "uruk")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against orcs, goblins and "
        +"similar kinds!\n");
            
        return 0;
    }
    
    // Deathbane
    if (weaponob2->query_prop(DEATHBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = DEATHBANE_FLAME;
        
        if (targets[0]->query_prop(LIVE_I_UNDEAD))
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work against the undead!\n");
            
        return 0;
    }
    
    // Naturebane
    if (weaponob2->query_prop(NATUREBANEOIL))
    {
        //weapon_oil_type = 1;
        weapon_oil_type_string = NATUREBANE_FLAME;
        
        if (targets[0]->query_race_name() == "efreet" 
        || targets[0]->query_race_name() == "elemental"
        || targets[0]->query_race_name() == "tempest"
        || targets[0]->query_race_name() == "wisp"
        || targets[0]->query_race_name() == "golem"
        || targets[0]->query_race_name() == "faerie"
		|| targets[0]->query_race_name() == "octopus"
		|| targets[0]->query_race_name() == "shark"
        || targets[0]->query_race_name() == "serpent"
		|| targets[0]->query_race_name() == "avatar"
        || targets[0]->query_race_name() == "presence")
        {      
            return 1;
        }
 
        player->catch_tell("Envenom with this weapon oil "
        +"will only work with creatures of nature and "
        +"the elements!\n");
            
        return 0;
    }
    
    player->catch_tell("Envenom requires a dagger or knife wielded in "
    +"the left hand coated with a weapon oil!\n");

    return 0;
}


public int
query_combat_aid_modifier()
{
	object weaponob2;
    
    weaponob2 = this_player()->query_weapon(W_LEFT);
		
	if (weaponob2->query_prop(CRIPPLINGOIL))
	{
        return 10;
	}
	
	return 100;
}
	

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    
    write("You are ready to perform envenom again.\n");    
}


public void special_did_hit(int aid, string hdesc, int hid,
                int phurt, object enemy, int dt,int phit,
                int dam,object * items)
{
    object weaponob;
    object weaponob2;

    weaponob = this_player()->query_weapon(W_RIGHT);
    weaponob2 = this_player()->query_weapon(W_LEFT);
    
    string weapon = weaponob->query_short();
    string weapon2 = weaponob2->query_short();
    
    
    string envenom_effect = 0;

    int envenom_effect_type = random(5);

    switch(envenom_effect_type)
    {
        case 0:
            envenom_effect = "cut";
            break;
        case 1:
            envenom_effect = "swipe";
            break;
        case 2:
            envenom_effect = "penetrate";
            break;
        case 3:
            envenom_effect = "pierce";
            break;
        case 4:
            envenom_effect = "impale";
            break;
    }

    if (dam<=0)
    {
        this_player()->catch_msg
        ("You attempt to "+envenom_effect+" "+QTPNAME(enemy)+" "
        +hdesc+", but miss connecting "+enemy->query_objective()+" with "
        +"your "+weapon_oil_type_string+" "+weapon2+".\n");

        this_player()->tell_watcher(
        QCTNAME(this_player())+" attempts to "+envenom_effect+" "
        +QTPNAME(enemy)+" "
        +hdesc+" with "+this_player()->query_possessive()+" "
        +weapon_oil_type_string+" "+weapon2+", but "
        +"misses "+enemy->query_objective()+".\n", ({ enemy }) ); 

        enemy->catch_msg(QTNAME(this_player())+" attempts to "
        +envenom_effect+" your "
        +hdesc+" with "+this_player()->query_possessive()+" "
        +weapon_oil_type_string+" "+weapon2+" "
        +"but misses.\n");

        return;
    }

    string dtype;

    switch (phurt)
    {
        case 0..4:
            dtype="imperceptible";
            break;
        case 5..9:
            dtype="unclear";
            break;
        case 10..19:
            dtype="scant";
            break;
        case 20..29:
            dtype="middling";
            break;
        case 30..39:
            dtype="profuse";
            break;
        case 40..60:
            dtype="copious";
            break;
        default:
            dtype="lethal";
    }
	
//	if (weaponob2->query_prop(CRIPPLINGOIL) 
	//	&& !enemy->query_prop(LIVE_I_UNDEAD)
		//&& !present("_fireknife_crippling_obj", enemy))
		
		
	//if (weaponob2->query_prop(CRIPPLINGOIL) 
		//&& !enemy->query_prop(LIVE_I_UNDEAD))
	if (weaponob2->query_prop(CRIPPLINGOIL) 
	&& !enemy->query_prop(LIVE_I_UNDEAD)
	&& !present("_fireknife_crippling_obj", enemy))
    {
		object slow_obj;

		this_player()->catch_msg
		("Your "+weapon_oil_type_string+" "+weapon2+" "
		+"bites deep into "+QTPNAME(enemy)+" "
		+hdesc+", leaving behind an infected wound.\n");

		this_player()->tell_watcher(QCTNAME(this_player())+" "
		+"bites deep into the "+hdesc+" of "+QTNAME(enemy)
		+" with "+this_player()->query_possessive()+" "
		+weapon_oil_type_string+" "+weapon2+", leaving "
		+"behind an infected wound.\n", ({ enemy }));

		enemy->catch_msg(QCTNAME(this_player())+" bites deep into"
		+" your "+hdesc+" with "
		+this_player()->query_possessive()+" "+weapon_oil_type_string
		+" "+weapon2+", "
		+"leaving behind an infected wound. The burning sensation spreads "
		+"quickly through your body, leaving you weakened and disoriented.\n");
		
		/*if (objectp(slow_obj = present("_fireknife_crippling_obj", enemy)))
        {
            slow_obj->dispel_spell_effect(this_player());
        }*/
		//else
		//{
		slow_obj = clone_object(FIREKNIVES_GUILD_DIR + "obj/fireknife_crippling_obj");
		slow_obj->move(enemy, 1);
		slow_obj->setup_spell_effect();
		//}

		ENVENOM_CRIPPLE_LOG("envenom_cripple_log",
		"The Assassin " +this_player()->query_name() 
		+" performed CRIPPLING envenom at "
		+enemy->query_name()+" for Dam:"+dam+"/Phit:"+phit+".\n");
	}
    else
	{
		this_player()->catch_msg
        ("Your "+weapon_oil_type_string+" "+weapon2+" "
        +envenom_effect+"s "+QTPNAME(enemy)+" "
        +hdesc+", causing "+dtype+" damage.\n");

		this_player()->tell_watcher(QCTNAME(this_player())+" "
        +envenom_effect+"s the "+hdesc+" of "+QTNAME(enemy)
        +" with "+this_player()->query_possessive()+" "
        +weapon_oil_type_string+" "+weapon2+", causing "+dtype
        +" damage.\n", ({ enemy }));

		enemy->catch_msg(QCTNAME(this_player())+" "+envenom_effect
        +"s your "+hdesc+" with "
        +this_player()->query_possessive()+" "+weapon_oil_type_string
        +" "+weapon2+", "
        +"causing "+dtype+" damage.\n");
		
		ENVENOM_LOG("envenom_dmg_log",
		"The Assassin " +this_player()->query_name() 
		+" performed envenom at "
		+enemy->query_name()+" for Dam:"+dam+"/Phit:"+phit+".\n");
	}
        
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_player());
    }   
    
        if (random(100) < ACTIVITY_POINT_CHANGE)
    {
        if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
	    {
            int fist_activity;
            fist_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        fist_activity = fist_activity +1;
            
            if (fist_activity > 1000)
            {
                fist_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), fist_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Fist " +this_player()->query_name() +" gained a point(envenom).\n");
        }
        
        if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()))
	    {
            int mentor_activity;
            mentor_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        mentor_activity = mentor_activity +1;
            
            if (mentor_activity > 1000)
            {
                mentor_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), mentor_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Inquisitor " +this_player()->query_name() +" gained a point(envenom).\n");
        }
        
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
	    {
            int boss_activity;
            boss_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        boss_activity = boss_activity +1;
            
            if (boss_activity > 1000)
            {
                boss_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), boss_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Elder " +this_player()->query_name() +" gained a point(envenom).\n");
        }
    }
}
