
 /* Object for the Shadow Wall spell.
  * The Tihosskias Object
  * Navarre October 22, 2006.
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

string* adjs1 = ({"shimmering", "shining", "distinct", "radiant",
                  "mesmerizing", "translucent", "gloomy", 
                  "obscure", "dimly", "ethereal", "translucent",
                  "vague"});

string blocked_exit = "";

public void set_blocked_exit(string exit);
public string query_blocked_exit();
public int try_to_exit();
public string shadows_long();
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
    add_adj("shadow");

    set_short(adj + " wall of shadows");

    spell_caster->add_prop(LIVE_I_TIHOSSKIAS_CAST, cooldown);
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
    set_name("_EC_shadow_wall");
    add_name("shadow wall");
    add_name("wall");
    add_name("shadows");
    set_long(shadows_long);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This shadow wall is " +
                                 "created to prevent any " +
                                 "undeads from passing through " +
                                 "it and evils have a chance of "+
                                 "suffering fatigue and panic when "+
                                 "passing through it.\n", 40}));
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
	mixed * spirit_team;
		
    // Wizards are not affected by tihosskias, regardless of their undead 
    // status or alignment.
    if (TP->query_wiz_level())
    {
        write("As a wizard you do not feel any effects of passing " +
              "through this wall.\n");
        say(QCTNAME(TP)+" walks through the wall of shadows unharmed.\n");
        return 0;
    }
    
    if (TP->query_real_name() == spell_caster->query_real_name())
    {
		write("You do not feel any effects of passing through" +
            "this wall.\n");
        say(QCTNAME(TP)+" walks through the wall of shadows unharmed.\n");
        return 0;
    }
    
    spirit_team = spell_caster->query_team_others();
    for(i=0; i < sizeof(spirit_team); i++)
    {
    	if (TP->query_real_name() == spirit_team[i]->query_real_name())
    	{
    		write("As a member of "+spell_caster->query_the_possessive_name(TO)+
    		    " team you do not feel any effects of passing through " +
                "this wall.\n");
	        say(QCTNAME(TP)+" walks through the wall of shadows unharmed.\n");
	        return 0;
	    }
	}

    int task = TASK_FORMIDABLE;
    task -= TP->query_magic_res(MAGIC_I_RES_MAGIC) * 6;

    // This section is for people who are not undead
    if (!TP->query_prop(LIVE_I_UNDEAD))
    {
        if(TP->query_alignment() < 0)
        {
            write("As you pass through the "+short()+", it is as if " +
                  "someone is looking directly into your soul " +
                  "taking good measures at your previous "+
                  "actions.\n");
            write("You feel slight panic creeping over you.\n");
            say(QCTNAME(TP)+" walks through the wall of shadows.\n");

            if (TP->resolve_task(task, ({TS_DIS, SKILL_AVG, SS_SPELLCRAFT,
                                         SS_FORM_ABJURATION, SKILL_END})) < 0)
            {
                TP->add_panic(150+random(50));
                TP->add_fatigue(-150);
            }
        }
        return 0;
    }

    // From here until the end of the function only applies to people who are
    // undead.

    spell_caster->catch_tell("You feel that a Soulless creature is trying to "+
        "pass through your " + short() + ", you focus your "+
        "mental concentration on maintaining the wall.\n"); 
    
    // Add a delay to the caster for maintaining the wall.

    spell_caster->add_attack_delay(1,0);
    
    write("As you attempt to move through the " + short() +
          " tendrils from the shadows reach out for you. "+
          "The tendrils try to pull you into the shadows "+
          "beyond which lies the celestial realm of utmost "+
          "beauty. Visions haunt you and a deep pain within "+
          "your soulless body cause you to stagger as "+
          "you manage to pull yourself loose.\n");
    say("As "+QTNAME(TP) + " attempts to pass through the "+short()+
        " tendrils from the shadows reach out for " + TP->query_objective() +
        ". With what appears to be a strenuous effort " + QTNAME(TP) +
        " manages to struggle " + TP->query_objective() + "self free.\n");
    return 1;
}

public void
remove_object()
{
    // Remove the spell object and display the message to the room.
    tell_room(environment(this_object()),"The " + short() + " blocking" +
        " the " + blocked_exit + " exit blinks out of existence!\n");
    ::remove_object();
}


/* This sets the description of the wall, so you can see which
 * direction the wall blocks by looking at it.
 * Returns: String description.
 */
public string
shadows_long()
{
    string description = "Before you a mesh of a " + short() + " pervades "+
        "the " + blocked_exit + ". It seems to exist in " +
        "a constant conflux of interchangable lights and " +
        "shadows. Now and again long twisting tendrils "+
        "reach out from the shadows. This " + short() +
        " covers the passage going " + blocked_exit + ".\n";
    if(TP->query_prop(LIVE_I_UNDEAD) || TP->query_alignment() < 0)
    {
        description += "Something about this " + short() +
                       " seems threatening to you.\n";
    }
    else
    {
        description += "You sense no threat from this shadow.\n";
    }
    return description;
}
