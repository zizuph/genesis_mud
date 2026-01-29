/*
 * File Name        : hall.c
 * By               : Elmore and Boron
 * Inspiration from : -
 * Date             : March 2001.
 * Description      : This is the joinroom of the Palathas Knights.
 *                    It has three methods. Become(), vouch()
 *                    and Leave().
 *
 */

#pragma strict_types

inherit "/d/Krynn/std/room";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include "../local.h"
#include "/d/Krynn/common/defs.h"

void
create_krynn_room()
{
    set_short("A grand hall");
    set_long("A grand hall with twelve pillars; six on each side "
        + "of a long path leading up to a lance thrusted into a "
        + "rock, behind the lance a door is leading north.\n");

    add_item("lance", "Its an amazing lance covered with diamonds and "
            + "gold, the letters 'Dragon Lance' can be read on it. Above "
            + "the lance a huge white banner hangs.\n");

    add_item("pillars", "There are six grand white pillars on each side "
            + "of the path up to the lance, seemingly protecting it.\n");

    add_item("banner","The white banner is huge with flaming "
            + "red letters. The banner reads 'Knights of Palanthas'\n");

    add_prop(OBJ_S_WIZINFO, "Wizards may 'vouch for <player>' to allow them "
            + "to join. However if the wizard don't have a valid reasson to "
            + "do so, expect a harsh word from the AoP or AoD.\n");

    add_exit("center_room","north",0,0);
}

int
vouch(string str)
{
    object ob,*obj;

    if(TP->query_name() == GUILD_LEADER ||
       TP->query_name() == GUILD_WIZARD)
    {
        if(strlen(str) == 0)
        {
                notify_fail("Vouch for who to become a Knight of Palanthas?\n");
                return 0;
        }

        if(strlen(str))
        {
            if(!sizeof(obj = PARSE_THIS(str, "[for] %l")))
            {
                notify_fail("Vouch for who to become a Knight of Palanthas?\n");
                return 0;
            }

            ob = obj[0];
        }

        TP->catch_msg("You vouch for " +QTNAME(ob)+ " as being " +
          "worthy to become a Knight of Palanthas.\n");
        TP->tell_watcher(QTNAME(TP)+ " accepts " +QTNAME(ob)+
          " as being worthy to become a Knight of Palanthas.\n", ob);
        ob->catch_msg("You have been found worthy as to become " +
          "a Knight of Palanthas.\n");
        ob->add_prop(I_CAN_BECOME_KNIGHT, 1);
        return 1;
    }
    write("Only an High Knight of the Solamnian Knights, The "
        + " Grand Master of the Solamnian Knights or a General "
        + "of the Knights of Palanthas may vouch for an applicant.\n");
    return 1;
}

int
become(string str)
{
    object sh;
    mixed why;
    if(strlen(str) == 0)
    {
        notify_fail("Become what? A knight?\n");
        return 0;
    }

    if (L(str) == "knight" || L(str) == "a knight" ||
        L(str) == "knight of palanthas" ||
        L(str) == "the knights" ||
        L(str) == "knights" ||
        L(str) == "a knight of the palanthas" ||
        L(str) == "sentries of palanthas" ||
        L(str) == "sentinel")
    {
        if (!TP->query_prop(I_CAN_BECOME_KNIGHT))
        {
            write("None have vouched for you to join the Knights "+
                  "of Palanthas.\n");
                return 1;
        }
        /* Clone the shadow */
        setuid();
        seteuid(getuid());

        sh = clone_object(GUILD_SHADOW);

        /* See if this member is acceptable */
        if (stringp(why = sh->acceptable_member(this_player())))
        {
            write(why);
        }
        else
        {
            /* Try to add the shadow to the player */
            switch (sh->add_lay_shadow(this_player()))
            {
              case 1:
                /* We have successfully shadowed the player, so we're set */
                find_living(GUILD_WIZARD)->catch_msg(TP->query_name() + " joined the Knights of Palanthas!\n");
                write("Welcome knight! May all your raids be succesful.\n");
                find_living(GUILD_WIZARD)->catch_msg(TP->query_name() + " just joined Knights of Palanthas!\n");
                write_file(GUILD_LOG+"join", TP->query_name() + " joined " +
                           extract(ctime(time()), 4, 15)+
                           ", StatAvg: "+TP->query_average_stat()+
                           ", Race: "+TP->query_race()+
                           ", Align: "+TP->query_alignment()+"\n");

                return 1;

              case -4:
                /* The player has an lay guild already, or one of his existing
               * guilds has blocked this one.
               */
               write("Your other guilds don't want you in this one!\n");
               break;

           default:
            /* Some error in shadowing */
           write("An error has prevented you from joining.\n");
           break;
          }
        }

        /* We couldn't shadow the player, so remove the shadow */
        sh->remove_shadow();
        return 1;
    }
}

int
leave(string str)
{
    if (L(str) == "knight" || L(str) == "a knight" ||
        L(str) == "knight of palanthas" ||
        L(str) == "the knights" ||
        L(str) == "knights" ||
        L(str) == "a knight of the palanthas" ||
        L(str) == "sentries of palanthas" ||
        L(str) == "sentinel")
    {
    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }
    this_player()->remove_lay_member();
    write("You decide to leave the Knights of Palanthas. Farewell for now.\n");
    say(QCTNAME(TP) + " has left the Knights of Palanthas.\n");

    write_file(GUILD_LOG+"leave", TP->query_name() + " left " +
               extract(ctime(time()), 4, 15)+
               ", StatAvg: "+TP->query_average_stat()+
               ", Race: "+TP->query_race()+
               ", Align: "+TP->query_alignment()+"\n");
    }
    return 1;
}

void
init()
{
    ::init();
    ADA("become");
    ADA("leave");
    ADA("vouch");
}
