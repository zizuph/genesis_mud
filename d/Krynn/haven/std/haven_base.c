/* Street base file for Haven.
 * By Aridor, Feb 98
 *
 * A typical room would look like this:
 * 
 * inherit HAVENBASE;
 * 
 * void
 * create_haven()
 * {
 *     add_my_desc("This is a crossroads in the middle of Haven. Houses line " +
 *                 "the three streets going off in different directions. The " +
 *                 "entrance to a large building is north.\n");
 *     / * Additional long description valid for this specific room * /
 *
 *     add_exit("building","north");
 *     add_exit("street1","south");
 *     add_exit("street2","east");
 *     add_exit("street3","west");
 *
 *     add_item("building","...");
 *     add_item("houses","...");
 * }
 *
 */

/*
 * Modifications:
 * Descriptions updated to Haven-town specific.
 *     Tibbit, 17 Feb 1998
 *
 */


#include "../local.h"

inherit OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban", }) );

public void
reset_haven()
{

}

public void
reset_haven_room()
{
    set_searched(random(2));
    reset_haven();
}

public void
create_haven()
{

}

nomask void
create_haven_room()
{
    /* These generic descriptions should be adjusted and should be valid for
     * ALL outside/street rooms in Haven!
     */
    set_place(TOWN); /* This will set up the correct short and long desc
		      * from haven/std/outside_base.c
		      */
    set_long_desc("You are in the town of Haven, home of the Seekers.");
    /* Additional long description valid for all outside rooms. */

    add_item("sky","It's above you.\n");
    add_item(({"Kharolis", "kharolis", "Kharolis Mountains", "kharolis mountains"}),
	     "The massive range of mountains known as the Kharolis loom to your west, "+
	     "travelling both northwards and southwards far beyond the range of your "+
	     "vision.\n");
    add_item(({"foothills","hills"}),"The foothills are rolling, and seem to "+
	     "melt into the mountains.\n");
    add_item("mountains","The mountains lining Darken Wood lie to your east, "+
	     "forming a barrier around the haunted woods, and the Kharolis mountains "+
	     "loom over you from the west.\n");
    add_item("mountain","Every mountain looks similar to you, and none stand out.\n");
    add_item(({"foothill","hill"}),"The hills are alike in most ways, although " +
	     "they each have their individual differences, of course.\n");

    set_tell_time(400);
    add_tell("One of the citizens of Haven hurries past.\n");
    add_tell("You hear a church bell tolling from not far away.\n");
    add_tell("A robed seeker walks by, nodding politely "+
        "as the townspeople bow and scurry out of his way.\n");
    
    OUTSIDE;
    
    seteuid(getuid(TO));
    set_up_herbs(({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs) }),
		 ({ "scraggly plants", "plant", "plants", }), 3);
    
    create_haven();
    reset_room();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
      start_room_tells();
}

