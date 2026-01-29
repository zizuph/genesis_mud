/*
 *  /d/Genesis/imbuement/shadows/poison_effect.c
 *
 *  The poison caused by poison_shadow
 *
 *  2010/09/13 Lavellan
 */
#pragma strict_types

inherit "/std/poison_effect";
#include <poison_types.h>

/* Global Variables */
public int               Power_Level = 1;

/* Prototypes */
public void              create_poison_effect();
public void              set_level(int level);
public string            query_poison_recover();
public void              init_poison_recover(string args);

/*
 * Function name:        create_poison_effect
 * Description  :        set the poison parameters
 */
public void
create_poison_effect()
{
    set_interval(20);
    //set_time(250);
    set_poison_type("imbuement_poison");
    add_name("_imbuement_poison");
} /* create_poison_effect */


/*
 * Function name:        set_level
 * Description  :        set the level of the imbuement
 */
public void
set_level(int level)
{
    Power_Level = level;
    //set_damage( ({ POISON_FATIGUE, 50 + (Power_Level * 20), 
    //               POISON_HP, Power_Level * 15 }) );
    //set_strength(Power_Level * 10);
    set_damage( ({ POISON_FATIGUE, ({ 15,20,40 })[Power_Level-1], 
                   POISON_HP, ({ 30,75,150})[Power_Level-1] }) );
    set_strength( ({ 25,50,100 })[Power_Level-1] );
    //set_time( (({ 5,10,20})[Power_Level-1]) * 60 );
    set_time( (({ 5,7,10})[Power_Level-1]) * 60 );
    set_time( 10 * 60 );
} /* set_level */


/*
 * Function name:        query_poison_recover
 * Description  :        return power level for autoload
 */
public string
query_poison_recover()
{
    return ({"", "1","2","3"})[Power_Level];
} /* query_poison_recover */


/*
 * Function name:        init_poison_recover
 * Description  :        set level when autoloading
 */
public void
init_poison_recover(string args)
{
    set_level(atoi(args));
} /* init_poison_recover */
