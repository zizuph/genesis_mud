
/*	store.c		Styles, 920926.
 *
 *	This is a simple example of a storage room for shops.
 *	It should be compatible with most shops since all it does
 *	is to provide the shop with a small sellection of items
 *	that may be generated upon reset. Thus the shop should
 *	never be totaly empty. It will allso remove excess so that
 *	the shop won't have 'to many' items in store.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

#include "defs.h"

#define MAX_ITEMS_IN_SHOP	30

void reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The back room of the shop");
    set_long("\nYou're in the back room of the shop. "+
             "This is where the shopkeeper lives.\n"+
             "He stores many rare and valuable items back here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    reset_room();
}

void
remove_excess(int limit)
{
    object sty, ob, *stuff;

    if (!limit) limit = MAX_ITEMS_IN_SHOP;

    stuff = all_inventory(this_object());
    if (sizeof(stuff) > limit) {
        ob = stuff[random(sizeof(stuff)-1)];
        if (!interactive(ob)) {			/* Remove ob if not a player */
            sty = find_player("styles");
            if (sty) tell_object(sty, "Removing: "+  /* Just a debug text. */
                                 ob->short() +"\n");
            ob->remove_object();
        }
        remove_excess(limit);		/* Recursive call to remove items */
    }
    else return;
}

void
reset_room()
{
    object sty;
    mixed *things;
    int decay, i;


    /* Example:
     * These things might be created each reset.
     * Item:		%chanse:	%chanse if more than one:
     *
     * Torch		100		60
     * Bag		 85		40
     * Bucket		 80		40
     * Knife		 85		40
     * Short sword	 30		15
     * Long sword	 20		10
     * Shield		 20		10
     * Helmet		 15		 5
     *
     *
     */


    // We will be cloning things, set access rights correctly.

    setuid (); seteuid (getuid ());

    /* These things happens to be what I can produce right now. */
    things = ({
        S_COMMON_WEP_DIR+"knife",	"knife",		 85,	 40,
        S_LOCAL_WEP_DIR+"ssword",	"short sword",		 30,	 15,
        S_LOCAL_WEP_DIR+"lsword",	"long sword",		 20,	 10,
        S_LOCAL_WEP_DIR+"rapier",	"rapier",		 35,	 18,
        S_LOCAL_WEP_DIR+"halberd",	"halberd",		 10,	  5,
        S_LOCAL_WEP_DIR+"axe",		"axe",			 60,	 30
    });


    /* If there are less than 20% of MAX_ITEMS_IN_SHOP here,
     * then we will try to make some new things.
     * We will try this "sizeof(things)/4" number of times.
     */
    if (sizeof(all_inventory(this_object())) < MAX_ITEMS_IN_SHOP /20)
        for (i=0 ; i < sizeof(things) ; i += 4) {

            if (!present(things[i+1]) && random(100) < things[i+2])
                clone_object(things[i])->move(TO);
            else if (random(100) < things[i+3])
                clone_object(things[i])->move(TO);
        }

    /* Will remove random items if there are to many.
     * Never allow more items than maximum. Sometimes a little bit less.
     */
    if (!random(5)) {
        decay = MAX_ITEMS_IN_SHOP - (random(MAX_ITEMS_IN_SHOP*3/10)+1);
        remove_excess(decay);

//        /*  Debug text.  */
//        sty = find_player("styles");
//        if (sty) tell_object(sty, file_name(this_object())+" - Decay :"+
//                             decay +"\n");
    }
    else
        remove_excess(MAX_ITEMS_IN_SHOP);
}
