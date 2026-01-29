/* help.c created by Shiva@Genesis
 *
 * Simple management of help files.
 *
 * Adds a help command using the syntax
 *
 *     "help <help type> <subject>"
 *
 * Allows simple addition of new help subjects by creating help files
 * in a specified directory with a name that corresponds to the subject
 * and a special extension that designates it as a help file (".help" by
 * default).
 * 
 *
 * Example usage:
 * 
 * inherit "/cmd/std/command_driver";
 * inherit "/d/Wiz/shiva/open/help";
 *
 * void
 * create()
 * {
 *     // The type of help we're giving.
 *     set_help_type(({ "shiva", "siva" }));
 *
 *     // Find the help files in my help directory
 *     read_help_dir("/d/Wiz/shiva/help/");
 * }
 *
 * // standard soul stuff
 * int
 * query_cmd_soul()
 * {
 *     return 1;
 * }
 *
 * // standard soul stuff
 * string
 * get_soul_id()
 * {
 *     return "My soul";
 * }
 *
 * // Gives the cmdlist mapping
 * mapping
 * query_cmdlist()
 * {
 *     // Return our command mapping plus the help command mapping 
 *     return ([ "dummy" : "dummy" ]) + help_cmdlist();
 * }
 *
 * // A dummy command; it does nothing.
 * int
 * dummy(string str)
 * {
 *     return 0;
 * }
 *
 * Given the soul above, one could execute the command
 *
 *     "help shiva xxx"
 *
 * and the contents of /d/Wiz/shiva/help/xxx.myhelp would be displayed.
 *
 * Simply executing
 *
 *     "help shiva"
 *
 * gives a listing of possible help subjects.
 */

static string *help_type = ({});
static mapping help_map = ([]);

/*
 * Function name: help_commands
 * Description:   Returns the filename passed to it, minus the extension if
 *                the extension matches the specified help file extension.
 * Arguments:     string file - a filename
 * Returns:       mixed - the filename minus it's extension or 0 if the
 *                         extension doesn't match the help file extension.
 */
mixed
help_commands(string file, string ext)
{
    string name;
    return (sscanf(file, "%s." + ext, name) ? name : 0);
}

/*
 * Function name: query_subjects
 * Description:   get the subject names currently available
 * Returns:       an array of subject names
 */
string *
query_subjects()
{
    return m_indices(help_map);
}

/*
 * Function name: get_help
 * Description: get the help data for a given subject
 * Arguments:   string subject - the subject name
 * Returns:     The help data or "" if none could be found
 */
string
get_help(string subject)
{
    mixed val = help_map[subject];
    int size;

    if (!val)
    {    
        return "";
    }

    if (stringp(val))
    {    
        if ((size = file_size(val)) == -1) // file does not exist
	{
            return val;
	}

        if (size < 1) // empty file or directory
	{
            return "";
	}

        return read_file(val);
    }

    if (functionp(val))
    {
        return val();
    }

    return "";
}
      
/*
 * Function name: _help
 * Description:   The "help" command.  Give a listing of help subjects or
 *                print the contents of a help file.
 * Arguments:     string str - arguments given to the "help" command.
 * Returns:       1 / 0 - success / failure
 */
int
_help(string str)
{
    string help, *subjects, temp;
    int i;

    setuid();
    seteuid(getuid());
  
    if (member_array(str, help_type) >= 0)
    {
        if (!sizeof(subjects = query_subjects()))
        {
            return 0;
        }
    
        str = implode(subjects, "\n");
    
        write("Help is available on these subjects:\n\n");
        write(sprintf("%-#60s\n", str));
        write("\nUse 'help " + help_type[0] + " <subject>' to access help files.\n\n");
    
        return 1;
    }
  
    if (!strlen(str))
    {
        return 0;
    }

    for (i = 0; i < sizeof(help_type); i++)
    {
        parse_command(str, this_object(), "'" + help_type[i] + "' %s",
            temp);        
        if (strlen(help = get_help(temp)))
	{
            write("\n");
            this_player()->more(help);
        
            return 1;
        }
    }
  
    return 0;
}

/*
 * Function name: read_help_dir
 * Description:   Check the specified directory to find help files
 * Arguments:     string dir - the directory
 *                string ext - the extension used to identify help
 *                             files in the specified directory.
 */
varargs void
read_help_dir(string dir, string ext = "help")
{
    string *files, help_cmd;
    int i;
    
    setuid();
    seteuid(getuid());

    files = get_dir(dir);

    for (i = 0; i < sizeof(files); i++)
    {
        if (help_cmd = help_commands(files[i], ext))
	{        
            help_map[help_cmd] = dir + files[i];
	}
    }
}

/*
 * Function name: add_help
 * Description:   Add a help subject.
 * Arguments:     string subject - the subject name
 *                mixed src - A filename if the data should be read from
 *                            disk, a string to be used as the data, or a
 *                            function pointer to a function which will
 *                            return the data.
 */
void
add_help(string subject, mixed src)
{
    help_map[subject] = src;
}

/*
 * Function name: set_help_type
 * Description:   Specify the type of help we're giving.  This will be
 *                used to determine correct syntax for the "help" command.
 * Arguments:     string *type - an array of strings.  Any of these strings
 *                               may be used as the second argument to the
 *                               "help" command.
 */
void
set_help_type(string *type)
{
    help_type = type;
}

/*
 * Function name: help_cmdlist
 * Description:   Returns a mapping that maps help command names to help
 *                function names
 * Returns:       See above
 */
mapping
help_cmdlist() 
{
    return ([ "help" : "_help" ]);
}
