/*
 *  /d/Sparkle/area/tutorial/guild/start.c
 *
 *  The startroom for the Patrol Guild in the tutorial.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "guild.h"

#define TUTORIAL_CHAPTER  48  /* the chapter for the sign */
#define            MARK_PROP       "_mark_warning_prop"

/* Prototypes */
public void              create_silverdell();
int                      start(string str);
void                     init();
public void              reset_room();
public int               do_mark(string arg);

public string      Mark_Text = "The insignia of the Patrol Guild has"
                     + " been stamped into it - no merchant would dare"
                     + " to buy it!\n";

/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("Bunkroom of the Patrol Guild of Silverdell");
    set_long("This is the " + GUILD_NAME + " bunk room. You may choose to"
      + " <start> here if you wish to have this be your place of residence"
      + " from henceforth. It is also a good place for you to store any"
      + " equipment that you may choose to want to keep track of with your"
      + " fellow guildmates. A large anvil rests against one wall, which"
      + " will allow you to <mark> armours or weapons for protection"
      + " against rack-thieves.\n\n");

    add_item( ({ "thief", "thieves", "rack thief", "rack thieves",
                 "rack-thief", "rack-thieves" }),
        "The bane of any guild's rack system! Don't ever be one.\n");
    add_item( ({ "guild", "patrol guild", "building" }),
        "You are within the guild. This building houses all its needs.\n");
    add_item( ({ "room", "area", "here", "bunk room", "bunkroom" }),
        "This room allows you to <start> here if you wish.\n");
    add_item( ({ "bunk", "bunks", "bed", "beds" }),
        "The bunks look cozy and inviting.\n");
    add_item( ({ "equipment" }),
        "You could store things in the rack, stand, or shelf. You can <exa>"
      + " or <list> each to see what is in them.\n");
    add_item( ({ "roof", "ceiling", "up" }),
        "The roof of this room is lower than the rest of the guild.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor in here is a bit dirty. It has a lived-in feel.\n");
    add_item( ({ "sky", "outside" }),
        "You would have to be outside to see much of that.\n");
    add_item( ({ "anvil", "large anvil" }),
        "The anvil is large enough to allow guild members room to place"
      + " any piece of armour or weaponry upon it. A heavy hammer"
      + " rests nearby which can be used to <mark> a desired piece"
      + " of gear with the insignia of the guild. Merchants"
      + " throughout the land know better than to trade in items"
      + " with that mark upon them, unless they have a deathwish.\n");
    add_item( ({ "mark" }),
        "Guild members can <mark> gear they wish to be protected from"
      + " sale here.\n");
    add_item( ({ "hammer", "heavy hammer" }),
        "The hammer looks much like any other, save that it is far"
      + " larger, and the strikepoint bears the insignia of the"
      + " Patrol Guild, such that anything that might be given a"
      + " <mark> with one of its blows will be protected from sale"
      + " to any merchant.\n");

    add_exit("joinroom", "west");

    room_add_object(GUILD_DIR + "weapon_rack");
    room_add_object(GUILD_DIR + "armour_rack");
    room_add_object(GUILD_DIR + "misc_rack");

    reset_room();
}

int
start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("You choose a bunk and make this place your home. You"
          + " will now start here when you enter the realms.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
    add_action(do_mark, "mark");
}


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        do_mark
 * Description  :        Allow players to mark weapons and armours
 *                       to prevent them from being sold.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_mark(string arg)
{
    mixed    obj;
    mixed    sell_prop;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to <mark>?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("Only Patrol members may use the anvil.\n");
        return 1;
    }

    obj = PARSE_COMMAND_ONE(arg, all_inventory(this_player()),
                "[the] [a] [an] %i");

    if (!objectp(obj))
    {
        notify_fail("You don't seem to have any such thing.\n");
        return 0;
    }

    if (!obj->check_weapon() && !obj->check_armour())
    {
        notify_fail("Only armours and weapons may be marked.\n");
        return 0;
    }

    if (obj->query_auto_load() ||
        obj->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("That is certainly not something you need to"
          + " mark!\n");
        return 0;
    }

    if (obj->query_worn() ||
        obj->query_wielded())
    {
        notify_fail("You cannot mark something you currently"
          + " have equipped!\n");
        return 0;
    }

    sell_prop = obj->query_prop(OBJ_M_NO_SELL);

    if (sell_prop)
    {
        if (sell_prop == Mark_Text)
        {
            notify_fail("It has already been marked with the Patrol"
              + " Guild insignia. No need to mark it twice!\n");
        }
        else
        {
            notify_fail("This already cannot be sold. There is no need"
              + " to mark it.\n");
        }
        return 0;
    }

    if (!obj->query_prop(MARK_PROP))
    {
        write("Mark the " + obj->short() + " with the Patrol Guild"
          + " insignia? Doing so will mean that it cannot be sold."
          + " If that is your wish, then re-enter the command.\n");
        obj->add_prop(MARK_PROP, 1);
        return 1;
    }

    this_player()->reveal_me(1);

    write("You place the " + obj->short() + " on the anvil and strike"
      + " it with a single clean blow with the heavy hammer. The"
      + " insignia of the Patrol Guild is now embedded in it's"
      + " surface, virtually guaranteeing that no merchant in the"
      + " realms will dare to accept it for sale.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " places "
      + LANG_ADDART(obj->short()) + " on the anvil and strikes"
      + " it once with a heavy hammer.\n", this_player());

    obj->add_prop(OBJ_M_NO_SELL, Mark_Text);
    return 1;
} /* do_mark */
