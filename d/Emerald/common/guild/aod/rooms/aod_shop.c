/*
 *  /d/Emerald/common/guild/aod/rooms/aod_shop.c
 *
 *  This is the General Store for the Army of Darkness guild. It
 *  is only available to players once enough human skulls have
 *  been harvested.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "shop";
inherit AOD_LIB_DIR + "add_spike";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>     /* for QTCNAME */

/* definitions */
#define  STORE_ROOM          AOD_ROOM_DIR + "storage"

/* prototypes */
public void         create_cave_room();
public int          bash_counter(string arg);


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("the general store of the Army");
    set_long("It appears as if the ogres have somehow learned the"
      + " art of capitalism - this is actually an ogre-run general"
      + " store (which should probably qualify it as one of the"
      + " seven wonders of Genesis!) That being said, there is a"
      + " huge stone block which appears to be acting as a counter"
      + " of sorts, behind which you can see a large hole in the"
      + " wall leading into darkness. You can probably get a <list>"
      + " here of what is available for sale.\n\n");

    add_item( ({ "large hole", "hole" }),
        "Looks like someone bashed through the east wall to create"
      + " a storage room for the shop.\n");
    add_item( ({ "store room", "storage room", "storage" }),
        "Yep, right through that hole.\n");
    add_item( ({ "east wall", "eastern wall" }),
        "Its got a hole bashed in it!\n");
    add_item( ({ "store", "shop", "area", "here", "general store" }),
        "Unbelievable. A shop run by ogres! Surely, this will lead"
      + " to nothing but trouble.\n");
    add_item( ({ "counter", "block", "stone block", "huge block",
                 "huge stone block" }),
        "This stone block looks about the same size as the hole"
      + " in the eastern wall. I suppose it used to be there, but"
      + " now its acting as a counter for the store. You could"
      + " probably <bash> counter if the shopkeeper isn't"
      + " present to get his attention.\n");
    add_item( ({ "shop", "store", "weapon shop", "weapons shop", 
                 "weapons shop of greenhollow", "room", "area" }), long);
    add_item( ({ "wall", "walls", "pile", "piles" }),
        "Heaps of loot have piled up along the walls. This is"
      + " probably the stuff that has yet to be inventoried. Well,"
      + " at least that is what would be the case if a more"
      + " civilized race was running things around here. Come to"
      + " think of it, these are probably not going anywhere anytime"
      + " soon.\n");
    add_item( ({ "heap", "heaps", "loot", "heap of loot",
                 "heaps of loot" }),
        "A total mess! What would the manager think?\n");
    add_item( ({ "mess", "total mess" }),
        "It's hopeless. Might as well forget about it.\n");

    add_cave_items();
    add_spike("aod_shop");

    add_exit("tunnel4", "south");
    add_exit("storage", "east", wiz_check, 1, 1);

    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the general store of the Army");

    reset_room();
} /* create_cave_room */


public void
print_message(string str)
{
    keeper->command("say " + str);
}


int
do_buy(string args)
{
  if (check_keeper()) return ::do_buy(args);
  return 0;
}


int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}


int
do_sell(string args)
{
  if (check_keeper()) return ::do_sell(args);
  return 0;
}


mixed
shop_hook_filter_sell(object x)
{
    return 0;
}


void
init()
{
    ::init();
    ::init_shop();

    add_action(bash_counter, "bash");
}


void
reset_room()
{
    set_alarm(2.0, 0.0, "summon_shopkeeper");
}


/*
 * Function name:       summon_shopkeeper
 * Description  :       restore npc as needed
 */
public void
summon_shopkeeper()
{
    object    npc;

    if (!present("_aod_shopkeeper"))
    {
        setuid();
        seteuid(getuid());
        npc = clone_object(AOD_NPC_DIR + "shopkeeper");
        set_keeper(npc);
        npc->move(this_object(), 1);

        tell_room(this_object(), "The shopkeeper stomps in from"
          + " the hole in the wall.\n");
    }
    else
    {
        tell_room(this_object(),
            "The shopkeeper booms: WHO COME? WHAT WANT?\n");
    }
} /* summon_shopkeeper */


/*
 * Function name:        bash_counter
 * Description  :        allow players to summon the shopkeeper if
 *                       the shopkeeper is not present.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
bash_counter(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to bash?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [huge] [stone] 'block' / 'counter'"))
    {
        return 0; /* bad syntax */
    }

    if (!IS_OGRE(this_player()))
    {
        write("You feebly pound on the counter with your fist."
          + " Ouch! That hurts! Figuring that didn't have much"
          + " effect, you simply call for the shopkeeper.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " slams a feeble fist into the counter and winces"
          + " in pain! Looking somewhat sheepish, "
          + this_player()->query_pronoun() + " simply calls for"
          + " the shopkeeper instead.\n", this_player());

        reset_room();
        return 1;
    }

    write("You pound on the counter with your mighty fists!\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " pounds on the counter with a mighty fist!\n", this_player());

    reset_room();

    return 1;
} /* bash_counter */

