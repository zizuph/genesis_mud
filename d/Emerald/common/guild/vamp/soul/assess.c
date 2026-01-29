#include "/std/combat/combat.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <tasks.h>

int
assess(string str)
{
    mixed *oblist = ({});
    string how = "", pos, target_is, pro;
    int i, j, res, size, *hitlocs, brief;
    object enemy, cob, *attackers, *targets = ({});
    string *stats = SD_STAT_DESC[..(SS_NO_EXP_STATS - 1)], *armoured;

    if (!strlen(str))
    {
        if (!(enemy = this_player()->query_attack()))
	{
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
	}

        oblist = ({ 0, enemy });
    }
    else if (!parse_command(str,
        all_inventory(environment(this_player())), "[the] %l", oblist) &&
        !parse_command(str, all_inventory(environment(this_player())),
        "[the] %l %s", oblist, how))
    {
        if ((str == "enemy") || sscanf(str, "enemy %s", how))
        {
            if (!(enemy = this_player()->query_attack()))
	    {
                notify_fail(capitalize(query_verb()) + " whom?\n");
                return 0;
	    }

            oblist = ({ 0, enemy });   
        }
        else if ((str == "me") || (str == "myself") ||
		 parse_command(str, ({}), "'me' / 'myself' %s", how))
	{
            targets = ({ this_player() });
	}
        else
	{
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
	}
    }

    if (!sizeof(targets) &&
       !sizeof(targets += NORMAL_ACCESS(oblist - ({ this_player() }), 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    if (strlen(how))
    {
        if (how == "briefly")
	{
            brief = 1;
	}
        else
	{
            notify_fail(capitalize(query_verb()) + " how?\n");
            return 0;
	}
    }        

    if (sizeof(targets) > 1)
    {
        brief = 1;
    }

    for (i = 0; i < sizeof(targets); i++)
    {
        if (targets[i] == this_player())
	{
            target_is = "You are ";
            pos = "your ";
            pro = "You";
	}
        else
	{
            target_is = capitalize(targets[i]->query_pronoun()) + " is ";
            pos = targets[i]->query_possessive() + " ";
            pro = capitalize(targets[i]->query_pronoun());
        }

        write((((this_player() != targets[i]) &&
            this_player()->query_met(targets[i])) ? 
            targets[i]->query_The_name(this_player()) + " is " : target_is) +
            "a " + targets[i]->query_nonmet_name() + ".\n");

        write(target_is +
            CMD_LIVE_STATE->show_subloc_health(targets[i], this_player()) +
            ".\n");
       
        if (targets[i] != this_player())
	{
            if (res = this_player()->resolve_task(TASK_ROUTINE, ({
        	SKILL_WEIGHT, 50, TS_INT,
        	SKILL_WEIGHT, 50, TS_WIS,
        	SKILL_WEIGHT, 50, SS_APPR_MON,
        	SKILL_WEIGHT, 50, SS_AWARENESS })) > 40)
	    {
        	if (!CAN_SEE_IN_ROOM(targets[0]) ||
        	    !CAN_SEE(targets[0], this_player()))
		{
        	     write(pro + " seems to be unable to see you.\n");
		}
        	else
		{
        	     write(pro + " seems to be able to see you.\n");
		}
            }
            else if (res > 0)
	    {
        	write("You aren't sure if " + lower_case(pro) + " can " +
        	    "see you.\n");
	    }
            else
	    {
  		write(pro + " seems to be " + (random(2) ? "able" : "unable") +
                " to see you.\n");
	    }
	}

        if (!brief)
	{
            write(targets[i]->show_cont_subloc("worn_a", this_player()));
            write(targets[i]->show_cont_subloc("wielded", this_player()));
	}
        else
	{
            if (size = sizeof(targets[i]->query_weapon(-1)))
	    {
                write(target_is + "wielding " + LANG_WNUM(size) + 
                    (size > 1 ? " weapons" : " weapon") + ".\n" );
	    }

            cob = targets[i]->query_combat_object();
            if (size = sizeof(hitlocs = cob->query_hitloc_id()))
	    {
                for (j = 0, armoured = ({}); j < size; j++)
		{
                    if (targets[i]->query_armour(hitlocs[j]))
		    {
 		        armoured +=
			    ({ cob->query_hitloc(hitlocs[j])[HIT_DESC] });
		    }
	        }

                if (sizeof(armoured))
		{
                    write(target_is + "wearing armour on " + pos +
                         COMPOSITE_WORDS(armoured) + ".\n");
		}
	    }
        }

        if ((targets[i] != this_player()) &&
            targets[i]->query_prop(LIVE_I_STUNNED))
	{
            write(pro + " appears to be stunned.\n");
        }

        if (!brief)
	{
            if (enemy = targets[i]->query_attack())
	    {
		write(target_is + "fighting " + 
        	    (enemy == this_player() ? "you" : 
        	    (CAN_SEE(this_player(), enemy) ?
        	    enemy->query_the_name(this_player()) : "someone")) + ".\n");
	    }
    
            attackers = 
        	filter(all_inventory(environment(this_player())) -
        	({ this_player(), targets[i] }),
        	&operator(==)(targets[i]) @ &->query_attack());
       
            if (this_player()->query_attack() == targets[i])
	    {
        	if (sizeof(attackers) > 1)
		{
        	    write("You, " + COMPOSITE_ALL_LIVE(attackers) + 
        		"are fighting " + targets[i]->query_objective() + ".\n");
		}
        	else if (sizeof(attackers))
		{
        	    write("You and " + COMPOSITE_ALL_LIVE(attackers) +
        		" are fighting " + targets[i]->query_objective() + ".\n");
        	}
        	else
		{
        	    write("You are fighting " + targets[i]->query_objective() + 
        		".\n");
		}
	    }
            else if (sizeof(attackers))
	    {
        	str = capitalize(COMPOSITE_ALL_LIVE(attackers));
    
        	write(str + (sizeof(attackers) > 1 ? " are " : " is ") +
        	    "fighting " + ((targets[i] == this_player()) ?
                    "you" : targets[i]->query_objective()) + ".\n");
	    }
    
            if (targets[i] != this_player())
	    {
            this_player()->command("$compare stats with " + OB_NAME(targets[i]));
	    }
	}
    }

    return 1;
}
