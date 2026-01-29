/* This is a shrine to Val-Shoreil built by the orcs to honor his
   aid in battle. A powerful spirit of His creation still manifests here
   from time to time. A particularly reverent player may obtain a quest.
   (see documentation on quest...)

   A slighly more explicit history of the cavern can be found in MAP

   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/paths.h"

#define ORC_DIR BLACKWALL_DIR + "orcs/"

inherit BLACKWALL_DIR + "orcs/base_cave";

void
create_cave()
{   
    set_short("A strangely powerful section of an underground cavern");
    set_em_long("There is something odd about this central portion of "+
		"the cavern. It is almost as if you can feel the presence "+
		"of something cold and powerful here. There is a large block "+
		"of carved stone here, surrounded "+
		"by a circle of skulls.\n");

    add_item(({"block", "altar", "large block", "large block of stone",
		 "stone altar", "large altar", "block of stone",
		 "stone block", "carved block", "large carved block",
		 "large carved block of stone"}),
	     "A two metre long by one metre wide by one metre deep "+
	     "block of pure black basalt. A ring of neatly placed skulls "+
	     "encircles it.  It gives the impression of being some "+
	     "sort of altar. Close inspection reveals stains on the top, "+
	     "and down its sides.\n");

    add_item(({"skulls", "ring", "ring of skulls", "row", "row of skulls",
		 "circle of skulls", "circle", "worn skulls",
		 "blackened skulls", "elf skulls", "elven skulls",
		 "elvish skulls"}),
	     "A ring of skulls encircles the carved stone block. The "+
	     "skulls are worn and blackened with age. A number of them are "+
	     "cracked, missing the jaw bone, or otherwise display signs "+
	     "of trauma. Close inspection reveals that the skulls are "+
	     "those of elves.\n");

    add_item(({"stains", "liquid"}),
	     "The stains are barely visible on the black surface of the "+
	     "block though they appear to have been formed by some sort "+
	     "of dark, viscous liquid.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave2", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave7", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave11", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave10", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave9", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave5", "west");
}

/* Returns true if an object has the id lamp, torch or candle. Ideally,
   it will identify all non-magical (and hence extinguishable)
   light sources.
*/
int
is_lamp(object ob)
{
    if (ob->id("torch") || ob->id("lamp") || ob->id("candle"))
    {
	return 1;
    }

    return 0;
}

/* Modified so that all torches/lamps etc. are extinguished upon
   entering the chamber.
                      
   Not presently functional.
*/
void
enter_inv(object ob, object from)
{
    object *lamps; //lamps, torches etc in the inventory of ob
    int i; //loop index

    ::enter_inv(ob, from);
    
    lamps = filter(all_inventory(ob), is_lamp);
    lamps = filter(all_inventory(ob), &->query_lit());

    for (i =  0;  i < sizeof(lamps); i++)
    {
	lamps[i]->extinguish_me();
	write("Abruptly, your " + lamps[i]->short() + " flickers and goes "+
	      "out!\n");
	tell_room(this_object(), "Abruptly, the " + lamps[i]->short() + 
		  " held by "+ QCTNAME(this_player()) +
		  " flickers and goes out!\n", this_player());
    }
}

    
/* This is done to prevent the lighting of torches, lanterns etc.
   in the room. For all intents and purposes, the "light" command is
   locked out. Note that all torches, lanterns etc. are extinguished
   upon entering this room. Hopefully, only magical light, or the
   ability to see in the dark will away someone to view this room.
*/
int
light_fun(string arg)
{
    write("No matter how hard you try, you cannot seem to do that "+
		"here.\n");
    return 1;
}

/* Add_action which allows players to pray while in this room. Specifically,
   an evil player who prays to Val-Shoreil can receive the desecrate_temple
   quest. It would be ill-advised to bring light into this place and then
   try to pray!

   Note: This is not yet fully functional
*/
int
pray_fun(string arg)
{
    string whom; // to whom the player is praying
    object player; //this_player()
    
    player = this_player();

    // correct syntax is "pray to <whom>", anything else and the command fails:
    if (! (strlen(arg)) || ! (sscanf(arg, "to %s", whom) == 1))
    {
	notify_fail("Pray to whom?\n");
	return 0;
    }
 
    write("You kneel reverently before the stone altar and begin to pray to "+
	  whom + ".\n");
    say(QCTNAME(this_player()) + " kneels before the stone altar and begins "+
	"to pray.\n");

    if ((whom == "Val-Shoreil") || (whom == "val-shoreil") ||
	(whom == "val shoreil") || (whom = "Val Shoreil"))
    {
	write("A few moments later a sudden "+
	      "chill permeates the air and the cavern seems to grow even "+
	      "darker than it was before, if that were possible. You "+
	      "feel the presence of some powerful otherwordly being, though "+
	      "you cannot see anything.\n");
	say("A few moments later a sudden "+
	    "chill permeates the air and the cavern seems to grow even "+
	    "darker than it was before, if that were possible. You "+
	    "feel the presence of some powerful otherwordly being, though "+
	    "you cannot see anything.\n");

	if (query_prop(OBJ_I_LIGHT) > 0)
	{
	    /*  the room is somehow lit up, probably by a magical light source
		carried by the praying player, or one of his friends!
		This sort of desecration followed by the audacity to pray 
		will not be tolerated */

	    write("Abruptly, a chilling voice disrupts your prayer:\n" +
		  "'Blasphemy! How dare you approach my master while "+
		  "defiling his temple!'\n");
	    write("A sudden force seizes you, picking you up and sending "+
		  "you hurtling away from the altar. You feel stunned.\n");
	    say("Abruptly, " + QTNAME(player) + " is thrown northwards, "+
		"as if picked up by some unseen force.\n");
	    player->add_mana(- 250);  // mental more than physical pain for the
	                              // offending player
	    player->move_living("M", ORC_DIR + "cave2", 1, 0);
	    player->add_prop("_defiled_shrine_to_vs", 1);
	    // player cannot re-enter this portion of the cavern until he
	    // logs out
	    return 1; // command successful
	}
	    
	// alarmed to give the player time to digest what is going on, and
	// create the fact of passage of time
	set_alarm(5.0, 0.0, &player->
		  catch_tell("Abruptly, a soft yet chilly "+
			     "voice speaks from the "+
			     "surrounding darkness. The "+
			     "sound, though quiet, "+
			     "seems to come at you from "+
			     "all directions at once.\n"+
			     "'So, you wish to serve my master...'\n"));
	set_alarm(10.0, 0.0, &player->
		  catch_tell("'Yes, I think you can be of use.'\n"+
			     "'Go to the temple of Telan-Ri in "+
			     "Telberin and desecrate it. When you have "+
			     "done this, pray to my master "+
			     "and perhaps He will deem your service "+
			     "worthy of a reward.'\n"));
	set_alarm(15.0, 0.0, &player->
		  catch_tell("With that, the chill and darkness "+
			     "receed, though that voice "+
			     "seems to still echo in your mind.\n"));
	set_alarm(15.0, 0.0, &tell_room(this_object(),
					"The chill and darkness seem to "+
					"dissipate.\n", player));
					
	/* quest = clone_object(ORC_DIR + "obj/defile_quest");
	   quest->move(player);
	*/
	return 1; // command successful
	
    }
    
    // Prayed to someone other than Val-Shoreil, or was good aligned
    
    set_alarm(5.0, 0.0, &player->catch_tell("Your prayers go unanswered.\n"));
    return 1;
}
   	      
void
init()
{
    ::init();
    add_action(light_fun, "light");
    add_action(pray_fun, "pray");
    // initiate the clone handler from this room, in future it will
    // be done from entrance rooms, as well
    if (interactive(this_player()))
      catch(call_other(ORC_DIR + "orc_clone_handler", "??"));
}





