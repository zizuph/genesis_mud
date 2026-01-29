/* Clock Master
 * 
 * Gondor's clock notifies this object when sunrise and sunset
 * occurs and this object is used to notify any objects within the
 * Shire about this event.
 *
 * Created by Igneous, Dec 1997
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include <macros.h>
#include "/d/Shire/sys/files.h"

#define SAVE_FILE "/d/Shire/sys/global/clock_master"

public string * Filenames = ({});

/* Function name: create
 * Description:   This files constructor function used to restore data
 */
void
create()
{
    setuid(); seteuid(getuid());
    restore_object(SAVE_FILE);
    if (!pointerp(Filenames))
	Filenames = ({});

    // Set up the master in the Gondor Clock
    CLOCK->set_shire_master(MASTER_OB(this_object()));
}

/* Function name: add_clock_master_file
 * Description:   Adds the filename to the list of files which this
 *                object notifies about sunrise, sunset and hourly changes.
 * Arguements:    string file:  The Filename to be added.
 */
void
add_clock_master_file(string file)
{
    if (!file || !stringp(file))
	return; 
    if (!pointerp(Filenames) || !sizeof(Filenames))
	Filenames = ({file});
    if (member_array(file, Filenames) == -1)
	Filenames += ({file});
    save_object(SAVE_FILE);
}

/* Function name: remove_clock_master_file
 * Description:   Removes the filename to the list of files which this
 *                object notifies about sunrise, sunset and hourly changes.
 * Arguements:    string file:  The Filename to be removed.
 */
void
remove_clock_master_file(string file)
{
    if (!file || !stringp(file))
	return; 
    if (!pointerp(Filenames) || !sizeof(Filenames))
	return;
    if (member_array(file, Filenames) != -1)
	Filenames -= ({file});
    save_object(SAVE_FILE);
}

/* Function name: query_clock_master_files
 * Description:   Returns a list of filenames
 * Returns:       The array of filenames this file notifies about
 *                sunrise and sunset.
 */
string *
query_clock_master_files()
{
    return Filenames;
}

/* Function name: sunrise
 * Description:   Notifies files that sunrise has just occured.
 */
void
sunrise()
{
    int i;
    object ob;

    if (!pointerp(Filenames) || !sizeof(Filenames))
	return;

    i = -1;
    while(++i < sizeof(Filenames))
    {
	catch(call_other(Filenames[i], "??"));
	if (!objectp(ob = find_object(Filenames[i])))
	    log_file("clock_master", ctime(time()) +" Failed to load "+
	      Filenames[i]+".\n");
	else
	    ob->sunrise();
    }
}

/* Function name: sunset
 * Description:   Notifies files that sunset has just occured.
 */
void
sunset()
{
    int i;
    object ob;

    if (!pointerp(Filenames) || !sizeof(Filenames))
	return;

    i = -1;
    while(++i < sizeof(Filenames))
    {
	catch(call_other(Filenames[i], "??"));
	if (!objectp(ob = find_object(Filenames[i])))
	    log_file("clock_master", ctime(time()) +" Failed to load "+
	      Filenames[i]+".\n");
	else
	    ob->sunset();
    }
}

/* Function name: change_hour
 * Description:   Notifies files that new hour has just begun.
 * Arguements:    int hour: The current hour.
 */
void
change_hour(int hour)
{
    int i;
    object ob;

    if (!pointerp(Filenames) || !sizeof(Filenames))
	return;

    i = -1;
    while(++i < sizeof(Filenames))
    {
	catch(call_other(Filenames[i], "??"));
	if (!objectp(ob = find_object(Filenames[i])))
	    log_file("clock_master", ctime(time()) +" Failed to load "+
	      Filenames[i]+".\n");
	else
	    ob->change_hour(hour);
    }
}
