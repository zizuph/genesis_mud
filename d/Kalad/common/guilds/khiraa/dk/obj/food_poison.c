inherit "/std/poison_effect";   
#include <poison_types.h>

/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/food_poison.c
 * Purpose    : This is the poison that is cloned when a player tries
 *              to eat a poisoned food.
 * Located    : Death Knight spell 'foul food' poisons food.
 * Created By : Sarr 19.Mar.97
 * Modified By: 
 */


void
create_poison_effect()
{
     set_interval(20);
     set_time(500);
     set_damage( ({ POISON_FATIGUE, 100, POISON_HP, 30 }) );
     set_strength(20);
     set_poison_type("food");
}
