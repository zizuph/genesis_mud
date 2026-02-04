/*
 *
 *  Telepath
 *
 *  For spell effect description, see doc/telepath.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */
#pragma strict_types

#include "../guild.h"

inherit SPELL_DIR+"blood_spell";


#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <std.h>


private static mapping messages = ([]);


public mixed * spell_target_vamp(object actor,string str);

public void
config_spell()
{
    ::config_spell();

    set_spell_name("telepath");
    set_spell_desc("Communicate with another vampire");
    set_spell_target(spell_target_vamp);

    set_spell_mana(21);

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);

    set_blood_cost(5);

    set_min_guild_stat(30);
    
    set_spell_resist(0);
    set_ability_target_verify(0);
    set_spell_peaceful(0);
    set_spell_stationary(0);
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int i;
    mixed *msgs;

    if (!sizeof(targets -= ({ 0 })))
    {
        write("You communicated with no-one.\n");
        return;
    }

    foreach (mixed target : targets)
    {
        string message=target[1];


        string style="You commmunicate telepathically: ";
        string style2=METNAME + " communicates telepathically: ";

        if (target[0]->query_sire()==caster->query_real_name())
        {
            style="Through the Eldest, you communicate telepathically: ";
            style2="Through the Eldest, "+style2;
        }
        if (caster->query_sire()==target[0]->query_real_name())
        {
            style="Through the Eldest, you communicate telepathically: ";
            style2="Through the Eldest, "+style2;
        }

        write((TP->query_option(OPT_ECHO) ? 
        style + message + "\n" : "Ok.\n"));


        if (IS_BG(target[0]) || IS_VAMP(target[0]) || IS_WIZ(target[0]))
        {
            target[0]->catch_tell(style2 + message + "\n");
        }
        else
        {
            if (target[0]->resolve_task(TASK_FORMIDABLE + 100, 
                ({ TS_WIS,SS_AWARENESS})) > 0)
            {
                target[0]->catch_msg("\nYou sense " +QTNAME(caster) + 
                " invading your mind, attempting to project a thought " +
                "to you: " + message + "\n");
            }                      
            else
            {
                target[0]->catch_msg("\nA thought passes through your " +
                "mind: " + message + "\n");
            }
        }                   

        msgs = messages[target[0]->query_real_name()];
        if (!sizeof(msgs))
        {
      	    msgs = ({ ({ METNAME, message }) });
    	}
    	else
    	{
            if (sizeof(msgs) > 9)
    	    {
                msgs = msgs[-9..];
            }

            msgs += ({ ({ METNAME, message }) });
	    }

        messages[target[0]->query_real_name()] = msgs;
    }


}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    if (arg == "remember")
    {
        mixed *msgs = messages[TP->query_real_name()];
        int i, scrw, maxname;

        if (!sizeof(msgs))
	    {
            write("You can't remember having received any telepathic " +
                  "messages recently.\n");
            return 0;
	    }

        if (sizeof(msgs) == 1)
	    {
            write("You search your memory and recall having received one " +
                "telepathic message from " + msgs[0][0] + ": " + msgs[0][1] +
                "\n");
            return 0;
    	}
	
        maxname = applyv(max, map(msgs, strlen @ &operator([])(, 0)));
        scrw = max(TP->query_option(OPT_SCREEN_WIDTH), 40);

        write("You search your memory and recall having received several " +
            "telepathic messages:\n");

        for (i = 0; i < sizeof(msgs); i++)
	    {
            write(sprintf("From %-" + (maxname + 1) + "s %-=" +
                (scrw - maxname - 7) + "s\n", msgs[i][0] + ":", msgs[i][1]));
	    }

        return 0;
    }        

    return ::check_valid_action(actor,targets,arg,execute);
}

public int can_receive_tell(object actor,object target)
{
    if (!target)
    {
        return 0;
    }
    if (!IS_VAMP(target) && !IS_BG(target) && 
        environment(actor)!=environment(target))
    {
        return 0;
    }
    
    if (!interactive(target) && !target->query_npc())
    {
        return 0;
    }
        
    if (target->query_wiz_level() && target->query_invis())
    {
        return 0;
    }
    if (actor==target)
    {
        return 0;
    }
    return 1;
}


public mixed * spell_target_vamp(object actor,string str)
{
    if (str=="remember")
    {
        return ({ actor });
    }
    
    if (!strlen(str))
    {
        write("Use telepathy to speak to who?\n");
        return ({ });
    }
    
    object * oblist;
    
    string name;
    string message;
    
    //Try a remote target
    if (parse_command(str,({ }),"%w %s",name,message))
    {
        if (name=="all" && 
            (actor->query_wiz_level() || actor->query_npc()))
        {
            mixed * results=({ });
            oblist=filter(users(),&can_receive_tell(actor,));
            foreach (object target : oblist)
            {
                results+=({ ({ target, message }) });
            }
            return results;
        }
        object user=find_player(name);
        if (user && can_receive_tell(actor,user))
        {
            return ({ ({ user, message }) });
        }
    }

    object target;
    //Try a local target    
    if (parse_command(str,filter(all_inventory(environment(actor)),
         &can_receive_tell(actor,)),"%o %s",target,message))
    {
        if (target)
        {
            return ({ ({ target, message }) });
        }
    }
    write("Use telepathy to speak to who?\n");
    return ({ });
}

public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    caster->catch_tell("You focus your energies inward.\n");
}
