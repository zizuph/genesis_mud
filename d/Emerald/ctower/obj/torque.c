/* torque.c originally done by Phase, redone by Mayhem.
 * This is the quest item for the Crystal Tower quest
 *
 * Completely redone by Shiva, Feb 26, 1998
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/magic/spellcasting";

#include "../ctower.h"
#include "/d/Emerald/quest_handler/quest_handler.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <wa_types.h>

#define MANA_COST	80
#define RECHARGE_MANA   12
#define MIN_INTERVAL	120

#define SUCCESS_CHARGE 18
#define FAILURE_CHARGE 8
#define MAX_CHARGE     99

#define LOST_TORQUE_FILE(who) (CTOWER_LOG + "lost_torque/" + who[0..0])

static int last_time, charge, wear_and_tear, alarm_id;

void stop_recharge();
int add_charge(int ch);
void update_desc();
public int create_spell_scry(object caster, object *targets, mixed arg);

void
create_object()
{
    set_name("torque");
    add_name("ctower_torque");
    add_adj("crystal");

    set_wf(this_object());
    set_slots(A_NECK);

    add_prop(OBJ_M_NO_DROP, "You can't drop that!\n");
    add_prop(OBJ_M_NO_STEAL, "That item is not stealable!\n");
    add_prop(OBJ_M_NO_SELL, "It is too priceless to sell!\n");
    add_prop(OBJ_M_NO_BUY, "It is not for sale!\n");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "divination" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The torque is enchanted with divine power.\n", 1,
	"It can be used to look at the surroundings of other " +
	"people\nanywhere in the world using the trigger 'scry "+
	"<name>'.\n", 15 }) );

    add_spell("scry", "Scry a player", create_spell_scry,
        spell_target_one_distant_known_living);

    charge = MAX_CHARGE;
    last_time = time();
    wear_and_tear = 0;
    alarm_id = 0;

    update_desc();
}

string
query_auto_load()
{
    return sprintf("%s:%d,%d,%d", MASTER, last_time, charge, wear_and_tear);
}

void
init_args(string args)
{
    sscanf(args, "%d,%d,%d", last_time, charge, wear_and_tear);
}

string
query_recover()
{
    return 0;
}

void
recharge_torque()
{
    object who = query_worn();

    if (!who)
    {
        stop_recharge();
        return;
    }

    if (who->query_mana() < RECHARGE_MANA)
    {
        return;
    }

    who->add_mana(-RECHARGE_MANA);
    add_charge(2);
}
    
void
start_recharge()
{
    if ((charge < MAX_CHARGE) && !alarm_id && query_worn())
    {
        alarm_id = set_alarm(300.0, 300.0, recharge_torque);
    }
}

void
stop_recharge()
{
    if (alarm_id)
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }
}
   
int
wear()
{
    start_recharge();
    return 0;
}

int
remove()
{
    stop_recharge();
    return 0;
}

void
get_lost()
{
    string msg;

    write("Oops! You fumble with the torque and drop it.\nThe crystal " +
        "torque shatters into myriad pieces as it strikes the ground.\n");

    msg = " fumbles with the torque and drops it.\n" +
        "The crystal torque shatters into myriad pieces as it strikes "+
        "the ground.\n";

    say(({ METNAME + msg, NONMETNAME + msg, "" }));

    remove_object();
}

void
dest_torque()
{
    object who = environment(this_object());
    string name = who->query_real_name();

    who->catch_tell("The " + short() + " glows brightly and begins to " +
        "implode, finally shrinking to a pinpoint of light and " +
        "disappearing!\n");
  
    remove_object();

    setuid();
    seteuid(getuid());

    write_file(LOST_TORQUE_FILE(name), name + "\n");
}

void
update_desc()
{
    string str;

    switch (charge)
    {
        case (3 * MAX_CHARGE / 4) .. MAX_CHARGE:
            str = " that swirls with every colour in the spectrum.";
            break;
        default:
            str = ".";
            break;
    }

    set_long("This beautifully crafted torque is made entirely of crystal" +
        str + "\n");
}

int
add_charge(int ch)
{
    charge += ch;

    if (charge < 0)
    {
        dest_torque();
        return 0;
    }

    update_desc();
    start_recharge();
    
    return 1;
}

void
add_wear_and_tear(int how_much)
{
    wear_and_tear += how_much;
}

void
remove_wear_and_tear()
{
    wear_and_tear = 0;
}

int
scry_concentrate(object caster, object *targets, mixed arg)
{
    if (!add_charge(FAILURE_CHARGE))
    {
        return 1;
    }

    return spell_concentrate(caster, targets, arg);
}
         
mixed
scry(object caster, object *targets, int *resist, int success)
{
    object env, who, *items, *dead, *live;
    string tmp;

    who = targets[0];

    if (!who || !(env = environment(who)) || who->query_wiz_level())
    {
        caster->catch_tell("You can't seem to locate the person whom you are trying to scry.\n");
        return 0;
    }

    if (((time() - last_time) < MIN_INTERVAL) ||
        env->query_no_snoop() ||
        env->query_prevent_snoop() ||
	env->query_prop(ROOM_M_NO_MAGIC) ||
	who->query_prop(OBJ_M_NO_MAGIC) ||
        (random(100) < resist[0]))
    {
        caster->catch_tell("For some reason, you were unable to do scry " +
            "your target.\n");
        return 0;
    }


#ifndef DEBUG_ON
    if (!add_charge(SUCCESS_CHARGE - random(wear_and_tear)))
    {
        return 0;
    }

    who->catch_tell("You have a sense of being watched.\n");
    who->add_prop("_player_s_last_scried_by", this_player()->query_real_name());
  
    add_wear_and_tear(1);

    last_time = time();
#endif

    write("You can see the following:\n");
  
    if (env->query_prop(OBJ_I_LIGHT) < 1)
    {
    	if (!stringp(tmp = env->query_prop(ROOM_S_DARK_LONG)))
    	{
	    write(LD_DARK_LONG);
	    return 1;
    	}
    	 
    	write(tmp);
    	return 1;
    }

    if (success < 75)
    {  
        write(env->short());
        return 1;
    }

    write(env->long());

    if (success > 125)
    {  
    	items = FILTER_CAN_SEE(all_inventory(env), this_player());
    	if (sizeof(items))
    	{
    	    if (sizeof(dead = FILTER_DEAD(items)))
    	    {
		write(capitalize(COMPOSITE_DEAD(dead)) + ".\n");
    	    }
    	    
    	    if (sizeof(live = FILTER_LIVE(items)))
    	    {
		write(capitalize(COMPOSITE_LIVE(live)) + ".\n");
    	    }
        }
    }
  
    return 1;
}

int
scry_cmd(string arg)
{
    if (!query_worn())
    {
        notify_fail("You must be wearing the torque in order to use its " +
            "powers.\n");
        return 0;
    }

    this_player()->start_spell("scry", arg, this_object());
    return 1;
}
    
void
init()
{
    string name;
    string file;

    ::init();
  
    if (this_player() != environment())
    {
        return;
    }

    if (!this_player()->query_wiz_level())
    {  
    	setuid();
    	seteuid(getuid());
    
    	if (!QH_QUERY_QUEST_COMPLETED(this_player(), CTOWER_QUEST_NAME))
    	{
    	    set_alarm(1.0, 0.0, get_lost);
    	    return;
    	}
    
    	name = this_player()->query_real_name();
    	file = LOST_TORQUE_FILE(name);
    
    	if ((file_size(file) > 0) &&
    	    (member_array(name, explode(read_file(file), "\n")) >= 0))
    	{
    	    set_alarm(1.0, 0.0, get_lost);
    	    return;
        }
    }

    add_action(scry_cmd, "scry");
}

public int
create_spell_scry(object caster, object *targets, mixed arg)
{
    set_spell_time(10);
    set_spell_mana(80);
    set_spell_task(TASK_DIFFICULT);
    set_spell_element(SS_ELEMENT_AIR, 0);
    set_spell_form(SS_FORM_DIVINATION, 0);
    set_spell_resist(spell_resist);
    set_spell_effect(scry);
    set_spell_stationary(1);
    set_spell_conc(scry_concentrate);
    set_spell_peaceful(1);
    set_spell_visual(1);
    set_spell_vocal(0);
    
    return 0;
}
