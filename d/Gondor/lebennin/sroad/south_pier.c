/*
 * /d/Gondor/lebennin/sroad/south_pier.c  (eventually)
 *
 * The ship to Poros & Lebennim lands here
 *    5/11/99 - Generally reformatted and added swim across river by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 */


#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define HARD_TO_SWIM  25 /* how hard is it to swim across the water? */
#define HARD_TO_CLIMB  7 /* how hard is it to climb the slope? */
#define SWIM_FATIGUE  30 /* how tiring is it to swim? */

inherit "/d/Genesis/gsl_ships/lib/pier";

public void	init();
public int	cross_river(string arg);


static void
add_stuff()
{
   object  sign;

   if (!present("sign", TO))
   {
      sign = clone_object(SHIP_DIR + "poros_sign");
      sign->set_file(SHIP_DIR + "poros_lebennin.txt");
      sign->move(TO);
   }
}


/*
 * Function name:    create_gondor
 * Description:      create the room
 */
public void
create_roads() 
{

    set_street("pier on the bank of the Anduin");
    set_where("southern");
    set_county("Lebennin");
    set_land("Gondor");

    set_extraline("The run-down pier is reaching into the Anduin. "
      + "Perhaps it is used by fishermen who do not want to use "
      + "the great harbour in Pelargir.");
   
    add_exit(LEB_DIR + "sroad/sr2", "north", 0, 2);

   
    add_item( ({ "pier", "dock" }) , BSN(
        "This pier reachs out into the river Anduin. It is in a rather "
      + "poor condition but it looks like a ship docked here not too "
      + "long ago."));


    add_item( ({ "river", "anduin", "river anduin", "anduin river" }), BSN(
        "The river isn't very broad here, it might even be possible "+
        "to swim to the other bank. Not far to the southwest are the "+
        "Mouths of the Anduin, the many smaller branches into which "+
        "the river divides before reaching the Bay of Belfalas."));

    add_item( ({ "road", }), BSN(
        "The road north of here is coming from Pelargir to the "
      + "northwest and continues southwest along the bank of the Anduin."));

    //add_stuff();

    add_cmd_item( ({ "river", "anduin", "water", "across river", }), 
        ({ "swim", "cross", }), cross_river);
   add_pier_entry(MASTER_OB(TO), "Pelargir beach", "Line to Tharbad and Poros");
   initialize_pier();

}   /*  end create_gondor()  */

/*
 * Function name:	init
 * Description	:	add the river verbs
 */
public void
init()
{
    ::init();

    add_action(cross_river, "swim");
    add_action(cross_river, "dive");
    add_action(cross_river, "cross");
} /* init */


/*
 * Function name:	cross_river
 * Description	:	handle attempts to cross the river
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 if we understand the arg, 0 if not
 */
public int
cross_river(string arg)
{
    string	junk;
    int		tired = SWIM_FATIGUE;


    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({}),
	    "[into] [over] [in] [across] [the] " +
	    "'river' / 'anduin' %s", junk))
    {
	NF0(CAP(QVB) + " where?\n");
    }

    if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
    {
        SAYBB(" leaves swimming across the river.");
        TP->move_living("M", (LEB_DIR  + "sroad/path3"));
        if (TP->query_encumberance_weight() > 80)
            tired *= 2;
        TP->add_fatigue(-tired);
        SAYBB(" arrives swimming across the river.");
    }
    return 1;
} /* cross_river */
