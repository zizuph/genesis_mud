/* Basic room, ready-made for modification, Azireon. */
/* Modified by Azireon, September 11, 1992, concert_hall.c */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <tasks.h>

#define NF(message)    notify_fail(message)
#define TP		this_player()
#define SG_TUNE_REPAIR  130053
object soprano;
int x;

reset_room(arg)
{
    if (x == 1)
    {
        soprano->remove_object();
        x = 0;
    }
    else
    return 1;
}
    
lunatic()
{
    seteuid(getuid());  /* Won't clone in VBFC otherwise... */

    write("You draw aside the blankets on the harpsichord.\n");
    say(break_string(QCNAME(this_player()) +
		     " draws aside the blankets on the harpsichord.\n", 70) );


    /* She should only come out if she is not already in the room;
     * however, if she has been killed, she should not come out
     * again until th room resets.
     */
    if (x == 0) {
	write("A strange woman comes bounding out from underneath it.\n");
	say("A strange woman comes bounding out from underneath it.\n");
	soprano=clone_object(MANSION + "second/soprano");
	soprano->move(this_object());
	x = 1;
	return 1;
    }
    else
	return 1;
}



create_room()
{
    set_short("Concert Hall Stage");
    set_long("The size of this chamber is incredible.  Its floor is " +
	     "contoured in such a way that it slopes into the center " +
	     "where the large ovalur marble stage that you stand on " +
	     "has been raised.  Water " +
	     "seeps and drips from the ceiling and walls and a pool has " +
	     "formed around the stage.  The smell of mildew is unbearable." +
	     "  A large box or case stands on three legs in the center " +
	     "of the stage;  several dirty blankets have been draped " +
	     "over it.  There is a vast circular opening in the vaulted " +
	     "ceiling.\n");

    add_item( ({ "opening", "ceiling" }),
	     "Far above, you can make out strange bas-relief work that " +
	     "covers the ceiling with a maze of images.  From here you " +
	     "can gaze far up into a massive gilded dome that leaves " +
	     "you with a dizzying sense of space.  There are frescoes " +
	     "but, from this distance, they are impossible to see " +
	     "clearly.  You think you can make out a human figure " +
	     "standing at a railing but you cannot be sure.\n");

    add_item( ({ "water", "pool" }),
	     "The pool is quite rancid;  the water and humidity have " +
	     "rotted anything of value in the chamber.\n");

    add_item( ({ "box", "case" }),
	     "Upon closer examination, you realize that this is what " +
	     "used to be a small harpsichord.  It has been covered " +
	     "with filthy wool blankets that drape down, creating a " +
	     "small shelter beneath the instrument.  A revolting smell " +
	     "and a deranged whispering sound emanate from within.\n");

    add_cmd_item( "harpsichord", "play", "@@play" );
    add_cmd_item( ({ "blanket", "blankets" }),
		 ({ "move", "open" }),
		 ({ "@@lunatic", "@@lunatic" }) );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room. */
    add_prop(ROOM_HAS_WATER, 1);  /* For Dust's quest! */
    add_prop("_untuned",1);

    add_exit(MANSION + "second/concert_hall", "south", 0);

    reset_room();
}

/*  Modified to fit quest by Geraden 940922  */
play()
{
    if (query_prop("_tuned")) {
	 write("You touch the rotting keys and are surprised " +
	       "by the beauty of the music that issues forth from " +
	       "such an old and broken down insturment.\n");
	 say(QCNAME(TP) +" plays the harpsichord beautifully.\n");
	 return 1;
     }
     if (query_prop("_untuned")) {
	 write("Touching the rotted keys, you try to play the harpsichord " +
	       "It makes an awful sound.  It is obviously in desparate " +
	       "need of being tuned.\n");
	 say(QCNAME(TP) + " makes an awful sound on the harpsichord.  " + 
	     "You wish "+ TP->query_pronoun() +" would stop.\n");
	 return 1;
     }
}


/* Minstrel quest to tune harpsicord.  Geraden 940922 */
init ()
{	
    ::init();
    add_action("do_tune", "tune");

}

int
do_tune(string what)
{
    object harpsichord, this_room, *obs;
    object fork, ob, twrench;
    string verb, s1;

    write("We have entered the do_tune function =) \n");
    verb = query_verb();

    if(!what) {
	NF(capitalize(verb) + " what?\n");	
	return 0;
    }

    if(what == "harpsichord") {
	NF("With what?\n");	
	return 0;
    }

    if(sscanf(what, "harpsichord with %s", s1) != 1) {
	NF(capitalize(verb) + "what?\n");	
	return 0;
    }
    
    if (!strlen(s1) || (s1 != "wrench") || (!present("wrench", TP))) {
	NF("You better get a tuning wrench.\n");
	return 0;
    }
	
    if (query_prop("_tuned")) {
	write("It has already been tuned.\n");
	return 1;
    }

    if (TP->query_skill(SG_TUNE_REPAIR) == 0) {
	NF("Only someone who has skill in tune/repair instrument " +
	   "would have a chance to accomplish this.\n");
	return 0;
    }
    
    if(TP->resolve_task(TASK_ROUTINE, ({SG_TUNE_REPAIR})) >0) {
	write("You tighten the strings on the harpsichord, sucessfully " + 
	      "bringing the harpsichord back into perfect pitch.\n");
	remove_prop("_untuned");
	add_prop ("_tuned",1);

	say(QCTNAME(TP)+ "tightens the string of the harpsichord, tuning "+
	    "it successfully.\n");

	if (TP->test_bit("Terel", QUEST_GG1_GROUP, QUEST_GG1_BIT)) {
	    TP->catch_msg("You have done this before, don't you remember?\n");
	}
	else {
	        if (TP->query_exp() < QUEST_GG1_EXP) {
		    TP->add_exp(TP->query_exp());
		}
		else TP->add_exp(QUEST_GG1_EXP);
		TP->set_bit(QUEST_GG1_GROUP, QUEST_GG1_BIT);
		TP->catch_msg("You feel a little more experienced.\n");
		write_file(QUEST_LOG, TP->query_name()+
			   " solved the harpsichord quest (" +
			   ctime(time()) + ")\n");
	    }
    }
    else {
	write("You try to tune the harpsichord but find your skills " +
	      "unequal to the task.  Perhaps you should visit the training " +
	      "hall in the minstrel guild.\n");
	return 1;
    }
    

    return 1;
}
