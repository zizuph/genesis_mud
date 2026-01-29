/* The routine for guards blocking
 *
 * Stralle @ Genesis July 2001
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

object *gGuards, *gTeam;
mixed *gAllowed;

void
set_guards(mixed guards)
{
    if (objectp(guards))
        gGuards = ({ guards });
    else
        gGuards = guards + ({ });
}

/* Function name: set_allowed
 * Description:   See add_allowed. The only difference is that this
 *                resets the variable before adding
 */
varargs void
set_allowed(int who, int team, string *dirs, string colour = "")
{
    gAllowed = ({ ({ who, team, dirs, colour }) });
}

/* Function name: add_allowed
 * Description:   Sets/Adds who will be allowed access when an exit
 *                has check_guards as VBFC call
 * Arguments:     int who  - see the T_* definitions in ../defs.h
 *                int team - see the T_TEAM* definitions in ../defs.h
 *                           Will allow either all the team or only
 *                           if we are leading it or not at all.
 *                string *dirs - what dirs this access is valid for
 *                string colour - the dragonarmy colours we allow (optional)
 */
varargs public void
add_allowed(int who, int team, string *dirs, string colour = "")
{
    if (!pointerp(gAllowed))
        gAllowed = ({ });
    
    gAllowed += ({ ({ who, team, dirs, colour }) });
}

void
do_greet(int whoiam, object guard)
{
    switch (whoiam)
    {
        case T_LEADER..T_HIGH_PRIEST:
            guard->command("bow reverently " + OB_NAME(TP));
            break;
        case T_PRIEST:
            guard->command("bow respectfully " + OB_NAME(TP));
            break;
        case T_INITIATE:
            guard->command("nod respectfully " + OB_NAME(TP));
            break;
        case T_GENERAL..T_OFFICER:
            guard->command("nod respectfully " + OB_NAME(TP));
            break;
        default:
            guard->command("nod briefly " + OB_NAME(TP));
            break;
    }
}

/* Function name: whoami
 * Description:   Check who we are
 */
int
whoami()
{
    int i;

    if (TP->query_guild_name_occ() == GUILD_NAME)
    {
        if ((i = member_array(TP->query_real_name(),
            (GUILD_ADMIN)->query_guild_council())) >= 0)
        {
            switch (i)
            {
                case 0:
                    return T_LEADER;
                case 1:
                    return T_INQUISITOR;
                case 2:
                    return T_MENTOR;
                case 3:
                    return T_LIBRARIAN;
                case 4:
                    return T_HERBMASTER;
            }
        }

        switch (TP->query_priest_level())
        {
            case GUILD_LEVEL_INITIATE:
                return T_INITIATE;
            case GUILD_LEVEL_PRIEST:
                return T_PRIEST;
            case GUILD_LEVEL_HIGH_PRIEST:
                return T_HIGH_PRIEST;
        }
    }
    
    if (GUILD_ADMIN->query_pilgrim(TP->query_real_name()))
        return T_PILGRIM;
    
    if (TP->query_guild_name_occ() == "Dragonarmy")
    {
        switch (TP->query_dragonarmy_rank())
        {
            case 4:
                return T_GENERAL;
            case 3:
                return T_HIGH_OFFICER;
            case 2:
                return T_OFFICER;
            case 1:
                return T_SOLDIER;
            case 0:
                return T_RECRUIT;
        }
    }

    if (TP->query_wiz_level())
        return T_WIZARD;

    return 0;
}

void
log(object who, string str)
{
    object *team;
    string *tmp = explode(file_name(environment(who)), "/");

    setuid();
    seteuid(getuid());

    team = who->query_team();
    if (!team && who->query_leader())
        team = (who->query_leader())->query_team() +
            ({ who->query_leader() });
    
    if (file_size("/d/Ansalon/log/new_pot/blocking") >= 50000)
        rename("/d/Ansalon/log/new_pot/blocking", "/d/Ansalon/log/new_pot/blocking.old");
    write_file("/d/Ansalon/log/new_pot/blocking", extract(ctime(time()), 4, 15) +
        ": " + tmp[sizeof(tmp) - 1] + " " + capitalize(who->query_real_name()) +
        (pointerp(who->query_team()) ? "*" : "") + " (" +
        COMPOSITE_WORDS(map(team->query_real_name(), capitalize)) +
        ") " + str + "\n");
}

/* Function name: check_guards
 * Description:   Add this func as a VBFC call in an exit to check if
 *                a player can pass through it. Previously guards and
 *                those allowed to pass must be set.
 * Returns:       int - 1, no pass or 0, pass
 */
int
check_guards()
{
    object ob;
    int whoiam, x, size, allowed;
    
    if (!pointerp(gAllowed) && sizeof(gGuards))
    {
        /* Noone is allowed and guards guard it */

        for (x = 0, size = sizeof(gGuards) ; x < size ; x++)
        {
            //Since it's a guild home we block no matter what.
            if (objectp(gGuards[x]))
            {
                if (CAN_SEE(gGuards[x], TP))
                {
                    gGuards[x]->command("say to " + OB_NAME(TP) + " I will " +
                        "have to see some orders before I can let you pass.");
                } else {
                    TP->catch_msg("The "+gGuards[x]->short()+" is standing in "+
                        "the way, and you are unable to pass.\n");
                }

                log(TP, "unset values, set guards");
                return 1;
            }
        }
        log(TP, "unset values, set guards but no guards to guard");
        return 0;
    }
           
    if (pointerp(gAllowed) && sizeof(gGuards))
    {
        whoiam = whoami();

        log(TP, "whoiam = " + whoiam);

        /* Check if TP is member of a team of someone who has already
         * passed
         */
        if (member_array(TP, gTeam) >= 0)
        {
            for (x = 0, size = sizeof(gGuards) ; x < size ; x++)
            {
                if (objectp(gGuards[x]) && CAN_SEE(gGuards[x], TP))
                {
                    do_greet(whoiam, gGuards[x]);
                    break;
                }
            }

            log(TP, "was allowed as teammember");            
            return 0;
        }
        
        /* Go through the array of all those allowed
         */
        for (x = 0, size = sizeof(gAllowed) ; x < size ; x++)
        {
            if (gAllowed[x][0] == whoiam &&
                member_array(query_verb(), gAllowed[x][2]) >= 0)
            {
                if (strlen(gAllowed[x][3]) &&
                    TP->query_dragonarmy_division() != gAllowed[x][3])
                    continue;
                
                /* Check if all his teammembers are allowed passage
                 */
                if (gAllowed[x][1] == T_TEAMMEMBER)
                {
                    gTeam = TP->query_team();
                    if (!sizeof(gTeam) && objectp(TP->query_leader()))
                        gTeam = (TP->query_leader())->query_team() +
                            ({ TP->query_leader() });
                }

                /* Check if only if being leader his team is allowed
                 */
                if (gAllowed[x][1] == T_TEAMLEADER)
                {
                    gTeam = TP->query_team();
                }

                allowed = 1;
                break;
            }
        }
                
        /* We were one of those allowed */
        if (allowed)
        {
            /* Check if the guards can acknowledge us */
            for (x = 0, size = sizeof(gGuards) ; x < size ; x++)
            {
                if (objectp(gGuards[x]) && CAN_SEE(gGuards[x], TP))
                {
                    do_greet(whoiam, gGuards[x]);
                    break;
                }
            }
            
            log(TP, "was allowed from set values");
            return 0;
        }
        else
        {
            /* We were not allowed */
            for (x = 0, size = sizeof(gGuards) ; x < size ; x++)
            {
                /* Check if any of the guards can block us */
                if (objectp(gGuards[x])) 
                {
                    if (CAN_SEE(gGuards[x], TP))
                    {
                        gGuards[x]->command("say to " + OB_NAME(TP) +
                            " I will have to see some orders before I can " +
                            "let you pass.");
                    } else {
                        TP->catch_msg("The "+gGuards[x]->short()+" is standing in "+
                        "the way, and you are unable to pass.\n");
                    }
                    log(TP, "was not allowed from set values");
                    return 1;
                }
            }
            
            /* If they were not here to block, we of course allowe
             * passage
             */
            log(TP, "Not allowed but no guards to block");
            return 0;
        }
    }
    
    /* This room did not set those allowed nor did it set any guards
     * to guard it
     */
    log(TP, "values/guards unset");
    return 0;
}
