/*
 *  regen_obj.c 
 *
 *         An object to regenerate hit points on an object.
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

inherit "/d/Shire/healers/lib/spell/effobj";

int interval, dur;
int turn;

/* Prototypes */
int alarm_id;
void heal_player(int power);

mixed
init_effect(object spell, object caster, int power)
{
    if(!living(qme()) || !living(caster) || !spell)
	return "Can't regenerate dead objects.\n";

    set_element(ELEMENT_LIFE);

    set_duration(spell->query_spell_class()*5*60);
    set_power(power);
    set_reducible(1);

    set_name("_regen_obj_");
    add_item(({"body","light"}), "@@exa_light@@");
    add_prop(OBJ_I_LIGHT, "@@query_light@@");

    set_this_player(qme());

    write("You start feeling a whole lot better!\n");
    say(QCTNAME(TP) + " stands amazed feeling a whole lot better!\n");

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    TO->set_interval(10);
    dur = ftoi(interval/2 + random(interval));
	alarm_id = set_alarm(dur,0.0, heal_player);
    //call_out("heal_player", interval / 2 + random(interval));
    return 1;
}

void
notify_dispel()
{
    set_this_player(qme());
    write("Your regeneration stops.\n");
	remove_alarm(alarm_id);
    //remove_call_out("heal_player");
}

/*
 * Function name: set_interval
 * Description:   This sets the average interval between healing being
 *                applied, in heartbeats
 */
void 
set_interval(int i) 
{
    interval = i;
}

/*
 * Function name: query_interval
 * Description:   This returns the average interval between healing
 *		  applications, in heartbeats.
 */
int 
query_interval(int i) 
{
    return interval;
}

/*
 * Function name: heal_player
 * Description:   This function actually carries out the healing of the
 *		  player.  It then sets a new heal_player call_out.
 */
nomask void
heal_player(int power)
{
	int the_time;
    int amount = (power+random(power))/2;
	mixed alarm_info;

    qme()->catch_msg("You are healed from within.\n");
    qme()->heal_hp(amount);
	alarm_info = get_alarm(alarm_id);
	the_time = ftoi(interval/2 + random(interval));
	if (!pointerp(alarm_info))
	  alarm_id = set_alarm( the_time , 0.0 , heal_player);
}

int
start_regeneration()
{
	heal_player(power);
	if (TP->query_wiz_level())
	  write("Regeneration started.\n");
	
    return 1;
}

/*
 * Function name: stat_object
 * Description:   Called when wizard stats the object
 * Returns:	  A string describing the object.
 */
string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Time:     " + time + "\n";
    str += "Interval: " + interval + "\n";

    return str;
}

