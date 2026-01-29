/*
 * Room for drow guild
 * -- Finwe, May 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";

public void
create_drow_room(void)
{
}

public nomask void
create_room(void)
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside a dark cave");    
    set_long("Inside the drow guild.\n");

    add_item(({"walls", "wall"}),
        "The walls are carved out of the mountain. They are polished " +
        "and reflect your image.\n");
    add_item(({"floor"}),
        "The floor is smooth. It has been polished from countless feet " +
        "that have crossed it.\n");
    add_item(({"ceiling"}),
        "The ceiling is high above you. It is lost in the shadows.\n");
    add_item(({"cave", "cavern"}),
        "The cave looks like it was once a natural fissure. It has " +
        "been enlarged and serves the drow. The rock is dark and " +
        "has been polished. Dark veins streak through the rock.\n");
    add_item(({"veins", "dark veins"}),
        "These are irregularly shaped lines of different colored ore " +
        "in the rock. They contrast with the rock and have been carved " +
        "and polished.\n");
    add_item(({"ore", "colored ore"}),
        "This is a type of rocks that makes up the veins in the rock. " +
        "They don't look valuable but are streaked through the rock of " +
        "the cave.\n");
    add_item(({"rock"}),
        "The rock is dark and likely granite. It is very hard and looks " +
        "impervious. Ornate designs have been carved into the rock.\n");
    add_item(({"fire", "faerie fire"}),
        "They are magical lights that highlight and decorate the cave. " +
        "The lights vary in colors from purple and red to bright yellows " +
        "and subtle blues and all shades in between. The lights provide " +
        "dim illumination.\n");
    add_item(({"shadows"}),
        "They hide the back of the cave and the ceiling, hiding what " +
        "may be there.\n");
    add_item(({"designs", "ornate designs"}),
        "The designs are expertly carved into the rock. They are exquisite " +
        "and acentuate the grain of the rock. Many of the designs are " +
        "mesmerizing and seem to hum with life.\n");
    create_drow_room();
}

/* Just a helper function to verify someones rank. */
int
check_drow(mixed who, int rank)
{
    if (objectp(who))
	who = who->query_real_name();
    else
	who = lower_case(who);

    return GSERVER->query_member(who, rank);
}


/* General list ability. */
public int
f_list(string str)
{
    if (!strlen(str))
    {
	    notify_fail("List what?  Choose amongst: houses/cities, <house>, " +
            "ranks.\n", 0);
	return 0;
    }

    switch(str)
    {
    case "cities":
	/* Fallthru */
    case "houses":
    {
	mapping cities = DROW_CITIES;
	string *arr = sort_array(m_indices(cities));
	int ix, size = sizeof(arr);

	/* Woo!  Print print the list */
	write("The known Cities and Houses of the Drow:\n\n");
	for (ix = 0; ix < size; ix++)
	{
	    string *arr2 = sort_array(cities[arr[ix]][0]);
	    int ix2, size2 = sizeof(arr2);

	    write("  City of "+ arr[ix] +":\n\n");
	    for (ix2 = 0; ix2 < size2; ix2++)
	    {
		write(sprintf("    House %-15s %s\n", arr2[ix2],
			(GSERVER->query_house_rank(arr2[ix2], HR_MATRON) ?
			    " Claimed" : "(available)")));
	    }
	    write("\n");
	}
    }
        break;
    case "ranks":
    {
	int size, length;
	string *arr, *darr;
	mapping dmap, drank = DROW_RANKS;

	dmap = map(filter(drank, &operator([])(, DR_APPNT)),
	                         &operator([])(, DR_TITLE));

	darr = m_indices(dmap);
	size = m_sizeof(dmap);
	arr = allocate(size);

	while(size--)
	{
	    arr[size] = sprintf("%20s  --->  %-s",
		darr[size], dmap[darr[size]]);
	}

	write("These are the appointable ranks within a drow House:\n\n");
	write(sprintf("%-=75s\n\n", implode(sort_array(arr), "\n")));
    }
	break;
    default:
	if (!GSERVER->query_house_rank(str, HR_MATRON))
	{
	    mapping cities = DROW_CITIES;

	    if (!cities[str])
	    {
		write("There is no drow House or drow City available "+
		    "by that name to query.\n");
		return 1;
	    }

	    TI->more(read_file(sprintf("%scities/%s",
			GUILD_HELP, cities[str][1])), 0);
	}
	else
	{
	    mixed *ranks = allocate(7);
	    mixed *hdata = GSERVER->query_house_data(str);
	    string *members = hdata[H_MEMBERS];

	    ranks[0] = hdata[H_RANKS][HR_MATRON]   ?: "(none)";
	    ranks[1] = hdata[H_RANKS][HR_DAUGHTER] ?: "(none)";
	    ranks[2] = hdata[H_RANKS][HR_PATRON]   ?: "(none)";
        ranks[6] = hdata[H_RANKS][HR_WIZARD]   ?: "(none)";
	    ranks[3] = hdata[H_RANKS][HR_WMASTER]  ?: "(none)";

	    ranks[4] = hdata[H_RANKS][HR_FNOBLES] ?
		sort_array(hdata[H_RANKS][HR_FNOBLES]) : ({ "(none)" });

	    ranks[5] = hdata[H_RANKS][HR_MNOBLES] ?
	        sort_array(hdata[H_RANKS][HR_MNOBLES]) : ({ "(none)" });

	    members = sizeof(members -= ranks[0..3] + ranks[4] + ranks[5]) ?
		sort_array(members) : ({ "(none)" });

	    write(sprintf("\n  House %s from the City of %s\n\n"+
		    "    Matron Mother:  %s\n"+
		    "   First Daughter:  %s\n"+
		    "     House Patron:  %s\n"+
		    "     House Wizard:  %s\n"+
		    "   Weapons Master:  %s\n\n"+
		    "  Noble Daughters:%2s%-#75s\n"+
		    "       Noble Sons:%2s%-#75s\n"+
		    "        Commoners:%2s%-#75s\n\n",
		str, GSERVER->query_house_city(str),
		CAP(ranks[0]), CAP(ranks[1]), CAP(ranks[2]), CAP(ranks[6]), CAP(ranks[3]),
		sizeof(ranks[4]) > 4 ? "\n" : "",
		implode(map(ranks[4], capitalize), "\n"),
		sizeof(ranks[5]) > 4 ? "\n" : "",
		implode(map(ranks[5], capitalize), "\n"),
		sizeof(members)  > 4 ? "\n" : "",
		implode(map(members, capitalize), "\n")));
	}
        break;
    }
    return 1;
}
