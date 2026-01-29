/*
 *  /d/Sparkle/area/tutorial/town/weapon_shop.c
 *
 *  This is the Weapon Shop of Greenhollow. It teaches players
 *  about weapons.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit LIB_DIR + "shop";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>     /* for QTCNAME */

/* definitions */
#define  TUTORIAL_CHAPTER    22  /* the chapter for the sign */
#define  STORE_ROOM          TOWN_DIR + "weapon_storage"

/* prototypes */
public void         hint(string arg);
public int          ring_bell(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("The Weapons Shop of Greenhollow");
    set_long("This is the Weapons Shop of Greenhollow. Here you can"
      + " <buy> or <sell> tools of combat. A door to the south"
      + " leads back to the General Store. You can type <list>"
      + " to see what items are currently in stock.\n\n");

    add_item( ({ "east", "east wall", "curtain", "store room" }),
        "A curtain in the east wall separates the main room of the"
      + " shop from the store room.\n");
    add_item( ({ "south", "general store", "south door",
                 "door to the south" }),
        "This shop connects with General Store"
      + " via a door to the south.\n");
    add_item( ({ "counter", "long counter" }),
        "A long counter is situated at the front of the store. It is"
      + " behind this that the owner spends most of his time. A"
      + " small silver bell rests on the counter.\n");
    add_item( ({ "bell", "silver bell", "small bell",
                 "small silver bell" }),
        "A card beside the bell reads: <ring bell> for service.\n");
    add_item( ({ "shop", "store", "weapon shop", "weapons shop", 
                 "weapons shop of greenhollow", "room", "area" }), long);
    add_item( ({ "wall", "walls", "weapon", "weapons" }),
        "The walls of the shop are crowded with shelves, many of"
      + " which display weapons of various types.\n");
    add_item( ({ "floor", "ground", "down", "carpet", "blue carpet",
                 "worn carpet", "well-worn carpet",
                 "well-worn blue carpet", "worn blue carpet" }),
        "The floor of the shop is covered by a well-worn blue carpet.\n");
    add_item( ({ "ceiling", "up", "roof", "beam", "beams",
                 "wooden beams", "wood", "powerful beams",
                 "powerful wooden beams" }),
        "The roof of the shop is supported by powerful wooden beams.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from inside this shop.\n");
    add_item( ({ "door", "doorway" }),
        "The door leads out of the shop back onto the street.\n");
    add_item(({ "shelves", "cases", "shelf", "case",
                "shelves and cases", "cases and shelves",
                "display case", "display cases", "wares" }),
        "Shelves and cases display a number of the owner's wares. You"
      + " can <list> what is available if the owner is present.\n");
    add_item( ({ "card" }),
        "The card reads: <ring bell> for service.\n");

    add_cmd_item( ({ "card" }),
                  ({ "read" }),
        "The card reads: <ring bell> for service.\n");

    add_indoor_items();
    add_door_items();
    add_window_items();

    prevent_attacks();
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("general_store", "south");
    add_exit("weapon_storage", "east", wiz_check, 1, 1);

    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the Weapons Shop of Greenhollow");

    reset_room();
} /* create_silverdell */


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
    if (!weapon_filter(x))
    {
        if (armour_filter(x))
        {
            return "The shopkeeper says: You'll have to take that "
              + x->short() + " to the Armourer. I only trade in"
              + " weapons.\n";
        }
        else
        {
            return "The shopkeeper says: You'll have to take that " 
              + x->short() + " to the General Store through the"
              + " door to the south. I only trade in weapons.\n";
        }
    }

    return 0;
}


void
init()
{
    ::init();
    ::init_shop();

    add_action(hint, "hint");
    add_action(ring_bell, "ring");
}


void
reset_room()
{
    set_alarm(2.0, 0.0, "summon_shopkeeper");

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
}


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Sure, here's a hint. If you are confused, re-read the sign"
      + " about how to use shop commands like <buy> and <sell>. It is"
      + " just south of here in the General Store. If you"
      + " don't have enough money, you'll need to go kill a few things"
      + " north of town and sell what you find to earn some coins.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       summon_shopkeeper
 * Description  :       restore npc as needed
 */
public void
summon_shopkeeper()
{
    object    npc;

    if (!present("_silverdell_weapon_shopkeeper"))
    {
        setuid();
        seteuid(getuid());
        npc = clone_object(NPC_DIR + "wep_merchant");
        set_keeper(npc);
        npc->move(this_object(), 1);

        tell_room(this_object(), "The shopkeeper appears from behind"
          + " a curtain in the east wall.\n");
    }
    else
    {
        tell_room(this_object(),
            "The shopkeeper smiles and says: How can I be of service?\n");
    }
} /* summon_shopkeeper */


/*
 * Function name:        ring_bell
 * Description  :        allow players to summon the innkeeper if
 *                       the innkeeper is not present.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
ring_bell(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to ring?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [small] [silver] 'bell'"))
    {
        return 0; /* bad syntax */
    }

    write("You ring the small silver bell.\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " rings the small silver bell.\n", this_player());

    reset_room();

    return 1;
} /* ring_bell */

