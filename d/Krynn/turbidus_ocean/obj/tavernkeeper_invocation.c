/*
*  Invocation by Nax Zeb against drowning
*  (breathing underwater for 600s)
*
*  based on skunk_poison.c
*  pseudo poison, for skunk berries
*  coded by Amelia, 5/14/97
*/
#pragma save_binary

inherit "/std/object";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BASE_DURATION 600
#define NUM_WARNINGS 10

static int gCount = 0;

void
create_object()
{

    set_name("_nax_invocation_breathe_water_");

    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}


int
tell_player(object plyr)
{
    switch(random(3))
    {
    case 0:
	plyr->catch_msg("Your teeth chatter from the cold of the deeps.\n");
	tell_room(environment(plyr), "The sound of chattering teeth can "+
          "be heard.\n");
	break;
    case 1:
	plyr->command("$shiver");
	break;
    default:
	plyr->catch_msg("Your lungs have the cold weight "+
                 "of the deeps within them.\n");
	break;
    }

    gCount++;

    if ( (gCount+2) >= NUM_WARNINGS ) 
    {
        plyr->catch_msg("\nYou feel the cold weight "+
         "in your lungs begining to wane.\n");
    }
    return 1;
}


int
remove_it(object TO, object player)
{
    player->catch_msg("You are warmed up, your lungs are "+
       "emptied of cold weight.\n");
    player->remove_prop(MAGIC_I_BREATHE_WATER);
    TO->remove_object();
    return 1;
}


int
enter_env(object env, object from)
{
    float endtime = itof(BASE_DURATION + random(100));
    float warntime = ( endtime - 1.0 ) / itof(NUM_WARNINGS);
    object TO = this_object();

    ::enter_env(env, from);
    if (living(env))
    {
        env->add_prop(MAGIC_I_BREATHE_WATER,100);
	set_alarm(1.0, warntime, &tell_player(env));
	set_alarm(endtime, -1.0, &remove_it(TO, env));
        gCount = 0;
	env->catch_msg("Your teeth begin to chatter with cold... "+
          "you taste saltwater in your mouth... you feel the pitiless "+
          "weight of the dark deeps sit upon your chest.\n");
	return 1;
    }
    return 1;
}
