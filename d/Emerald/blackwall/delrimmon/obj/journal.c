/*
 *  /d/Emerald/blackwall/delrimmon/obj/journal.c
 *
 *  This journal was kept by Borgil in his attempts to discover the
 *  secret of Maeltar which he discovered in Telberin. He cast
 *  an enchantment upon it which will prevent it from being taken
 *  far from his (now dead) person.
 *
 *  Copyright (c) ?? 1996 by Cooper Sherry (Gorboth)
 */
inherit "/std/object";

#include <language.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
string *cmd_array = ({"first page", "page one", "page 1",
                      "the first page", "the 1st page", "1st page",
                      "second page", "page two", "page 2",
                      "the second page", "the 2nd page", "2nd page",
                      "third page", "page three", "page 3",
                      "the third page", "the 3rd page", "3rd page",
                      "fourth page", "page four", "page 4",
                      "the fourth page", "the 4th page", "4th page" });

/* prototypes */
public void    create_object();
public void    read_page(int page);
public int     read_pages(string str);
void           enter_env(object dest, object from);
public void    enchantment_message(object who);
public void    init();


/*
 * Function name:        create_object
 * Description  :        set up the journal
 */
public void
create_object()
{
    set_name("journal");
    add_name( ({ "del_rimmon_quest_journal", "book" }) );
    add_adj(({"dusty","tattered"}));

    set_short("tattered journal");
    set_long(BSN("While dusty and tattered, this journal is still in"
      + " one piece, and does not seem fragile or brittle. The name"
      + " 'Rillian' is printed on the front cover, and beneath it,"
      + " 'My findings on Del Rimmon'. Within, a few pages have"
      + " what appears to be legible printing on them."));

    add_item(({"print","printing","page","pages"}), BSN(
        "Which page do you wish to read?"));

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(MAGIC_AM_ID_INFO, ({
      "/nThere seems to be some kind of enchantment present.\n", 1,
      "Someone, presumably the owner, has cast an enchantment of"
    + " possession upon this item. It cannot be taken more than a"
    + " few feet from the person to whom it has been connected. In"
    + " this case, it appears as if that person is the corpse"
    + " at your feet.\n", 15 }) );
    add_prop(OBJ_S_WIZINFO, "This journal was enchanted by its"
      + " owner when he was still alive with a powerful spell which"
      + " prevents it from travelling far from his body.\n");

    FIX_EUID
} /* create_object */


/*
 * Function name:        read_page
 * Description  :        prints the text on a given page
 * Arguments    :        int page -- the page we want to read
 */
public void
read_page(int page)
{
    string ptext = read_file(DELRIMMON_DIR
                     + "text/journal_page" + page + ".txt", 0);

    write("The " + LANG_WORD(page) + " page of the journal reads"
        + " as follows:\n\n");
    write(ptext);
} /* read_page */


/*
 * Function name:        read_pages
 * Description  :        allow the player to read various pages
 *                       from the journal.
 * Arguments    :        string str -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 */
public int
read_pages(string str)
{
    string readtxt = "You flip through the journal, and read what is"
                   + " printed on one of the few legible pages:";

    if (!strlen(str))
        NFN0("Read what?");

    switch(str)
    {
        case "page":
        case "pages":
        case "journal":
            WRITE("Which page do you wish to read?");
            return 1;
            break;
        case "print":
        case "printing":
             WRITE("Read the printing on which page?");
             return 1;
            break;
    }


    if (member_array(str, cmd_array) == -1)
        NFN0("Read what?");

    write BSN(readtxt);

    switch(member_array(str, cmd_array))
    {
        case 0..5:
            read_page(1);
            MANAGER->set_read_journal(this_player(), "Yes");
            break;
        case 6..11:
            read_page(2);
            break;
        case 12..17:
            read_page(3);
            break;
        case 18..23:
            read_page(4);
            break;
        default:
            break;
    }

    return 1;
} /* read_pages */


/*
 * Function name:        enter_env
 * Description  :        This function is called each time this object     
 *                       enters a new environment. We redefine it to
 *                       create the effect that an enchantment has been
 *                       placed on the items in the inventory of the
 *                       corpse that this item is found on.
 * Arguments    :        object to - the object we are entering.
 *                       object from - the object we come from.
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!interactive(dest))
    {
        return;
    }

    set_alarm(1.0, 0.0, &enchantment_message(dest));

    return;
} /* enter_env */


/*
 * Function name:        enchantment_message
 * Description  :        Let the player know that this object is
 *                       enchanted, and cannot travel far from its
 *                       owner.
 * Arguments    :        object who - the player who is holding it.
 */
public void
enchantment_message(object who)
{
    if (who->query_stat(4) >= 136)
    {
        who->catch_msg("A sudden strange feeling comes over you, and"
          + " you recognize the tell-tale signs of an enchantment of"
          + " protection which must have been placed on this journal"
          + " by its long-dead owner. Though you can keep it while in"
          + " close proximity to the corpse, the enchantment will not"
          + " allow you to leave with it in your posession.\n");

        return;
    }

    who->catch_msg("A sudden strange feeling comes over you, and you"
      + " have a very bad feeling about the fact that this journal"
      + " is not resting safely in the posession of the corpse.\n");

    return;
} /* enchantment_message */


/*
 * Function name:        init
 * Description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(read_pages, "read");
} /* init */
