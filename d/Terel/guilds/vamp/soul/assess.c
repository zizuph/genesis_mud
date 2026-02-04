
#include "../guild.h"

#include "/std/combat/combat.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include <composite.h>
#include <language.h>

#define AC_TYPES     ({ "very fragile", \
                        "fragile", \
                        "rather frail", \
                        "frail", \
                        "delicate", \
                        "weak", \
                        "sturdy", \
                        "strong", \
                        "tough", \
                        "robust", \
                        "rugged", \
                        "very rugged", \
                        "invincible" })

/*
 * Function name: cut_sig_fig
 * Description:   Will reduce the number given to a new number with two
 *                significant numbers.
 * Arguments:     fig - the number to correct.
 * Returns:       the number with two significant numbers
 */
public int
cut_sig_fig(int fig)
{
    int fac;
    fac = 1;

    while(fig > 100)
    {
        fac = fac * 10;
        fig = fig / 10;
    }
    return fig * fac;
}


public string get_name_for_ac(mixed ac)
{
    int val=0;
    if (intp(ac))
    {
        val=ac;
    }
    if (pointerp(ac) && sizeof(ac)>0)
    {
        foreach (int sub : ac)
        {
            val+=sub;
        }
        val/=sizeof(ac);
    }
    int skill;
    skill = 1000 / (TP->query_skill(SS_APPR_MON) + 1);
    skill = random(skill);
    val = cut_sig_fig(val+ (skill % 2 ? -skill % 70 : skill) *
        val / 100);
    return(GET_NUM_DESC(val,100,AC_TYPES));

}

int
assess(string str)
{
    mixed *oblist = ({});
    string how = "", pos, target_is, pro;
    int i, j, res, size, *hitlocs;
    object enemy, cob, *targets = ({});

    if (!strlen(str))
    {
        if (!(enemy = TP->query_attack()))
	{
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
	}

        oblist = ({ 0, enemy });
    }
    else if (!parse_command(str,
        all_inventory(environment(TP)), "[the] %l", oblist) &&
        !parse_command(str, all_inventory(environment(TP)),
        "[the] %l %s", oblist, how))
    {
        if ((str == "enemy") || sscanf(str, "enemy %s", how))
        {
            if (!(enemy = TP->query_attack()))
	    {
                notify_fail(capitalize(query_verb()) + " whom?\n");
                return 0;
	    }

            oblist = ({ 0, enemy });   
        }
        else if ((str == "me") || (str == "myself") ||
		 parse_command(str, ({}), "'me' / 'myself' %s", how))
	{
            targets = ({ TP });
	}
        else
	{
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
	}
    }

    if (!sizeof(targets) &&
       !sizeof(targets += NORMAL_ACCESS(oblist - ({ TP }), 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    for (i = 0; i < sizeof(targets); i++)
    {
        if (targets[i] == TP)
	{
            target_is = "You are";
            pos = "your ";
            pro = "You";
	}
        else
	{
            target_is = capitalize(targets[i]->query_pronoun()) + " is";
            pos = targets[i]->query_possessive() + " ";
            pro = capitalize(targets[i]->query_pronoun());
        }

        write((((TP != targets[i]) &&
            TP->query_met(targets[i])) ? 
            targets[i]->query_The_name(TP) + " is" : target_is) +
            " a " + targets[i]->query_nonmet_name() + ".\n");

        write(target_is + " "+
            CMD_LIVE_STATE->show_subloc_health(targets[i], TP) +
            ".\n");

        if (targets[i]->query_attack())
        {
            write(target_is +
                CMD_LIVE_STATE->show_subloc_fights(targets[i], TP));
        }

        if (targets[i] != TP)
	    {
            if (res = TP->resolve_task(TASK_ROUTINE, ({
        	SKILL_WEIGHT, 50, TS_INT,
        	SKILL_WEIGHT, 50, TS_WIS,
        	SKILL_WEIGHT, 50, SS_APPR_MON,
        	SKILL_WEIGHT, 50, SS_AWARENESS })) > 0)
	        {
            	if (!CAN_SEE_IN_ROOM(targets[0]) ||
        	        !CAN_SEE(targets[0], TP))
		        {
        	        write(pro + " seems to be unable to see you.\n");
		        }
        	    else
		        {
        	        write(pro + " seems to be able to see you.\n");
		        }
            }
            else
	        {
  		        write(pro + " seems to be " + 
  		        (random(2) ? "able" : "unable") + " to see you.\n");
    	    }
    	}

        cob=targets[i]->query_combat_object();
        hitlocs=cob->query_hitloc_id();
        foreach (int hitloc : hitlocs)
        {
            mixed res=cob->query_hitloc(hitloc);
            if (!sizeof(res))
                continue;
            string level=get_name_for_ac(res[0]);
            write(capitalize(pos)+ level +" " + res[2] + 
            (sizeof(res[4]) ? " is covered by "+
            COMPOSITE_DEAD(res[4])+".\n" : " is uncovered.\n"));
        }                
    
        object * held=targets[i]->query_tool(-1) -
                    targets[i]->query_armour(-1);
        
        if (sizeof(held))
        {
            write(pro+ " has "+COMPOSITE_DEAD(held) + " in "+
            pos + "hands.\n");
        }                   

        if ((targets[i] != TP) &&
            targets[i]->query_prop(LIVE_I_STUNNED))
	    {
            write(pro + " appears to be stunned.\n");
        }

    }

    return 1;
}
