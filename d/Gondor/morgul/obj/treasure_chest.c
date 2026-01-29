/*
 *  Revision: Feb 7, 2000 use of Genesis gems instead of Gondor gems
 *            by Stern on Feb 7, 2000
 */

inherit "/std/receptacle";

#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	LOOT_ROOM	(MORGUL_DIR + "cellar/pass_2e1")

#define GEM_DIR "/d/Genesis/gems/obj/"

void	create_receptacle();
void    reset_container();
void	leave_inv(object ob, object dest);

static string	last_logged;

void
create_receptacle()
{
    set_short("metal chest");
    set_pshort("metal chests");
    set_name("chest");
    set_adj("metal");
    set_long(BSN("A heavy metal chest, probably to store valuables. "
      + "It once had a lock, but the chest was opened by brute force "
      + "and the lock is broken."));

    add_item(({"lock", }), "The lock on the metal chest is broken.\n");

    add_prop(OBJ_I_VOLUME,   4000);
    add_prop(OBJ_I_WEIGHT,  25000);
    add_prop(CONT_I_VOLUME, 16000);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    1);

    reset_container();
}

void
reset_container()
{
    object  gem, env = ENV();

    if (objectp(env) &&
	(interactive(env) ||
	 sizeof(FILTER_PLAYERS(all_inventory(env)))))
    {
	return;
    }

    /*
     * at gorboth's suggestion, make the loot very low value gems
     * since they are needed for use as spell components, but
     * we don't want to be providing an ATM here.
     */

    FIX_EUID
    if (!present("gem", TO))
    {
        gem = clone_object(GEM_DIR + "agate");
        gem->set_heap_size(5 + random(10));
        gem->move(TO, 1);
        gem = clone_object(GEM_DIR + "jasper");
        gem->set_heap_size(4 + random(8));
        gem->move(TO, 1);
        gem = clone_object(GEM_DIR + "onyx");
        gem->set_heap_size(3 + random(6));
        gem->move(TO, 1);
        gem = clone_object(GEM_DIR + "garnet");
        gem->set_heap_size(2 + random(4));
        gem->move(TO, 1);
	last_logged = "";
    }
}

public void
leave_inv(object ob, object dest)
{
    string	name;
    ::leave_inv(ob, dest);

    if (objectp(dest) &&
	interactive(dest) &&
	(name = dest->query_name()) != last_logged)
    {
	log_file("chests", ctime(time())+" "+name+" took the morgul loot.\n");
	last_logged = name;

	/* if we're still in the cellar room, call room to add
	 * this player to looter list.  if we've been removed from
	 * the room, the call will have been made in the room itself
	 * when the player picked up the chest.
	 */
	if (file_name(ENV()) == LOOT_ROOM)
	{
	    ENV()->player_took_loot(name);
	}
    }
}
