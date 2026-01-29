/*
 * This is the master object of Pax Tharkas. It has full control of
 * almost all events that may occur in Pax Tharkas and the Sla-Mori
 *
 * 950401 by Rastlin
 */

#pragma no_inherit

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit  "/std/object";

#define LINES 1000

/* Static global vars - not to be saved */
static mapping gPlayermap = ([ ]);
static int gSlugactive = 0;
static int gZombie;

public void handle_pax_logs();
public void select_zombie();

void
reset_object()
{
    select_zombie();
}


void
create_object()
{
    set_name(({"pax object", "_pax_controller_", "controller"}));
    set_long("This is the master controller for Pax Tharkas and the Sla-Mori.\n");
    set_short("controller");

    seteuid(getuid());

    if (IS_CLONE)
	remove_object();

    handle_pax_logs();

    enable_reset(200);
    reset();
}

/* 
 * Function:	read_log
 * Arguments:	logarea - A part of the path, ie 'pax', 'solace'
 *		logname - The name of the log to scan
 *		logdir  - Put the result files here
 * Description:	Extract all the log text according to a certain area
 *		and put them in a file. It will also save a new version
 *		of the log, with all the extracted text removed.
 */
public void
read_log(string logarea, string logname, string logdir)
{
    int end_file, size_lines, line_nr, start, t, found_area, save;
    string t1, t2, file, area;
    string area_log, new_log, buffer;
    mixed lines;

    area_log = "";
    new_log = "";
    start = 1;
    line_nr = 0;
    end_file = 0;

    while(!end_file)
    {
	buffer = read_file("/d/Krynn/log/" + logname, start, LINES);

	if (!buffer || !strlen(buffer))
	  return;

        lines = explode(buffer, "\n");
        size_lines = sizeof(lines);

        if (size_lines < LINES)
	    end_file = 1;

        while (line_nr < size_lines)
        {
	    sscanf(lines[line_nr], "%s %d %s (%s)", t1, t, file, t2);

	    if (sscanf(file, "/d/Krynn/%s/%s", area, t1) == 2)
	    {
		if (area == logarea)
	        {
		    area_log += lines[line_nr] + "\n";

		    found_area = 1;

		    while (found_area)
		    {
			if (++line_nr >= LINES)
			{
			    start += LINES;

			    buffer = read_file("/d/Krynn/log/" + logname, start, LINES);

		 	    lines = explode(buffer, "\n");
			    size_lines = sizeof(lines);

			    line_nr = 0;
			    save = 1;

		            if (size_lines < LINES)
				end_file = 1;
			}

			if ((line_nr >= size_lines) && (size_lines < LINES))
			{
			    write_file(logdir + logname, area_log);
			    write_file(logdir + logname + ".new", new_log);
			    return;
			}

 			if (sscanf(lines[line_nr], "%s %d %s (%s)", t1,
					t, file, t2) != 4)
			    area_log += lines[line_nr] + "\n";
			else
			    found_area = 0;
		    }
		}
	        else
		{
		    new_log += lines[line_nr] + "\n";
		    line_nr++;
		}
	    }
	    else
	    {
		new_log += lines[line_nr] + "\n";
		line_nr++;
	    }

	    if (save)
	    {
		write_file(logdir + logname, area_log);
		write_file(logdir + logname + ".new", new_log);
		area_log = "";
		new_log = "";
		save = 0;
	    }
	}

	write_file(logdir + logname, area_log);
	write_file(logdir + logname + ".new", new_log);
	area_log = "";
	new_log = "";
	line_nr = 0;
	start += LINES;
    }
}

/*
 * Function:	move_file
 * Arguments:	oldfile - The name of the old file
 * 		newfile - The name of the new file
 * Description: Move a file from one place to another and if the file
 *		already exists on the new place remove it.
 */
public int
move_file(string oldfile, string newfile)
{
    string buffer;
    int size, i, counter;

    rm(newfile);

    size = file_size(oldfile);

    i = 0;
    counter = 0;

    while (i < size)
    {
	buffer = read_file(oldfile, (counter * 1000) + 1, 1000);
	i += strlen(buffer);
	write_file(newfile, buffer);
	counter++;
    }

    rm(oldfile);
}

/*
 * Function:	handle_pax_logs
 * Description:	Scan every choosed log and replace the old log
 *		with the new one.
 */
public void
handle_pax_logs()
{
/*
    set_alarm(1.0, 7200.0, "fix_pax_praise");
*/
}

public void
fix_pax_praise()
{
    read_log("pax", "praise", "/d/Krynn/pax/log/");
    move_file("/d/Krynn/pax/log/praise.new", "/d/Krynn/log/praise");
    set_alarm(5.0, 0.0, "fix_pax_bugs");
}

public void
fix_pax_bugs()
{
    read_log("pax", "bugs", "/d/Krynn/pax/log/");
    move_file("/d/Krynn/pax/log/bugs.new", "/d/Krynn/log/bugs");
    set_alarm(5.0, 0.0, "fix_pax_typos");
}

public void
fix_pax_typos()
{
    read_log("pax", "typos", "/d/Krynn/pax/log/");
    move_file("/d/Krynn/pax/log/typos.new", "/d/Krynn/log/typos");
    set_alarm(5.0, 0.0, "fix_pax_ideas");
}

public void
fix_pax_ideas()
{
    read_log("pax", "ideas", "/d/Krynn/pax/log/");
    move_file("/d/Krynn/pax/log/ideas.new", "/d/Krynn/log/ideas");
}

/* Player stuff */
public void
add_player(string name, object obj)
{
    gPlayermap += ([ name : obj ]);
}

public void
remove_player(string name)
{
    gPlayermap = m_delete(gPlayermap, name);
}

public mapping
query_players()
{
    return gPlayermap;
}

public int
filter_player(object ob)
{
    string t;

    return sscanf(file_name(E(ob)), "/d/Krynn/pax/%s", t);
}

public void
update_player_map()
{
    gPlayermap = map(gPlayermap, "filter_player", TO);
}

public object *
query_player_objects()
{
    update_player_map();

    return m_values(gPlayermap);
}

/*
 * Function:	select_zombie
 * Description: Select the Zombie that will carry the key in the Tomb
 */
public void
select_zombie()
{
    gZombie = random(8) + 1;
}

/*
 * Function:	query_zombie
 * Description:	Return the selected Zombie number
 * Returns:	Return the selected Zombie number
 */
public int
query_zombie()
{
    return gZombie;
}

static void
give_wiz_info(mixed wiz, object who)
{
    if (objectp(wiz))
        if (wiz->query_prop("_live_i_want_pax_info"))
	    wiz->catch_msg("*PAX* " + who->query_name() + " enters.\n");
}

/*
 * Function:    try_enter_pax
 * Arguments:   the player object that tries to enter.
 * Description: Log the name and time on the player who tries
 *              to enter the Pax area.
 */
public void
try_enter_pax(object who)
{
    string str;

    give_wiz_info(find_living("rastlin"), who);
    give_wiz_info(find_living("jeremiah"), who);
    give_wiz_info(find_living("aridor"), who);

    str = who->query_name() + "\t" + ctime(time()) + 
      sprintf("\tAvg stat: %i\n", who->query_average_stat());

    /*write_file(PLOG + "TRY_ENTER", str);*/
}
