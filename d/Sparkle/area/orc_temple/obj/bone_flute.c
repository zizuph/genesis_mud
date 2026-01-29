/*
 *  /d/Sparkle/area/orc_temple/obj/bone_flute.c
 *
 *  This is the bone flute worn by the High Priest in the
 *  Sparkle Dungeons.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 *  Updated July 24, 2016 by Gronkas - fixed a minor typo
 */
#pragma strict_types

inherit "/std/object"; 
inherit "/lib/wearable_item"; 

#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "../defs.h"


/* Definitions */
#define    LOSE_WARNING              "_flute_lose_warning"

/* prototypes */
public void        create_object();
public string      drop_flute();
public int         play_flute(string arg);
public void        flute_effect(object pl, object room);
public void        init();
public void        enter_env(object dest, object old);
public void        do_vanish();
public int         lose_it(string arg);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name( ({ "flute" }) );
    add_name("_imbuement_quest_bone_flute");
    set_adj( ({ "bone" }) ); 

    set_short("bone flute"); 

    set_long("What appears to have been the leg bone of a large"
      + " living being has been carved down and hollowed out to"
      + " create this flute. A leather cord has been wound around"
      + " its mouthpiece, allowing it to be worn as a necklace. It"
      + " might be possible to <play> it.\n"); 

    config_wearable_item(A_NECK, 1, 6, this_object()); 

    add_item( ({ "cord", "leather cord" }),
        "The leather cord has been wound around the flute just"
      + " below the mouthpiece.\n");
    add_item( ({ "mouthpiece" }),
        "The mouthpiece on the flute is crude, but bears the same"
      + " basic properties as one you might find on a recorder.\n");

    add_prop(OBJ_M_NO_GIVE, "@@drop_flute@@");
    add_prop(OBJ_M_NO_SELL, "The bone flute has no monetary value.\n");
    add_prop(OBJ_M_NO_DROP, "@@drop_flute@@");
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(OBJ_I_WEIGHT, 4); 
    add_prop(OBJ_I_VOLUME, 5); 
    add_prop(OBJ_M_NO_STEAL, 1); 

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        drop_flute
 * Description  :        lets have this be called when someone tries
 *                       to give the flute away so we give the right
 *                       message to the player.
 * Returns      :        string - the message
 */
public string
drop_flute()
{
    if (environment(this_object())->query_npc())
    {
        return 0;
    }

    if (query_verb() == "give")
    {
        return "You should probably hang on to it. Perhaps you could"
          + " <show> it to someone instead?\n";
    }

    return "You should probably hang on to this. You could probably"
      + " <discard> it if you really wanted to.\n";
} /* drop_flute */


/*
 * Function name:        play_flute
 * Description  :        allow players to play this flute
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
play_flute(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [note] [on] [the] [bone] 'flute'"))
    {
        notify_fail("Do you wish to " + query_verb() + " on the"
          + " bone flute, perhaps?\n");
        return 0;
    }

    write("You bring the bone flute to your lips and blow, producing"
      + " a strange, haunting tone.\n");
    tell_room(QCTNAME(this_player()) + " plays a bone flute,"
      + " producing a strange, haunting tone.\n", this_player());

    set_alarm(2.0, 0.0, &flute_effect(this_player(),
        environment(this_player())));

    return 1;
} /* play_flute */


/*
 * Function name:        flute_effect
 * Description  :        The effect (if any) the flue being played
 *                       has on the room.
 * Arguments    :        object pl - the player who played it
 *                       object room - the room in which it was played
 */
public void
flute_effect(object pl, object room)
{
    if (!room->id(DUNGEON_CELL))
    {
        return;
    }

    room->summon_ghost(pl);
} /* flute_effect */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(play_flute, "play");
    add_action(play_flute, "blow");
    add_action(lose_it, "discard");
} /* init */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * We redefine this to make sure the flute doesn't last if dropped.
 */
public void
enter_env(object dest, object old)
{
    if (dest->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, "do_vanish");
    }

    ::enter_env(dest, old);
} /* enter_env */


/*
 * Function name:        do_vanish
 * Description  :        the object disappears
 */
public void
do_vanish()
{
    object env = environment(this_object());

    tell_room(environment(this_object()), 
        "The bone flute shatters as it hits the ground!\n");

    remove_object();
} /* do_vanish */


/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      :        string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */


/*
 * Function name:        lose_it
 * Description  :        Allow players to get rid of this item, if they
 *                       really want to.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
lose_it(string arg)
{
    string  word;
    object *obj;

    notify_fail("Discard what, the flute\n?");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
            "[the] %w", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        return 0;
    }

    if (obj[0] != this_object())
    {
        return 0;
    }

    if (!this_object()->query_prop(LOSE_WARNING))
    {
        this_object()->add_prop(LOSE_WARNING, 1);

        write("Permanently discard your " + short() + "? Retype to"
          + " confirm.\n");
        return 1;
    }

    write("You discard your " + short() + ".\n");
    this_object()->remove_object();
    return 1;
} /* lose_it */


