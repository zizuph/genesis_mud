/* vsay.c created by Shiva@Genesis
 * This file contains the code for the "vsay" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * This allows vampires to speak in such a way as to be understood
 * only by other vampires.
 *
 * Lucius Dec 2007: Added so that wizards can hear also.
 */

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <options.h>
#include <composite.h>
#include <cmdparse.h>

varargs int 
vsay(string str, int short)
{
    int i;
    object *others;
    mixed *oblist = ({});
    string message;
  
    if (!strlen(str))
    {
        notify_fail("Vsay what?\n");
        return 0;
    }

    if (parse_command(str,
        all_inventory(environment(this_player())) - ({ this_player() }),
        "'to' [the] %l %s", oblist, message))
    {
        oblist = NORMAL_ACCESS(oblist, 0, 0);
    }
        
    if (!short)
    {    
        write("You speak quickly in an inhumanly low and quiet " +
            "voice.\n");
    }
  
    if (sizeof(oblist))
    {
        message = ": " + message + "\n";
    }
    else
    {
        message = ": " + str + "\n";
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You " + (short ? "vsay" : "say") + 
            (sizeof(oblist) ? (" to " + COMPOSITE_ALL_LIVE(oblist)) : "") +
            message);
    }
    else
    {
        write("Ok.\n");
    }
  
    others = all_inventory(environment(this_player())) -
        ({ this_player() }) - oblist;

    for (i = 0; i < sizeof(others); i++) 
    {
        if (!interactive(others[i]))
        {
            continue;
        }
    
        if (IS_VAMP(others[i]) || others[i]->query_wiz_level())
        {
            others[i]->catch_msg("With your preternatural senses, you hear " +
                this_player()->query_The_name(others[i]) + " speak.\n" + 
                capitalize(this_player()->query_pronoun()) + " says" + 
                (sizeof(oblist) ? (" to " + 
                FO_COMPOSITE_ALL_LIVE(oblist, others[i])) : "") + message);
        }
        else if (CAN_SEE(others[i], this_player()) && CAN_SEE_IN_ROOM(others[i]) &&
              (others[i]->resolve_task(TASK_FORMIDABLE + 250, 
              ({ SKILL_WEIGHT, 75, SS_AWARENESS, SKILL_WEIGHT, 25, TS_INT })) > 0))
        {
            others[i]->catch_msg(this_player()->query_The_name(others[i]) + 
                " seems to mumble something; you hear no sound, though.\n");
        }
    }
  
    for (i = 0; i < sizeof(oblist); i++)
    {
        if (!interactive(oblist[i]))
	{
            continue;
	}

        if (IS_VAMP(others[i]) || others[i]->query_wiz_level())
	{
            oblist[i]->catch_msg("With your preternatural senses, you hear " +
                this_player()->query_The_name(oblist[i]) + " speak.\n" + 
                capitalize(this_player()->query_pronoun()) + " says to you" + 
                message);
	}
        else if (CAN_SEE(oblist[i], this_player()) && CAN_SEE_IN_ROOM(oblist[i]) &&
              (oblist[i]->resolve_task(TASK_FORMIDABLE + 250, 
              ({ SKILL_WEIGHT, 75, SS_AWARENESS, SKILL_WEIGHT, 25, TS_INT })) > 0))
        {
            oblist[i]->catch_msg(this_player()->query_The_name(oblist[i]) + 
                " seems to mumble something to you; you hear no sound, though.\n");
        }
    }

    return 1;
}
