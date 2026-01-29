
#pragma save_binary
#pragma strict_types

inherit "std/leftover";
inherit "/lib/keep";

#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TEREL_MEAT "Terel_meat"

int decay_time;         /* The time it takes for the food to decay in min */
string l_organ, l_race; /* Race and organ name */
static private int decay_alarm;

public void decay_fun();

/*
 * Function name: leftover_init
 * Description  : This function is called when the leftover is
 *                being set-up. It takes over some of the details
 *                of the create_object() function, and configures
 *                them based on attributes of the previous object.
 * Arguments    : string organ - the organ to be used.
 *                string race - the race to be used.
 */
public void
leftover_init(string organ, string race)
{
    organ = "meat";
    l_organ = organ;
    l_race = previous_object()->query_race_name();

    set_name(organ);
    set_pname(LANG_PWORD(organ));
    set_long("This is the usable remainder of " +
      LANG_ADDART(race + " " + organ) + ".\n");
    add_prop(OBJ_I_WEIGHT,
      previous_object()->query_prop(CONT_I_WEIGHT)/40);
    add_prop(OBJ_I_VOLUME,
      previous_object()->query_prop(CONT_I_VOLUME)/40);
}

public nomask void
create_leftover() 
{ 
    decay_time = (30 + this_player()->query_skill(SS_HUNTING));
    set_name("meat");
    add_pname("meats");
    set_amount(100 + random(50));
    remove_prop(OBJ_M_NO_SELL);
    add_prop(TEREL_MEAT,1);

    switch(this_player()->query_skill(SS_HUNTING) + 
      (previous_object()->query_prop(CONT_I_VOLUME)/1000) +
      (previous_object()->query_prop(CONT_I_WEIGHT)/1000))
    {

    case 0..55:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(50)));
        break;

    case 56..140:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(150)));
        break;

    case 141..197:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(250)));
        break;

    case 198..305:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(350)));
        break;

    case 306..680:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(550)));
        break;

    default:
        add_prop(OBJ_I_VALUE,
          previous_object()->query_average_stat() + (random(750)));
        break;

    }
}

/*
 * Function name: set_decay_time
 * Description  : This function sets the time of decay for the object,
 *                the time from cloning to wasting away.
 * Arguments:     int time - the time in minutes to decay
 */
public void
set_decay_time(int time)
{
    decay_time = time;
}

/*
 * Function name: query_decay_time
 * Description  : This function allows a method of finding out the 
 *                remaining time the object has to exist in minutes.
 * Returns      : The amount of time left to decay in minutes.
 */
public int
query_decay_time()
{
    return decay_time;
}

/*
 * Function name: query_race
 * Description  : This function allows a method of finding out
 *                the race of the creature that the leftover is from.
 * Returns      : The leftover race of the creature.
 */
public string
query_race()
{
    return l_race;
}

/*
 * Function name: query_organ
 * Description  : This function allows a method of finding out the
 *                organ which was created from the creature.
 * Returns      : The leftover organ of the creature.
 */
public string
query_organ()
{
    return l_organ;
}

/*
 * Function name: enter_env
 * Description  : This function is called to check the changing
 *                environments the leftover object passes through.
 *                It checks to see if the object has been placed in
 *                a container, which will not start the decay alarm.
 * Arguments    : object dest - The destination object.
 *                object old - The old object.
 */
public void 
enter_env(object dest, object old) 
{
    ::enter_env(dest, old);

    remove_alarm(decay_alarm);
    if (function_exists("create_container", dest) == ROOM_OBJECT)
        decay_alarm = set_alarm(1.0, 0.0, decay_fun);
}

/*
 * Function name: decay_fun
 * Description  : This function operates all the decay capabilities
 *                of the object. It is the countdown function,
 *                and also prints out a message when the object has
 *                decayed.
 */
public void
decay_fun()
{
    if (--decay_time)
        decay_alarm = set_alarm(60.0, 0.0, decay_fun);
    else
    {
        tell_room(environment(this_object()),
          capitalize(LANG_THESHORT(this_object())) +
          " slowly decays into nothing from the continuous feastings " +
          "of insects.\n");
        remove_object();
    }
}

/*
 * Function name: query_recover
 * Description  : Get the recover string, so that the race and organ are
 *                preserved.
 * Returns      : string - the recover string.
 */
public string
query_recover()
{
    return MASTER + ":" + l_race + ":" + l_organ + ":" +
    query_prop(OBJ_I_WEIGHT) + ":" + query_prop(OBJ_I_VOLUME) +
    ":" + query_prop(OBJ_I_VALUE) + ":" + query_decay_time() + ":";
}

/*
 * Function name: init_recover
 * Description  : Re-initialise the leftover.
 * Arguments    : string - the recover arguments.
 */
public void
init_recover(string arg)
{
    string race;
    string organ;
    int weight;
    int volume;
    int value;
    int decaytime;

    if ((sscanf(arg, "%s:%s:%d:%d:%d:%d", race, organ, weight,
          volume, value, decaytime) == 6) &&
      (race != "0"))
    {
        leftover_init(organ, race);
        add_prop(OBJ_I_WEIGHT, weight);
        add_prop(OBJ_I_VOLUME, volume);
        add_prop(OBJ_I_VALUE, value);
        set_decay_time(decaytime);
    }
    else
    {
        remove_object();
    }
}


