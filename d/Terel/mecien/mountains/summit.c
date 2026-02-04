/*
   sc_room.c 
   a room to show how one can use the swim and climb skill
*/

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>

#define HARD_TO_CLIMB 40 /* how hard is it to climb the tree ? */
#define DAMAGE        10 /* What's the damage if you don't succeed? */
/* Note that a player with the skill 40 will always manage to swim or climb
   but with lower in that skill he will only succees if he's lucky. */

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room()
{
   set_short("Mountain Summit");
    set_long("This is the top of the one of the greatest mountains\n" +
	     "in this chain. There is little wind here. A small icy\n" +
  "peak rises just a little higher. A strange ice bridge juts\n" +
  "out of the summit westward into the mountain mists.\n");
    add_exit("/d/Terel/mecien/mountains/peak", "up", "@@climb");
    add_exit("/d/Terel/mecien/mountains/ice8", "down", 0);
   add_exit("/d/Terel/mecien/mountains/ibr1", "west", "@@bridge_check");
    add_item("peek", 
	     "The peak of the mountain is a little higher, but it\n" +
	     "looks a little high.\n");
   add_item(({"bridge", "ice bridge"}), "It looks very fragile.\n");
}

/*
 * Function name: climb and swim
 * Description  : This function is run every time someone tries to move up
 *                or as we think of it, tries to climb the tree.
 * The returning value decides what will happen to the player.
 * 0 means that the player isn't delayed.
 * 1 means that the player don't move, and that no other exits are tried.
 * 2 and more also stops the player, but the player can still move if 
 * there's another exit in the same dir. 2 is a very good value if you want
 * to make an 'enter mansion' direction.
 */

climb() 
{
    if (this_player()->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
    {
	write("You try to climb up but fall back.\n");
        write("You get hurt.\n");
	this_player()->reduce_hit_point(DAMAGE);
	say(QCTNAME(this_player()) + " falls from the side of the peak.\n");
	return 1;
    }

    write("You climb up to the peak.\n");
    return 0;
}

public int
bridge_check()
{
    write("Hmm. You better reconsider this. The ice bridge looks too fragile.\n");
    say(QCTNAME(this_player()) + " hesitates to walk out on the ice bridge.\n");
    return 1;
}
