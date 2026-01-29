/*
 *  /d/Genesis/doc/examples/journal/example_object.c
 *
 *  This object is used to demonstrate how a call can be made to a
 *  specific object other than the journal if needed.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/object";


public void
create_object()
{
    set_short("example object");
    set_long("This object is never really in the game, it just can be"
      + " targetted by the example_journal for a function call.\n");
} /* create_object */


/*
 * Function name:        do_stuff
 * Description  :        make something happen
 * Arguments    :        object who - the player reading the journal
 */
public void
do_stuff(object who)
{
    who->catch_tell("Whoa! This page doesn't even seem to be coming from"
      + " the journal! You should read the following code to see how"
      + " it is all working:\n\n");
    who->catch_tell("   /d/Genesis/doc/examples/journal/entries/6.txt\n");
    who->catch_tell("   /d/Genesis/doc/examples/journal/example_object.c\n");
} /* do_stuff */
