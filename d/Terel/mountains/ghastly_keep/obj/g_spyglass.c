/*
 *  /d/Terel/mountains/ghastly_keep/obj/g_spyglass.c
 *
 *  Ghostly spyglass.
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:
 *  ---------------------------------------------------------------------------
 *  20/04-17      Language tweak complete                              Gorboth
 *  27/04-17      Fixed a bug with the object                          Znagsnuf
 *  29/05-17      Fixed capitalize before ROOM_SEE                     Znagsnuf
 *  06/06-17      Made it recoverable                                  Znagsnuf
 *  21/12-17      query_prevent_snoop() check                          Lucius
 *  22/12-17      Increased mana cost and interval		               Lucius
 *  22/5-4   Lilith: added keepability, converted to set_item_expiration  Lilith
 *  22/5-28  Lilith: swapped MANA_DRAIN for dynamic mana calc so 
 *              it costs as much as a scry spell does. Also, since
 *              the mana cost for the scry is so high, remove the 
 *              mana cost for "focus".
 */

#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/resource";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <tasks.h>
#include <formulas.h>
#include <tasks.h>

#define MANA_DRAIN   (get_dynamic_mana_cost(TP, TS_INT, 0, TASK_ROUTINE, 300))
//#define MANA_DRAIN	40
#define IVAL		300
#define USED_SPYGLASS	"_live_i_used_spyglass"


int use_spyglass(string str);
int focus_spyglass(string str);

string set_location = "Null";
int found_location = 0;

object spyglass_obj;

/*
 * Function name: create_object
 * Description  : Set up default values for parts of the ship
 */
void
create_object()
{
    set_name("spyglass");
    add_name("_ghastly_spyglass");
    set_adj("ghostly");

    set_short("ghostly spyglass");

    set_long("Made out of indistinguishable material, this "
      +this_object()->short()+ " might give you the strategic edge "
      + "you need to defeat your enemies. The spyglass is "
      + "outlined by four bright stars at the corners of an "
      + "imaginary trapezoid. Within the space defined by these "
      + "four points, seeming to draw them together into a pattern, "
      + "is a row of three stars tilted at an angle, formed as a belt. "
      + "Arcing downward from the belt is another group of fainter "
      + "stars which form a sword. It has a round golden adorned glass "
      + "with a substantial black lens.\n@@stars_aligned@@");

    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

    add_prop (MAGIC_AM_ID_INFO,
      ({"The " + short() + " has a powerful enchantment.\n", 10,
	"Gaze through the " + short() + " and you will see "
	+ "the past, not the future.\n",                       20,
	"Focus the lens of the " + short() + " and the " +
	"stars will align.\n", 30}));


    add_prop(OBJ_S_WIZINFO, "If the stars are aligned "
      + "this " +this_object()->short()+ " will let you "
      + "gaze into the past, not the future.\n"
      + "It can be used to mark a room and then scry"
      + " it at a later time.\n");

    add_prop(OBJ_I_VALUE, 1000 + random(500));
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 400);

    set_keep(1); // Lilith, May 2022.

    // This was deprecated and basically means that this object always recovers.
    //    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);
    // using the item_expiration lib instead. Lilith, May 2022
    if (IS_CLONE)
	set_item_expiration();

}

void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

/*
 * Function name: stars_aligned()
 * Description  : Checking if the stars are aligned, and if the item is
		  ready to use again.
 */
string
stars_aligned()
{

    if (this_player()->query_prop(USED_SPYGLASS) + IVAL > time()
      || query_prop(USED_SPYGLASS) + IVAL > time())
    {
	return "The four bright stars forming the imaginary trapezoid "
	+ "are still not aligned.\n";
    }
    else
    {
	return "The four bright stars forming the imaginary trapezoid "
	+ "are perfectly aligned.\n";
    }
}

public void
init()
{
    ::init();

    if (this_player() != environment())
	return;

    // If it is broken there is no functionality.	
    // Added by Lilith, May 2022.
    if (this_object()->query_prop(OBJ_I_BROKEN))
	return;

    add_action(use_spyglass,     "see");
    add_action(use_spyglass,    "gaze");
    add_action(use_spyglass,   "glare");
    add_action(focus_spyglass, "focus");
    add_action(focus_spyglass,  "turn");
}

/*
 * Function name: use_spyglass()
 * Description  : Gaze through the spyglass, look in to the past!
 */
int
use_spyglass(string str)
{
    object *inv, remote;

    // Added by Lilith. When the item expires, it no longer works.
    if (this_object()->query_prop(OBJ_I_BROKEN))
    {
	notify_fail("The spyglass is broken and no longer works!\n");
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " through what?\n");
	return 0;
    }

    notify_fail(capitalize(query_verb()) + " through what?\n");
    if (!parse_command(str, ({}), "[through] [the] [ghostly] 'spyglass'"))
	return 0;

    // Need to set focus first.
    notify_fail("The world around you becomes a kaleidoscope, blurred, "
      + "spinning and brilliant.\n");
    if(set_location == "Null")
	return 0;

    // If the set_room is updated, and the location is lost.
    notify_fail("The " +this_object()->short()+ " has lost its current "
      + "focus.\n");
    if((found_location) && (!spyglass_obj))
	return 0;

    // If the player can't see, they can't see through the spyglass.
    notify_fail("Pitch darkness keeps you from gazing through the "
      +this_object()->short()+ ".\n");
    if (!CAN_SEE_IN_ROOM(this_player()))
	return 0;

    // Can they see in the room with the focus?
    remote = environment(spyglass_obj);
    notify_fail("You gaze through the indistinguishable but all you "
      + "observe is a cimmerian shade.\n");
    if (CAN_SEE_IN_ROOM(remote))
	return 0;

    // Some rooms is not able to focus the spyglass in.
    notify_fail("Glaring through the " +this_object()->short()+ ", all "
      + "you see is total darkness.\n");
    if(remote->query_prop(ROOM_M_NO_SCRY) || remote->query_prevent_snoop())
	return 0;


    notify_fail("You do not possess the mental strength to go through "
      + "with this.\n");
    if (this_player()->query_mana() < MANA_DRAIN)
	return 0;

    // Wait for cooldown.
    notify_fail("The four bright stars forming the imaginary trapezoid "
      + "are still not aligned.\n");
    if (this_player()->query_prop(USED_SPYGLASS) + IVAL > time()
      || query_prop(USED_SPYGLASS) + IVAL > time())
	return 0;

    // Adding cooldown to both item, and player.
    this_player()->add_prop(USED_SPYGLASS, time());
    add_prop(USED_SPYGLASS, time());

    // Draining mana.
    this_player()->add_mana(-MANA_DRAIN);

    // Execute the 'look'.
    // short desc + long desc + living + items
    write(remote->short() + ".\n");
    write(remote->long());

    inv = all_inventory(remote) - ({ this_player() });

    inv = filter(inv, &->check_seen(this_player()));

    object *live=FILTER_LIVE(inv);
    object *dead=FILTER_DEAD(inv);

    if (sizeof(live))
	this_player()->catch_msg(capitalize(COMPOSITE_LIVE(live))+ ".\n");

    if (sizeof(dead))
	this_player()->catch_msg(capitalize(COMPOSITE_DEAD(dead))+ ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the "
      +this_object()->short()+ ".\n", TP);

    return 1;

}

/*
 * Function name: set_spyglass()
 * Description  : Set a location.
 */
mixed
set_spyglass(string str)
{
    set_location = str;
}

/*
 * Function name: query_spyglass()
 * Description  : Returns the location.
 */
mixed
query_spyglass(string str)
{
    return set_location;
}

/*
 * Function name: focus_spyglass()
 * Description  : Focus the spyglass, setting a location to look at.
 */
int
focus_spyglass(string str)
{

    string l_file;

    string location = file_name(environment(this_player()));

    // Added by Lilith. When the item expires, it no longer works.
    if (this_object()->query_prop(OBJ_I_BROKEN))
    {
	notify_fail("The spyglass is broken and no longer works!\n");
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    if (!parse_command(str, ({}), "[the] [ghostly] 'spyglass'"))
	return 0;

    // If there is an object already present, there is no need to focus
    // again.
    notify_fail("You focus your " +this_object()->short()+ ", but nothing "
      + "happens.\n");
    if (present("_ghastly_spyglass_obj_" +this_player()->query_real_name(),
	(environment(this_player()))))
	return 0;

    // If the player can't see, they can't focus.
    notify_fail("You gaze through the "+this_object()->short()+ " but all you "
      + "observe is a cimmerian shade.\n");
    if (!CAN_SEE_IN_ROOM(this_player()))
	return 0;

// No mana cost to focus, the cost for scry was upped -Lilith May 2022
//    notify_fail("You do not possess the mental strength to go through "
//      + "with this.\n");
//    if (this_player()->query_mana() < MANA_DRAIN)
//	return 0;

    // Waiting for cooldown.
    notify_fail("The four bright stars forming the imaginary trapezoid "
      + "are still not aligned.\n");
    if (this_player()->query_prop(USED_SPYGLASS) + IVAL > time()
      || query_prop(USED_SPYGLASS) + IVAL > time())
	return 0;

    // Adding cooldown to both item, and player.
    this_player()->add_prop(USED_SPYGLASS, time());
    add_prop(USED_SPYGLASS, time());

    // Make sure there is only one object around.
    if(spyglass_obj)
	spyglass_obj->remove_object();

    // Mana-cost for focus removed. Mana cost to scry was upped. -Lilith
    // Consuming mana.
    //this_player()->add_mana(-MANA_DRAIN);

    // Setting the location.
    set_spyglass(location);

    setuid();
    seteuid(getuid());

    // Cloning the object.
    spyglass_obj = clone_object(GKEEP_OBJ + "g_spyglass_obj");
    spyglass_obj->add_prop("_ghastly_spyglass_obj_"
      + this_player()->query_real_name(),
      file_name(this_object()));
    spyglass_obj->add_name("_ghastly_spyglass_obj_"
      + this_player()->query_real_name(),
      file_name(this_object()));
    spyglass_obj->move(location);

    found_location = 1;

    write("You focus the " +this_object()->short() + " by turning the "
      + "substantial black lens.\n"
      + "\nEach of the four bright stars at the corners of an "
      + "imaginary trapezoid, shimmers brightly as they align "
      + "and blasts a bright light out of the "
      +this_object()->short()+ ".\n");


    l_file = ctime(time()) + " " + CAP(TP->query_real_name()) +
    " (" +TP->query_average_stat()+ ") focused:\n\t" + location + "\n";

    // Write a log file.
    write_file(FOCUSED_SPYGLASS, l_file);

    tell_room(ENV(TP), QCTNAME(TP) + " focus the " +this_object()->short()+ ", "
      + "by turning the substantial black lens.\n", TP);

    return 1;
}
