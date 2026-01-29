/* Stralle @ Genesis 010408
 *
 * A simple join object
 */

#pragma strict_types

inherit "/std/object";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <composite.h>
#include <const.h>
#include <login.h>

void
create_object()
{
    set_name("takhisis");
    set_long("This is a join object. Simply type 'join the guild' " +
        "to join it.\n");
}

nomask private int
join(string str)
{
    int err, i, size;
    object sh;
    object pl = this_player();
    object mentor = this_object();

    if (!str && str != "the guild")
    {
        notify_fail("Join what?\n");
        return 0;
    }
    
    if (!wildmatch("*jr", this_player()->query_real_name()))
    {
        notify_fail("But you are not a jr.. Where did you get " +
            "hold of this, eh?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    sh = clone_object(POTSHADOW);
    switch (sh->add_occ_shadow(pl))
    {
        case 1:
            pl->catch_tell("You are now a member of the Dark Queen's " +
                "Priesthood!\n");
            tell_room(TO, QCTNAME(pl) + " is now a member of the " +
                "Dark Queen's Priesthood!\n", ({ pl })); 
            
            for (i = 0, size = sizeof(PS_NUM) ; i < size ; i++)
                pl->remove_skill(PS_NUM[i]);
            pl->clear_guild_stat(SS_OCCUP);
            pl->set_skill(PS_STANDING, -99);
            if (ATTACKERS_ADMIN->remove_attacker(pl->query_real_name(),
                "joined the PoT") == "Ok.\n")
            {
                pl->catch_msg("As you join the guild, you are forgiven " +
                    "your past transgressions against the guards of " +
                    "Neraka.\n");
            }
            (GUILD_ADMIN)->add_priest(pl, mentor);            
            return 1;
        case -4:
            /* The player has an occ guild already, or one of his
             * existing guilds has blocked this one.
             */
            pl->catch_msg("Your other guilds don't want you in this one!\n");
            break;
        default:
            /* Some error in shadowing */
            tell_room(this_object(), "An error occurred that prevented " +
                "a successful initiation. Report this to the responsible " +
                "wizards " + COMPOSITE_WORDS(map(GUILDMASTERS, capitalize)) +
                "!\n");
            break;
    }

    write("You successfully joined the guild.\n");
    return 1;
}

void
init()
{
    ::init();
    
    add_action(join, "join");
}
