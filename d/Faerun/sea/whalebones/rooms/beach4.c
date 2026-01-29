/*  /d/Faerun/sea/whalebones/rooms/beach4.c
*
*   By Nucifera, 2020
*
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_WHALEB_OUTDOOR;

//Simulates debris being washed up onto shore when wave action occurs
string
waves() {
  add_object("/d/Faerun/sea/whalebones/obj/debris/bottle");
  add_object("/d/Faerun/sea/whalebones/obj/debris/driftwood");
  return "A large wave crawls gently accoss the shore scraping debris "
      +"accross the sand and leaving it behind as it receeds.";
}

//Function for initial room creation
void
create_whaleb_outdoor()
{
    extraline = "There is a gentle "
        +"crunch underfoot of shells and the remains of various sea life"
        +". Columns of skeletal substance from large seaborne vertebrate "
        +"have scattered themselves along the entire length of coast "
        +"around you.";

    set_short("Somewhere on a narrow bone littered beach");

    add_std_herbs("mere");

    add_item(({"path", "footsteps"}), "There is not a footstep in sight o"
        +"n this sandy wasteland but your own.");

    add_item(({"floor", "ground"}),
        "Your immered to the ankle in sand, pebbles, and other debris dep"
        +"osited by the ebbing water. A You notice weathered bone fragmen"
        +"ts by your feet.\n");

    add_item(({"crunch","sand"}), "Bones and shells produce a distinct cr"
        +"unching sound underfoot.\n");

    add_item(({"shell", "shells"}), "Shells of every shape and color, or "
        +"atleast fragments which look like shells are inundated in the c"
        +"oarse grey-tinged sand.\n");

    add_item(({"sea","water"}),"Flawless turquoise water forming the "
        +"Sea of Swords to your east is broken by choppy white waves as t"
        +"hey aproach the shore at your feet.\n");

    add_item(({"bone", "bones", "substance", "substances", "vertebrate"}),
        "You identify them as the weathered bone structures of massive se"
        +"aborne mammals.\n");

    add_item(({"driftwood"}),"A collection of the remains from shaped pie"
        +"ces of timber and bazaarly knotted remains of organic debris ar"
        +"e haphazardly scattered between the bones and shells.\n");

    add_item(({"debris","reffuse","flotsam"}), "Reffuse and flotsam dragg"
        +"ed in my the foaming water litter the beach.\n");

    add_item(({"pebbles"}), "Pebbles and assorted rocks broken away from "
        +"the cliff to your west produce the course sand beneath you.\n");

    add_item(({"fragment", "fragments"}), "Fragments of bones, shells and"
        +"other various reffuse litter the shore.\n");

    add_item(({"cliff","cliffs"}), "The sheer vertical mass of rock besid"
        +"e you has been weathered away over time to an almost completely"
        +" smooth wall.\n");

    add_item(({"shore", "beach"}), "You are standing on the southeastern"
        +"shore of Finback Island, and the Sea of Swords is to your"
        +" east.\n");

    add_item(({"wave", "waves"}), "Briney white foaming waves ebb and flo"
        +"w, hauling debris further inland.\n");

//Events that occur while player is within room to add some flavour
    add_room_tell("The stomach-churning aroma of rotting sea life drifts "
        +"past you. ");

    add_room_tell("Salty sea spray from a large wave hit's you square in "
        +"the face. Ouch!");

    add_room_tell("The soothing melody of lapping waves fills you with a "
        +"sense of calm.");

    add_room_tell(waves());

//Messages player recieves when trying to uses a non-exit to provide a
//more immersive expirience.
    set_no_exit_msg( ({"north", "northwest", "west"}), "There is a cl"
        +"iff in the way. You decided it is too risky to climb a horizont"
        +"al face of rock.\n");

    set_no_exit_msg( ({"east"}), "You consider moving east, but "
        +"noticing the crumbling rockface above, decide against it.\n");

    set_no_exit_msg( ({"southeast", "south", "southwest"}), "B"
        +"reaking waves deter you from moving in that direction.\n");

    add_exit(ROOM_DIR + "beach3.c", "northeast");

//Adding in NPC
    add_npc("/d/Faerun/sea/whalebones/npcs/crab", random(6)-2);

//Adding in objects (debris)
    add_object("/d/Faerun/sea/whalebones/obj/debris/bottle", random(4)-2);
    add_object("/d/Faerun/sea/whalebones/obj/debris/driftwood", random(4)-2);

//Resetting herbs
    reset_faerun_room();
}

//Function to reset herbs in room once room has been reset
void
reset_faerun_room()
{
    set_searched(0);
}
