// file name:        /d/Avenir/common/village/obj/clock_merc.c
// creator(s):       Lilith, March 2004
// revisions: 
// purpose:          Gives time in the center of the market.
// note:             
// bug(s):           
// to-do:

inherit "/d/Avenir/common/obj/clepsydra";
#include <macros.h>
#include <stdproperties.h>

/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string.
 */
public string 
tell_time(void)
{
    return get_time_text();
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
        "The clepsydra indicates that it is currently the "+tell_time()+".\n");
}

public void
create_object(void)
{
    set_name("clepsydra");
    set_pname("clepsydrae");
    add_name(({"clock", "water clock", "fountain"}));
    set_adj(({"water", "copper", "verdigris"}));
    set_short("copper clepsydra");
    set_long("It is a copper clepsydra, or water clock. "+
        "Clepsydrae are devices which use the flow of water "+
        "to measure the passage of time.  Doubling as an "+
        "intricate and appealing fountain, this clepsydra "+
        "is fed by a small spring.  Water flows through a copper pipe "+
        "and empties into a copper basin with three openings "+
        "near the bottom.  The three streams of water arcing "+
        "from the basin then fill numbered copper recepticles, "+
        "each of which indicate Hour, day, and Wei. The copper "+
        "has oxidized over time, so that most of it is that dis"+
        "tinctive verdigris colour.\nThe clepsydra indicates "+
        "that it is currently the @@tell_time@@.\n");

    set_no_show_composite(1);  //don't want it to show up in room desc.

    add_item(({"basin", "copper basin", "openings"}), 
        "It is a broad, oval basin made of copper. There are three "+
        "differently-sized openings near the base, each of which "+
        "projects a crystalline rope of water.\n");
    add_item(({"water", "stream", "streams", "rope"}), 
        "The water is beautifully clear, and it sparkles like "+
        "crystal as it cascades from the basin.\n");
    add_item(({"recepticles", "copper recepticles"}), 
        "Numerous recepticles made of copper, each "+
        "recording a different aspect of the sybarite year.\n");

    add_prop(OBJ_M_NO_GET, "You and what army?\n");    

    /* start the call_out - it also automatically updates the time */
    start_avtime();
}

public int
do_dive(string str)
{
    if (!strlen(str))
        return notify_fail("Dive into what?\n");

    if (!parse_command(str, ({ }), "[into] [the] 'fountain' / 'pool'"))
        return notify_fail("You can't do that.\n");

    // In they go! 
    write("You jump into the fountain.\nThe shockingly cold water "+ 
        "makes you gasp as you come into contact with it.\nYou "+
        "get right back out again.\n");
    say(QCTNAME(this_player()) + " jumps into the fountain, then hurriedly gets "+
        "out again.\n");

    return 1;
}

public int
do_drink(string str)
{
    if (!strlen(str))
        return notify_fail("Drink what?\n");
        
    if (!parse_command(str, ({ }),
	    "[from] [the] 'water' / 'fountain' / 'pool'"))
    {
        notify_fail("You can't do that.\n");
	return 0;
    }

    if (this_player()->drink_soft(200, 1))
    {
	write("You scoop up a handful of water and drink greedily "+
	    "from your cupped palms.\n");
	say(QCTNAME(this_player()) + " scoops up water from the fountain "+
	    "and drinks thirstily.\n");
	this_player()->drink_soft(200, 0);
    }
    else
    {
	write("You scoop up a handful of water, but are too full "+
	    "to drink.\n");
	say(QCTNAME(this_player()) + " runs "+
	    this_player()->query_possessive() +" fingers through "+
	    "the waters of the fountain.\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();

    add_action( do_drink, "drink" );
    add_action(  do_dive, "dive"  );
}
