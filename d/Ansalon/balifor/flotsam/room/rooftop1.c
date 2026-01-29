#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_OUT;
#define HARD_TO_JUMP 20

void
reset_flotsam_room()
{
    return;
}


create_flotsam_room()
{
    set_short("On a rooftop in the town of Flotsam");
    set_long("@@long_descr");

    add_item(({"tiles","tile","roof","tiled roof","rooftop","roof top"}),
      "Muddy-brown coloured tiles make up the roof of this " +
      "one-story old house. \n");
    add_item(({"street","south"}),"To the south you cannot " +
      "see the street as the angle of the roof blocks your view " +
      "of it.\n");
    add_item(({"alley","dark alley"}),"Between the houses " +
      "meanders an alley. Darkness so black that it is almost " +
      "tangible fills it like a river, hiding everything in it " +
      "with shadows. \n");
    add_item(({"shuttered window","window"}),"About twelve " +
      "feet across the alley and directly across from you to " +
      "the north is a shuttered window, most likely to an upper " +
      "room of the local Inn. A wide ledge sits underneath it.\n");
    add_item(({"ledge","wide ledge"}),"The stone ledge sits " +
      "underneath the window. It is probably wide enough to stand " +
      "on... maybe.\n");
    add_item("deserted house","To your east rises the wall of a " +
      "large manor house. It may have been once owned by a wealthy " +
      "merchant, but now it is rundown and deserted.\n");
    add_item("wall","The wall to the east rises up to the roof " +
      "of the large manor.\n");
    add_item(({"rusty drainpipe","drainpipe"}),"This rusty " +
      "drainpipe runs down of the roof and into the darkness " +
      "of the alley below.\n");
    add_item("house","Not surprisingly you see many houses from " +
      "up here on the rooftops. \n");
    add_item(({"inn","local inn"}),"Across the alley is the side " +
      "of the local Inn. Apart from a window on the side of its " +
      "second story, there is nothing interesting about it.\n");

    add_cmd_item(({"down","drainpipe","pipe","down drainpipe"}),
      ({"climb","down"}),
      "@@climb_down");
    add_cmd_item(({"to window","to ledge","to the window",
	"to the ledge","over alley","across alley"}),
      ({"jump","leap"}),"@@jump_to_ledge");
    add_cmd_item(({"east wall","wall"}),"climb","@@climb_wall");

    add_prop(ROOM_I_NO_ALLOW_STEED,1);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand on the " +
    "tiled roof of an old house. The street to your south is hidden " +
    "from view due to the angle of the roof. Below you to the west " +
    "and north is a dark alley. Directly across the alley " +
    "to your north on the second story of the local Inn " +
    "you notice a shuttered window. To your east rises " +
    "the wall of a large deserted house. A rusty drainpipe " +
    "runs down from the roof into the darkness of the alley " +
    "below. " + season_descr() + "\n";
}

string
climb_down()
{
    write("You climb down the rusty drainpipe and into the alley.\n");
    TP->move_living("down the drainpipe",FROOM + "street30",1,0);

    return "";

}

string
jump_to_ledge()
{
    if(this_player()->query_skill(SS_ACROBAT) < HARD_TO_JUMP)
    {
	write("You leap forward off the roof! You clear the distance, but land badly " +
	  "on the ledge... you plummet into the alley below!!!\n");
	say(QCTNAME(this_player()) + " leaps off the roof " +
	  "towards the window across the alley. \n" +
	  "You see " + OBJECTIVE(TP) + " land badly on the " +
	  "windows ledge, and then " +
	  "fall backwards into the alley! \n");
	TP->heal_hp(-400);
	tell_room(FROOM + "street30",QCTNAME(TP)+ " falls from a " +
	  "building above and lands awkwardly right in front " +
	  "of you!\n");
	TP->move_living("down into the alley",FROOM 
	  + "street30",1,0);

	return "";
    }
    write("You leap forward off the roof! \n " +
      "You make the distance easily, and land with catlike grace " +
      "on the windows wide ledge. Guess those acrobatic lessons " +
      "paid off eh?\n");
    say(QCTNAME(this_player()) + " leaps forward off the roof! \n" +
      "Clearing the twelve foot distance with ease and landing with " +
      "catlike grace on the windows wide ledge, you are most " +
      "impressed!\n");
    tell_room(FROOM + "street30","Out of the corner of your eye you notice a " +
      "shadowy figure leap over the alley above you.\n");
    TP->move_living("across the alley and onto the windows ledge",
      FROOM + "ledge",1,0);

    return "";
}

string
climb_wall()
{
    if(TP->query_skill(SS_CLIMB) < 30)
    {
	write("Nah, you don't feel confident climbing to " +
	  "such great heights! \n");
	return "";
    }
    write("You scale the wall of the deserted manor house.\n");
    say(QCTNAME(TP) + " starts climbing the eastern wall.\n");
    TP->move_living("up the wall",FROOM + "rooftop2",1,0);

    return "";
}
