/*
 *  /d/Gondor/gorboth/open/example_herb_room.c
 *
 *  A basic room which explains the usage of the Gondor
 *  herbsearch code.
 *
 *  Copyright (c) February 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/d/Gondor/defs.h"

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

#define  SWAMP_HERBS          ({ (HERB_DIR + "blung"),\
                                 (HERB_DIR + "tuo"),\
                                 (HERB_DIR + "sumac"),\
                                 (HERB_DIR + "tyelka"),\
                                 (HERB_DIR + "ungolestel"),\
                                 (HERB_DIR + "curugwath"),\
                                 (HERB_DIR + "redweed"),\
                                 (HERB_DIR + "coccinea"),\
                              })


/*
 * function name:        create_room
 * description  :        set up the room
 */
public void
create_room()
{
    set_short("an example room for the Gondor herb code");
    set_long(BSN("This room is an example room for the Gondor herb"
               + " code. It is swampy here, with lots of mud, pools,"
               + " and weeds on the ground."));

    add_item( ({ "mud", "pool", "pools", "weed", "weeds", "ground" }),
    BSN("It looks like there might be a few herbs there."));


    /*
     * The first argument is an array of three different herbs. The
     * first two elements in the array are chosen at random from a
     * list defined above. The third, madwort, will always be available
     * in this room to a person with sufficient skill in herbalism.
     *
     * The second argument is an array of various places that the
     * player can type, and still get the herbs they are searching
     * for. e.g. 'search weeds for herbs'
     *
     * The third argument is the search delay, of which 3 is the
     * current domain standard for Gondor.
     */
    set_up_herbs( ({ ONE_OF_LIST(SWAMP_HERBS),
                     ONE_OF_LIST(SWAMP_HERBS),
                     HERB_DIR + "madwort"
                  }),
                         ({ "pool","pools","mud","ground",
                            "weed","weeds" }),
                   3 );
} /* create_room */
