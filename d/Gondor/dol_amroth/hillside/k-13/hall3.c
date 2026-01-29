/*
 * hall3.c
 *
 * Skippern 20(c)02
 *
 * The parlor.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define SOFA       "red velvet sofa"
#define COUCH      "black leather couch"

/* Prototypes */
public void           leave_inv(object ob, object dest);
public string         look_at(string arg);

void
create_inside()
{
    set_short("a lounge");
    set_long("This is a quiet lounge, with a red sofa and a black " +
		"couch on each side of a large teak table. It looks quite " +
		"cozy with a painting of a Belerian winefield hanging behind " +
		"the red sofa. This looks like a comfortable place to <sit> " +
		"and enjoy a glass of exquisit wine.\n");

    add_chair(SOFA, "[down] [in] [the] [red] [velvet] 'sofa'", 3, "in");
    add_chair(COUCH, "[down] [in] [the] [black] [leather] 'couch'", 3, "in");
    add_item( ({ "sofa", "red sofa", "velvet sofa", "red velvet sofa" }),
		&look_at(SOFA));
    add_item( ({ "couch", "black couch", "leather couch", 
		"black leather couch" }), &look_at(COUCH));
    add_item( ({ "table", "teak table", "large table", "large teak table" }), 
		"This is a large teak table.\n");
	add_item( "painting", "The painting shows a large Belerian landscape " +
		"with wine-ranks occupying the most dominent part of the picture. " +
		"Some people are seen harvesting the wine grapes somewhere in the " +
		"distance, and far away a forest stretches to the horizont.\n");

    add_exit(DOL_HILLS + "k-13/hall1", "east", 0, 1);
}

void
init()
{
    ::init();
    init_room_chairs();
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}


public string
look_at(string arg)
{
    switch(arg)
    {
    case SOFA:
        return "This sofa is made of the finest red velvet. " +
            sitting_on_chair(SOFA, this_player(), 0);
    case COUCH:
	return "This couch is made of black leather. The tanner must " +
	    "have done a great job as the leather is soft. " +
	    sitting_on_chair(COUCH, this_player(), 0);
    }
}
