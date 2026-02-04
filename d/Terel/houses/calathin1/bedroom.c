/*
 * calathin1/bedroom.c
 *
 * Lilith, March 2022
 *
 * Revisions: New owner reported incorrect message when jumping the railing.
 *     I fixed it -- I hav move_living set to X instead of M.
 *
 */

#pragma strict_types

#include "h1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit H1 +"housebase";
inherit "/lib/commands";
inherit "/d/Avenir/inherit/emotes";

#define SEE_DOWN	({ H1 + "living" })

public string
down_view(void)
{
    object *live = get_view(SEE_DOWN);

    if (!sizeof(live))
	return "A tidy livingroom with two couches is below";
    if (sizeof(live) == 1)
	return COMPOSITE_LIVE(live) + " is in the living room below";  
    else
	return COMPOSITE_LIVE(live) + " are in the living room "+
        "below";
}
int do_sleep(string str);
int do_jump(string str);

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    room_add_object(HOBJ + "wardrobe1");
    room_add_object(HOBJ + "bed1");

    add_exit("kitchen", "down");
 
    set_short("loft bedroom");
    set_long("The loft of the townhouse is being used as a bedroom. "+
      "The walls angle sharply down to the floor on each side of the "+
      "room. A chimney forms part of the east wall, radiating warmth. "+ 	  
      "Some fur pelts have been scattered on the pine floor alongside "+
      "the four-poster bed which dominates the space. It has been " +
      "placed near a wooden railing that overlooks the living room. " +
      "In the northwest corner is a tall wardrobe where "+
      "the homeowner may put things for safekeeping. " +
      "To the south, two big windows have views of the river and "+
      "forest beyond it. A set of stairs leads down to the kitchen.\n");
	  

    set_items_bedroom();
    set_items_stone();

    add_help_topic("here",  HELP +"bed_help");
    add_help_topic("room",  HELP +"bed_help");
    add_help_topic("bedroom", HELP +"bed_help");
	

    add_item(({"fur", "furs", "pelts", "pelt", "fur pelts"}),
      "Scattered on the floor along side the bed are numerous "+
      "fur pelts that must feel marvellous under bare feet.\n");
    add_item(({"living room", "down", "below" }), 
	"@@down_view@@.\n");
}



/*
 * Function name: init
 * Description  : initialize couch & time
 */

public void
init()
{   
    ::init();
    add_action("do_sleep","sleep");
    add_action("do_sleep","nap");
    add_action("do_start","start");
	add_action("do_jump", "jump");
}

/*
 * Function name:        do_sleep
 * Description  :        Provides an emote to sleep in the bed
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_sleep(string str)
{
    if(!str)
    {
	notify_fail("What are you trying to sleep on? The bed?\n");
	return 0;
    }

    if (!parse_command(str, ({}),
	"[on] / [in] [the] [big] [luxurious] 'bed'", str))
    { 
	write("What are you trying to sleep on? The bed?\n");
	return 1;
    }
    write("You climb into the big, luxurious bed and discover " +
      "that it is even more comfortable than it looks! " +
      "Closing your eyes, you enjoy a nice little nap.\n");
    say(QCTNAME(TP) +" takes a short nap on the wide luxurious bed.\n");
    return 1;
}


int
do_jump(string str)
{

    if (!strlen(str))
	return 0;

    /* over the railing */
    if (!parse_command(str, ({}), "[over] [the] 'rail' / 'railing'", str))
    {
	notify_fail(capitalize(query_verb()) +" over what?\n");
	return 0;
    }


    write("You "+ query_verb() +" over the railing and fall toward "+
      "the living room below.\n");
    say(QCTNAME(this_player()) + " "+ query_verb() +"s over the "+
      "railing.\n");	
    this_player()->move_living("M", H1 +"living", 1, 0);
    return 1;		



}


public int
query_prevent_snoop(void)       { return 1; }
