/* The graveyard controller
 *
 * //Nick
 */

#include <language.h>
#include "local.h"

/*
 * Function name: killed
 * Description:   A monster killed someone,
 * Arguments:     killer - The killer
 *                str2 - The killed one
 */
void
killed(object killer, string name)
{
    string desc, filename, age;
    object killed;
    int i, j;

    seteuid(getuid(this_object()));
    if (!(killed = find_player(lower_case(name))))
	return;

    name = capitalize(name);

    i = killed->query_age();
    if (i / 43200 > 0)
	age = "" + (i / 43200) + (i / 43200 > 1 ? " days" : " day");
    else if (i / 1800 > 0)
	age = "" + (i / 1800) + (i / 1800 > 1 ? " hours" : " hour");
    else
	age = "" + (i / 30) + (i / 30 > 1 ? " minutes" : " minute");

    desc = break_string( "Killed, " + extract(ctime(time()), 4, 9) + 
	", " + age + " old by " +
	LANG_ADDART(killer->query_nonmet_name() + ".\n"), 70);
    filename = GRAVE_LOG + extract(name, 0, 0) + "/" + name;
    /* Has this player a grave already? */
    if (file_size(filename) >= 0)
    {
	write_file(filename, desc);
	return;
    }

    /* A new grave */
    write_file(filename, "Here rests the remains of poor " +
	capitalize(name) + ".\nMay " + killed->query_pronoun() + 
	" rest in peace.\n\n");
    write_file(filename, desc);
    filename = GRAVE_LOG + "rooms/room";
    i = random(NUM_OF_GRAVES + 1);
    for (j = 0; j < NUM_OF_GRAVES + 1; j++)
    {
	if (++i >= NUM_OF_GRAVES)
	    i = 0;
	if (file_size(filename + i) < 150)
	    break;
    }

    write_file(filename + i, " " + name + " ");   
}



/* help function to prevent a too long evaluation error when digging up graves
 * -called via alarms
 */
dig_up_one_room(string roomname, int i, int rem_time, object tp)
{
    int graves, j;
    string filename, str, *names;
    
    
    str = read_file(roomname + i);
    names = explode(str, " ");
    for (j = 0; j < sizeof(names); j++)
    {
	filename = GRAVE_LOG + extract(names[j], 0, 0) + "/" + names[j];
	if ((file_size(filename) > 0) && (file_time(filename) < rem_time))
	{
	    rm(filename);
	    graves++;
	    names[j] = 0;
	}
    }
    str = implode(names - ({ "" }), " ");
    rm(roomname + i);
    if (strlen(str) > 1)
      write_file(roomname + i, str);
    
    tp->catch_msg("GRAVECONTROLLER: " + graves +
				     " graves removed.\n");
}


/*
 * Function name: dig_up_old_graves
 * Description:   This functions should dig up old graves to make room for
 *		  new ones, i.e. clean up things.
 * Arguments:     days - How old files we shall remove
 * Returns:       number of graves removed.
 */
int
dig_up_old_graves(int days)
{
    int rem_time, i;
    string roomname;

    seteuid(getuid(this_object()));
    days = days * 24 * 60 * 60;
    rem_time = time() - days; /* Older files will be removed, graves dug up. */

    roomname = GRAVE_LOG + "rooms/room";
    while (file_size(roomname + i) > 0)
    {
	set_alarm(itof(i*2),0.0,&dig_up_one_room(roomname,i,rem_time,this_player()));
	i++;
    }

    return 0;/*graves;*/
} 
    
/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
