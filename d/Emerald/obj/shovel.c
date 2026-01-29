/*
 *  /d/Emerald/obj/shovel.c
 *
 *  This code is based in large part on the code Olorin created for
 *  Gondor, located at:
 *
 *      /d/Gondor/common/obj/shovel.c
 *
 *  The difference, is that this code is a bit more up to date, and
 *  the english a bit tighter. Likewise, it is set up to respond to
 *  rooms which have some special reason to require digging. I
 *  dislike requiring a single "special" shovel to do these kinds
 *  of jobs for quests, and therefore want to make it possible for
 *  the room to work with anything that responds to obj->id("shovel").
 *  If you have a room with its own dig code, and want to be able to
 *  cancel out the properties of this dig code, simply add the
 *  following in the room's create function:
 *
 *      add_name( ({ "_special_digging_room" }) );
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h";


/* prototypes */
public void        create_weapon();
public void        init();
public int         do_dig(string str);



/*
 * Function name:        create_weapon
 * Description  :        set up the shovel
 */
public void
create_weapon()
{
  set_name("shovel");
  set_short("shovel");
  set_long("This shovel is a sturdy and well made tool which can"
         + " be used for digging. It has a long wooden handle which"
         + " is mounted with a strong iron spade at one end.\n");

  set_default_weapon(15,10,W_POLEARM,W_SLASH|W_BLUDGEON,W_BOTH,0);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,10)+150-random(50));
} /* create weapon */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
  ::init();

  add_action(do_dig, "dig");
} /* init */


/*
 * Function name:        do_dig
 * Description  :        allow the player to dig with the shovel
 *                       in outdoor rooms
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_dig(string str)
{
  object room;
  object hole;

    if (!strlen(str))
    {
        notify_fail("Where do you want to dig with what?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        "[a] [hole] [in] [the] 'hole' / 'here' / 'ground' [in] [the]"
      + " [ground] [with] [the] [shovel]"))
    {
        notify_fail("Where do you want to dig with what?\n");
        return 0;
    }


    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot dig indoors.\n");
        return 0; /* cannot dig indoors */
    }

    if (this_player()->query_fatigue() < 40)
    {
        write("You are too tired to dig right now.\n");
        return 1;
    }

    this_player()->add_fatigue(-40);

    seteuid(getuid(TO));

    room = environment(this_object());
    while(!room->query_prop(ROOM_I_IS))
    {
        room = environment(room);
    }

    if (room->id("_special_digging_room"))
    {
        return 0; /* let the room handle it from here */
    }

    if (hole = present("_hole_", room))
    {
        write("Taking the shovel, you dig deeper, increasing the"
            + " size of the hole.\n");
        say(QCTNAME(this_player()) + " spends some time digging"
            + " in the ground, increasing the size of the hole.\n");

        hole->increase_size();
        return 1;
    }

    write("Taking the shovel, you begin digging a hole in the ground."
        + " After a short while, you grow weary, and stop to rest.\n");
    say(QCTNAME(this_player()) + " takes a shovel, and begins to dig"
        + " a hole in the ground. After a bit of time, "
        + this_player()->query_pronoun() + " stops and wipes "
        + this_player()->query_possessive() + " brow.\n");

    hole = clone_object("/d/Emerald/obj/hole");
    hole->move(room);
    return 1;
} /* do_dig */
