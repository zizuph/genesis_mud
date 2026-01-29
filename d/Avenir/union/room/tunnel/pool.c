#pragma strict_types
inherit "/std/room";

#include "defs.h"
/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"

public string *cv = HERB_MASTER->query_herbs( ({"cave"}) );


public void
reset_room(void)	{ set_searched(0); }

public void
create_room(void)
{
    set_short("luminous cavern");
    set_long("Refracted light plays all along the walls here, its source "
      + "coming from the very walls of the cavern. The heights of "
      + "the cave are black and shadowy, and the sounds of "
      + "the rippling water play with a hollow echo in the air. The "
      + "east side of the cavern is flat, smoothed stone, as if "
      + "by the passage of many feet over a long time, and ends "
      + "at a sharp edge that leads to the glimmering surface "
      + "of the water. A narrow, square tunnel is downwards to the "
      + "north.\n");

    add_item(({"wall","walls","light","luminescence"}), "The walls of the "
      + "cavern are craggy and rough, with numerous cracks leading "
      + "into some shadowy, unknowable darkness.\nThe walls seem "
      + "aglow with a vague and indistinct light.\n");
    add_item(({"crack","cracks"}), "The cracks in the walls are tiny "
      + "and narrow, fissures that lead into darkness. Lichens, "
      + "fungi, and other plants grow out of them.\n");
    add_item(({"ground","floor"}), "As opposed to the walls, the floor "
      + "here is very smooth, even, and clean.\n");
    add_item(({"water","pool"}), "The water is clear, and small wavelets "
      + "from no discernable source occasionally move along its surface.\n");

    set_up_herbs(({ one_of_list(cv), one_of_list(cv), one_of_list(cv) }),
	({ "walls", "wall", "stone", "crack", "cracks" }), 5);

    add_exit("tunnel1", "north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

public int
drink(string str)
{
    int dr;

    NF("Drink what?\n");
    if (!strlen(str) || !parse_command(str, ({}),
	    "[from] [the] 'water' / 'pool'"))
	return 0;

    dr = TP->query_prop(LIVE_I_MAX_DRINK) / 16;
    if (!dr) dr = 200;

    if (!TP->drink_soft(dr))
    {
	write("The water is too much for you.\n");
	return 1;
    }

    write("You kneel at the edge of the water and drink deeply "+
	"from it.\nThe water is cool and refreshing.\n");
    say(QCTNAME(TP) +" kneels at the edge of the water and drinks "+
	"deeply from it.\n");

    return 1;
}

public int
dive(string str)
{
    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[in] / [into] [the] 'water' / 'pool'"))
	return 0;

    write("You dive into the pool, and immendiatly feel drawn deep "+
	"down into the shadowy darkness.\nThe current pulls you "+
	"through a long, rough-hewn tunnel.\nYou emerge, gasping for "+
	"breath, on the edge of a beautiful, sparkling cavern.\n");

    say(QCTNAME(TP) +" dives into the water.\n");
    TP->move_living("M", ROOM + "astuary", 1, 1);
    say(QCTNAME(TP) +" emerges from the water.\n");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(dive,  "dive");
    add_action(dive,  "enter");
    add_action(drink, "drink");
}
