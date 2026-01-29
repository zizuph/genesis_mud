/*
 * /d/Gondor/river/anduin/anduin_tod.c
 *
 * time-of-day descs for the anduin -- in progress
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"

public void	set_anduin_tod_descs();
public string	my_night_desc();


/*
 * Function name:	set_anduin_tod_descs
 * Description	:	set the time-of-day descs
 */
public void
set_anduin_tod_descs()
{
    set_stars_desc("The stars are a gossamer scarf of silver "+
	"flung across the night sky.");
    set_night_desc("@@my_night_desc@@");
} /* set_anduin_tod_descs */


/*
 * Function name:	my_night_desc
 * Description	:	mask parent to make lowercase for room desc
 * Returns	:	string -- the desc of the night
 */
public string
my_night_desc()
{
    return "Stars glitter overhead, and "+LOW(query_moon_desc())+
	" It is night in "+query_tod_landname()+".";
} /* my_night_desc */
