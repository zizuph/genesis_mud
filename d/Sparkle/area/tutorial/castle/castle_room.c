/*
 *  /d/Sparkle/area/tutorial/woods/castle_room.c
 *
 *  This is the base file for the rooms in the Castle of Baron von
 *  Krolock to inherit.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma no_clone
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* Global Variables */
public string      Trigger_Room = "";  /* does entering from this room
                                        * trigger a message? */

/* Prototypes */
public void        create_castle_room();
public void        create_silverdell();
public void        add_castle_items();
public void        add_torch_items();
public int         check_exit(string message = "");
public void        clone_guard(int number, string size = "normal");
public void        broadcast(string txt, object player);
public void        init();
public int         get_torch(string arg);

public void        set_trigger_room(string s = "yes")
                   { Trigger_Room = s; }
public string      query_trigger_room() { return Trigger_Room; }


/*
 * Function name:        create_castle_room();
 * Description  :        dummy file for inheriting rooms
 */
public void
create_castle_room()
{
} /* create_castle_room */


/*
 * Function name:        create_silverdell
 * Description  :        set up the room with area presets
 */
nomask void
create_silverdell()
{
    add_prop(ROOM_I_INSIDE, 1); /* castle rooms are indoor */
    add_prop(ROOM_I_LIGHT, 1);  /* most rooms are lit by torches */

    setuid();
    seteuid(getuid());

    //By default, these rooms are instanced.
    instance_entrance = 0;

    create_castle_room();
} /* create_silverdell */


/*
 * Function name:        add_castle_items
 * Description  :        add_items for the rooms inside the castle
 */
public void
add_castle_items()
{
    try_item( ({ "floor", "down", "ground" }),
        "Thick dusty carpet runs the length of the floor here, covering"
      + " cold, unlovely stone slabs beneath.\n");
    try_item( ({ "stone slab", "stone slabs", "unlovely slab",
                 "unlovely slabs", "dust", "cobweb", "corner",
                 "corners", "cobwebs", "slab", "slabs" }),
        "The stone slabs that make up the floor do not appear to have"
      + " ever been swept. Dust is everywhere, and cobwebs fill the"
      + " corners of the room.\n");
    try_item( ({ "carpet", "dusty carpet", "old carpet", "rug" }),
        "Though originally probably very expensive and well made, the"
      + " carpet has been worn down by years of neglect and hard use."
      + " It is covered with dust and heavily worn.\n");
    try_item( ({ "wall", "walls", "stone wall", "stone walls",
                 "castle wall", "castle walls", "walls of the castle" }),
        "The castle walls are cold and unwelcoming, their heavy stone"
      + " masonry having been occasionally covered with garish"
      + " tapestries which depict horrible images.\n");
    try_item( ({ "tapestry", "tapestries", "image", "images",
                 "horrible image", "horrible images", "garish tapestry",
                 "garish tapestries", "art", "artwork" }),
        "The tapestries, though crafted with great skill, depict hideous"
      + " demonic rituals which have no place in artwork such as this.\n");
    try_item( ({ "stone", "stones", "masonry", "stone masonry",
                 "surface", "surfaces", "stone surfaces",
                 "stone surface", "castle" }),
        "The masonry which has gone into building this castle, though"
      + " achieved with great skill, does not appear to have been done"
      + " to satisfy any aesthetic sensibilities. Cold, hard, unwelcoming"
      + " stone surfaces surround you.\n");
    try_item( ({ "up", "ceiling", "roof" }),
        "The ceiling is vaulted, and rises up many feet above your"
      + " head.\n");

    add_cmd_item( ({ "tapestry", "tapestries" }),
                  ({ "move", "search", "lift" }),
        "You look behind the tapestries, but find only cold stone"
      + " walls.\n");
    add_cmd_item( ({ "rug", "carpet", "old carpet", "dusty carpet" }),
                  ({ "move", "search", "lift" }),
        "You lift up the edge of the carpet, but find only more dust"
      + " beneath.\n");
} /* add_castle_items */


/*
 * Function name:        add_torch_items
 * Description  :        add_items appropriate for lit rooms of the
 *                       castle
 */
public void
add_torch_items()
{
    add_item( ({ "light", "torch", "torchlight", "flame",
                 "flames", "fire" }),
        "Flame burns dully from a torch held in a crude iron sconce"
      + " which is affixed to the wall. The flickering of the light"
      + " causes the shadows in the room to dance with each lick of"
      + " fire.\n");
    add_item( ({ "sconce", "iron sconce", "crude sconce",
                 "crude iron sconce", "bolt", "bolts", "heavy bolt",
                 "heavy bolts" }),
        "The sconce which holds the torch is fastened to the wall"
      + " with heavy bolts.\n");
    add_item( ({ "shadow", "shadows" }),
        "The shadows in the room radiate outward from the flickering"
      + " torchlight.\n");
} /* add_torch_items */


/*
 * Function name:        check_exit
 * Description  :        see if there is a guard preventing the
 *                       player from using this exit
 * Arguments    :        string message - do we want a special message
 *                                        for when the npc blocks?
 * Returns      :        int 1 - don't allow, 0 - allow
 */
public int
check_exit(string message = "")
{
    if (!present("_tutorial_demon_guard", this_object()))
    {
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        write("The guard allows you to pass.\n");
        return 0;
    }

    if (strlen(message))
    {
        write(message);
    }
    else
    {
        write("The demon guard won't allow you to pass that way.\n");
    }
    if (this_player()->query_wiz_level())
    {
        write("Since you're a wizard, you pass him anyway.\n");
        return 0;
    }

    return 1;
} /* check_exit */


/*
 * Function name:        clone_guard
 * Description  :        bring the right amount of guards into
 *                       this room
 * Arguments    :        string size - what type of guard do we want?
 *                       int number - the amount of clones we want
 */
public void
clone_guard(int number, string size = "normal")
{
    int     i, n;
    string  filename = NPC_DIR + "demon_guard";
    object *guard = allocate(number);

    if (present("_tutorial_demon_guard", this_object()))
    {
        return;
    }

    if (size == "massive")
    {
        filename = NPC_DIR + "massive_guard";
    }

    for (i = 0, n = sizeof(guard); i < n; i++)
    {
        if (!objectp(guard[i]))
        {
            guard[i] = clone_object(filename);
            guard[i]->set_restrain_path(CASTLE_DIR);
            guard[i]->arm_me();
            guard[i]->move_living("from the void", this_object());
        }
    }
    return;
} /* clone_guard */


/*
 * Function name:        broadcast
 * Description  :        Krolock's voice booms throughout the castle
 *                       at various times.
 * Arguments    :        string txt - what does he say?
 *                       object player - who gets the message?
 */
public void
broadcast(string txt, object player)
{
    player->catch_tell("A voice booms: " + txt + "\n");
    return;
} /* broadcast */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_torch, "get");
    add_action(get_torch, "take");
    add_action(get_torch, "steal");
    add_action(get_torch, "lift");
    add_action(get_torch, "remove");
} /* init */


/*
 * Function name:        get_torch
 * Description  :        Allow players to try to get the torches from the
 *                       walls.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        0 always - they can't get it.
 */
public int
get_torch(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [burning] 'torch' [from] [the] [wall] [sconce]"))
    {
        return 0; /* The mudlib can handle this one easily. */
    }

    notify_fail("The torch is fastened to the sconce, and cannot be taken."
      + " You'll have to buy one back in town.\n");
    return 0;
} /* get_torch */
