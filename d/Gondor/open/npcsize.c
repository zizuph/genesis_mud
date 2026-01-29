/*
 * /d/Gondor/open/npcsize.c
 *
 * the command:
 *	npcsize race height_desc and width_desc
 * will print the CONT_I_HEIGHT and CONT_I_WEIGHT values that will 
 * produce the desired appearance.
 *
 * e.g.:
 *	npcsize human short and skinny
 * prints:
 *	CONT_I_HEIGHT 144 CONT_I_WEIGHT 33552
 * the command:
 *	npcsize help
 * prints all races and height/width descriptions
 *
 * to use, inherit this file in your workroom and call init_npcsize()
 * from your workroom's init().
 */

#include <composite.h>
#include <login.h>

/* prototypes */
public void	init_npcsize();
public int	npcsize(string arg);

/*
 * Function name:	init_npcsize
 * Description	:	called from room's init() to add
 *			the 'npcsize' command
 */
public void
init_npcsize()
{
    add_action(npcsize, "npcsize");
}


/*
 * Function name:	npcsize
 * Description	:	find the height and weight needed to get
 *			a desired appearance for a particular race.
 * Arguments	:	string arg -- "race heightdesc and widthdesc"
 *				      or "help"
 * Returns	:	1 (always)
 *
 * Requiring 'and' between height & width description vastly simplifies
 * parsing.
 */
public int
npcsize(string arg)
{
    int		hindex,
		windex,
		*spread,
		spreadsize,
		height,
		*raceattr;
    string	racestr,
		heightstr,
		widthstr;

    if (arg == "help")
    {
	write("Valid races:\n"+
	    break_string(COMPOSITE_WORDS(RACES), 75)+".\n");
	write("Valid heights:\n"+
	    break_string(COMPOSITE_WORDS(HEIGHTDESC), 75)+".\n");
	write("Valid widths:\n"+
	    break_string(COMPOSITE_WORDS(WIDTHDESC), 75)+".\n");
	return 1;
    }

    /* sanity checks */
    if (!arg ||
	 sscanf(arg, "%s %s and %s", racestr, heightstr, widthstr) != 3)
    {
    	write("USAGE: npcsize race heightdesc and widthdesc\n"
	    + "or:    npcsize help\n");
	return 1;
    }

    /* ok, we got race, height & width -- see if they're valid */
    if (member_array(racestr, RACES) < 0)
    {
	write("npcsize err: unknown race '"+racestr+"'\n");
	return 1;
    }
    raceattr = RACEATTR[racestr];
    if (sizeof(raceattr) < 6 ||
        raceattr[0] <= 0 ||
        raceattr[4] <= 0 ||
        raceattr[5] <= 0)
    {
	write("npcsize err: bad attributes for race '"+racestr+"'\n");
	return 1;
    }
    spread = SPREAD_PROC;
    spreadsize = sizeof(spread);
    if (heightstr == "normal")
    {
	heightstr = "of normal length";
    }
    if ((hindex = member_array(heightstr, HEIGHTDESC)) < 0)
    {
	write("npcsize err: bad height desc '"+heightstr+"'\n");
	return 1;
    }
    if (hindex >= spreadsize)
    {
	write("npcsize err: bad height index into SPREAD_PROC\n");
	return 1;
    }
    if (widthstr == "normal")
    {
	widthstr = "of normal width";
    }
    if ((windex = member_array(widthstr, WIDTHDESC)) < 0)
    {
	write("npcsize err: bad width desc '"+widthstr+"'\n");
	return 1;
    }
    if (windex >= spreadsize)
    {
	write("npcsize err: bad width index into SPREAD_PROC\n");
	return 1;
    }

    height = ((raceattr[0] * spread[hindex]) / 100);
    write("CONT_I_HEIGHT "
	+ height
	+ " CONT_I_WEIGHT "
	+ (((raceattr[5] * spread[windex]) / 100) * height)
	+ " CONT_I_VOLUME "
	+ (raceattr[4] * 1000)
	+ "\n");
    return 1;
}
