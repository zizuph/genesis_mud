// Sybarus Source fluctuations (/d/Avenir/common/source_flux.c)
// creator(s):   Tepisch July 94
// last update:  Ilyian  30 March, 1995 (remove extra CRs because I think
//                                       they look ugly, added messages.)
//               Boriska Aug 95: Changes to reduce CPU usage
//               Cirion Jan 96: Added function special_flux
//		         Denis, Jul'97: Recoded to take less cpu.
// purpose:      Provides 'ambiance' for the Utterdark/Sybarus.
// note:         Gives messages indicating fluctuations of the Source.
// bug(s):
// to-do:

#pragma no_clone
#pragma no_shadow
#pragma strict_types

/* Prototyps.
 */
void start_tells();

#define FLUX_PERIOD	(itof(random(300)) + 300.0)

/* Globals.
 */
/* What areas should be affected by the fluctuation? The Cavern: 
 * Sybarus and surrounding areas will all recieve the same message.
 * Every specific file that is named in this array will be affected.
 * Every file in every subdir that is named will be affected.
 * If you have an entire subdir you want affected, and only one
 * or two rooms you don't, use the property IN_IN in those rooms
 * (see common.h or macros.h for IN_IN define.
 */
	   
private static string *gAreas = ({ 
    "/d/Avenir/common/bazaar/green/*",
    "/d/Avenir/common/bazaar/extr/*", 
    "/d/Avenir/common/city/entry/*",
    "/d/Avenir/common/city/zigg/garden/*",
	"/d/Avenir/common/dead/hill/*",
	"/d/Avenir/common/dead/marsh/*",
    "/d/Avenir/common/dead/path/*",
    "/d/Avenir/common/holm/jungle/*",
    "/d/Avenir/common/holm/shore/*",
    "/d/Avenir/common/holm/t_camp/*",
	"/d/Avenir/common/ledge/*",
    "/d/Avenir/common/outpost/*",
    "/d/Avenir/common/outpath/*", 	
    "/d/Avenir/common/park/*",
    "/d/Avenir/common/village/merc/*",
});

private static string *gTells =  ({ 
    "A painfully bright light floods the area from above, making "+
        "your eyes water.\n", 
    "The light pulses brightly for a moment, then fades to an "+ 
        "intensity similar to that of sunlight.\n", 
    "You can't help but notice that the light source is "+ 
        "gradually fading.\n", 
    "The light from above gently throbs in intensity, almost like a "+ 
        "heartbeat.\n", 
    "...Blackness.\nUtter Blackness consumes you.\nJust as you are "+ 
        "ready to panic, watery yellow light glows from above, "+ 
        "relieving the darkness.\n", 
    "The shadowy half-light dims to a point reminiscent of gloaming.\n", 
    "The light-level slowly rises, haloing everything in a misty "+
        "white nimbus for a brief moment.\n", 
    "The illumination from above is so fuzzy and indirect that you "+
        "notice nothing casts a shadow.\n", 
    "The light ebbs and flows in a gentle, pleased pulsing.\n",
});

private static int gAlarm_id = 0;

/*
 * Function name: create
 * Description:   Initializes tells.
 */
private void
create(void)
{
    start_tells();
}

/*
 * Function name: in_tell_zone
 * Description:   Check to see if a specific player should be affected.
 * Arguments:     ob - the player to check
 * Returns:       1 - in tell zone,
 *		  0 - not.
 */
private int
in_tell_zone(object ob)
{
    string str;

    // If the player was removed or is not in a room, he should not be
    // affected 
    if (!ob || !environment(ob) ||
	environment(ob)->query_prop("_not_in_flux_zone"))
    {
        return 0;
    }

    str = file_name(environment(ob));

    if (!wildmatch("/d/Avenir/*", str))
	return 0;

    /*
     * Check to see if the filename matches anything in the AREAS
     * array
     */
    foreach(string area : gAreas)
    {
	if (wildmatch(area, str))
	    return 1;
    }

    /* The player should not be affected */
    return 0;
}

/*
 * Function name: do_tells
 * Description:   main tells' teller :) 
 */
private void
do_tells(void)
{
    gAlarm_id = 0;
    start_tells();
    filter(users(), in_tell_zone)->catch_tell(one_of_list(gTells));
}

/*
 * Function name: start_tells
 * Description:   call this to start area tells
 */
public void
start_tells(void)
{
    if (!gAlarm_id)
	gAlarm_id = set_alarm(FLUX_PERIOD, 0.0, do_tells);
}

/*
 * Function name: stop_tells
 * Description:   call this when area tells should be stopped for some reason
 */
public void
stop_tells(void)
{
    remove_alarm(gAlarm_id);
    gAlarm_id = 0;
}

/*
 * Function name: query_alarms
 * Description:   Needed for the 'Dump alarms' to work.
 * Returns:       
 */
public mixed *
query_alarms(void)
{
    return get_all_alarms();
}

/* special fluctuation controller */
public void
special_flux(string str) 
{
    filter(users(), in_tell_zone)->catch_tell(str);
}
