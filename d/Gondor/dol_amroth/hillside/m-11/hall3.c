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
	     "couch on each side of a large teak table. Along the " +
	     "walls a cupboard is placed between some shelves. " +
	     "The shelves are filled with various books, and in the " +
	     "cupboard you see some bottles of the expensive sort, " +
	     "and some glasses. This looks like a good place to <sit>.\n");

    add_chair(SOFA, "[down] [in] [the] [red] [velvet] 'sofa'", 5, "in");
    add_chair(COUCH, "[down] [in] [the] [black] [leather] 'couch'", 5, "in");
    add_item( ({ "sofa", "red sofa", "velvet sofa", "red velvet sofa" }),
	      &look_at(SOFA));
    add_item( ({ "couch", "black couch", "leather couch", 
		     "black leather couch" }), &look_at(COUCH));
    add_item( ({ "table", "teak table", "large table", "large teak table" }), 
	      "This is a large teak table.\n");
    add_item("cupboard", "This large cupboard is made of maple wood, and " +
	     "inside it you see some bottles of the expensive sort and some " +
	     "appropriate glasses.\n");
    add_item( ({ "shelf", "shelves" }), "Along the walls several shelves " +
	      "containing a large and private book collection.\n");
    add_item("quiet lounge", "This is a quiet lounge, with a red sofa and " +
	     "a black couch on each side of a large teak table. Along the " +
             "walls a cupboard is placed between some shelves. " +
             "The shelves are filled with various books, and in the " +
             "cupboard you see some bottles of the expensive sort, " +
             "and some glasses.");
    add_item( ({ "books", "various books" }), "This looks like a part of " +
	      "a private book collection. Among the books you see is " +
	      "books about historically events in Gondor, and some " +
	      "collections of feary tales.\n");
    add_item( ({ "bottles", "expensive bottles" }), "Inside the cupboard " +
	      "you see various bottles with the best and most expensive " +
	      "liqours from all over the world. Among what you see is some " +
	      "Rohirrim whiskey, and dwarven spirits.\n");
    add_item("glasses", "To drink expensive liqour needs class, and these " +
	     "glasses surely have class. They have clean shapes with a " +
	     "red line from the base circeling up to the rim of the glass.\n");

    add_exit(DOL_HILLS + "m-11/hall1", "west", 0, 1);
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
        return "This sofa is made of the finest red velvet.\n" +
            sitting_on_chair(SOFA, this_player(), 0);
    case COUCH:
	return "This couch is made of black leather. The tanner must " +
	    "have done a great job as the leather is soft.\n" +
	    sitting_on_chair(COUCH, this_player(), 0);
    }
}
