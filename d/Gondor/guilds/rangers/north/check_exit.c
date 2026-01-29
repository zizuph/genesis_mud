/*
 * /d/Gondor/guilds/rangers/north/check_exit.c
 *
 * Validates moves through exits.
 */

#include <composite.h>
#include <files.h>
#include <macros.h>
#include "../rangers.h"
#include "/d/Gondor/defs.h"

#define EXIT_SAVE (RANGERS_NOR_DIR + "check_exit")
#define ENTRANCE  (RANGERS_NOR_DIR + "stairs")

mapping gAllowed = ([]);

/*
 * Function name: check_perms
 * Description  : Is this person allowed to add a name to the allowed list?
 * Arguments    : object who - the person to test
 * Returns      : 1 - yes, 0 - no
 */
int
check_perms(object who)
{
    string allower = who->query_real_name();

    if (this_player()->query_wiz_level()) return 0;

    if ((MANAGER->query_council(allower, "north") < 0) &&
//      !(SECURITY->query_wiz_dom(allower) == "Gondor") &&
      !SECURITY->query_guild_is_master(RANGERS_GUILD_NAME, allower) &&
      (member_array(lower_case("passage"), 
          MANAGER->query_admin_cmds(allower)) == -1))
        return 0;

    return 1;
}

/*
 * Function name: add_allowed
 * Description  : Adds a name to the list of those allowed into the guild.
 * Arguments    : string name - the one to allow
 */
void
add_allowed(string name)
{
   if (!check_perms(TI))
       return;

   name = CAP(name);
   gAllowed += ([ name : TI->query_real_name() ]);
   save_map(gAllowed, EXIT_SAVE);
   MANAGER->rlog(NORTH_LOG, CAP(TI->query_real_name()) +
       " allowed North access to " + name + ".");
   return;
}

/*
 * Function name: rem_allowed
 * Description  : Removes a name from the allowed list.
 * Arguments    : string name - the name to remove
 */
void
rem_allowed(string name)
{
   if (!check_perms(TI))
       return;

   name = CAP(name);
   gAllowed = m_delete(gAllowed, name);
   save_map(gAllowed, EXIT_SAVE);
   MANAGER->rlog(NORTH_LOG, CAP(TI->query_real_name()) +
        " removed North access from " + name + ".");
   return;
}

/*
 * Function name: query_allowed
 * Description  : Returns 1 if name is allowed, 0 if not
 * Arguments    : string name - the name to test
 */
int
query_allowed(string name)
{
    name = CAP(name);
    return (member_array(name, m_indexes(gAllowed)) != -1);
}

/*
 * Function name: query_all_allowed
 * Description  : Returns an array of those allowed
 */
string *
query_all_allowed()
{
    return m_indexes(gAllowed);
}

void
restore_allowed()
{
    gAllowed = restore_map(EXIT_SAVE);
}

/*
 * Function name: check_ranger
 * Description  : Checks if the player being moved is a Ranger
 *                to be added to add_exit to prevent movement
 *                of unauthorized people.
 * Arguments    : If there is an npc ranger you want to bow to
 *                the player, it can be included in object ranger.
 *                If only North Rangers should be able to pass,
 *                only allow them. Gondorian wizards can pass always.
 * Returns      : 0 if they are, 1 if they aren't.
 */
public varargs int
check_ranger(int north_only = 0, object ranger = 0)
{
   object pl = this_player();
    int enter = 0;

    /* The most common case, let's put it at the top with no
       other checks to be more efficient. */
    if (NORTH_MEMBER(pl) ||
      MANAGER->query_voted_in(pl->query_real_name(), "north") ||
      SECURITY->query_wiz_dom(pl->query_real_name()) == "Gondor" ||
      ENTRANCE->query_allowed(pl->query_real_name()) )
        enter = 1;
    /* The exit is north only, but the player is on the allowed
       list and is a wizard of ME */
    else if (north_only &&
      (SECURITY->query_wiz_dom(pl->query_real_name()) == "Gondor") ||
      (ENTRANCE->query_allowed(pl->query_real_name())))
        enter = 1;
    /* Open to non-company Rangers who are on the allowed list if
       the exit is not marked as north only. */
    else if (!north_only &&
      (ENTRANCE->query_allowed(pl->query_real_name())) &&
      RANGERS_MEMBER(pl))
        enter = 1;

    if (enter)
    {
        if (objectp(ranger))
            ranger->command(one_of_list(({"hail ", "bow ", "greet ",
             "smile solemn "})) + OB_NAME(pl));
        return 0;
    }

    if (objectp(ranger) &&
      CAN_SEE_IN_ROOM(ranger) &&
      CAN_SEE(ranger, pl))
        ranger->command("say You are not allowed to enter here!");
    else
        pl->catch_tell("A grey-cloaked sentinel hidden in the shadows " +
            "stops you.\n");

    return 1;
}
