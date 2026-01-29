/*
 * /w/petros/open/debugger_tell.c
 *
 * A debugger object that will send messages to those people who are
 * listening to particular debug mesasges
 *
 * Files that have included debugger_tell.h can send messages to
 * anyone who holds a debugger object and is listening to the
 * appropriate tags. The tags do not recover, so you will have to set
 * them each time.
 *
 * Commands:
 *   list tags
 *   list files
 *   list available
 *   addtag <tagname>
 *   remtag <tagname>
 *   addfile <filename>
 *   remfile <filename>
 *   showfiles <tagname>
 *
 * Created by Petros, May 2008
 */
 
#pragma strict_types

inherit "/std/object";

#include "debugger_tell.h"

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

// Prototypes
public int          list_tags(string arg);
public int          add_tag(string arg);
public object       add_file(mixed obj);
public int          remove_tag(string arg);
public object       remove_file(mixed obj);
public int          is_listening(string tag, mixed filename);
public void         add_available(string tag, mixed filename);
public int          showfiles(string arg);

// Global variables
private mapping     tags_available;
private string *    listening_tags;
private string *    listening_files;

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the armour recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover(void)
{
    return (string)0;
}

/*
 * Function name: query_auto_load
 * Description  : Returns the path to this object
 * Returns      : string - the path.
 */
public string
query_auto_load(void)
{
    return MASTER;
}

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("debugger");
    add_name(DEBUGGER_TELL_ID);
    set_short("debugger");
    set_long("This debugger sends tell messages to those people who want "
           + "to listen to the debug message. Here are some basic "
           + "commands:\n\n"         
           + "  list tags          - Shows the tags you're listening to\n"
           + "  list files         - Shows the files you're listening to\n"
           + "  list available     - Shows all the available tags you can "
                                  + "listen to\n"
           + "  addtag <tagname>   - Adds a new tag to listen to\n"
           + "  remtag <tagname>   - Removes a tag from listening\n"
           + "  addfile <filename> - Adds a new file to listen to\n"
           + "  remfile <filename> - Removes a file from the listen list\n"
           + "  showfiles <file>   - Show the list of files that a "
                                  + "particular tag has.\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    
    tags_available  = ([ ]);
    listening_tags  = ({ });
    listening_files = ({ });
}

/*
 * Function name: init
 * Description  : Add the 'command items' of this object. Note that if
 *                you redefine this function, the command items will not
 *                work unless you do ::init(); in your code!
 */
public void
init()
{
    ::init();

    add_action(add_tag, "addtag");
    add_action(list_tags, "list");
    add_action(remove_tag, "remtag");
    add_action(showfiles, "showfiles");
    add_action(add_file, "addfile");
    add_action(remove_file, "remfile");
}


/*
 * Function name: list_tags
 * Description  : List tags that the current person is listening
 *                to. Only messages you are listening for are
 *                shown.
 * Arguments    : arg - argument to the command. must be "tags"
 * Returns      : 0/1 - non-success/success
 */
public int          
list_tags(string arg)
{    
    string header, output, argument;   

    output = "";
    switch (arg)
    {
    case "tags":
        if (sizeof(listening_tags))
        {
            header = "These are the tags you are listening to: \n";
            foreach (string tag : listening_tags)
            {
                output += tag + "\n";
            }
        }
        else
        {
            header = "You are not currently listening to any "
                   + "debugger tags.\n";
        }
        break;
        
    case "files":
        if (sizeof(listening_files))
        {
            header = "These are the files you are listening to: \n";
            foreach (string file : listening_files)
            {
                output += file + "\n";
            }
        }
        else
        {
            header = "You are not currently listening to any "
                   + "files for debug messages.\n";
        }
        break;
        
    case "available":
        if (sizeof(m_indices(tags_available)))
        {
            header = "These are the available tags you can add: \n";
            foreach (string tag : m_indices(tags_available))
            {
                output += tag + "\n";
            }
        }
        else
        {
            header = "The debugger has not yet received any tags.\n";
        }
        break;
        
    default:
        notify_fail("Debugger Usage: list [tags/files/available]\n");
        return 0;
    }
    
    write(header + output + "\n");    
    return 1;
}

/*
 * Function name: showfiles
 * Description  : Lists the files associated with the tag
 * Arguments    : arg - tag to be checked
 * Returns      : 0/1 - non-success/success
 */
public int
showfiles(string arg)
{
    string header, output;
    
    output = "";
    if (IN_ARRAY(arg, m_indices(tags_available)))
    {
        header = "These are the files which send the tag '" + arg + "':\n";
        foreach (string file : tags_available[arg])
        {
            output += "\t" + file + "\n";
        }
    }
    else
    {
        header = "That tag has not been sent to the debugger yet.\n";
    }
    write(header + output);
    return 1;
}

/*
 * Function name: add_file
 * Description  : Adds a new file to listen to
 * Arguments    : arg - file to be added
 * Returns      : 0/1 - non-success/success
 */
public int          
add_file(mixed arg)
{
    string filename;
    object obj;
    
    if (!arg || (!objectp(arg) && !stringp(arg)))
    {
        notify_fail("Add what file?\n");
        return 0;
    }
    
    if (objectp(arg))
    {
        filename = file_name(arg);
    }
    else if (stringp(arg))
    {
        obj = PARSE_COMMAND_ONE(arg, 0, "[the] %i");
        if (!objectp(obj))
        {
            if (!find_object(arg))
            {
                notify_fail("Could not find file object " + arg + ".\n");
                return 0;
            }
            filename = arg;
        }
        else
        {
            filename = file_name(obj);
        }
    }

    if (IN_ARRAY(filename, listening_files))
    {
        notify_fail("The file '" + filename + "' has already been "
                  + "added.\n");
        return 1; 
    }
    
    listening_files += ({ filename });
    write("Ok.\n");
    return 1;
}

/*
 * Function name: remove_file
 * Description  : Removes a new file to listen to
 * Arguments    : arg - file to be added
 * Returns      : 0/1 - non-success/success
 */
public int          
remove_file(mixed arg)
{
    string filename;
    object obj;
    
    if (!arg || (!objectp(arg) && !stringp(arg)))
    {
        notify_fail("Remove which file?\n");
        return 0;
    }
    
    if (objectp(arg))
    {
        filename = file_name(arg);
    }
    else if (stringp(arg))
    {
        obj = PARSE_COMMAND_ONE(arg, 0, "[the] %i");
        if (!objectp(obj))
        {
            if (!find_object(arg))
            {
                notify_fail("Could not find file object " + arg + ".\n");
                return 0;
            }
            filename = arg;
        }
        else
        {
            filename = file_name(obj);
        }
    }
        
    if (!IN_ARRAY(filename, listening_files))
    {
        notify_fail("The file '" + filename + "' is not in the list.\n");
        return 1; 
    }
    
    listening_files -= ({ filename });
    write("Ok.\n");
    return 1;
}

/*
 * Function name: add_tag
 * Description  : Adds a new tag to listen to
 * Arguments    : arg - tag to be added
 * Returns      : 0/1 - non-success/success
 */
public int          
add_tag(string arg)
{
    if (!arg)
    {
        notify_fail("Add what tag?\n");
        return 0;
    }
    
    if (IN_ARRAY(arg, listening_tags))
    {
        notify_fail("The tag '" + arg + "' has already been added.\n");
        return 1; 
    }
    
    listening_tags += ({ arg });
    write("Ok.\n");
    return 1;
}

/*
 * Function name: remove_tag
 * Description  : Removes a new tag to listen to
 * Arguments    : arg - tag to be added
 * Returns      : 0/1 - non-success/success
 */
public int          
remove_tag(string arg)
{
    if (!arg)
    {
        notify_fail("Remove which tag?\n");
        return 0;
    }
    
    if (!IN_ARRAY(arg, listening_tags))
    {
        notify_fail("The tag '" + arg + "' is not in the list.\n");
        return 1; 
    }
    
    listening_tags -= ({ arg });
    write("Ok.\n");
    return 1;
}

/*
 * Function name: is_listening
 * Description  : One can listen to either a tag and/or a specific file
 *                This checks to see if the debugger is currently
 *                listening to either one
 * Arguments    : tag - name of tag to check
 *                obj - object sending the message
 * Returns      : 0/1 - does not have tag/has tag
 */
public int
is_listening(string tag, mixed obj)
{
    string filename, masterfile;
    
    if (objectp(obj))
    {
        filename = file_name(obj);
        masterfile = MASTER_OB(obj);
    }
    else
    {
        filename = obj;
        masterfile = obj;
    }    
    return (IN_ARRAY(tag, listening_tags) 
            || IN_ARRAY(filename, listening_files)
            || IN_ARRAY(masterfile, listening_files));
}

/*
 * Function name: add_available
 * Description  : Every time a send_debug_message is sent, the debugger
 *                will keep track of it. The user can display the ones
 *                that are being received, and can listen to them if
 *                they want.
 * Arguments    : tag      - name of tag being sent
 *                obj      - the object that sent the message
 * Returns      : nothing
 */
public void
add_available(string tag, mixed obj)
{
    string * invalid_files;
    string filename;
    
    if (!IN_ARRAY(tag, m_indices(tags_available)))
    {
        tags_available[tag] = ({ });
    }
    
    if (objectp(obj))
    {
        filename = file_name(obj);
    }
    else
    {
        filename = obj;
    }
    if (!IN_ARRAY(filename, tags_available[tag]))
    {
        tags_available[tag] += ({ filename });
    }
    
    invalid_files = ({ });
    // Now, remove all the objects that are no longer valid
    foreach (string file : tags_available[tag])
    {
        if (!find_object(file))
        {
            invalid_files += ({ file });
        }
    }
    tags_available[tag] -= invalid_files;
}
