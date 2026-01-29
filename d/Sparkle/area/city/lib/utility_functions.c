/*
 * Sparkle City Utility Function
 *
 * We keep commonly used functions here to be reused in other
 * parts of the code.
 *
 * Created by Petros, May 2009
 */

#include <std.h>
#include <macros.h>
 
/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    if (!strlen(filename))
    {
        return 0;
    }

    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
}
