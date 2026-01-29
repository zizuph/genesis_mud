/*
 * Standard file for the rooms in Helm's Deep
 * The file idea was taken from Olorin's /d/Gondor/morgul/tower/tower.c
 *
 * March 1994 by Arren
 * The rooms were first made in June 1993, but are now modified
 * to inherit this file.
 *
 * 21-Dec-97, Gnadnar, general cleanup:  
 * 1) of the 58 rooms that inherit this file, only 2 used the global
 *   vars q_guard[123] and erkenbrand -- seems somewhat wasteful to
 *   have those globals in the other 56 rooms, so i removed the globals
 *   and changed those 2 files.
 * 2) the globals foot_room, court_room, clock, time were unnecessary.
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

static int	inside_keep;
static string	extra_long,
                short_desc,
                track_dir1,
                track_dir2,
                below_desc,
                below_room;

/* Prototypes */
public string	long_desc();
public string	find_tracks();
public string	down_there();
public int	call_helmsdeep_guard(object abuser);
public void	set_extra_long(string x);
public void	set_short_desc(string s);
public void	set_inside_keep(int i);
public void	set_track_dir1(string s);
public void	set_track_dir2(string s);
public void	set_below_desc(string s);
public void	set_below_room(string s);


public void 
create_helmsdeep_room()
{
    set_short("In Helm's Deep");
    set_extra_long("Somewhere in Helm's Deep in Rohan.\n");
}

nomask void 
create_gondor()
{
    add_item(({ "ground", "track", "tracks", "footprints" }), find_tracks);

    create_helmsdeep_room();

    set_short(short_desc);
    set_long(long_desc);
}

public void set_extra_long(string x)	{ extra_long = x; }
public void set_short_desc(string s)	{ short_desc = s; }
public void set_inside_keep(int i)	{ inside_keep = i; }
public void set_track_dir1(string s)	{ track_dir1 = s; }
public void set_track_dir2(string s)	{ track_dir2 = s; }
public void set_below_desc(string s)	{ below_desc = s; }
public void set_below_room(string s)	{ below_room = s; }

public string
long_desc()
{
    string desc, time;

    time = tod();
    desc = "";
    if (file_name(TO) == FOOTPRINT_ROOM)
    {
         if (TP->query_prop(FOUND_ORC) &&
             TP->query_skill(SS_TRACKING) > TRACK_LOW)
            desc += "Two deep footprints can be seen at "+
            "the base of the wall. ";
    }
    else if (file_name(TO) == COURTYARD_ROOM)
    {
        if (TP->query_race() == "dwarf")
             desc += "You feel that the country has tough bones. The "+
             "Gondorians choose well when they placed a keep here. ";
    }

    switch(time)
    {
        case "night":
            desc += "The dark sky above you is full of stars. ";
            break;
        case "early morning":
        case "morning":
            if ( !inside_keep )
                desc +=  "The light of the day shines from the east, "+
                         "and the cliffs cast long shadows. ";
            else
                desc +=  "The light of the day shines from the east. ";
            break;
        case "noon":
            desc += "The light of the day shines down from right above "+
            "your head. ";   
            break;
        case "afternoon":
        case "evening":
            if ( !inside_keep )
                desc +=  "The light of the day shines from the west, "+
                         "and the cliffs cast long shadows. ";
            else
                desc +=  "The light of the day shines from the west. ";
            break;
    }
    desc += "It is " + time + " in Rohan. ";
    return BSN(extra_long + desc);
}

public string
find_tracks()
{
    string track_desc;
    int skill;

    if ( !strlen(track_dir1) )
	return "You find nothing special.\n";

    skill = TP->query_skill(SS_TRACKING);
    switch(skill)
    {
        case 0..TRACK_LOW : 
            track_desc = "You find nothing special. ";
            break;
        case TRACK_LOW + 1..TRACK_HIGH :
            if(TP->query_prop(FOUND_TRACK))
                track_desc = "You find some orc tracks leading to the "+
                track_dir1 +". "; 
            else
                track_desc = "You find nothing special. ";
            break;
        case TRACK_HIGH + 1..100 :
            if(TP->query_prop(FOUND_TRACK))
                track_desc = "You find some orc tracks leading to the "+
                track_dir1 +". Very faintly can you also see some orc "+
                "tracks leading to the "+ track_dir2 +". It looks as if an "+
                "attempt has been made to cover the tracks leading to the burg. ";
            else
                track_desc = "Very faintly can you see some orc tracks "+
                "leading to the "+ track_dir2 +". It looks as if an "+
                "attempt has been made to cover the tracks. ";
            break;
        default :
            break;
    }
    return BSN(track_desc);
}

public string
down_there()
{
    string desc;
    object *persons, room;

    desc = "You look out through some of the clefts. " + below_desc;

    if ( objectp(room = find_object(below_room)) &&
    sizeof(persons = FILTER_LIVE(all_inventory(room))) )
    {
        desc += "Just below, you see " + 
        COMPOSITE_LIVE(persons) + ".";
    }
    else
    	desc += "There is no one below you.";
    return BSN(desc);
}

public int
call_helmsdeep_guard(object abuser)
{
    object here = TO;

    tell_room(here, "A tall Rohirrim guard arrives.\n");
    tell_room(here, "The tall Rohirrim guard looks around.\n");
    tell_room(here, "The tall Rohirrim guard shakes his head in "+
	"disappointment.\n");
    tell_room(here, "The tall Rohirrim guard says: You shouldn't have sounded "+
	"the horn when there is no danger.\n");
    tell_room(here, "The tall Rohirrim guard takes the horn.\n");
    tell_room(here, "The tall Rohirrim guard leaves.\n");
    present("_helmsdeep_horn", abuser)->remove_object();
    if(abuser->query_prop(FOUND_ORC))
         abuser->remove_prop(FOUND_ORC);
    if(abuser->query_prop(FOUND_TRACK))
         abuser->remove_prop(FOUND_TRACK);
    if(abuser->query_prop(SHOWN_MAP))
         abuser->remove_prop(SHOWN_MAP);
    if(abuser->query_prop(MADE_REPORT))
         abuser->remove_prop(MADE_REPORT);
    HIDE_OUT->brave_orc();
    return 1;
}

