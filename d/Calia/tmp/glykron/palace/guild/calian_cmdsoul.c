/*      this is the cmdsoul of the Calian guild

    coder(s):   Glykron & Maniac

    history:    16. 8.93    move behind delay added         Glykron
                20. 4.93    created                         Glykron
		   1-2.94   emotes and list warriors added   Maniac
                     3.94   dismemberment added to swarm     Maniac
                     3.94   move behind tempr protection     Maniac
                     5.94   council additions - swarm check  Maniac 

    purpose:    to load commands into a Calian warrior
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/cmd/std/command_driver";

#define GUILD_NAME "Calian warrior's guild"
#define OLD_SOUL "/d/Calia/tmp/glykron/palace/guild/calian_cmdsoul"
#define NEW_SOUL "/d/Calia/glykron/palace/specials/calian_cmdsoul"

/* Add a command soul to the player and activate its commands. */
void
check_soul(object tp)
{
    string *soul_list;

    soul_list = tp->query_cmdsoul_list();
    if (member_array(OLD_SOUL, soul_list) != -1)
    {
        tp->remove_cmdsoul(OLD_SOUL);
        tp->update_hooks();
    }

    if (member_array(NEW_SOUL, soul_list) == -1)
    {
        tp->add_cmdsoul(NEW_SOUL);
        tp->update_hooks();
    }
}

/*
 * Function name: get_soul_id
 * Description:   give identification of soul
 * Arguments:     none
 * Returns:       string with id
 */

string
get_soul_id()
{
    return "Calian";
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this one as cmd soul
 * Arguments:     none
 * Returns:       always 1
 */

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    check_soul(this_player());
    return
    ([
    ]);
}



