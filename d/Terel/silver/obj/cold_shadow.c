/* cold room shadow */
/* 2017-09-26 Malus: Added $ prefix to command() calls */ 

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>

#ifndef E
#define E(x) environment(x)
#endif


#define COLD_IMMUNE_LEVEL 3
/* How often getting_.. methods are called. */
#define COLD_INTERVAL 10.0
/*How fast does player warm up in a non-cold room.*/
#define WORMUP_RATE 15
/* Reaching those numbers mades cold worse */
#define COLD_LEVELS ({100, 500, 1000, 1500})
/* How often bad thing will happen to a player exposed to cold weather. Increasing that will the decrease a
  of having such an effect */
#define COLD_EFFECT_POSSIBILITY 3
/* How often bad thing mentioned above will also display message to affected player. Increasing this const
  will dicrease a chance msg will be sent */
#define COLD_DISPLAY_POSSIBILITY 3

inherit "/std/shadow";


/*Called to reduce the the PLAYER_I_COLD property, called repeatedly by alarm as long as player
  has that property positive and he's not in cold room*/
public void getting_warm();
/* Similar to one above, except it increase that property and is only called in cold rooms */
public void getting_cold();
/* Does bad things to frozen players, and some descriptions occasionally */
void cold_effects();
/* Notifies player of beeing to cold */
void cold_display(int cold_level);
/* Give a description from time to time */
void warm_effects();

int cAlarm;

public int has_cold_shadow()
{
	return 1;
}

/* Other things can make room warmer (only ranger campfire currently). */
int is_cold_room(object ob)
{
	object *campfires = filter(all_inventory(ob), &->id("_firewood"));
	object *elemental_flames = filter(all_inventory(ob), &->id("elemental_flames"));
	if(!ob->query_prop(ROOM_I_TEREL_COLD))
		return 0;
	if(sizeof(elemental_flames))
		return 0;
	if(sizeof(filter(campfires, &->query_prop(OBJ_I_HAS_FIRE))))
		return 0;
	return 1;
}

public void start_cold(object ppl)
{
	if(!interactive(ppl))
	{
		remove_shadow();
		return;
	}
	if(shadow_me(ppl))
		cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_cold());
}
 
public void linkdeath_hook(int linkdeath)
{
	if(linkdeath && pointerp(get_alarm(cAlarm)))
		remove_alarm(cAlarm);
	if(!linkdeath && is_cold_room(environment(shadow_who)))
		cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_cold());
}

/* How cold player gets if he stays in that room - it's a value
  between 0 and 10, reduced by one for every cold-protecting item
  player possess */
// This needs to check for magic cold res, as well as for the number values
// on the OBJ_I_COLD_WEATHER_PROTECT
int cold_factor()
{
  int cold_protection = 0;
  for(int i = 0; i < sizeof(shadow_who->query_armour(-1)); ++i)
    cold_protection += shadow_who->query_armour(-1)[i]->query_prop(OBJ_COLD_WEATHER_PROTECT);
  if(cold_protection >= COLD_IMMUNE_LEVEL || shadow_who->query_npc())
    return 0;
  cold_protection = max(COLD_IMMUNE_LEVEL - cold_protection, 0);
  return cold_protection;
}

public void getting_warm()
{
	
	/*sanity checks*/
	if(pointerp(get_alarm(cAlarm)))
		return;
	
	
	/* function body */
 
	
	if(is_cold_room(environment(shadow_who)))
	{
		cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_cold());
		return;
	}  
	/*He's ok now, the alarm is cleared */
	if(WORMUP_RATE > shadow_who->query_prop(PLAYER_I_COLD))
	{
		shadow_who->remove_prop(PLAYER_I_COLD);
		shadow_who->catch_msg("You're completely warmed up.\n");
		remove_shadow();
		return;
	}
  
	shadow_who->add_prop(PLAYER_I_COLD, shadow_who->query_prop(PLAYER_I_COLD) - WORMUP_RATE);
	warm_effects();
	cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_warm());
}

void warm_effects()
{
	if(shadow_who->query_prop(PLAYER_I_COLD) < COLD_LEVELS[0])
		return;
	switch(random(10))
	{
		case 0:
			shadow_who->catch_msg("You feel a little warmer.\n");
			break;
		case 1:
			shadow_who->catch_msg("You feel you can move your fingers again.\n");
			break;
		default:
			break;
	}
}

/* returns true if i_cold - change lies between different values of COLD_LEVELS then i_cold */
int level_change(int i_cold, int change)
{
  for(int i = 0; i < sizeof(COLD_LEVELS); ++i)
    if(i_cold > COLD_LEVELS[i] && COLD_LEVELS[i] >= i_cold - change)
      return 1;
  return 0;
}
public void getting_cold()
{
	/*sanity checks*/
	if(pointerp(get_alarm(cAlarm)))
		return;
  
	/* function body */
	
	if(!is_cold_room(environment(shadow_who)))
	{
		cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_warm());
		return;
	}
	if(shadow_who->query_prop(PLAYER_I_COLD) < COLD_LEVELS[3])
		shadow_who->add_prop(PLAYER_I_COLD, shadow_who->query_prop(PLAYER_I_COLD) +
			cold_factor());
	cold_effects();
	if(level_change(shadow_who->query_prop(PLAYER_I_COLD), cold_factor()))
		shadow_who->catch_msg("You're starting to feel even colder.\n");
	cAlarm = set_alarm(COLD_INTERVAL, 0.0, &getting_cold());
}

void cold_display(int cold_level)
{
	int message = random(3);
	if(cold_level >= COLD_LEVELS[3])
	{
		switch(message)
		{
			case 0:
				shadow_who->catch_msg("You can't feel your legs from the cold. You start seeing things. You might be dying.\n");
				break;
			case 1:
				shadow_who->command("$shiver");
				break;
			case 2:
				shadow_who->catch_msg("Your numb legs makes you lose your balance.\n");
				tell_room(E(shadow_who), QCTNAME(shadow_who) + " suddenly staggers, beeing unable to keep " +
					shadow_who->query_possessive() + " balance.\n", shadow_who);
				break;
		}
		return;
	}
	if(cold_level >= COLD_LEVELS[2])
	{
		switch(message)
		{
			case 0:
				shadow_who->catch_msg("You're freezing. If you don't find a shelter fast you might lose your fingers.\n");
				break;
			case 1:
				shadow_who->command("$shiver");
				break;
			case 2:
				shadow_who->command("$cough");
				break;
		}
		return;
	}
	if(cold_level >= COLD_LEVELS[1])
	{
		switch(message)
		{
			case 0:
				shadow_who->catch_msg("Your face, toes, fingers are hurting terribly from the frost.\n");
				break;
			case 1:
				shadow_who->command("$cough");
				break;
			case 2:
				shadow_who->catch_msg("You swing your arms few times, hoping to warm up.\n");
				tell_room(E(shadow_who), QCTNAME(shadow_who) + " swings " + 
					shadow_who->query_possessive() + " arms few times, trying to warm up.\n", 
					shadow_who);
				break;
		}
		return;
	}
	switch(message)
	{
		case 0:
			shadow_who->catch_msg("It's too cold out here. You feel you're losing your strength.\n");
			break;
		case 1:
			shadow_who->command("$cough");
			break;
		case 2:
			shadow_who->catch_msg("You rub your hands together, trying to warm them.\n");
			tell_room(E(shadow_who), QCTNAME(shadow_who) + " rubs " + shadow_who->query_possessive() + 
				" hands together.\n", shadow_who);
			break;
	}
}
void cold_effects()
{
  int cold_level = shadow_who->query_prop(PLAYER_I_COLD);

/*nothing happens this time.*/
  if(!random(COLD_EFFECT_POSSIBILITY))
    return;

  if(!random(COLD_DISPLAY_POSSIBILITY))
	cold_display(cold_level);
  
  if(cold_level >= COLD_LEVELS[3])
  {
    shadow_who->heal_hp(- 100 - random(100));
    shadow_who->add_fatigue(- 10 - random(10));
    return;
  }
  if(cold_level >= COLD_LEVELS[2])
  {
    shadow_who->heal_hp(- 50 - random(50));
    shadow_who->add_fatigue(- 10 - random(10));
    return;
  }
  if(cold_level >= COLD_LEVELS[1])
  {
    shadow_who->add_fatigue(- 10 - random(10));
    return;  
  }
  if(cold_level >= COLD_LEVELS[0])
  {
    shadow_who->add_fatigue(- 5 - random(5));
    return;  
  }
  if(shadow_who->query_hp() <= 0)
  {
    shadow_who->catch_msg("You can't find a will to fight anymore. You lay on the ground and fall into deep sleep.\n");
    shadow_who->do_die();
  }
}
