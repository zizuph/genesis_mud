/* cv/grotto.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 * This grotto room connects to /d/Avenir/common/dark/l1/grotto
 * as an alternate exit from the covenhouse.
 * add emotes/actions like splash, dunk, etc.
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";



/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.		
    set_short("crystal grotto");
    set_long("This grotto is a place of serenity and beauty. "
      +"Crystals of all sizes surround a pool of warm water. " 
      +"Steam rises and condenses on the crystals, then forms "
      +"droplets that either rain into the pool, or join "
      +"the rivulets running down nearly every surface. "
      +"A crystal formation that resembles a tree reaches "
      +"toward the ceiling. "
      +"Some of the crystals have fallen and broken over "
      +"time making them useful as seating.\n");

    add_exit("room14", "north");

    add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
      "The stone appears to be a basalt made when magma cooled. It is "
      +"black and glittering with microcrystals.\n");
    add_item(({"crystal", "crystals", "microcrystals"}),
      "The crystals are of every size, from microcrystals sprinkled in "
      +"the basalt to crystals as thick as your thumb sprouting out of "
      +"the walls.\n");
    add_item(({"tree", "crystal tree", "large crystal", "crystal formation"}),
      "It took eons to form a branching crystal of this size. It looks "
      +"a bit like a tree made of glass by a skilled artisan, and it is "
      +"tall enough that you cannot see the top for the shadows up "
      +"above.\n");		
    add_item(({"floor", "ground", "basalt floor"}),
      "The basalt floor is chiseled level and polished to a high gloss "
      +"that accentuates the sparkle of the microcrystals within it.\n");
    add_item(({"ceiling","stalactites", "formations"}),
      "The ceiling of this corridor is draped in darkness that is pierced "
      +"by crystal-encrusted stalactites formed over the eons.\n");
    add_item(({"dark", "darkness"}), "The darkness above is so deep that "
      +"even your eyes cannot penetrate it.\n");			
    add_item(({"agate", "colourful agate", "agates", "grape-like",
	"clusters", "stripes", "minerals"}),	
      "Formed eons ago when heated gases were trapped in these magma "
      +"tunnels and then slowly cooled. They are beautiful, forming "
      +"ribbons, bands, grape-like clusters, and lacy swirls in reds, "
      +"purples, and white.\n");		

    reset_faerun_room();

}


/*
 * Function that allows the player to stand up.
 */
public int
action_stand(string str)
{
    if(str == "up")
    {
	if(this_player()->query_prop("_sitting_outside"))
	{
	    this_player()->catch_msg("You stand up from the block of "
	      +"crystal you were sitting on.\n");            
	    say(QCTNAME(this_player())+" stands up.\n");
	    this_player()->remove_prop("_sitting_outside");
	    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
	    return 1;
	}
	if(this_player()->query_prop("_sitting_inside"))
	{
	    this_player()->catch_msg("You stand up and climb out of "
	      +"the pool of warm water.\n");            
	    say(QCTNAME(this_player())+" gets out of the pool.\n");
	    this_player()->remove_prop("_sitting_inside");
	    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
	    return 1;
	}
    }
    else
    {
	this_player()->catch_msg("Stand? Stand up?\n");
	return 1;
    }
    return 1;
}



/*
 * Function that allows the player to sit by the pool or in it.
 */
public int 
action_sit(string str)
{

    notify_fail(capitalize(query_verb()) + " how? On a crystal block, "
      +"or in the pool?\n");
    if(!strlen(str) || !parse_command(str, ({}), "[on] / [in] [a] / "
	+"[the] 'crystal' / 'pool' [block]"))
	return 0;

    if(parse_command(str, ({}), "[on] [a] / [the] 'crystal' [block]"))
    {
	if(this_player()->query_prop("_sitting_outside"))
	{
	    write("You stand up and move to sit on a different crystal block.\n");
	    return 1;
	}
	if(this_player()->query_prop("_sitting_inside"))
	{
	    write("You leave the pool and move to sit on a crystal block.\n");
	    say(QCTNAME(this_player()) +" gets out of the pool and sits on "
	      +"a crystal block.\n");
	    this_player()->add_prop("_sitting_outside", 1);
	    this_player()->remove_prop("_sitting_inside");
	    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting by the pool");
	    return 1;			
	}
	say(QCTNAME(this_player()) +" sits on a crystal block by the pool.\n");
	write("You sit on a crystal block by the pool.");
	this_player()->add_prop("_sitting_outside", 1);
	this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting by the pool");
    }    

    if(parse_command(str, ({}), "[in] [the] 'pool'"))
    {
	if(this_player()->query_prop("_sitting_outside"))
	{
	    write("You stand up and move to sit in the pool.\nThe water is "
	      +"the same soothing temperature as fevered blood.\n");
	    say(QCTNAME(this_player()) +" slips into the warm pool.\n");
	    this_player()->remove_prop("_sitting_outside", 1);
	    this_player()->add_prop("_sitting_inside");
	    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting in the pool");
	    return 1;
	}
	if(this_player()->query_prop("_sitting_inside"))
	{
	    write("You are already sitting in the pool.\n");
	    return 1;			
	}
	say(QCTNAME(this_player()) +" slips into the warm pool.\n");
	write("You slip into the warm pool and sit down.");
	this_player()->add_prop("_sitting_inside", 1);
	this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting in the pool");
    }    
}


/*
 * Function that allows the player to enter the pool.
 */
public int 
action_enter(string str)
{
    notify_fail(capitalize(query_verb()) + " what, the pool?\n");
    if(!strlen(str) || !parse_command(str, ({}), "[the] 'pool'"))
	return 0;

    if(this_player()->query_prop("_sitting_outside"))
    {
	write("You move to sit in the pool.\nThe water is "
	  +"the same soothing temperature as fevered blood.\n");
	say(QCTNAME(this_player()) +" slips into the warm pool.\n");
	this_player()->remove_prop("_sitting_outside", 1);
	this_player()->add_prop("_sitting_inside");
	this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting in the pool");
	return 1;
    }

    if(this_player()->query_prop("_sitting_inside"))
    {
	write("You are already in the pool.\n");
	return 1;			
    }

    write("You enter the pool.\nThe water is "
      +"the same soothing temperature as fevered blood.\n");
    say(QCTNAME(this_player()) +" slips into the warm pool.\n");
    this_player()->add_prop("_sitting_inside");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting in the pool");
    return 1;

}


/*
 * Function that allows the player to wash in the pool
 * and remove dirt.
 */
public int
action_wash(string str)
{
    object ob;

    notify_fail("Wash how? Wash in the pool, maybe?\n");
    if (!strlen(str) || !parse_command(str, ({}),
	"[me] / [myself] 'in' [the] 'pool' / 'water'"))
	return 0;

    write("You "+ query_verb() +" yourself in the pool.\n");
    say(QCTNAME(this_player())+" washes "+
      this_player()->query_objective() +"self in the pool.\n");

    while(ob = present("dirty", this_player()))
    {
	ob->remove_object();
	this_player()->catch_tell("You feel much less dirty now.\n");
    }
    return 1;
}


/*
 * Function that allows the player to dive into the pool
 * and exit elsewhere.
 */
int
action_dive(string str)
{
    notify_fail("What?\n");
    if (!strlen(str) || !parse_command(str, ({}), 
	"[deep] [down] [into] [the] 'pool' / 'water'"))
	return 0;    

    write("You dive into the pool of water.\n");
    say(QCTNAME(this_player()) + " dives deep down into the water...\n");
    // move to an underwater room that moves them to the L1 grotto.
    this_player()->move_living("M", "/d/Avenir/common/outpost/cv/underwater.c");
    return 1;
}



void
init()
{
    ::init();
    add_action("action_sit",   "sit");
    add_action("action_stand", "stand");
    add_action("action_enter", "enter");
    add_action("action_wash",  "wash");
	add_action("action_dive",  "dive");
}


/*
 * Function to cleanup props if a player leaves the room.
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
	return;

    if (ob->query_prop("_sitting_inside"))
	ob->remove_prop("_sitting_inside");		
    if (ob->query_prop("_sitting_outside"))
	ob->remove_prop("_sitting_outside");		
    if (ob->query_prop(LIVE_S_EXTRA_SHORT))
	ob->remove_prop(LIVE_S_EXTRA_SHORT);        

}

