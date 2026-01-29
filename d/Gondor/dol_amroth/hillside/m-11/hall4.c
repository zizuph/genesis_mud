/*
 * hall4.c
 *
 * Skippern 20(c)02
 *
 * The kitchen.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";
inherit DOL_LIB + "fire_noise";

#include <macros.h>

/* Globale Variables */
       int      F_alrm;
/* Prototypes */
       string   fireplace();
       int      fire(string arg);
       int      ext_fire(string arg);


void
create_inside()
{
    set_short("a kitchen");
    set_long("This is a large kitchen fit to serve a large and lavish " +
	     "household. Pots and pans in all sizes are present, and " +
	     "along the walls shelves with large and smaller jars are " +
	     "filled with exotic spices and strange vegitables. " +
	     "From the beams in the ceiling hangs some pieces of dried " +
	     "meat and saucages. In the center of the room a large stove " +
	     "is placed.\n");

    add_item( ({ "stove", "large stove" }), &fireplace());
    add_item( ({ "beam", "beams", "ceiling" }), 
	      "Large wooden beams goes across the room suspending " +
	      "the ceiling. Some pieces of dried meat and saucages hangs " +
	      "from the beams.\n");
    add_item( ({ "saucages", "meat", "pieces of meat", "dried meat", 
		   "pieces of dried meat" }), "Some saucages and pieces of " +
	      "dreid meat hangs from the wooden beams.\n");
    add_item( ({ "pot", "pots", "pan", "pans", "pots and pans" }), "There " +
	      "are pots and pans present in all sizes. Some are on the " +
	      "workbench as other hangs on hooks or stands on the stove.\n");
    add_item( ({ "shelf", "shelves" }), "Along the walls several shelves " +
	      "are put up. On the shelves you find jars in all sizes, " +
	      "containing things like exotic spices and vegitables, aswell " +
	      "as flour.\n");
    add_item( ({ "bench", "workbench" }), "In the middle of the room, from " +
	      "the stove, a large workbench is put, so the cook have good " +
	      "space for his work. Marks in the bench shows that the cook " +
	      "have had times with rough work.\n");
    add_item("large kitchen", "This is a large kitchen fit to serve a large " +
	     "and lavish household. Pots and pans in all sizes are present, " +
	     "and along the walls shelves with large and smaller jars are " +
             "filled with exotic spices and strange vegitables. " +
             "From the beams in the ceiling hangs some pieces of dried " +
             "meat and saucages. In the center of the room a large stove " +
             "is placed.\n");
    add_item("walls", "Allong the walls you see various shelves with " +
	     "large and smaller jars filled with exotic spices, strange " +
	     "vegitables and some with flour.\n");
    add_item( ({ "jars", "large jars", "smaller jars", }), "On the " +
	      "shelves along the walls, glass and ceramic jars in various " +
	      "sizes stands storing various exotic spices, strange " +
	      "vegitables and flour. Some of the jars are labeled, and some " +
	      "are not.\n");
    add_item("exotic spices", "In some jars you see exotic spaces. " +
	     "This is spices imported to Gondor at a high cost.\n");
    add_item("strange vegitables", "In some jars here, you see strange " +
	     "vegitables. Some of the vegitables are so strange you've " +
	     "never seen them before.\n");
    add_item("flour", "A few large jars contains flour. This white powder " +
	     "is made from grounding grain. It is used for cooking.\n");
    

    add_exit(DOL_HILLS + "m-11/hall1", "north", 0, 1);

}

init()
{
    ::init();
    add_action(fire, "light");
    add_action(fire, "fire");
    add_action(ext_fire, "extinguish");
}

int
fire(string arg)
{
    string verb = query_verb();

    if ( ((arg == "stove") && verb != "fire") || (verb == "fire" && !arg))
    {
        if (FIREMASTER->query_smoke_s())
        {
            notify_fail("It is allready burning.\n");
            return 0;
        }
        write("You put some logs into the stove and lights a match. The dry " +
              "wood ignites easily and the warmth from the fire comforts " +
              "your body.\n");
        say(QCTNAME(this_player()) + " puts some logs into the stove " +
            "and lights it.\n");
        FIREMASTER->fire_south();
        return 1;
    }
    notify_fail(CAP(verb) + " what?\n");
    return 0;
}

int
ext_fire(string arg)
{
    string verb = query_verb();

    if (arg == "stove")
    {
        if (FIREMASTER->query_smoke_s() == 0)
        {
            notify_fail("What? Its allready extinguished.\n");
            return 0;
        }
        write("You put out the fire in the stove and cools down the " +
              "ashes with a glass of water.\n");
        say(QCTNAME(this_player()) + " extinguishes the stove.\n");
        FIREMASTER->extinguish_south();
        return 1;
    }
    notify_fail(CAP(verb) + " what?\n");
    return 0;
}


string
fireplace()
{
    string r;

    r = "";

    if (FIREMASTER->query_smoke_s())
        r += "The fire in the stove is burning.";
    else
        r += "The stove looks cold.";

    r += "\n";

    return r;
}

void
do_noise()
{
    fire_noise("stove");
    F_alrm = set_alarm(itof(10+random(150)), 0.0, &do_noise());
}

void
start_noise()
{
    F_alrm = set_alarm(5.0, 0.0, &do_noise());
}

void
stop_noise()
{
    remove_alarm(F_alrm);
}
