/*
 * pTell
 */
#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h> 

mapping gWhispers = ([]);

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 1;
}

public object *
ptell_target(object caster, string str)
{
    object who;
    string whisper;

    if (!stringp(str) || (sscanf(str,"%s %s",str,whisper)!=2))
    {
        write("You need to specify a target and a message.\n");
        return ({ });
    }

    who = find_player(str);

    if (!objectp(who) || environment(who) == find_object(OWN_STATUE))
    {
        caster->catch_tell(C(str) + " is not present in the realms.\n");
        return ({ });
    }

    if (who->query_wiz_level() && member_array(str, GUILDMASTERS) < 0)
    {
	caster->catch_tell("No ptell to wizards!\n");
	return ({ });
    }

    // We can ptell to all members, regardless of if they're known or not
    if (who->query_pot_member() || member_array(str, GUILDMASTERS) >= 0)
    {
    	set_spell_mana(10);
    }
    else
    {
        set_spell_mana(20);
        // For non-members, they must be known to the caster unless full priests
        if (!caster->query_met(who) &&
            caster->query_priest_level() <= GUILD_LEVEL_INITIATE)
        {
            caster->catch_tell("You do not remember any " + C(str) + ".\n");
            return ({ });
        }
    }    

    gWhispers[caster->query_real_name()] = whisper;

    return ({ who });
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
    object tar = targets[0];
    string *arr, *arr2 = ({}), str = "";
    int x, size;
    
    all_msgbb(QCTNAME(caster)+" closes " + HIS(caster) + " eyes and " +
        "whispers something.\n", caster);

//Commented out by Louie - just use break string...
/*
    if (objectp(tar))
    {
        for (x = 0, arr = explode(gWhispers[caster->query_real_name()], " "),
            size = sizeof(arr) ; x < size ; x++)
        {
            arr2 += ({ arr[x] });
            
            if (strlen(implode(arr2, " ")) > 65)
            {
                arr2 = arr2[0 .. sizeof(arr2) - 2];
                
                str += "     " + implode(arr2, " ") + "\n";
                arr2 = ({});
                x--;
            }
        }
        
        str += "     " + implode(arr2, " ") + "\n";
*/      
    if (objectp(tar)) {
        str = gWhispers[caster->query_real_name()];

        tar->catch_tell("As if from behind you, you hear " +
            (tar->query_met(caster) ? caster->query_name() :
            LANG_ADDART(caster->query_race_name())) +
            " whispering:\n" + 
            break_string(str, 60, "\t")+"\n");
        caster->catch_tell("Across the distance, you whisper to " +
            tar->query_the_name(caster) + ":\n" + 
            break_string(str, 60, "\t")+"\n");
    }
    else
    {
	caster->catch_tell("You whisper across the distance but find noone to listen.\n");
    }
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
varargs public int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("ptell");
    set_spell_desc("Talk to someone across a distance");
    
    set_spell_time(3);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
    set_spell_mana(20);
    set_spell_task(TASK_SIMPLE);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(ptell_target);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"copper coin"}));
#endif

    set_spell_visual(0);
    set_spell_stationary(0);

    return 0;
}
