
/*	store.c		Styles, 920926.
 * 
 *	This is a simple example of a storage room for shops.
 *	It should be compatible with most shops since all it does
 *	is to provide the shop with a small sellection of items
 *	that may be generated upon reset. Thus the shop should
 *	never be totaly empty. It will allso remove excess so that
 *	the shop won't have 'to many' items in store.
 *
 * Modifications:
 *  October 2009 - Added the Gnomish Fan as a general item that
 *                 one can buy. (Petros)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

#define OBJ_PATH		    HUMAN_DIR + "obj/"
#define GNOMISH_FAN         "/d/Sparkle/std/obj/gnomish_fan"
#define GNOMISH_FAN_NAME    "_gnomish_sunpowered_fan"
#define MEDIUM_TORCH         HUMAN_DIR + "obj/t_torch"
#define MEDIUM_TORCH_NAME    "_medium_torch"
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

/*
 * Function:    query_decayable_items
 * Description: This functions looks for the items that should be
 *              considered when the room tries to remove excess items.
 *              One should filter out any persistent items here.
 */
public object *
query_decayable_items()
{
    object * decay_items = filter(all_inventory(this_object()), not @ &->id(GNOMISH_FAN_NAME));
    decay_items = filter(decay_items, not @ &->id(MEDIUM_TORCH_NAME));
    
    if (!decay_items)
    {
        return ({ });
    }
    
    return decay_items;
}

void
remove_excess(int limit)
{
    object sty, ob, *stuff;

    if (!limit) 
	limit = MAX_ITEMS_IN_SHOP;

    // We look for all things that aren't gnomish fans when considering the
    // limit.
    stuff = query_decayable_items();
    if (sizeof(stuff) > limit) {
	ob = stuff[random(sizeof(stuff)-1)];
	if (!interactive(ob)) {			/* Remove ob if not a player */
//	    sty = find_player("styles");
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

   
    /* These things happens to be what I can produce right now. */
    things = ({
	OBJ_PATH+"knife",	"knife",		 85,	 40,
	OBJ_PATH+"ssword",	"short sword",		 30,	 15,
	OBJ_PATH+"lsword",	"long sword",		 20,	 10,
	OBJ_PATH+"rapier",	"rapier",		 35,	 18,
	OBJ_PATH+"halberd",	"halberd",		 10,	  5,
	OBJ_PATH+"axe",		"axe",			 60,	 30
    });
   

    /* If there are less than 20% of MAX_ITEMS_IN_SHOP here,
     * then we will try to make some new things.
     * We will try this "sizeof(things)/4" number of times.
     */
    if (sizeof(query_decayable_items()) < MAX_ITEMS_IN_SHOP / 5)
	for (i=0 ; i < sizeof(things) ; i += 4) {

	    if (!present(things[i+1]) && random(100) < things[i+2]) 
		clone_object(things[i])->move(TO);
	    else if (random(100) < things[i+3])
		clone_object(things[i])->move(TO);
	}
    
    // If the gnomish fan is not here, we create it.
    if (!present(GNOMISH_FAN_NAME))
    {
        clone_object(GNOMISH_FAN)->move(this_object());
    }

    // If the torch is not here, we create it.
    if (!present(MEDIUM_TORCH_NAME))
    {
        clone_object(MEDIUM_TORCH)->move(this_object());
    }
    
    /* Will remove random items if there are to many. 
     * Never allow more items than maximum. Sometimes a little bit less.
     */
    if (!random(5)) {
	decay = MAX_ITEMS_IN_SHOP - (random(MAX_ITEMS_IN_SHOP*3/10)+1);
	remove_excess(decay);

	/*  Debug text.  */
//	sty = find_player("styles");
	if (sty) tell_object(sty, file_name(this_object())+" - Decay :"+
                             decay +"\n");
    }
    else
        remove_excess(MAX_ITEMS_IN_SHOP);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    // We mask this function so that we can make sure that we always
    // have the gnomish fan and a torch in store.
    if (to != this_object() && MASTER_OB(ob) == GNOMISH_FAN)
    {
        clone_object(GNOMISH_FAN)->move(this_object());
    }
    if (to != this_object() && MASTER_OB(ob) == MEDIUM_TORCH)
    {
        clone_object(MEDIUM_TORCH)->move(this_object());
    }
}
