/*
 * /d/Genesis/specials/debugger/debugger_tell.h
 *
 * Include this in whatever file you want to send debugger tell
 * messages.
 *
 * The Debugger object is located at /d/Genesis/specials/debugger/debugger_tell.c
 * To use this to send debug messages, simply call:
 *     send_debug_message(tag, message, logfile)
 *
 * For example, if I want to send a debug message with the "LIBRARY" tag,
 * I can do this by calling like this:
 *     send_debug_message("LIBRARY", "This is a test.")
 *
 * Anyone with a debugger object listening to the "LIBRARY" tag will
 * receive this message.
 *
 * Created by Petros, May 2008
 */

#include <macros.h>
#include <filepath.h>

#define DEBUGGER_TELL_ID    "_debugger_tell_object_"
#define DEBUGGER_OBJ_FILE   "/d/Genesis/specials/debugger/debugger_tell"
#define DEBUGGER_CENTRAL    "/d/Genesis/specials/debugger/debugger_central"

public string
variable2string(mixed var)
{
    string result;
    
    if (stringp(var))
    {
        return var;
    }
    else if (mappingp(var))
    {
        result = "([ ";
        foreach (mixed key : m_indices(var))
        {
            result += variable2string(key) + ":" 
                    + variable2string(var[key]) + ", ";
        }
        result += " ])";
    }
    else if (pointerp(var))
    {
        result = "({ ";
        foreach (mixed element : var)
        {
            result += variable2string(element) + ", ";
        }        
        result += " })";
    }
	else if (objectp(var))
	{
	    result = file_name(var);
	}
	else if (floatp(var))
        {
	    result = ftoa(var);
	}
	else
	{
	    result = sprintf("%O", var);
	}
	
    return result;
}

/*
 * Function name: send_debug_message
 * Description  : Sends a debug message and optionally logs it the
 *                the message to a file.
 * Returns      : tag  - the tag that people will be listening to
 *                text - the actual error text
 *                file - the optional log file (full path)
 */
public varargs void
send_debug_message(string tag, mixed input, string file)
{
    object * debuggers;
    object player;
    string text;
        
    if (!tag || !input)
    {
        return;
    }
    
    if (LOAD_ERR(DEBUGGER_CENTRAL)) 
    { 
        return; 
    }
    
    text = variable2string(input);
    string message = sprintf("<DEBUG> %s: %s [%s]\n", tag, text, file_name(this_object()));
    DEBUGGER_CENTRAL->send_debug_message(this_object(), tag, message);
   
    if (file)
    {
        seteuid(getuid());
        if (file_size(file) > 200000)
        {
            rename(file, file + ".old");
        }
        write_file(file, ctime(time()) + ": " + text + "\n");
    }
}


