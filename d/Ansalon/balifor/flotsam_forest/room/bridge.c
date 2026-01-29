/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On a wooden bridge over a merrily running river");
    set_long("@@long_descr");

    add_item(({"forest","evergreen forest","ancient forest",
	"great oaks","oaks","ancient oaks","thick underbrush","underbrush",
	"shadows","trees"}),
      "The river here divides the ancient evergreen forest only " +
      "barely in two, with the canopies of the ancient oaks " +
      "entangling like estranged lovers.\n");
    add_item(({"river","merrily running river"}),
      "Beneath the bridge a river runs merrily away " +
      "into the forest to your south.\n");
    add_item(({"bridge","wooden bridge"}),
      "You stand on a wooden bridge that spans over " +
      "a merrily flowing river. You notice a small trail " +
      "down on the eastern side of the bank.\n");
    add_item(({"small trail","trail"}),
      "A small trail follows the eastern bank. You " +
      "could probably climb down to it from here.\n");

    add_cmd_item(({"down","down bridge","down to trail"}),
      "climb","@@climb_down");

/*    add_exit(FROOM + "nowhere","east","@@no_go"); */
    add_exit(FROOM + "road13","west",0);
    add_exit("/d/Ansalon/goodlund/kendermore/room/trail5", "east", 0);

    add_prop(LIVE_I_CAN_FISH, "freshwater");

    set_tell_time(120);
    add_tell("The river babbles noisily as it flows under " +
      "the bridge.\n");
    add_tell("The ancient oaks beside the river groan " +
      "as a strong wind blows " +
      "through them.\n");

    reset_flotsam_room();
}

int
climb_down()
{
    write("You climb down the side of the bridge to the trail.\n");
    say(QCTNAME(TP)+ " climbs down the side of the bridge to " +
      "the eastern bank of the river.\n");
    TP->move_living("M",FROOM + "traila",1,0);
    tell_room(FROOM + "traila",QCTNAME(TP) + " arrives climbing down " +
      "the bridge.\n", TP);
    return 1;
}

int
no_go()
{
    int random_message = random(4);

    if(random_message == 0)
	write("You start heading east, but then out of the " +
	  "corner of your eye you think you see a naked " +
	  "water nymph playing in the river. You stop to " +
	  "gawk but it is gone.\n");
    if(random_message == 1)
	write("You start heading east, when a small " +
	  "rainbow trout jumps out of the river and lands " +
	  "helplessly on the bridge. You stop, and mercifully " +
	  "throw it back in.\n");
    if(random_message == 2)
	write("You hear a distinct dwarven voice yelling " +
	  "'Hey! You little thief! Come back with my axe!' " +
	  "coming from the east, and you decide it would be wise not " +
	  "to head down there just yet.\n");
    if(random_message == 3)
	write("The trees to the east close rank in " +
	  "front of you, stopping your passage into the " +
	  "lands of kendermore.\n");
    return 1;
}

string
long_descr()
{
    return "You stand in the middle of a wooden bridge " +
    "that spans over a merrily running river that flows " +
    "noisily to the south through an ancient evergreen forest." +
    tod_descr2()+
    "\n";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}
