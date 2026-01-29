/* Stralle @ Genesis 010409
 *
 * Punishment severe
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

#include "../../guild.h"
#include "../../admin/admin.h"
#include <macros.h>

#define POT_ISSUED_EXPEL_COMMAND    "_pot_issued_expel_command"

mapping
query_punishment_commands()
{
    return ([ "expel" : "do_expel" ]);
}

int
do_expel(string arg)
{
    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    arg = lower_case(arg);

    if (!arg || member_array(arg, GUILD_ADMIN->query_guild_list()) < 0)
    {
        notify_fail("Expel whom from the guild?\n");
        return 0;
    }
    
    if (GUILD_ADMIN->query_priest_has_punishment(arg, 
        P_EXPELLED))
    {
        write(capitalize(arg) + " has already an expulsion pending.\n");
        return 1;
    }
   
    if (this_player()->query_prop(POT_ISSUED_EXPEL_COMMAND) + 20 < time())
    {
        write("If you are certain you wish to expel " + capitalize(arg) +
            " issue the same command again within a short moment of time.\n");
        this_player()->add_prop(POT_ISSUED_EXPEL_COMMAND, time());
    }
    
    this_player()->remove_prop(POT_ISSUED_EXPEL_COMMAND);

    if (find_player(arg))
    {
        GUILD_ADMIN->log(find_player(arg), "join", "Was expelled by " +
            this_player()->query_real_name());
        find_player(arg)->punish_for_leaving(3);
        find_player(arg)->remove_occ_member();

        find_player(arg)->catch_tell("Your vision turns dark for a moment " +
            "only to have a five-headed multi-coloured dragon towering " +
            "infront of you when your vision clears. It tilts its head " +
            "back and spouts forth flames that scorches you.\n");
        tell_room(environment(find_player(arg)), QCTNAME(find_player(arg)) +
            " gets a blank stare.\n", find_player(arg));
    }
    else
    {
        GUILD_ADMIN->set_priest_punishment(arg, P_EXPELLED);
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Expels " + capitalize(arg));

    write("You expel " + capitalize(arg) + " from the guild.\n");
    return 1;
}
