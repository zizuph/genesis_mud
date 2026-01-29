/*
 *  /d/Genesis/doc/examples/journal/example_journal.c
 *
 *  This object demonstrates how to use /std/journal.c effectively.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/journal";

/* Prototypes */
public void        create_journal();
public void        special_entry(object who);
public int         cast_foobar(string arg);
public void        init();

/*
 * Function name:        create_journal
 * Description  :        set up the object
 */
public void
create_journal()
{
    set_journal_adj("dusty");
    set_journal_desc("This dusty journal looks like it must hold some"
      + " very dark magic. Readers beware!");
    set_journal_path("/d/Genesis/doc/examples/journal/entries/");
} /* create_journal */


/*
 * Function name:        special_entry
 * Description  :        When a player reads the 5th entry, we have the
 *                       journal call this function. To see how it is
 *                       done, read the contents of:
 *
 *   /d/Genesis/doc/examples/journal/entries/5.txt
 */
public void
special_entry(object who)
{
    who->catch_tell("The page is filled with strange demonic symbols"
      + " that you cannot decipher. However, upon reading them, you feel"
      + " a terrible evil presence rise up from the journal and cause"
      + " you great pain!\n");

    who->heal_hp(-100);
    who->catch_tell("You are badly hurt by the demonic powers!\n");
} /* special_entry */


/*
 * Function name:        cast_foobar
 * Description  :        allow the player to try to cast the foobar
 *                       spell. Unless the player has read entry
 *                       #3, they won't know how. This demonstrates
 *                       how reading an entry can set a prop in a
 *                       player via the final line of the text file.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
cast_foobar(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* The mudlib can handle cast failures. */
    }

    if (arg != "foobar")
    {
        notify_fail("Do you want to <cast foobar> perhaps?\n");
        return 0;
    }

    if (!this_player()->query_prop("_can_cast_foobar_now"))
    {
        write("You make a feeble attempt to cast Foobar, but"
          + " fail miserably! Totally embarassing! Looks like"
          + " you'll need to <read entry 3> first to let it"
          + " set the prop.\n");
        return 1;
    }

    write("You cast foobar like a real pro! Wow. That did"
      + " absolutely nothing. But still! You cast it properly! To"
      + " see how it works in code, look at the cast_foobar()"
      + " function in:\n\n");
    write("    /d/Genesis/doc/examples/journal/example_journal.c\n\n");
    write("Then, to see how the call is made, look at:\n\n");
    write("    /d/Genesis/doc/examples/journal/entries/3.txt\n");

    return 1;
} /* cast_foobar */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(cast_foobar, "cast");
} /* init */