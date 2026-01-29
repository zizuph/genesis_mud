/* Flotsam sidestreet by Gorr 8.12.96 */

#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <macros.h>

inherit FLOTSAM_OUT;

create_flotsam_room()
{
    set_short("Side street in the town of Flotsam");
    set_long("@@long_descr");

    add_item(({"side street","street","sidestreet"}),
      "A narrow side street, leading in south-north direction. \n");
    add_item(({"house","houses","buildings","deserted houses"}),
      "Tall, stone houses look lifeless and deserted. \n");
    add_item(({"windows","window","dark windows"}),
      "No sign of life could be seen in these dark windows. \n");
    add_item("wall","The brickwall is blocking the street to the south. " +
      "It is covered with dirt and moss but it still looks solid. \n");
    add_item(({"moss","dirt"}),"The wall is covered with slimmy moss. " +
      "It could hinder your movement but the wall still looks climbable. \n");
    add_item("bricks","The bricks are hardly visible from under the moss. \n");

    add_cmd_item(({"wall","brickwall"}),({"climb","up"}),"@@climbwall");

    add_exit(FROOM + "gstreet2","north",0);

    set_tell_time(90);
    add_tell("A black cat runs through the street, chasing nearly the " +
        "same size rat.\n");
    add_tell("You hear a woman cry from one of the houses. Unfortunately " +
        "you can't say from which one. \n");
    add_tell("You are nearly sure you saw someones shadow just behind " +
        "your back. \n");
    add_tell("You step in a pool of dirty water, splashing the stinking " +
        "fluid all around. \n");
    add_tell("Something moves in one of the windows. Or maybe it is just " +
        "your imagination. \n");

}

string
long_descr()
{
    return tod_descr1() + "You are standing on a small " +
    "side street in the wretched town of Flotsam. The overwhelming stink of " +
    "rotten food is hard to stand. All the houses around look deserted, with " +
    "dark windows like the eyes of some evil beast. " +
    "This street leads north, while not far to the south " +
    "it ends suddenly with some kind of wall. "
    + season_descr() + "\n";

}

string
climbwall()
{
    if(TP->query_skill(SS_CLIMB) < 20 + random(20))
    {
	write("You try to climb the wall but your foot slips on the moss " +
	  "and you land hard on the ground.\n");
	say(QCTNAME(TP) + " tries to climb the wall but slips on the moss " +
	  "and lands hard next to your feet.\n");
	return "";
    }
    write("You successfully climb the brickwall and jump on the other side. \n");
    TP->move_living("up the brickwall",FROOM + "gstreet4",1,0);

    return "";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
