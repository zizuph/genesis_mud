/*
 *   /d/Gondor/ithilien/poros/obj/chest_treasure.c
 *
 *   This is the chest where the corsair treasure is put.
 *
 *   Talisan,  February 1996
 *
 *   16 June 1999, Gnadnar: put loot control on chest, as with
 *		the shades and the morgul chests.
 *
 * Revisions: 8 feb. 2000 Stern: adapted to use Genesis gem system
 *   Gwyneth, 8 november 2000 Added silver dust to the chest.
 *   Rohim, May 19 2011. Made the room & chest reset like any other.
 */

#pragma strict_types
inherit "/std/receptacle";

#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

private int looted = 0;


void    reset_container();

void
create_receptacle()
{
    set_name("chest");
    set_pname("chests");
    set_adj(({"dark wooden"}));
    set_long(BSN("This large heavy chest is made from a rich dark "
      + "wood. Exceptionally solid, the chest is reinforced with steel "
      + "bands, and has a sturdy steel lock set into its front."));
    set_key("Corsairs_Chest_Key");
    set_pick(45);


    add_prop(OBJ_I_VOLUME,   4000);
    add_prop(OBJ_I_WEIGHT,  25000);
    add_prop(CONT_I_VOLUME, 16000);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
    add_prop(CONT_I_REDUCE_VOLUME,150);
    add_prop(CONT_I_REDUCE_WEIGHT,150);
    add_prop(OBJ_I_VALUE,90);    /* Value ?? cc*/
    add_prop(OBJ_M_NO_GET, 1);

    enable_reset();
    reset_container();
}

void
reset_container()
{
    object ob;

    FIX_EUID
    if (!present("gem", TO))
    {
        ob = clone_object(GEM_DIR + "sapphire");
        ob->set_heap_size(3 + random(5));
        ob->move(TO, 1);
        ob = clone_object(GEM_DIR + "ruby");
        ob->set_heap_size(3 + random(3));
        ob->move(TO, 1);
        ob = clone_object(GEM_DIR + "emerald");
        ob->set_heap_size(3 + random(3));
        ob->move(TO, 1);
        ob = clone_object(GEM_DIR + "diamond");
        ob->set_heap_size(2 + random(4));
        ob->move(TO, 1);
        ob = clone_object(OBJ_DIR + "sdust");
        ob->move(this_object(), 1);
	
	add_prop(CONT_I_CLOSED, 1);
	add_prop(CONT_I_LOCK, 1);
	looted = 0;
    }
}

public void
leave_inv(object ob, object dest)
{
    string name;

    ::leave_inv(ob, dest);

    if (objectp(dest) && interactive(dest))
    {
	name = dest->query_name();
	log_file("chests",
	  ctime(time()) + " " + name + " took loot from the corsairs chest.\n");
	looted = 1;
    }
}

public int
got_looted()
{
    return looted;
}
