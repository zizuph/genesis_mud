
 /* Object for the Fire Wall spell.
  * The Teichos Object
  *
  * Adapted from the Spirit Circle Shadow Wall Spell
  * Jaacar, February 2017
  */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include <time.h>
#include "defs.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])

string* adjs1 = ({"blazing", "red-orange", "mesmerizing", "hypnotic",
                  "red-hot", "white-hot", "crackling", 
                  "dancing", "roaring", "towering", "blistering",
                  "scorching"});

string blocked_exit = "";

public void set_blocked_exit(string exit);
public string query_blocked_exit();
public int try_to_exit();
public string fire_long();
public object spell_caster;
int res_value;
int sp_result;
int duration = 0;

public void
set_caster(object caster)
{
    spell_caster = caster;
}

public int
start()
{
    string adj = ONE_OF(adjs1);
    int cooldown = time() + 30;

    set_adj(adj);
    add_adj("flame");

    set_short(adj + " wall of flames");

    spell_caster->add_prop(LIVE_I_TEICHOS_CAST, cooldown);
    set_alarm(itof(duration), 0.0, remove_object);
    
    return 1;
}

public void
init()
{
    ::init();
    add_action(try_to_exit, blocked_exit, 1);
}

public void
create_object()
{
    set_name("_EC_fire_wall");
    add_name("fire wall");
    add_name("wall");
    add_name("flames");
    set_long(fire_long);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This fire wall is created to prevent any " +
                                 "players from passing through it.\n", 40}));
    add_prop(MAGIC_I_RES_IDENTIFY, 40);
    add_prop(MAGIC_I_RES_MAGIC, 40);
}


/* Check which exit this wall blocks.
 * Returns a string with the exit
 */

public string
query_blocked_exit()
{
    return blocked_exit;
}


/* This is to get which exit we want to block from the spell.
 * Argument: string exit
 */

public void
set_blocked_exit(string exit)
{
    blocked_exit = exit;
}

public void
set_wall_duration(int value)
{
	duration = value;
}

public void
set_res_value(int value)
{
    res_value = value;
}

public void
set_sp_result(int value)
{
  sp_result = value;
}

/* This function is called when a player tries to walk through the
 * exit that this wall blocks. He has to pass a formidable task
 * that's made easier with a high degree of resistance, and is
 * drained, which is also modified by the resistance.
 * Returns: 0 if we succeed in walking through the wall, 
 *          1 if not (currently we always succeed).
 */
public int
try_to_exit()
{
	int i;
	mixed * fire_team;
		
    // Wizards are not affected by teichos, regardless of their status
    // or alignment.
    if (TP->query_wiz_level())
    {
        write("As a wizard you do not feel any effects of passing " +
              "through this wall.\n");
        say(QCTNAME(TP)+" walks through the wall of flames unharmed.\n");
        return 0;
    }
    
    if (TP->query_real_name() == spell_caster->query_real_name())
    {
		write("You do not feel any effects of passing through " +
            "this wall.\n");
        say(QCTNAME(TP)+" walks through the wall of flames unharmed.\n");
        return 0;
    }
    	
    fire_team = spell_caster->query_team_others();
    for(i=0; i < sizeof(fire_team); i++)
    {
    	if (TP->query_real_name() == fire_team[i]->query_real_name())
    	{
    		write("As a member of "+spell_caster->query_the_possessive_name(TO)+
    		    " team you do not feel any effects of passing through " +
                "this wall.\n");
	        say(QCTNAME(TP)+" walks through the wall of flames unharmed.\n");
	        return 0;
	    }
	}

    int task = TASK_FORMIDABLE;
    task -= TP->query_magic_res(MAGIC_I_RES_MAGIC) * 6;

    spell_caster->catch_tell("You feel that someone is trying to " +
                             "pass through your "+short()+", you focus your " +
                             "mental concentration on maintaining the wall.\n"); 
    
    // Add a delay to the caster for maintaining the wall.

    spell_caster->add_attack_delay(1,0);
    
    write("As you attempt to move through the "+short()+
          " tendrils from the flames reach out for you. "+
          "Deciding that you don't want to be burned, you "+
          "stay where you are.\n");
    say("As "+QTNAME(TP) + " attempts to pass through the "+short()+
        " tendrils from the flames reach out for "+TP->query_objective() +
        ". "+QTNAME(TP)+ " decides not to be burned and stays put.\n");
    return 1;
}

public void
remove_object()
{
    // Remove the spell object and display the message to the room.
    tell_room(environment(this_object()),"The "+short()+" blocking" +
        " the " + blocked_exit + " exit blinks out of existence!\n");
    ::remove_object();
}


/* This sets the description of the wall, so you can see which
 * direction the wall blocks by looking at it.
 * Returns: String description.
 */
public string
fire_long()
{
    string description = "Before you a mesh of a "+short()+" pervades the "+
                          blocked_exit+". It seems to exist in " +
                         "a constant conflux of interchangable lights and " +
                         "flames. Now and again long twisting tendrils "+
                         "reach out from the flames. This "+short() +
                         " covers the passage going "+blocked_exit+".\n";
    description += "Something about this " + short() +
                    " seems threatening to you.\n";
    return description;
}
