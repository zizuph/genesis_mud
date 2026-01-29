/*
 * Revisions: 7 Feb. 2000 by Stern: Adapted to Genesis gem system.
 */

inherit "/std/receptacle";

#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	LOOT_ROOM	(SHADES_DIR + "loot2")
#define GEM_DIR         "/d/Genesis/gems/obj/"

void    setup_treasure();

static string	last_logged;

void
create_receptacle()
{
    set_name("chest");
    set_pname("chests");
    set_adj("sturdy");
    /*
     * must set_pshort() explicitly or you'll end up seeing stuff 
     * like:
     *          Two sturdy chest (open)s
     */
    set_pshort("sturdy chests");
    set_long(BSN("This is a sturdy wooden chest, it's been stained " +
                 "black. The chest seems in excellent condition and " +
                 "it can surely hold quite a bit."));
    set_key("Shades_Chest_Key");
    set_pick(35);


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
    add_prop(OBJ_M_NO_SELL,"@@no_sell");

    setup_treasure();
}

void
setup_treasure()
{
    object  diamond, env = ENV();

    /*
     * some concern over the richness of the loot. rather than
     * make it less valuable, we decided to have a 50% chance
     * of not generating it.
     */
    if (!random(2))
    {
	return;
    }

    /* players were idling in loot2, waiting for chest to reset,
     * and then using 'pick' to get gems which re-appeared in the
     * conveniently unlocked and open chest without being stopped
     * by the shade npc.
     */
    if (objectp(env) &&
	(interactive(env) ||
	 sizeof(FILTER_PLAYERS(all_inventory(env)))))
    {
	return;
    }

    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
    FIX_EUID
    if (!present("gem", TO))
    {
        diamond = clone_object(GEM_DIR + "sapphire");
        diamond->set_heap_size(2 + random(5));
        diamond->move(TO, 1);
        diamond = clone_object(GEM_DIR + "garnet");
        diamond->set_heap_size(1 + random(2));
        diamond->move(TO, 1);
        diamond = clone_object(GEM_DIR + "diamond");
        diamond->set_heap_size(1 + random(2));
        diamond->move(TO, 1);
    	last_logged = "";
    }
}

mixed
no_sell()
{
  if(sizeof(all_inventory(TO)))
    return BSN("Luckily you notice that the chest is not empty just " +
      "before you sell it. Perhaps you should remove everything from " +
      "the chest before you sell it? ");
  return 0;
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
	log_file("chests",
	    ctime(time())+" "+name+" took loot from the shades chest.\n");
	last_logged = name;


	/* if we're still in the shades room, call room to add
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
