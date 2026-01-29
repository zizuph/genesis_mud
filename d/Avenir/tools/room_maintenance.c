/*
 * File:     room_maintenance
 * Created:  Cirion, 1998.05.03
 * Purpose:  tool to facilitate the easy adding
 *           of items, command items, and properties
 *           to rooms.
 * Modification Log:
 *
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>    /* MASTER_OB, etc      */
#include <cmdparse.h>  /* FIND_STR_IN_OBJECT  */

#define RM_PROP_LAST_DESCRIBER "_rm_tool_s_last_describer_file"

inherit "/cmd/std/tracer_tool_base";
string indentation = "    ";
string quote = "\"";


// prototypes
string puncuate_str (string str);
int get_last_str_pos (string str, string start, string end);
varargs int find_in_string (string str, string check, int start_at = 0);
varargs string parse_leading_trailing_spaces (string str, int char = ' ');
varargs string make_quoted_string(string str, int linebreak = 1, int breaklen = 50);
public varargs mixed parse_command_flags (string str, mapping flag_defs = ([ ]));
public string get_backup_file_name (string fname);
varargs mixed rewrite_file (string fname, string text, int backup = 1);
nomask int update_ob(string str);
int insert_code (string insert_str, string *location_tags, string fname, int preview);

// global vars
int debug_level = 0;
mapping flags = ([]);

string
get_soul_id()
{
  return "Cirion's Room Maintainer";
}

int
query_tool_soul()
{
  return 1;
}

mapping
query_cmdlist()
{
  return ([
           "ai" : "ai",
           "aci": "aci",
           "ap" : "ap"
          ]);
}

varargs string
get_room_file_name (string fname = "", object who = this_player (), object where = environment (who))
{
    string   str;

    if (strlen (fname)) // did we specify the room file name?
    {
        if (!wildmatch("*/*", fname)) // check for partial file name
            fname = who->query_path() + "/" + fname; // resolve to full file name

        if (fname [(strlen(fname)-2) .. (strlen(fname)-1)] != ".c")
            fname += ".c"; // complete the LPC source code file name
    }
    else
    {
        if (!where)
        {
            notify_fail ("error: could not obtain file.\n");
            return 0;
        }

        fname = MASTER_OB (where) + ".c";
    }


    return fname;
}

varargs string
get_room_file (string fname = "", object who = this_player (), object where = environment (who))
{
    string str;

    fname = get_room_file_name (fname, who, where);

    if (file_size (fname) > 45000)
    {
        notify_fail ("error: file is too large to read completely. Aborting.\n");
        return 0;
    }

    str = read_file (fname);

    if (!strlen (str))
    {
        notify_fail ("error: could not read file: " + fname + "\n");
        return 0;
    }

    return str;
}

/*
 * Function name: ai
 * Description:   command to add an item to a room
 *                file.
 * Arguments:
 * Returns:
 */
int
ai(string str)
{
    string item_str, desc, add_item_str;
    string *items;
    mixed args;
    mapping flag_defs;
    string *location_tags;

    flags = ([]);

    flag_defs = ([ "file" : ({ "the file name which you want to"
            + " edit", 1, file_name(environment(this_player())) }),
        "verbose" : ({ "give verbose debugging information", 0, 0 }),
        "debug_level" : ({ "level of debugging information", 1, "0" }),
        "describer" : ({ "object through which to filter the description of "
            + "the item, command, etc.", 1, this_player()->query_prop(RM_PROP_LAST_DESCRIBER) }),
        "preview" : ({ "only preview the new file, do not rewrite it", 0, 0 })
        ]);

    location_tags = ({ "add_item", ");", "set_long", ");" });

    debug_level = 0; // reset the debugging level flag

    notify_fail ("syntax: ai [flags] (item1,item2,...,itemn) <description>\n");

    if(!strlen(str))
        return 0;

    if (str == "-help") // special command line flag -help
    {
        // ### todo: add in a dumping of the command line mapping
        write ("This command will allow you to add an item to the room.\n");
        return 1;
    }

    args = parse_command_flags (str, flag_defs);

    if (sizeof (args) != 2)
        return 0; // parse_command_flags handles the notify_fail is it fails

    flags = args[0];  // get the mapping of flag definitions...
    str = args[1];    // ...and the remainder of the string

    if (flags["debug_level"])
        debug_level = atoi(flags["debug_level"]);

    if (flags["debug"])
    {
        write("debug: command line flag specifications:\n");
        dump_mapping (flags);
    }

    // parse for the command line specification
    if(sscanf(str, "(%s) %s", item_str, desc) != 2)
        return 0;

    items = explode(item_str, ",");
    if(!sizeof(items)) // we need some item specification
        return 0;

    items = map (items, parse_leading_trailing_spaces); // get rid of leading and trailing spaces

    // if we specified a special module to remake the description
    // of our module, send desc to that module.
    if (flags["describer"] != 0)
    {
        // we will reset this flag is we were successful
        this_player()->remove_prop(RM_PROP_LAST_DESCRIBER);

        if(catch(desc = flags["describer"]->describe(desc)))
        {
            notify_fail("error: describer module: " + flags["describer"]
                + "\n       raised an error when trying to describe: "
                + desc + "\n");
            return 0;
        }
        else
            this_player()->add_prop(RM_PROP_LAST_DESCRIBER, flags["describer"]);
    }
    else
        desc = make_quoted_string (desc); // otherwise just do our own word wrapping

    if (sizeof (items) == 1) // single item added
        add_item_str = indentation + "add_item(" + quote
            + items[0]
            + quote + ",\n"
            + indentation + indentation + desc
            + ");\n";
    else // multiple items added -- make it an array
        add_item_str = indentation + "add_item(({" + quote
            + implode(items, quote + "," + quote)
            + quote + "}),\n"
            + indentation + indentation + desc
            + ");\n";


    if (!insert_code (add_item_str, location_tags, flags["file"], flags["preview"]))
        return 0;
    else
    {
        write("Success.\n");
        return 1;
    }
}

/*
 * Function name: aci
 * Description:   command to add a command item to a room
 *                file.
 * Arguments:
 * Returns:
 */
int
aci(string str)
{
    string item_str, desc, add_item_str, cmd_str;
    string *items, *cmds;
    mixed args;
    mapping flag_defs;
    string *location_tags;

    flags = ([]);

    flag_defs = ([ "file" : ({ "the file name which you want to"
        + " edit", 1, file_name(environment(this_player())) }),
        "verbose" : ({ "give verbose debugging information", 0, 0 }),
        "describer" : ({ "object through which to filter the description of "
            + "the item, command, etc.", 1, this_player()->query_prop(RM_PROP_LAST_DESCRIBER) }),
        "debug_level" : ({ "level of debugging information", 1, "0" }),
        "preview" : ({ "only preview the new file, do not rewrite it", 0, 0 })
        ]);

    location_tags = ({ "add_cmd_item", ");", "add_item", ");", "set_long", ");" });

    debug_level = 0; // reset the debugging level flag

    notify_fail ("syntax: aci [flags] (cmd1,cmd2,...,cmdn)"
        + " (item1,item2,...,itemn) <description>\n");

    if(!strlen(str))
        return 0;

    if (str == "-help") // special command line flag -help
    {
        // ### todo: add in a dumping of the command line mapping
        write ("This command will allow you to add an item to the room.\n");
        return 1;
    }

    args = parse_command_flags (str, flag_defs);

    if (sizeof (args) != 2)
        return 0; // parse_command_flags handles the notify_fail is it fails

    flags = args[0];  // get the mapping of flag definitions...
    str = args[1];    // ...and the remainder of the string

    if (flags["debug_level"])
        debug_level = atoi(flags["debug_level"]);

    if (flags["debug"])
    {
        write("debug: command line flag specifications:\n");
        dump_mapping (flags);
    }

    // parse for the command line specification
    if(sscanf(str, "(%s) (%s) %s", cmd_str, item_str, desc) != 3)
        return 0;

    items = explode(item_str, ",");
    if(!sizeof(items)) // we need some item specification
        return 0;

    items = map (items, parse_leading_trailing_spaces); // get rid of leading and trailing spaces

    cmds = explode(cmd_str, ",");
    if(!sizeof(cmds)) // we need some command specification
        return 0;

    cmds = map (cmds, parse_leading_trailing_spaces); // get rid of leading and trailing spaces

    // if we specified a special module to remake the description
    // of our module, send desc to that module.
    if (flags["describer"] != 0)
    {
        // we will reset this flag is we were successful
        this_player()->remove_prop(RM_PROP_LAST_DESCRIBER);

        if(catch(desc = flags["describer"]->describe(desc)))
        {
            notify_fail("error: describer module: " + flags["describer"]
                + "\n       raised an error when trying to describe: "
                + desc + "\n");
            return 0;
        }
        else
            this_player()->add_prop(RM_PROP_LAST_DESCRIBER, flags["describer"]);
    }
    else
        desc = make_quoted_string (desc); // otherwise just do our own word wrapping


    add_item_str = indentation + "add_cmd_item(({" + quote
        + implode(items, quote + "," + quote)
        + quote + "}), ({" + quote
        + implode(cmds, quote + "," + quote)
        + quote + "}),\n"
        + indentation + indentation + desc
        + ");\n";


    if (!insert_code (add_item_str, location_tags, flags["file"], flags["preview"]))
        return 0;
    else
    {
        write("Success.\n");
        return 1;
    }
}


/*
 * Function name: ap
 * Description:   command to add a property to a room
 *
 * Arguments:
 * Returns:
 */
int
ap(string str)
{
    string item_str, desc, add_item_str;
    string *items;
    mixed args;
    mapping flag_defs;
    string *location_tags;

    flags = ([]);

    flag_defs = ([ "file" : ({ "the file name which you want to"
        + " edit", 1, file_name(environment(this_player())) }),
        "verbose" : ({ "give verbose debugging information", 0, 0 }),
        "debug_level" : ({ "level of debugging information", 1, "0" }),
        "preview" : ({ "only preview the new file, do not rewrite it", 0, 0 })
        ]);

    location_tags = ({ "add_prop", ");", "set_long", ");" });

    debug_level = 0; // reset the debugging level flag

    notify_fail ("syntax: ap [flags] <prop> <value>\n");

    if(!strlen(str))
        return 0;

    if (str == "-help") // special command line flag -help
    {
        // ### todo: add in a dumping of the command line mapping
        write ("This command will allow you to add an item to the room.\n");
        return 1;
    }

    args = parse_command_flags (str, flag_defs);

    if (sizeof (args) != 2)
        return 0; // parse_command_flags handles the notify_fail is it fails

    flags = args[0];  // get the mapping of flag definitions...
    str = args[1];    // ...and the remainder of the string

    if (flags["debug_level"])
        debug_level = atoi(flags["debug_level"]);

    if (flags["debug"])
    {
        write("debug: command line flag specifications:\n");
        dump_mapping (flags);
    }

    // parse for the command line specification
    if(sscanf(str, "%s %s", item_str, desc) != 2)
        return 0;

    add_item_str = indentation + "add_prop(" + item_str + ", " + desc + ");\n";

    if (!insert_code (add_item_str, location_tags, flags["file"], flags["preview"]))
        return 0;
    else
    {
        write("Success.\n");
        return 1;
    }
}



int
insert_code (string insert_str, string *location_tags, string fname, int preview)
{
    int    loc_index;
    int pos;
    string bkfile;
    string room_file;

    fname = get_room_file_name (fname);
    room_file = get_room_file (fname);

    if (!room_file)
        return 0; // get_file () handles the notify_fail()

    notify_fail ("error: could not locate an appropriate place "
        + "in the file to put the item.\n");

    for (loc_index = 0; loc_index < sizeof(location_tags); loc_index+=2)
    {
        /* Try to add it after the last instance of "location tag*);" */
        /* in the room.                                             */
        pos = get_last_str_pos (room_file, location_tags[loc_index],
            location_tags[loc_index+1]);

        if (debug_level > 6)
            write ("debug: last instance of '"
                + location_tags[loc_index] + "' was " + pos + "\n");

        if (pos >= 0) // found it, beak out of the loop
            break;
    }

    if (pos < 0)
        return 0;

    pos = find_in_string (room_file, "\n", pos); // get the next newline

    if (debug_level > 4)
        write ("debug: next instance of a newline was " + pos + "\n");

    if (pos < 0)
        return 0;

    room_file = room_file[0 .. pos]
        + insert_str
        + room_file[pos+1 .. strlen(room_file)-1];

    if (flags["debug"])
        write ("debug: resulting room file will be:\n" + room_file);

    if (preview)
    {
        write (" ------- Preview of " + fname + " -------\n" + room_file);
        return 1;
    }

    
    if (!(bkfile = rewrite_file(fname, room_file)))
        return 0;
    else
        write ("Successfully rewrote file: " + fname + ".\n");

    // now update the room
    if (!flags["noupdate"])
    {
        if (!update_ob (fname))
        {
            write ("Error: update of " + fname + " failed.\n");
            if (strlen(bkfile))
                write ("Backup file is saved at: " + bkfile + "\n");
        }
        else
        {
            // remove the unneeded backup file
            if (!flags["save_backup"])
                rm (bkfile);

        }
    }

    return 1;
}

/*
 * Function name: rewrite_file
 * Description:   rewrite text into a file.
 *
 * Arguments:
 * Returns:       the backed up file name, if any, or
 *                0 if failure.
 */
varargs mixed
rewrite_file (string fname, string text, int backup = 1)
{
    string bkfile = "";

    if (file_size (fname) < 0)
    {
        notify_fail("error: could not locate file to write to.\n");
        return 0;
    }

    if (backup)
    {
        bkfile = get_backup_file_name (fname);

        if(!strlen(bkfile))
        {
            notify_fail ("error: could not obtain a backup file name.\n");
            return 0;
        }

        if(rename (fname, bkfile) != 1) // perform the file backup
        {
            notify_fail ("error: could not write to backup file: "
                + bkfile + " ... aborting.\n");
            return 0;
        }
    }

    rm (fname); // remove the file name, which may or may not exist

    if (write_file (fname, text) == 0)
    {
        notify_fail ("error: could not write to file " + fname + ".\n");
        return 0;
    }

    return bkfile;
}

/*
 * Function name: get_backup_file_name
 * Description:   get a unique backup file name for the
 *                specified file.
 * Arguments:     fname - the file name to backup
 * Returns:       the name of what the backup file will be.
 */
public string
get_backup_file_name (string fname)
{
    string test_fname;
    int index;

    index = 0;
    fname += ".bk";
    test_fname = fname;

    while (file_size (test_fname) > 0)
        test_fname = fname + (++index); // get a unique name

    return test_fname;

}

/*
 * Function name: parse_command_flags
 * Description:   parse through any flags set on
 *                the command line. This will set up
 *                a mapping of boolean flags.
 * Arguments:     str - the command line string to parse
 *                flags_defs - the definition of the flags. This
 *                    is a mapping of the possible flags and
 *                    whether they need an argument or not, of
 *                    the form: ([ flag_name : ({ help string, needs_arg }) ])
 * Returns:       array of ({ mapping flag_settings,
 *                remainder of string })
 */
public varargs mixed
parse_command_flags (string str, mapping flag_defs = ([ ]))
{
    mapping newflags = ([]);
    mixed   flag_spec;
    int     needs_arg, i;
    string  arg, flag;
    string  *defindices;

    // keep looping over the string while the first
    // character is a '-' (which is the flag specification)
    while (sscanf (str, "-%s %s", flag, str) == 2)
    {
        flag_spec = flag_defs[flag];

        // check to see if we have this flag defined in
        // our flag specification
        if ((sizeof (flag_spec) > 1) && (needs_arg = flag_spec[1]))
        {

            if (needs_arg)
            {
                arg = "";

                // allow then to specify a string with spaces as the
                // command line option by quoting it (otherwise it would
                // count as the next flag)
                if(sscanf (str, "\"%s\" %s", arg, str) != 2)
                    sscanf (str, "%s %s", arg, str); // the next word is the argument

                // validate the arg, abort if it is not valid
                if ((!strlen(arg)) || (arg[0] == '-'))
                {
                    notify_fail ("error: flag -" + flag + " requires "
                        + "an argument.\n");
                    return ({});
                }

                newflags += ([ flag : arg ]); // assign the arg to the specified flag
            }
        }
        else // otherwise it is just a boolean arg
        {
            newflags += ([ flag : 1 ]);
        }
    }


    // now apply the defaults to the remainder of the command line flags
    defindices = m_indices (flag_defs);
    for (i=0;i<sizeof(defindices);i++)
    {
        if (member_array (defindices[i], m_indices (newflags)) == -1)
            newflags += ([ defindices[i] : flag_defs[defindices[i]][2] ]);
    }

    return ({ newflags, str });
}


/*
 * Function name: puncuate_str
 * Description:   support function to add puncuation to a
 *                string that does not already have any
 *                puncuation
 * Arguments:     The string to check for
 * Returns:       the puncuated string
 */
string
puncuate_str (string str)
{
    int test_char;

    test_char = str[strlen(str) - 1];

    // Is the last character of the string alpha? If so,
    // complete it with a period.
    if (test_char < 'z' && test_char > 'A')
        str += ".";

    return str;
}

/*
 * Function name: get_last_str_pos
 * Description:   obtain the position in the string
 *                of the last instance of two consecutive
 *                strings.
 * Arguments:     str - the string to look in
 *                start - the start of the string to look for
 *                end - the end of the string to look for
 * Returns:       the index in the string of the end of the
 *                last instance of the specified start and
 *                end strings. -1 if no instances existed
 *                in str.
 */
int
get_last_str_pos (string str, string start, string end)
{
    int last_instance = 0, check_instance, ending_instance = -1;
    int call_count = 0;

    if (!wildmatch ("*" + start + "*" + end + "*", str)) // make sure there is an instance
        return -1;

    // keep looking for the next instance of the specified string
    // until we find the last one
    while ((check_instance = find_in_string (str, start, last_instance)) >= 0 && call_count++<200)
    {
        if (debug_level > 9)
            write("debug: get_last_str_pos position found in " + check_instance + "\n");

        last_instance = check_instance + 1;
    }

    // now get the next instance of the ending string
    ending_instance = find_in_string(str, end, last_instance);

    if (last_instance < 0)
        return -1;

    if (ending_instance < 0)
        return -1;
    else
        return ending_instance;
}

/*
 * Function name: find_in_string
 * Description:   find the position of a certain string
 *                within another string
 * Arguments:     str - the string to check in
 *                check - the string to check for
 *                start_it - integer specifying the position
 *                    in the string to start looking at.
 * Returns:       the position of check in str, or -1
 *                if no instances were found.
 */
varargs int
find_in_string (string str, string check, int start_at = 0)
{
    string    *broken;

    if (start_at > strlen(str))
        return -1;

    if (start_at > 0)
        str = str [start_at .. strlen(str)-1];

    broken = explode (str, check);

    if (sizeof (broken) > 1) // at least one instance occured
        return strlen (broken[0]) + start_at; // send the length of the first instance
    else
        return -1;

}

/*
 * Function name: parse_leading_trailing_spaces
 * Description:   parse out the leading and trailing
 *                speces of a certain string.
 * Arguments:     str - the string to check for
 * Returns:       the stirng minus any leading and
 *                trailing instances of char
 */
varargs string
parse_leading_trailing_spaces (string str, int char = ' ')
{
    if (!strlen(str))
        return "";

    while (str[0] == char)
        str = str [1 .. strlen(str)-1];

    while (str[strlen(str)-1] == char)
        str = str [0 .. strlen(str)-2];

    return str;
}

/*
 * Function name: make_quoted_string
 * Description:   take a long string and break it up
 *                into different lines, while preserving
 *                LPC indentation and string continuation
 *                conventions and rules.
 * Arguments:     str - the string to break
 *                linebreak - 1 if we want to append an extra '\n'
 *                    to the end of the string (default = 1)
 *                breaklen - the length at which we will break
 *                    the string (using break_stirng ()).
 *                    (default = 50)
 * Returns:
 */
varargs string
make_quoted_string(string str, int linebreak = 1, int breaklen = 50)
{
    string newline;

    if (linebreak)
        newline = "\\n";
    else
        newline = "";

    // break it line by line
    str = break_string(str, breaklen);

    // now add the necessary quotes
    str = implode(explode(str, "\n"), " " + quote + "\n" + indentation
        + indentation + "+ \"");

    // surround the whole thing by quotes
    str = quote + str + newline + quote;

    return str;
}


/*
 * Function name: update_ob
 * Description:   reload a file
 *
 * Arguments:     the file name to reload
 * Returns:       1 if successful, 0 for failure.
 * Note:          this function is mostly just copied
 *                from /cmd/wiz/normal/files.c. I would
 *                have just inherited it, but that file seems
 *                to not be loadable on its own.
 */
nomask int
update_ob(string str)
{
    object ob, *obs;
    int kick_master, i, error;

    ob = find_object (str);

    if (!ob) // object is not loaded: just load it
        return (!(catch(ob->teleldensanka())));
    else
    {
        // OK -- now we need to check to see if there are any players in the room
        // if so, move them to their start locations, and then
        // move them back afterwards.
        str = MASTER_OB(ob);
        obs = filter(all_inventory(ob), interactive);

        error = 0;
        for (i = 0; i < sizeof(obs); i++)
        {
            // check for start locations of players in the room.
            if (obs[i]->query_default_start_location() == str)
            {
                error = 1;    
                write("Cannot update the start location of "
                    + capitalize(obs[i]->query_real_name()) + ".\n");
            }
        }

        if (error == 1)
        {
            notify_fail("error: update failed.\n");
            return 0;
        }

        write("ai: updating object...\n");
        say(QCTNAME(this_player()) + " updates the room.\n");

        /* Move all objects out of the room */
        for (i = 0; i<sizeof(obs); i++)
        {
            if (debug_level > 4)
                write ("debug: sending " + obs[i]->query_name() + " home to to "
                    + obs[i]->query_default_start_location() + ".\n");

            obs[i]->move(obs[i]->query_default_start_location());
        }

        // destruct the object
        ob->remove_object();
        ob = find_object(str);
        if (ob) // still there? Kill it with prejeduce
            SECURITY->do_debug("destroy", ob);

        // try to reload it
        if (catch(str->teleldensanke()))
            return 0;

        ob = find_object (str);

        for (i = 0; i < sizeof(obs); i++)
        {
            if (debug_level > 4)
                write ("debug: sending " + obs[i]->query_name() + " back to "
                    + file_name (ob) + ".\n");
            obs[i]->move(ob, 1);
        }

        return 1;
    }
}

