/*
 *  /std/journal.c
 *
 *  A journal that can have many entries which may be read by
 *  players.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 *---------------------------------------------------------------------
 *  Example Useage:
 *---------------------------------------------------------------------
 *    inherit "/std/journal";
 *
 *    public void
 *    create_journal()
 *    {
 *        set_journal_name("diary");
 *        set_journal_adj("tattered");
 *        set_journal_desc("This appears to have been the journal"
 *          + " of Earnest Hemmingway himself!");
 *        set_journal_path("/d/Domain/path_name/journal_dir/");
 *    }
 *--------------------------------------------------------------------
 *  Then, in /d/Domain/path_name/journal_dir/ have individual
 *  text files for each entry with names for each number:
 *
 *    1.txt
 *    2.txt
 *    3.txt  ... etc.
 *
 *  If you want to have a particular entry set a prop in a player
 *  when read, follow the instructions given in the header for the
 *  function read_entry().
 *
 *  You may also have a journal entry make a function call. Again,
 *  see the header of read_entry() for details.
 *
 *  Also, set_journal_adj() is used to give the journal a special
 *  one-word description (i.e. "tattered journal"). Do not try to
 *  use an array here, as that will cause bugs.
 *
 *  For a complete example of how this can all work, refer to the
 *  code in:
 *
 *  /d/Genesis/doc/examples/journal/*
 */
#pragma strict_types;
inherit "/std/object";

#include <language.h>       /* For LANG_WORD2NUM, etc */
#include <macros.h>         /* For QCTNAME            */
#include <stdproperties.h>  /* For OBJ_I_WEIGHT, etc  */


/* Definitions */
#define            JOURNAL_NEXT_PROP   "_std_journal_i_next_prop"
#define            JOURNAL_OBJECT_PROP "_std_journal_currently_reading"

/* Global Variables */
public string      Journal_Name;  /* Item type - e.g. "diary", etc */
public string      Journal_Adj;   /* An adjective for the journal  */
public string      Journal_Path;  /* the dir where the entries are */
public int         Num_Entries;   /* How many entries are there?   */
public string      Journal_Desc;  /* Unique long_desc string       */
public int         Closed = 1;    /* True if the journal is closed.*/
public int         Entry_Word = 1;/* False if the journal describes
                                   * its separate entries as "pages"
                                   * instead of "entries".
                                   */

/* Prototypes */
nomask void        create_object();
public void        create_journal();
public int         read_journal(string arg);
public int         init();
public void        configure_journal();
public string      describe();
public void        read_entry(object who, int entry);
public int         open_close(string arg);

public void        set_journal_closed(int i)   { Closed = i;          }
public void        set_journal_path(string s)  { Journal_Path = s;    }
public void        set_journal_desc(string s)  { Journal_Desc = s;    }
public void        set_journal_adj (string s)  { Journal_Adj  = s;    }
public void        set_journal_name(string s)  { Journal_Name = s;    }
public void        set_entry_word(int i)       { Entry_Word = i;      }
public string      query_journal_path()        { return Journal_Path; }
public int         query_num_entries()         { return Num_Entries;  }
public int         query_closed()              { return Closed;       }

/*
 * Function name:        create_object
 * Description  :        the constructor for the object
 */
nomask void
create_object() 
{
    Journal_Name = "journal";
    Journal_Adj  = "leatherbound";
    Journal_Desc = "This journal appears to have been used by someone"
      + " to keep a log of sorts.";
    Journal_Path = "none";

    set_long("@@describe@@");

    add_prop( OBJ_I_VALUE,     0 );
    add_prop( OBJ_I_WEIGHT,   40 );
    add_prop( OBJ_I_VOLUME,  120 );

    setuid();
    seteuid(getuid());

    create_journal();
    set_alarm(0.0, 0.0, &configure_journal());
} /* create_object */


/*
 * Function name:        create_journal
 * Description  :        Dummy routine to be replaced in inheriting
 *                       files
 */
public void
create_journal()
{
} /* create_journal */


/*
 * Function name:        read_journal
 * Description  :        allow players to read the various entries
 *                       in the journal
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
read_journal(string arg)
{
    int       next = this_player()->query_prop(JOURNAL_NEXT_PROP);
    string    entry;
    int       num_word;
    int       string_word;
    string    closed_fail = "The " + Journal_Name + " is closed.\n";
    string    page =  ((Entry_Word) ? "entry"   : "page");
    string    pages = ((Entry_Word) ? "entries" : "pages");

    if (!strlen(arg))
    {
        notify_fail("Read what? The " + Journal_Name + "?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[the] [" + Journal_Adj + "] '" + Journal_Name + "'"))
    {
        if (Closed)
        {
            write(closed_fail);
            return 1;
        }

        if (!Num_Entries)
        {
            write("The " + Journal_Name + " appears to be blank.\n");
            return 1;
        }

        write("You count " + Num_Entries + " separate " + pages + " in the "
          + Journal_Name + ". You must <read " + page + " #> or"
          + " <read next> to specify where in the " + Journal_Name
          + " you want to read.\n");
        return 1;
    }

    if (arg == "next" || arg == "next entry" || arg == "next page")
    {
        if (Closed)
        {
            write(closed_fail);
            return 1;
        }

        if (!Num_Entries)
        {
            write("The " + Journal_Name + " appears to be blank.\n");
            return 1;
        }

        /* If the player's "next" prop is from a different journal than
         * this object, we want to make sure they get a fresh slate.
         */
        if (this_player()->query_prop(JOURNAL_NEXT_PROP))
        {
            if (this_player()->query_prop(JOURNAL_OBJECT_PROP) !=
                file_name(this_object()))
            {
                this_player()->remove_prop(JOURNAL_NEXT_PROP);
                next = 0;
            }
        }

        if (!next)
        {
            write("Since you've not read anything in the " + Journal_Name
              + " yet, you decide to just start at the beginning"
              + " and read the first " + page + ".\n\n");
            read_entry(this_player(), 1);
            return 1;
        }

        if (next > Num_Entries)
        {
            write("There are no further " + pages + " in the " + Journal_Name
              + ". You have already read the last one.\n");
            return 1;
        }

        read_entry(this_player(), next);
        return 1;
    }

    if (!parse_command(arg, ({}),
        "'entry' / 'page' %w", entry))
    {
        if (Closed)
        {
            notify_fail(closed_fail);
            return 0;
        }

        if (parse_command(arg, ({}),
            "%w 'entry' / 'page'", entry))
        {
            string_word = LANG_WORD2ORD(entry);

            if (!Num_Entries)
            {
                write("The " + Journal_Name + " appears to be blank.\n");
                return 1;
            }

            if (string_word)
            {
                if (string_word <= Num_Entries)
                {
                    read_entry(this_player(), string_word);
                    return 1;
                }

                notify_fail("There are only " + Num_Entries + " " + pages
                  + " in the " + Journal_Name + ".\n");
                return 0;
            }
        }

        notify_fail("What are you trying to read? Do you wish to read a"
          + " particular " + page + " in the " + Journal_Name + "? If so, you"
          + " can, for example, <read " + page + " 4> and so on.\n");

        return 0;
    }

    num_word    = atoi(entry);
    string_word = LANG_WORD2NUM(entry);

    if (num_word)
    {
        if (Closed)
        {
            write(closed_fail);
            return 1;
        }

        if (!Num_Entries)
        {
            write("The " + Journal_Name + " appears to be blank.\n");
            return 1;
        }

        if (num_word <= Num_Entries)
        {
            read_entry(this_player(), num_word);
            return 1;
        }

        notify_fail("There are only " + Num_Entries
          + " " + pages + " in the " + Journal_Name + ".\n");
        return 0;
    }

    if (string_word)
    {
        if (Closed)
        {
            write(closed_fail);
            return 1;
        }

        if (!Num_Entries)
        {
            write("The " + Journal_Name + " appears to be blank.\n");
            return 1;
        }

        if (string_word <= Num_Entries)
        {
            read_entry(this_player(), string_word);
            return 1;
        }

        notify_fail("There are only " + Num_Entries + " " + pages
          + " in the " + Journal_Name + ".\n");
        return 0;
    }

    return 0; /* Should never happen, but just in case. */ 
} /* read_journal */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(read_journal, "read");
    add_action(open_close, "open");
    add_action(open_close, "close");
} /* init */    


/*
 * Function name:        configure_journal 
 * Description  :        This function sets everything up properly
 *                       in the journal, using any values set by
 *                       inheriting files in the final construction.
 */
public void
configure_journal()
{
    Num_Entries = 0;

    if (pointerp(get_dir(Journal_Path)))
    {
        Num_Entries = sizeof(get_dir(Journal_Path));
    }

    set_name(Journal_Name);
    set_short(Journal_Adj + " " + Journal_Name);
    add_adj(Journal_Adj);
} /* configure_journal  */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant long description 
 *                       for the journal.
 * Returns      :        string - the description
 */
public string
describe()
{
    string    desc = Journal_Desc;
    string    page =  ((Entry_Word) ? "entry"   : "page");
    string    pages = ((Entry_Word) ? "entries" : "pages");

    if (Closed)
    {
        return desc + " The " + Journal_Name + " is closed.\n";
    }

    if (!Num_Entries)
    {
        return desc + " The " + Journal_Name + " appears to be blank.\n";
    }

    return desc + " There are " + Num_Entries
      + " " + pages + " that you can <read> if you wish. You can also"
      + " <read next> if you want to read the next " + page + ".\n";
} /* describe */


/*
 * Function name:        read_entry
 * Description  :        print the contents of a particular
 *                       journal entry to the player
 * Arguments    :        object who - the player to show it to
 *                       int entry - the entry number
 *
 * OPTIONAL #1  : If you want to have a journal entry be handled
 *                by a function call simply make the corresponding
 *                text file a single line that looks like one of the
 *                following examples.
 *
 *                If you want it to call a function in the inheriting
 *                object, just do:
 *
 *     ::FUNCTION_CALL::function_name
 *
 *                Which works like:
 *
 *     this_object()->function_name(this_player());
 * 
 *                If you need to call a function in a different
 *                object, then do:
 *
 *     ::FUNCTION_CALL::function_name::FILE::/d/Domain/file_path
 *
 *                Which works like:
 *
 *     find_object("/d/Domain/file_path")->function_name(this_player());
 *
 * OPTIONAL #2  : It is sometimes important to set a prop in a player
 *                if they read something important in a journal. If
 *                you want to do that, you must have the *last* line
 *                of that journal entry begin with the string:
 *
 *                    ::SET_PROP::
 *
 *                followed immediately by the prop name, followed by:
 *
 *                    ::PROP_VALUE::
 *
 *                followed immediately by the prop value. So, for
 *                example, if I wanted to have a player get a specific
 *                name from reading a given entry, the last line of
 *                the text file might look like this:
 *
 *     ::SET_PROP::_read_the_journal_of::PROP_VALUE::Hemmingway
 *
 *                Then, when the player reads that entry, it will
 *                have the same effect as having made the call:
 *
 *     this_player()->add_prop("_read_the_journal_of", "Hemmingway");
 */
public void
read_entry(object who, int entry)
{
    string        n_page = read_file(Journal_Path + entry + ".txt");
    string       *entry_sections;
    string       *prop_sections;
    string       *journal_function_call;
    string       *section_newline;
    string        page =  ((Entry_Word) ? "entry"   : "page");
    string        pages = ((Entry_Word) ? "entries" : "pages");

    if (Closed)
    {
        who->catch_tell("The " + Journal_Name + " is closed.\n");
        return;
    }

    if (!strlen(n_page))
    {
        who->catch_tell("The page appears blank. Please contact"
          + " a wizard about this.\n");
        return;
    }

    who->add_prop(JOURNAL_OBJECT_PROP, file_name(this_object()));

    who->catch_tell("\nThe " + LANG_ORD2WORD(entry)
      + " " + page + " in the " + Journal_Name + " reads as follows:\n\n");

    entry_sections = explode(n_page, "::SET_PROP::");
    journal_function_call = explode(n_page, "::FUNCTION_CALL::");

    tell_room(environment(who), QCTNAME(who) + " reads something"
      + " written in the " + Journal_Name + ".\n", who);
    who->add_prop(JOURNAL_NEXT_PROP, entry + 1);

    if (sizeof(entry_sections) == 2)
    {
        prop_sections = explode(entry_sections[1], "::PROP_VALUE::");
        section_newline = explode(prop_sections[1], "\n");

        /* section_newline[0] is used in the case that the text file
         * has a newline at the end of the line, rather than
         * an EOF. We don't want a newline in the prop value!
         */
        who->add_prop(prop_sections[0], section_newline[0]);
        who->catch_tell(entry_sections[0] + "\n\n");
    }
    else if (sizeof(journal_function_call) == 2)
    {
        prop_sections = explode(journal_function_call[1],
                                "::FILE::");
        section_newline = explode(prop_sections[1], "\n");
        
        if (sizeof(prop_sections) == 2)
        {
            /* This check is necessary in the case that the text file
             * has a newline at the end of the line, rather than
             * an EOF. We don't want a newline in the object pathname!
             */
            if (sizeof(section_newline) == 2)
            {
                call_other(section_newline[0], prop_sections[0], who);
                return;
            }
            else
            {
                call_other(prop_sections[1], prop_sections[0], who);
                return;
            }
        }

        call_other(this_object(), prop_sections[0], who);
        who->catch_tell("\n");
    }
    else
    {
        who->catch_tell(n_page + "\n\n");
    }

    return;
} /* read_entry */


/*
 * Function name:        open_close
 * Description  :        Allow players to open or close the
 *                       Journal as needed
 * Arguments    :        string arg - what was typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
open_close(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [" + Journal_Adj + "] '" + Journal_Name + "'"))
    {
        notify_fail(capitalize(query_verb()) + " the "
          + Journal_Name + ", perhaps?\n");
        return 0;
    }

    if ((query_verb() == "open" && !Closed) ||
        (query_verb() == "close" && Closed))
    {
        write("The " + Journal_Name + " is already "
          + ((query_verb() == "open") ? "open" : "closed") + "!\n");
        return 1;
    }

    write("You " + query_verb() + " the " + short() + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " " + query_verb() + "s the " + short() + ".\n", this_player());

    Closed = !Closed;

    return 1;
} /* open_close */
