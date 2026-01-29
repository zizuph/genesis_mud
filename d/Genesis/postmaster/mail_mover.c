/*
 * /d/Genesis/postmaster/mail_mover.c
 *
 * This tool can be used to check all mail-files in the directory of the
 * postmaster in order to (re)move all mail-files that belong to players
 * that do not exist any longer. For security reasons this device will
 * only move the files to OLD_MAIL_DIR in order to have a backup. These
 * files can be manually deleted later.
 *
 * Due to privacy reasons this object has been given some security extra's
 * for I do not want anyone to mess with this and (re)move other players
 * mail if there is no reason to do so.
 *
 * /Mercade, 15 March 1994
 *
 * Revision history:
 */

#pragma no_inherit
#pragma strict_types

inherit "/std/object";

#include <std.h>
#include <stdproperties.h>

#define MAIL_DIR       "/d/Genesis/postmaster/mail/"
#define OLD_MAIL_DIR   "/d/Genesis/postmaster/old_mail/"
#define MAIL_MOVER_LOG "/d/Genesis/postmaster/log/mail_mover"
#define CYCLE_SIZE     50 /* max number of files to check in one cycle */

/* 
 * Global variables
 */
static private object  mover     = 0;
static private string *mailfiles = ({ });

/*
 * Function name: create_object
 * Description  : This function is called to create and configure the mail
 *                mover.
 */
nomask void
create_object()
{
    set_name("mover");
    set_pname("movers");
    set_adj("mail");
    set_short("mail mover");
    set_pshort("mail movers");
    set_long(break_string("This mail mover can be used to move all the " +
        "mail-files of the players who do not have a save-file any longer. " +
        "This should be done every once in a while to free the diskspace. " +
        "For security reasons the obsolete mail-files are only moved to the " +
        "directory " + OLD_MAIL_DIR + " and can be manually removed later. " +
        "The command that will start this mail mover is <move mail> and it " +
        "might take a little while before all files are checked. Set_alarm " +
        "is used to stay below the eval-cost limit. If you are not an " +
        "archwizard of keeper, do not even think about executing the command.",
        75) + "\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_S_WIZINFO, "Just examine the mail mover.\n");

    setuid();
    seteuid(getuid());
}

/*
 * Function name: init
 * Description  : This function is used to add the commands attached to
 *                this mail mover to the livings that get close to it.
 */
nomask void
init()
{
    ::init();

    add_action("do_move", "move");
}

/*
 * Function name: move_mail
 * Description  : This function actually moves the mail and reports to the
 *                responsible wizard about it. It uses call_out to keep
 *                away from the eval-cost limit.
 */
nomask static void
move_mail()
{
    int    cycle;
    int    i;
    int    result;
    string name;

    if ((!objectp(mover)) || (!sizeof(mailfiles)))
    {
        return;
    }

    cycle = ((sizeof(mailfiles) >= CYCLE_SIZE) ?
        CYCLE_SIZE : sizeof(mailfiles) );

    for (i = 0; i < cycle; i++)
    {
        if (sscanf(mailfiles[i], "%s.o", name) != 1)
        {
            mover->catch_msg("MAIL MOVER ->> strange filename: " +
                mailfiles[i] + "\n");
            continue;
        }

        if (SECURITY->exist_player(name))
        {
            continue;
        }

        if (file_size(OLD_MAIL_DIR + mailfiles[i]) > 0)
        {
            mover->catch_msg("MAIL MOVER ->> file exists: " +
                mailfiles[i] + "\n");
            continue;
        }

/*duh*/
#ifdef ODD_RENAME
        result = (!rename(MAIL_DIR + mailfiles[i],
                          OLD_MAIL_DIR + mailfiles[i]));
#else
        result = rename(MAIL_DIR + mailfiles[i],
                        OLD_MAIL_DIR + mailfiles[i]);
#endif

        if (result)
        {
            mover->catch_msg("MAIL MOVER ->> failed on: " +
                mailfiles[i] + "\n");
        }
        else
        {
            mover->catch_msg("MAIL MOVER ->> moved: " + mailfiles[i] + "\n");
        }
    }

    mailfiles = exclude_array(mailfiles, 0, (cycle - 1));

    if (!sizeof(mailfiles))
    {
        mover->catch_msg("MAIL MOVER ->> DONE MOVING.\n");
        mailfiles = 0;
        mover = 0;
        return;
    }

    call_out("move_mail", 1);
}

/*
 * Function name: do_move
 * Description  : This function is called what a player gives the command
 *                to move mail. Some checks are made before the actual
 *                moving takes place. Use common sense :-)
 * Arguments    : str - the command line argument
 * Returns      : int - 1/0 == success/failure
 */
nomask static int
do_move(string str)
{
    if (environment() != this_player())
    {
        notify_fail("You do not have the mail mover on you.\n");
        return 0;
    }

    if (str != "mail")
    {
        notify_fail("Remove what? mail?\n");
        return 0;
    }

    if (this_player() != this_interactive())
    {
        notify_fail("You need to use the mail mover alone.\n");
        return 0;
    }

    if (objectp(mover))
    {
        notify_fail(capitalize(mover->query_real_name()) +
            " is already moving mail.\n");
        return 0;
    }

    if (SECURITY->query_wiz_level(this_player()->query_real_name()) <=
        WIZLEV_LORD)
    {
        write_file(MAIL_MOVER_LOG, ctime(time()) + " " +
            capitalize(this_player()->query_real_name()) +
            " tried to use the mail mover.\n");
        notify_fail(break_string("You have been warned. This attempt is " +
            "logged. Report to Mercade for demotion within seven days.", 75) +
            "\n");
        return 0;
    }

    write_file(MAIL_MOVER_LOG, ctime(time()) + " " +
        capitalize(this_player()->query_real_name()) +
        " used the mail mover.\n");

    if (file_size(OLD_MAIL_DIR) == -1)
    {
        mkdir(OLD_MAIL_DIR);
    }

    mover = this_player();
    mailfiles = get_dir(MAIL_DIR + "*");

    move_mail();

    return 1;
}

/*
 * Function name: remove_object
 * Description  : This function is a shadow of the remove_object function
 *                to ensure that the mail mover is not removed while it is
 *                moving mail.
 */
varargs nomask void
remove_object()
{
    if (objectp(mover))
    {
        mover->catch_msg("MAIL MOVER ->> Remove_object() called.\n");
        mover->catch_msg("MAIL MOVER ->> Attempt rejected.\n");
        return;
    }

    ::remove_object();
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function returns 1 in order to indicate that it
 *                should not be shadowed ever.
 * Returns      : int - always 1
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
