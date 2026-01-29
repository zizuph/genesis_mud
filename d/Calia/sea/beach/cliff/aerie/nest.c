/*
 *  coder: Tigerlily
 *  date:  2001-12-27
 *  notes: 
 *
 */

#pragma strict_types
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

#include "defs.h"


object chick;
object poop;

void
reset_room()
{

    //reset chick and quest, clean-up if chick is gone
    if (!objectp(chick))
    {
	chick = clone_object(SEA_CREATURES + "osprey_chick");
	chick->move(this_object(), 1);
	tell_room(this_object(), "Suddenly one of"+
	  " the large pink-speckled eggs pops open!\n", ({}),);
	chick->command("emote hops in.");
    }

    // if chick is still in nest, reset just the chick
    if (objectp(chick))
	chick->reset_quest();
    return;
}


void
create_room()
{
    set_short("Inside an osprey's nest");
    set_long("The walls and floor are constructed from branches,"+
      " twigs, and leaves interwoven like the inside of a basket."+
      " You are up to your ankles in a heap of soft downy feathers."+
      " Nestled in among the feathers, you notice several large eggs."+
      " It is quite cosy and warm, belying the harshness of the"+
      " elements outside. Overhead you see a scraggly branch of"+
      " a tree that appears to be growing out from the"+
      " cliff wall above. You see bits and pieces of leftovers"+
      " from osprey meals lying around.\n");

    add_item(({"excrement", "bird doo", "bird poop", "guano",
	"poop", "bird excrement"}),
      "The bird doo forms a hard plaster-like substance"+
      " on the floor and walls of the nest.\n");
    add_item(({"walls", "floor"}), "The walls and floor of the"+
      " nest are woven together with branches, twigs and leaves of"+
      " some green plant that looks like seaweed. There is a thick"+
      " plaster-like substance covering the walls and exposed areas"+
      " of the floor of the nest.\n");
    add_item(({"cliff wall", "cliff", "tree"}),
      "The granite cliff wall rises up behind the nest"+
      " overhead. You would not expect a tree to be able"+
      " to grow in this environment, yet there is a small"+
      " scraggly tree that ekes out a living on the cliff"+
      " wall overhanging the nest to the west.\n");
    add_item(({"branch", "scraggly branch"}),
      "The branch extends over the edge of the nest"+
      " to the west.\n");
    add_item(({"bits", "pieces", "leftovers"}),
      "There are remnants of osprey meals which normally"+
      " include fishes of various types as well as"+
      " an occasional frog or other sea creature. There"+
      " is a well picked over skeleton of what must have been"+
      " a huge fish lying on the floor of the nest.\n");
    add_item("skeleton", "The fish must have been at least"+
      " a meter long, judging from the skeletal remains. Part of the"+
      " head with eerie dead eyes and the tail are still"+
      " attached.\n");

    add_item(({"feathers", "downy feathers"}), "A thick layer of"+
      " soft feathers makes a thick cushion in the bottom of"+
      " the nest. There are several pink-speckled osprey"+
      " eggs nestled gently in the cushion of feathers.\n");

    add_item(({"eggs", "osprey eggs"}), "You see that there"+
      " are several large pink-speckled osprey eggs partially covered"+
      " in feathers.\n");
    add_item(({"substance", "plaster-like substance"}),
      "Upon closer inspection, you realize that the substance"+
      " is bird guano or excrement.\n");
    add_item("nest", "You are standing in a large"+
      " bird's nest. The walls and floor are constructed"+
      " from interwoven branches and twigs, and the"+
      " floor is covered with fluffy feathers and"+
      " down, making it quite comfortable. You"+
      " notice however that bird excrement is"+
      " all around and forms a hard plaster-like"+
      " substance.\n");



    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);
    add_exit(AERIE + "aerie1", "out");
    reset_room();

}

void
hook_smelled(string str)
{
    write("There is a rather unpleasant odour emanating"+
      " from the left-overs of dead fish and bird guano.\n");
    return;

}
