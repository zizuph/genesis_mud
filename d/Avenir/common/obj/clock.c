/* A simple clock that shows the Hour only. For a more sophisticated
 * one, use the clepsydra.
 */

inherit "/d/Avenir/inherit/avenir_time";
inherit "/std/object";

#include <language.h>
#include <stdproperties.h>

/*
 *  This gets the hour from the avenir_time object 
 *  and returns it as a string.
 */
string 
tell_time()
{
    int hour;
    hour = get_avenir_hour();
    return "the "+ capitalize(LANG_WORD(hour)) +" Hour";
}

/*
 * We are masking this function from the avenir_time.c
 * It notifies us of the change of hours once every hour.
 */
public void
avenir_time_callout(int av_year,int av_week_of_year,int av_dow,int av_hour)
{
   /* this will tell the time every hour */  
   tell_object(environment(this_object()),
        "The "+ short() +" indicates that it is approximately "+tell_time()+".\n");
}

void
create_object()
{
    set_name("clepsydra");
    set_pname("clepsydrae");
    add_name(({"clock", "water clock"}));
    set_adj(({"simple"}));
    set_short("simple water clock");
    set_long("This is a simple water clock, one that indicates "+
        "the Hour.  It is not as accurate as its more elaborate "+
        "counterparts, but is is easily maintained and corrected.\n"+
        "It consists of two vessels suspended from a metal rod, each "+
        "one having identical markings and a plugable hole at the "+
        "bottom.  "+
        "One of the vessels is raised higher than the other, and "+
        "from it, water pours into the other.  The water level in "+
        "the lowermost vessel corresponds with the markings for "+
        "the Hours of each day. When the lower one is filled and "+
        "the upper one emptied, twelve hours have passed.  Then the "+
        "hole in the empty vessel is plugged, the plug in the full "+
        "vessel is removed, and the metal rod is then tilted the "+
        "other way, so that water may flow back from one to the "+
        "other.\n   The "+ short() +" indicates that it is approx"+
        "imately @@tell_time@@.\n");

    add_item(({"vessel", "vessels"}),
        "There are two identical vessels.\n");
    add_item(({"water", "stream", "streams", "rope"}), 
        "The water is beautifully clear, and it sparkles like "+
        "crystals as it cascades from the vessel.\n");

    add_prop(OBJ_M_NO_GET, "Its too heavy!\n");    
        /* start the call_out - it also automatically updates the time */
        start_avtime();
}

