/* /d/Gondor/tharbad/ford/f04.c */

inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define HARD_TO_SWIM  20 /* how hard is it to swim across the water? */
/* Note that a player with the requisite skill will always manage to swim 
   but with less in that skill he will only succeed if he's lucky. */

#define HARD_TO_CLIMB  5 /* how hard is it to climb the slope? */
/* Note that a player with the requisite skill will always manage to climb 
   but with a lower skill he will only succeed if he's lucky. */

create_room() 
{
 street = "old stone road";
 where = "northwest";
 county = "Tharbad";
 land = "old Gondor";
 mountain = "Greyflood slopes";
 vegetation = "scrubby evergreen creepers and rosebushes";
 extraline = "You are on the northwest bank of a brown turbid"
     + " wide river, perhaps the river Greyflood. To the northwest, the " 
     +vegetation+ " cover the land of " +county+ ". You see an overgrown"
     + " wide stone road made of cracked and slippery paving stones to"
     + " the northwest. A small ruined village lies at the top of the hill."
     + " Southeast the path is blocked by a turbulent brown river, perhaps"
     + " the Greyflood. In the middle of the river is a large island"
     + " covered with half-drowned ruins. The old bridge has long since"
     + " collapsed into ruin.";
    add_exit(THARBAD_DIR+"ford/f03","southeast","@@swim",30);
    add_exit(THARBAD_DIR+"road/r28","northwest","@@climb",6);
    add_item("road",
       "The northwest road is steep but negotiable with a minimum of skill.\n");
    add_item((({"bridge","water","river","Greyflood","River Greyflood"})),
       "The old stone bridge has collapsed leaving a spuming wreck in the river bed.\nSwimming looks possible but very hazardous for all but the most expert.\n");

 make_the_room();
}

reset_room();

query_road()
{
 return 1;
}

/*
 * Function name: swim
 * Description  : This function is run every time someone tries to swim
 * The returning value decides what will happen to the player.
 * 0 means that the player makes it to their destination.
 * 1 means that the player doesn't move, and that no other exits are tried.
 * 2 and more also stops the player, but the player can still move if 
 * there's another exit in the same dir. 2 is a very good value if you want
 * to make an 'enter mansion' direction.
 */

swim()
{   
    int SWIM_TRY;
    SWIM_TRY=random(HARD_TO_SWIM)-2;
    if (this_player()->query_skill(SS_SWIM) < SWIM_TRY)
    {
        write("This water is too difficult for you to swim safely.\n");
	write("You are struggling.\n");
        write("You start to inhale water!\n");
        write("You try to grab a trailing rosebush and lose some blood.\n");
	this_player()->reduce_hit_point(SWIM_TRY-this_player()->query_skill(SS_SWIM));
	write("Your body washes back to near your starting point.\n");
        say(QCTNAME(this_player()) + " fails to make it to the other shore.\n");
        return 1;
    }

    write("You swim across the mighty river Greyflood.\n");
    return 0;
}

climb()
{   
    int CLIMB_TRY;
    CLIMB_TRY=random(HARD_TO_CLIMB)-2;
    if (this_player()->query_skill(SS_CLIMB) < CLIMB_TRY)
    {
        write("This hill is too dangerous for you to climb safely.\n");
	write("You lose your footing.\n");
        write("You fall down in a shower of small rocks and gravel!\n");
	this_player()->reduce_hit_point(CLIMB_TRY-this_player()->query_skill(SS_CLIMB));
	write("Your body tumbles to a stop near your starting point.\n");
        say(QCTNAME(this_player()) + " fails to make it up the slope.\n");
        return 1;
    }

    write("You climb up the stone-choked road.\n");
    return 0;
}

