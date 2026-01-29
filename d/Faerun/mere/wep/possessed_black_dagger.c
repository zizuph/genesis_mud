/*
 *
 * by Nerull, 2020
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;
inherit "/lib/keep";

#define LAST_SPECIAL_HIT        "_last_special_hit"

int objective_counter;

int objective1;
int objective2;
int objective3;
int objective4;


void
do_whispers()
{
	if (living(environment(this_object())))
	{
		
		
		if (environment(this_object())->query_skill(SS_WEP_KNIFE) < 80)
		{
			return;
		}
		
		int dice = random(5);
		
		switch(dice)
		{
			case 0:
			environment(this_object())->catch_tell("You hear a faint whisper in "
			+"your mind, saying: Feed me...mortal, and free me...ask me about details..\n");
			break;
			
			case 1:
			environment(this_object())->catch_tell("You hear a faint whisper in "
			+"your mind, saying: Free me...ask me about details..\n");
			break;
			
			case 2:
			environment(this_object())->catch_tell("You hear a faint whisper in "
			+"your mind, saying: Free me, and I shall reward you, mortal...\n");
			break;
			
			case 3:
			environment(this_object())->catch_tell("You hear a faint whisper in "
			+"your mind, saying: Free me from this cursed prison mortal, and I shall "
			+"reward you bountifully!\n");
			break;
			
			case 4:
			environment(this_object())->catch_tell("You hear a faint whisper in "
			+"your mind, saying: Satisfy my needs, and free me! I shall reward "
			+"you...\n");
			break;
		}
		
		return;
	}
	
	return;
}


void
create_faerun_weapon()
{
    seteuid(getuid());

    set_name("dagger");
    add_pname(({"daggers"}));
    
    set_adj("rusty");
    set_adj("black");
    
    set_short("rusty black dagger");
    set_pshort("rusty black daggers");
   
    set_long("The blade of this dagger about five fingers "
	+"wide at the guard and it probably used to be about "
	+"over 20 inches long but now it is broken in half "
	+"and corroded beyond recognotion. The hilt itself used "
	+"to be a wooden and leather grip which is now shriveled "
	+"and torn. The crossguard itself is in prime condition "
	+"though and made from a dull black metal with considerable "
	+"weight for it size.\n");
    
    set_default_weapon(10, 10, 
    W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT, this_object());
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_KNIFE));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 150);
	
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    
    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));
    
    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "magic.\n",1,
        "The enhancement keeps a soul of some sentient being "
		+"trapped within.\n",30 }));
        
    add_prop(OBJ_S_WIZINFO, "This is a weapon dropping from "
        +"assassin boss from the cave in Mere of Dead "
        +"Men.\nThe weapon deals additional damage, randomly "
        +"(light, electricity, acid and cold) and in addition "
        +"hastens the wielder.\n");
	
    objective_counter = 0;
	
	objective1 = random(3);
	objective2 = 3 + random(3);
	objective3 = 6 + random(3);
	objective4 = 9 + random(3);
	
	set_alarm(120.0, 120.0, &do_whispers());
	
    set_keep();
}


int 
ask_black_dagger(string str)
{
	string current_objective1;
	string current_objective2;
	string current_objective3;
	string current_objective4;
	
	if (str == "dagger details" || str == "black dagger details" 
	|| str == "rusty dagger details" || str == "rusty black dagger details"
	|| str == "dagger about details" || str == "black dagger about details" 
	|| str == "rusty dagger about details" || str == "rusty black dagger about details")
	{
		if (environment(this_object()) != this_player())
		{
			return 0;
		}
		
		if (environment(this_object())->query_skill(SS_WEP_KNIFE) < 80)
		{
			return 0;
		}
		
		switch (objective1)
		{
			case 0:
			current_objective1 = "elf";
			break;
			
			case 1:
			current_objective1 = "bullywug";
			break;
			
			case 2:
			current_objective1 = "hobbit";
			break;
		}
		
		switch (objective2)
		{
			case 3:
			current_objective2 = "dwarf";
			break;
			
			case 4:
			current_objective2 = "troll";
			break;
			
			case 5:
			current_objective2 = "lizardman";
			break;
		}
				
		switch (objective3)
		{
			case 6:
			current_objective3 = "kroug";
			break;
			
			case 7:
			current_objective3 = "dragon";
			break;
			
			case 8:
			current_objective3 = "vampire";
			break;
		}
		
		switch (objective4)
		{
			case 9:
			current_objective4 = "wraith";
			break;
			
			case 10:
			current_objective4 = "ghost";
			break;
			
			case 11:
			current_objective4 = "sentinel";
			break;
		}
        
        if (objective_counter == 0)
        {
			this_player()->catch_msg("You hear a faint whisper in "
			+"your mind, saying: "
			+current_objective1+".\n");
		}

        if (objective_counter == 1)
        {
			this_player()->catch_msg("You hear a faint whisper in "
			+"your mind, saying: "
			+current_objective2+".\n");
		}			

        if (objective_counter == 2)
        {
			this_player()->catch_msg("You hear a faint whisper in "
			+"your mind, saying: "
			+current_objective3+".\n");
		}			

        if (objective_counter == 3)
        {
			this_player()->catch_msg("You hear a faint whisper in "
			+"your mind, saying: "
			+current_objective4+".\n");
		}		

        // Weapon is ready
        if (objective_counter == 4)
        {
			this_player()->catch_msg("You hear a faint whisper in "
			+"your mind, saying: I have what I need to be released from "
			+"this cursed prison! Your final task for me will be "
			+"to 'chant xhelarenos', which will break the bond between "
			+"me and this rusty dagger!. Hurry up, mortal! I want to be "
			+"free!\n");
		}							
					
		return 1;
	}
	
	return 0;
}


int chant_black_dagger(string str)
{
	seteuid(getuid());
	
	if (str == "xhelarenos" || str == "Xhelarenos")
	{
		if (objective_counter == 4)
		{
			if (environment(this_object())->query_skill(SS_WEP_KNIFE) < 80)
			{
				return 0;
			}
			
			this_player()->catch_msg("You faintly chant the word 'xhelaneros', and "
			+"suddenly, the "+short()+" silently erodes away into dust!\nYou hear "
			+"a faint whisper in your mind, saying: My prison is destroyed, and I am "
			+"finally free! As a token of my gratitude, and as promised, I will "
			+"grant you a small token, a magical long black dagger!\nYou feel "
			+"that a long black dagger is suddenly among your belongings!\n");
			
			clone_object("/d/Faerun/mere/wep/undull_black_dagger")->move(this_player(), 1);
			
			remove_object();
			
			return 1;
		}		
	}
	
	return 0;
}


/*
* Function:    do_describe_extra_damage
* Description: This function should be masked by each weapon that wishes to
*              customize the damage description for the extra damage.
*              All the necessary info should be available in the arguments,
*              which are identical to did_hit, except for an extra argument
*              to pass the actual extra damage that was done.
*/
public void
do_describe_extra_damage(int aid, string hdesc, int phurt,
    object enemy, int dt, int phit, int dam, int extra_dam, int dice)
{
	
	if (objective_counter == 0)
	{
		wielder->catch_msg("As you strike " + QTNAME(enemy) + " with "
			+ "your " + short() + " at "+ enemy->query_possessive() 
			+ " " + hdesc + ", you hear "
			+"a faint whisper in your mind, saying: Excellent! A good start "
			+"indeed! I have the blood I need from this one. Ask me "
			+"about details regarding the next target!\n");
			
		return;
	}
	
	if (objective_counter == 1)
	{
		wielder->catch_msg("As you strike " + QTNAME(enemy) + " with "
			+ "your " + short() + " at "+ enemy->query_possessive() 
			+ " " + hdesc + ", you hear "
			+"a faint whisper in your mind, saying: Splendid, more blood! Let us move "
			+"to the next target. If still in doubt, ask me about details.\n");
			
		return;
	}
	
	if (objective_counter == 2)
	{
		wielder->catch_msg("As you strike " + QTNAME(enemy) + " with "
			+ "your " + short() + " at "+ enemy->query_possessive() 
			+ " " + hdesc + ", you hear "
			+"a faint whisper in your mind, saying: We are almost there! Let us "
			+"move to the next target!\n");
			
		return;
	}
	
	if (objective_counter == 3)
	{
		wielder->catch_msg("As you strike " + QTNAME(enemy) + " with "
			+ "your " + short() + " at "+ enemy->query_possessive() 
			+ " " + hdesc + ", you hear "
			+"a faint whisper in your mind, saying: This is sufficient! I have "
			+"all what I need to escape this prison! Ask me about "
			+"details for the last target.\n");
			
		return;
	}
			
	return;
}


/*
* Function name: did_hit
* Description  : Special attack. What happens when the weapon hits
*                the target.
* Arguments    : int aid, string hdesc, int phurt, object enemy, int dt,
*                int phit, int dam.
*/
public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int
    dam)
{
    int extra_damage = 0;
    int dice = random(4);
    int did_hit_result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    // If we miss, we miss.
    if (phurt < 0 || dam == 0)
    {
        return did_hit_result;
    }
    
    /*if (query_prop(LAST_SPECIAL_HIT) + 5 > time())
    {
        // We limit the special attack to once every 5 seconds
        return did_hit_result;
    }*/
    
    string component1;
	string component2;
	string component3;
	string component4;
	
	switch(objective1)
	{
		case 0:
		component1 = "elf";
		break;
		
		case 1:
		component1 = "bullywug";
		break;
		
		case 2:
		component1 = "hobbit";
		break;
	}
	
	switch(objective2)
	{
		case 3:
		component2 = "dwarf";
		break;
		
		case 4:
		component2 = "troll";
		break;
		
		case 5:
		component2 = "lizardman";
		break;
	}
	
	switch(objective3)
	{
		case 6:
		component3 = "kroug";
		break;
		
		case 7:
		component3 = "dragon";
		break;
		
		case 8:
		component3 = "vampire";
		break;
	}
	
	switch(objective4)
	{
		case 9:
		component4 = "wraith";
		break;
		
		case 10:
		component4 = "ghost";
		break;
		
		case 11:
		component4 = "sentinel";
		break;
	}
	
	// Objective 1	
	if (objective_counter == 0)
	{
		if (enemy->query_race_name() == component1)
		{
			// This weapon has a 5 percentage chance to trigger dagger counter event.
			if (random(100) < 50)
			{
				add_prop(LAST_SPECIAL_HIT, time()); 
				
				extra_damage = 1;
				
				enemy->heal_hp(-extra_damage);
				
				do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
				extra_damage, dice);  
				
				objective_counter = objective_counter +1;
			}
		}
	}
		
	// Objective 2	
	if (objective_counter == 1)
	{
		if (enemy->query_race_name() == component2)
		{
			// This weapon has a 5 percentage chance to trigger dagger counter event.
			if (random(100) < 50)
			{
				add_prop(LAST_SPECIAL_HIT, time()); 
				
				extra_damage = 1;
				
				enemy->heal_hp(-extra_damage);
				
				do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
				extra_damage, dice);  
				
				objective_counter = objective_counter +1;
			}
		}
	}
	
	// Objective 3	
	if (objective_counter == 2)
	{
		if (enemy->query_race_name() == component3)
		{
			// This weapon has a 5 percentage chance to trigger dagger counter event.
			if (random(100) < 50)
			{
				add_prop(LAST_SPECIAL_HIT, time()); 
				
				extra_damage = 1;
				
				enemy->heal_hp(-extra_damage);
				
				do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
				extra_damage, dice);  
				
				objective_counter = objective_counter +1;
			}
		}
	}
	
	// Objective 4	
	if (objective_counter == 3)
	{
		if (enemy->query_race_name() == component4)
		{
			// This weapon has a 5 percentage chance to trigger dagger counter event.
			if (random(100) < 50)
			{
				add_prop(LAST_SPECIAL_HIT, time()); 
				
				extra_damage = 1;
				
				enemy->heal_hp(-extra_damage);
				
				do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
				extra_damage, dice);  
				
				objective_counter = objective_counter +1;
			}
		}
	}

    wielder->catch_msg("Encounter: "+objective_counter+".\n"
	+"Component1: "+component1+".\n"
	+"Component2: "+component2+".\n"
	+"Component3: "+component3+".\n"
	+"Component4: "+component4+".\n");
    return did_hit_result;
}


int
query_objective_encounter()
{
	return objective_counter;
}


void
init()
{
    ::init();

    add_action(ask_black_dagger, "ask");
	add_action(chant_black_dagger, "chant");
    //add_action(request_defeated, "dummystatus");
}



	
    

