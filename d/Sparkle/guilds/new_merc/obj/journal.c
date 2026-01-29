/*
 *  /d/Sparkle/guilds/new_merc/obj/journal.c
 *
 *  This is the quest item for the Mercenary Spy quest. It is given
 *  out by the npc:
 *
 *     /d/Sparkle/guilds/mercs/npc/gnimpsh_new.c
 *
 *  Who is clone to the location:
 *
 *     /d/Sparkle/guilds/mercs/room/gnimpsh_room.c
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>


/* Global Variable */
public mixed       Note_Txt;


/* Prototypes */
public void        create_object();
public mixed       give_journal();
public string      describe();
public void        init();
public int         do_read(string arg);
public int         do_copy(string arg);
public void        leave_env(object from, object to);
public void        blow_away();
public int         return_journal(string arg);

public void        set_Note_Txt(mixed m) { Note_Txt = m; }
public mixed       query_note_txt() { return Note_Txt; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("journal");
    add_name( ({ "book", "_merc_spy_journal" }) );
    add_adj( ({ "red", "leather", "leatherbound" }) );

    set_short("red leatherbound journal");
    set_long(describe);

    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GIVE, "@@give_journal@@"); 
    add_prop(OBJ_M_NO_DROP, "@@give_journal@@");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        give_journal
 * Description  :        We don't want this being given out by
 *                       anyone other than Gnimpsh.
 * Returns      :        int 0 - if Gnimpsh is the one doing it
 *                       string - the fail message otherwise
 */
public mixed
give_journal()
{
    if (environment(this_object())->id("_merc_spy_quest_npc"))
    {
        return 0;
    }

    return "Give the journal away? You'd better hang"
      + " on to it until you can <return> it to its owner.\n";
} /* give_journal */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant long description
 *                       for the journal
 * Returns      :        string - the description
 */
public string
describe()
{
    string  desc = "The journal is bound in leather that has been covered"
      + " with a glossy red finish. On the front cover of the book,"
      + " the shape of a dragon has been branded into the material.";

    if (!Note_Txt)
    {
        desc += " You were asked to sneak into the new guildhall of the"
      + " Mercenaries and <copy> down the most recent note on their"
      + " bulletin board before returning this to Gnimpsh in the abandoned"
      + " former Mercenary camp northwest of Sparkle.\n";
    }
    else
    {
        desc += " You managed to copy down the most recent post on the"
          + " Mercenary board. Now all you need to do is <return> the"
          + " book to Gnimpsh.\n";
    }

    return desc;
} /* describe */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_copy, "copy");
    add_action(do_read, "read");
    add_action(return_journal, "return");
} /* init */


/*
 * Function name:        do_read
 * Description  :        let players read the journal
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_read(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to read?\n");
        return 0;
    }

    if (PARSE_COMMAND_ONE(arg, 0, "[the] %i") != this_object())
    {
        notify_fail("Do you want to read the journal, perhaps?\n");
        return 0;
    }

    if (!Note_Txt)
    {
        write("The journal is currently blank. You need to find the"
          + " bulletin board in the new guildhall for the Mercenaries"
          + " and copy down the most recent note.\n");
        return 1;
    }

    write("You've copied down the following into the journal:\n\n");
    write(Note_Txt + "\n");

    return 1;
} /* do_read */


/*
 * Function name:        do_copy
 * Description  :        Allow players to try to copy the most recent
 *                       note from the board to their journal
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_copy(string arg)
{
    mixed  recent_note;

    if (!strlen(arg))
    {
        notify_fail("What do you want to copy to the journal?\n");
        return 0;
    }

    if (!environment(this_player())->id("_new_merc_board_room"))
    {
        notify_fail("You have been tasked to seek out the bulletin"
          + " board in the new Mercenary guildhall, and copy down the"
          + " most recent note. You'll need to locate the board"
          + " before you can copy anything down in the journal.\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [latest] [most] [recent] 'note' [from] [the]"
      + " [mercenary] [bulletin] [board] [in] [to] [into] [the] [red]"
      + " [leatherbound] [leather] [bound] [journal]"))
    {
        notify_fail("What are you trying to do? You've found the"
          + " bulletin board, now you just need to copy the most"
          + " recent note into the journal.\n");
        return 0;
    }

    if (Note_Txt)
    {
        notify_fail("You've already copied the note down. No need to"
          + " repeat the process!\n");
        return 0;
    }

    recent_note = environment(this_player())->copy_merc_note_to_journal();

    if (!recent_note)
    {
        notify_fail("There don't appear to be any notes posted on the"
          + " board to copy down! What a disappointment!\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Here, we would force the player to type a secret trigger"
          + " using command(). Since you are a wizard, that won't work."
          + " Instead, simply type \"_trigger_copy _board\" yourself.\n");
        return 1;
    }

    this_player()->command("$_trigger_copy _board");
    return 1;
} /* do_copy */


/*
 * Function name:        leave_env
 * Description  :        we don't want these ending up in non-quester
 *                       inventories
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, blow_away);
        return;
    }

    return;
} /* leave_env */


/*
 * Function name:        blow_away
 * Description  :        give a delay before we blow the crop away. Also
 *                       check to see if anyone has picked it up first.
 */
public void
blow_away()
{
    if (living(environment(this_object())))
    {
        return;
    }

    tell_room(environment(this_object()), "The book vanishes in a puff"
      + " of smoke!\n");
    remove_object();
} /* blow_away */


/*
 * Function name:        return_journal
 * Description  :        allow players to try to return this journal
 *                       to Gnimpsh
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
return_journal(string arg)
{
    object   gnome;

    if (!strlen(arg))
    {
        notify_fail("What do you want to return?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [red] [leatherbound] 'journal' [to] [the] [nervous]"
      + " [little] [male] [gnome] [gnimpsh]"))
    {
        notify_fail("Perhaps you want to try to return the journal"
          + " to Gnimpsh?\n");
        return 0;
    }

    if (!objectp(gnome = present("_merc_spy_quest_npc",
            environment(this_player()))))
    {
        notify_fail("You'll need to go find Gnimpsh before you"
          + " can return his journal to him!\n");
        return 0;
    }

    write("You return the journal.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " hands a red leatherbound journal to " + QTNAME(gnome)
      + ".\n", this_player());

    gnome->check_journal(this_player(), this_object());

    return 1;
} /* return_journal */