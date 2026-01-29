/*
 *  /d/Sparkle/area/city/rooms/inside/enchanter_forge.c
 *
 *  This room is where players who have solved the Enchanter Quests
 *  are allowed to craft imbuements using the imbuement stones they
 *  have collected.
 *
 *  Created January 2010, by Cooper Sherry (Gorboth)
 *  Updated March 2017, by Tim Breen (Mirandus) to add a no steal property.
 *  
 *  2017-12-20 - Cotillion
 *  - Fixed find_stone when the stone had been removed.
 *  2018-01-12 - Gorboth
 *  - Implemented features for the rollback of ironstones.
 *  2021-01-30 - Arman
 *  - Reversed rollback of ironstones.
 * 
 */
#pragma strict_types

inherit "/std/room";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Genesis/imbuement/imbuement.h"


/* Prototypes */
public void        create_room();
public int         check_exit();
public int         climb_stairs(string arg);
public void        init();
public string      exa_device();
public string      exa_socket();
public int         pry_socket(string arg);
public void        return_stone(object who);
public int         fit_socket(string arg);
public mixed      *find_stone(object who);
public int         do_insert(string arg);
public int         stone_power_lvl(object stone);
public void        leave_inv(object ob, object to);

/* Global Variables */


/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    object  codex;

    set_short("within the enchanter's forge");
    set_long("You stand within a long stone chamber whose low ceiling"
      + " hangs heavily over many alcoves along the walls. Within each"
      + " alcove, a strange device of some kind has been placed. A"
      + " spiral staircase leads up through the ceiling beside a doorway"
      + " which leads west. A leather-bound codex rests upon a"
      + " pedestal.\n\n");

    add_item( ({ "door", "doorway", "west" }),
        "The doorway leads west into a small room.\n");
    add_item( ({ "small room" }),
        "You'd need to go there yourself for a closer look.\n");
    add_item( ({ "room", "here", "area", "chamber", "stone chamber",
                 "long chamber", "long stone chamber", }),
        "This must be the enchanter's forge. You see many devices along"
      + " the walls in which one might attempt to craft enchantments.\n");
    add_item( ({ "wall", "walls" }),
        "The walls are broken up by many alcoves, all of which house"
      + " device of some sort.\n");
    add_item( ({ "ceiling", "roof", "low ceiling", "low roof" }),
        "The low gives the room a rather cramped feeling.\n");
    add_item( ({ "alcove", "alcoves", "many alcoves" }),
        "Each alcove houses a strange device. There are dozens of them"
      + " here.\n");
    add_item( ({ "stair", "stairs", "staircase", "step", "steps",
                 "stairway", "spiral stair", "spiral staircase" }),
        "The staircase leads back up to the Enchanter's Shop.\n");
    add_item( ({ "shop", "enchanters shop", "enchanter's shop" }),
        "The shop is above you. You could climb the stairs to return"
      + " there.\n");
    add_item( ({ "enchanter", "karkadelt" }),
        "He is most likely above in the shop.\n");
    add_item( ({ "ground", "floor", "down" }),
        "The ground here is nothing more than a dirt floor.\n");
    add_item( ({ "dirt", "dirt floor" }),
        "No need to sweep in here, at least.\n");
    add_item( ({ "fuel", "unknown fuel", "furnace", "base" }),
        "The base of each device is comprised of a furnace that burns"
      + " hotly with some unknown fuel.\n");
    add_item( ({ "opening", "large opening" }),
        "The opening on the front of each device would allow you to <insert>"
      + " an object of your choice.\n");
    add_item( ({ "device", "strange device", "devices",
                 "strange devices", "forge", "forges" }),
        "@@exa_device@@");
    add_item( ({ "socket", "sockets" }),
        "@@exa_socket@@");

    add_cmd_item( ({ "floor", "ground", "dirt", "dirt floor" }),
                  ({ "sweep" }),
        "No need!\n");
    add_cmd_item( ({ "enchantment", "imbuement", "enchantments",
                     "imbuements" }),
                  ({ "craft" }),
        "There are very specific methods one must use. Perhaps you know"
      + " what they are?\n");
    add_cmd_item( ({ "pedestal" }),
                  ({ "search" }),
        "You give the pedestal a thorough examination. Other than the"
      + " codex resting upon it, there is nothing particularly interesting"
      + " about it.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    /* I do not want people to feel endangered by would-be stone
     * snatchers.
     */
    add_prop(ROOM_M_NO_ATTACK,
        "Some strange and powerful enchantment must exist here! It seems"
      + " that no matter how you try, your hostile actions die within"
      + " your mind as soon as they are formed.\n");
    
    add_prop(ROOM_M_NO_STEAL,
        "Just as you are reaching out to pilfer you ill-begotten goods,"
      + " you feel as though your hand is slapped by some invisible force."
      + " There must be some powerful enchantments in this room to prevent"
      + " such an action.\n");

    add_exit("/d/Sparkle/area/city/rooms/inside/enchanter", "up",
              check_exit, 1, 0);
    add_exit("/d/Sparkle/area/city/rooms/inside/enchanter_bedroom", "west",
              check_exit, 1, 0);

    room_add_object("/d/Sparkle/area/orc_temple/obj/enchanter_codex");

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        make sure the player doesn't leave with a
 *                       stone in one of the devices
 * Returns      :        0 - always
 */
public int
check_exit()
{
    return_stone(this_player());
    return 0;
} /* check_exit */


/*
 * Function name:        climb_stairs
 * Description  :        Let players climb the stairs
 * Arguments    :        What the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [dark] 'stair' / 'stairs' / 'stairway'"))
    {
        notify_fail("Do you want to climb up the stairs perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("Normally, we would move the player 'up' here using"
          + " command(). Since you're a wizard, that won't work. You can"
          + " simply type <up> manually to use the stairs.\n");
        return 0;
    }

    this_player()->command("$u");
    return 1;
} /* climb_stairs */


/*
 * Function name:        init
 * Description  :        add some actions to the player 
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
    add_action(fit_socket, "fit");
    add_action(pry_socket, "pry");
    add_action(do_insert, "insert");
} /* init */


/*
 * Function name:        exa_device
 * Description  :        Allow players to examine the devices
 * Returns      :        string - the description
 */
public string
exa_device()
{
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[1];

    if (!stone)
    {
        return "There are many devices here, and all appear completely"
          + " identical. Cube-like in shape, they contain a small furnace"
          + " at the base, which is burning with some unknown fuel. Above"
          + " this, a large opening that faces outward would allow"
          + " you to <insert> an item of your choice. The top of each device"
          + " contains a single empty socket into which it looks as if"
          + " you could <fit> something.\n";
    }

    return "This device looks exactly like the others in the room except"
      + " for the fact that you have fitted " + LANG_ADDART(stone)
      + " into the socket at the top. Above the small furnace at the"
      + " base of the device is a large opening into which you could"
      + " probably <insert> an object of your choosing.\n";
} /* exa_device */


/*
 * Function name:        exa_socket
 * Description  :        Show players a description of the
 *                       sockets, with state-dependant results.
 * Returns      :        string - the description
 */
public string
exa_socket()
{
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[1];

    if (!stone)
    {
        return "You examine the socket on one of the devices. It looks"
          + " as if you could <fit> something into it.\n";
    }

    return "You see your " + stone + " fit into the socket atop the"
      + " device nearest to you. You could <pry> the stone from the"
      + " socket if you wished to get it back.\n";
} /* exa_socket */


/*
 * Function name:        pry_socket
 * Description  :        allow players to get their stone back from the
 *                       socket if they so choose.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
pry_socket(string arg)
{
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[0];
    string   stone_name = stone_vars[1];

    if (!stone)
    {
        return 0; /* Nothing to pry! */
    }

    if (!strlen(arg))
    {
        notify_fail("Pry what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] '" + stone_name + "' / 'stone' [from] [the] [socket]"))
    {
        notify_fail("Do you wish to pry something from the socket?\n");
        return 0;
    }

    /* sanity check */
    if (!present(stone, this_player()))
    {
        notify_fail("That's strange. The " + stone_name + " doesn't seem"
          + " to be there any longer!\n");

        this_player()->remove_prop(CRAFT_STATUS);
        return 0;
    }

//    write_file(IMBUE_LOG_DIR + "craft_stones", 
//        TIME2FORMAT(time(), "mm/dd/yyyy")
//      + " (" + ctime(time())[11..18] + ") "
//      + capitalize(this_player()->query_name())
//      + " pries " + LANG_ADDART(stone_name) + " in the forge.\n");

    IMBUE_LOGGER->log("craft_stones", capitalize(this_player()->query_name())
        + " pries " + LANG_ADDART(stone_name) + " from the forge.");

    return_stone(this_player());
    return 1;
} /* pry_socket */


/*
 * Function name:        return_stone
 * Description  :        "remove" the stone the player has fit into one
 *                       of the sockets.
 * Arguments    :        object who - this_player()
 */
public void
return_stone(object who)
{
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[0];
    string   stone_name = stone_vars[1];

    /* sanity check */
    if (!present(stone, who))
    {
        this_player()->remove_prop(CRAFT_STATUS);
        return;
    }

    who->catch_tell("You carefully pry your " + stone_name + " out of"
      + " the socket and take it with you.\n");
    tell_room(this_object(), QCTNAME(who) + " pries something out of the"
      + " top of one of the devices.\n", who);

    //write_file(IMBUE_LOG_DIR + "craft_stones", 
    //    TIME2FORMAT(time(), "mm/dd/yyyy")
    //  + " (" + ctime(time())[11..18] + ") "
    //  + capitalize(this_player()->query_name())
    //  + " recovers " + LANG_ADDART(stone_name) + " from the device.\n");

    IMBUE_LOGGER->log("craft_stones", capitalize(this_player()->query_name())
        + " recovers " + LANG_ADDART(stone_name) + " from the device.");
    stone->set_no_show_composite(0);
    stone->set_in_socket(0);
    who->remove_prop(CRAFT_STATUS);
} /* return_stone */


/*
 * Function name:        fit_socket
 * Description  :        Allow players to try to fit tears into the
 *                       sockets.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
fit_socket(string arg)
{
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[0];
    string   stone_name = stone_vars[1];
    object  *obj;
    string   word;

    if (!stringp(arg) || !strlen(arg))
    {
        notify_fail("Fit what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i 'in' / 'into' [to] [the] 'socket' / 'sockets'", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
        "[the] 'socket' / 'sockets'"))
        {
            notify_fail("Fit what into the socket?\n");
            return 0;
        }

        if (parse_command(arg, all_inventory(this_player()),
            "[the] %i 'in' / 'into' [to] [the] [strange] 'device'", obj) ||
            !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
        {
            notify_fail("Fit something into the socket, perhaps?\n");
            return 0;
        }

        if (parse_command(arg, ({}),
            "[the] %w 'in' / 'into' [to] [the] 'socket' / 'sockets'", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("Fit what into where?\n");
        return 0;
    }

    if (!obj[0]->id(STONE_NAME))
    {
        notify_fail("That does not seem to fit into the socket.\n");
        return 0;
    }

    if (obj[0]->query_in_socket())
    {
        notify_fail("It is already fitted into the socket!\n");
        return 0;
    }

    if (stone)
    {
        notify_fail("You've already fitted " + LANG_ADDART(stone_name)
          + " into the socket. You'd need to <pry> it out first to"
          + " make room.\n");
        return 0;
    }

    if (obj[0]->id("nullstone"))
    {
        notify_fail("The nullstone looks too small to fit into the"
          + " socket.\n");
        return 0;
    }

    stone_name = obj[0]->query_stone_type();

    if (!stone_power_lvl(obj[0]))
    {
        notify_fail("The " + stone_name + " almost fits into the"
          + " socket, but does not appear to be of sufficient quality."
          + " It does not fit well enough to snap into place.\n");
        return 0;
    }

/*
    if (obj[0]->id("ironstone"))
    {
        notify_fail("A pulse of energies washes over your mind, and"
          + " you suddenly hear the voice of Karkadelt: \"Yes, I"
          + " see you are attempting to use an ironstone in"
          + " one of my forges. I fear that will not be"
          + " possible. That particular stone type has become"
          + " highly unstable, and is no longer able to be used"
          + " in crafting. Bring it to me and I will be happy"
          + " to <trade> you for a new stone of your choice.\"\n");
        return 0;
    }
*/

    write("You fit your " + stone_name + " into the socket of the"
      + " nearest device. It pushes in with a loud 'snap!'\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " takes " + LANG_ADDART(stone_name)
      + " and fits it into the socket atop one of the devices with"
      + " a loud 'snap!'\n", this_player());

    this_player()->add_prop(CRAFT_STATUS, file_name(obj[0]));
    obj[0]->set_no_show_composite(1);
    obj[0]->set_in_socket(1);

    //write_file(IMBUE_LOG_DIR + "craft_stones", 
    //    TIME2FORMAT(time(), "mm/dd/yyyy")
    //  + " (" + ctime(time())[11..18] + ") "
    //  + capitalize(this_player()->query_name())
    //  + " fits " + LANG_ADDART(stone_name) + " into a device.\n");

    IMBUE_LOGGER->log("craft_stones", capitalize(this_player()->query_name())
        + " fits " + LANG_ADDART(stone_name) + " into a device.");

    return 1;
} /* fit_socket */


/*
 * Function name:        find_stone
 * Description  :        set up some values based on whether or not
 *                       the player has fit a stone into a socket.
 * Arguments    :        object who - the player
 * Returns      :        mixed array: 0 - the stone object
 *                                    1 - the stone name
 */
public mixed *
find_stone(object who)
{
    string   stone = this_player()->query_prop(CRAFT_STATUS);
    object   stone_obj;

    if (stringp(stone)) 
    {
        stone_obj = find_object(stone);
    }

    if (!objectp(stone_obj))
    {
        return ({ 0, 0 });
    }

    return ({ stone_obj, stone_obj->query_stone_type() });
} /* find_stone */


/*
 * Function name:        do_insert
 * Description  :        Allow players to insert something into the
 *                       device, imbueing it if there is a stone in
 *                       the socket, and the object is of a type that
 *                       can accept imbuements.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_insert(string arg)
{
    object   obj;
    mixed   *stone_vars = find_stone(this_player());
    mixed    stone = stone_vars[0];
    string   stone_name = stone_vars[1];
    int      stone_lvl;
    mapping  imbuements;
    string   mod;
    int      is_armour_mod;
    int      is_weapon_mod;
    int      is_wearable;
    int      is_weapon;
    int      id;

    /* Special note: We are going to avoid notify_fail here with a return
     * of 0 so that people with other objects that call for an <insert>
     * verb are not confounded. Normally, this is very bad practice, but
     * for this specific room, the evil proves worthwhile.
     */

    if (!strlen(arg))
    {
        write("Insert what?\n");
        return 1;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o [in] [into] [the] [enchanter] [enchanters] [enchanter's]"
      + " [strange] [large] 'forge' / 'device' / 'opening'", obj))
    {
        write("Do you want to <insert> something into the device,"
          + " perhaps?\n");
        return 1;
    }

    if (obj->id(STONE_NAME))
    {
        write("Perhaps you wish to <fit> the stone into a socket"
          + " on one of the devices?\n");
        return 1;
    }

    if (obj->query_prop(HEAP_I_IS))
    {
        write("That object doesn't seem to belong in the forge.\n");
        return 1;
    }

    if (!this_player()->query_prop(CRAFT_STATUS))
    {
        write("You insert the " + obj->short() + " into the forge, but"
          + " nothing seems to happen.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());

        return 1;
    }

    if (obj->query_prop(IMBUE_SHORT))
    {
        write("The " + obj->short() + " has already been imbued, and will"
          + " accept no further enchantment.\n");

        return 1;
    }

    is_wearable = obj->query_wearable_item();
    is_weapon = obj->check_weapon();

    if (!IS_WEAPON_OBJECT(obj) &&
        !IS_ARMOUR_OBJECT(obj))
    {
        write("You insert the " + obj->short() + " into the forge, and"
          + " the " + stone_name + " in the socket turns momentarily"
          + " black. Nothing else happens.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());

        return 1;
    }

    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("It is broken, and doesn't seem to fit into the forge.\n");

        return 1;
    }

    if (IS_HEAP_OBJECT(obj))
    {
        write("That item is all heaped together, and doesn't seem to"
          + " be something you can insert into the forge.\n");

        return 1;
    }

    if (obj->query_auto_load() ||
        obj->query_prop(OBJ_M_NO_DROP))
    {
        write("That item looks a bit too important to try to"
          + " enchant.\n");

        return 1;
    }

    stone_lvl = stone_power_lvl(stone);

    /* This should never be possible, but just in case ... */
    if (!stone_lvl)
    {
        write("You insert the " + obj->short() + " into the forge, and"
          + " the " + stone_name + " in the socket vibrates violently"
          + " and pops out of its socket! You catch the stone before it"
          + " hits the floor.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, and something"
          + " pops out of the top of the device, which "
          + this_player()->query_pronoun() + " catches before it hits"
          + " the ground.\n", this_player());

        stone->set_no_show_composite(0);
        stone->set_in_socket(0);
        this_player()->remove_prop(CRAFT_STATUS);
        return 1;
    }

    imbuements = IMBUE_GENERATOR->query_stone_results();
    mod = imbuements[stone_name];

    if (IMBUE_GENERATOR->disabled(mod))
    {
        write("You insert the " + obj->short() + " into the forge, and"
          + " the " + stone_name + " in the socket produces a strange"
          + " hissing sound. Nothing else happens.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());

        return 1;
    }


    is_weapon_mod = IN_ARRAY(mod, IMBUE_GENERATOR->query_mods_weapon());
    is_armour_mod = IN_ARRAY(mod, IMBUE_GENERATOR->query_mods_armour());

    if ((IS_ARMOUR_OBJECT(obj)   && !is_armour_mod) ||
        (IS_WEAPON_OBJECT(obj)   && !is_weapon_mod))
    {
        write("You insert the " + obj->short() + " into the forge, and"
          + " the " + stone_name + " in the socket turns momentarily"
          + " red. Nothing else happens.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());

        return 1;
    }

    id = IMBUE_GENERATOR->imbue(obj, mod, stone_lvl);


    // Temporary commented this one out for later investigations on why shadows
    // don't stick on some items.
    /*if (IMBUE_GENERATOR->get_error()) {
        write("You insert the " + obj->short() + " into the forge, and"
          + " the " + stone_name + " in the socket turns momentarily"
          + " yellow. Nothing else happens.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " inserts " + LANG_ADDART(obj->short())
          + " into the strange device, but nothing"
          + " seems to happen.\n", this_player());
          return 1;
    }*/

    // Turned 'yellow' to black as a quick fix, instead of altering the codex.
    if (IMBUE_GENERATOR->get_error()) {
        write("You insert the " + obj->short() + " into the forge, and"
            + " the " + stone_name + " in the socket turns momentarily"
            + " black. Nothing else happens.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
            + " inserts " + LANG_ADDART(obj->short())
            + " into the strange device, but nothing"
            + " seems to happen.\n", this_player());
        return 1;
    }

    write("As you insert the " + obj->short() + " into the forge,"
      + " the " + stone_name + " melts into the device. There is"
      + " a powerful flash of light, and as you draw the object back"
      + " out, it appears to have been transformed somehow!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " inserts " + LANG_ADDART(obj->short()) 
      + " into the strange device. There is a powerful" 
      + " flash of light, and the object appears to have been transformed"
      + " somehow!\n", this_player());

    //write_file(IMBUE_LOG_DIR + "imbue_craft", 
    //    TIME2FORMAT(time(), "mm/dd/yyyy")
    //  + " (" + ctime(time())[11..18] + ") "
    //  + capitalize(this_player()->query_name())
    //  + " crafts an imbuement:\n\t"
    //  + obj->short() + ": " + file_name(obj) + "\n\t"
    //  + "mod: " + mod + "\n\t"
    //  + "power level: " + stone_lvl + "\n");

    IMBUE_LOGGER->log("craft_stones", capitalize(this_player()->query_name())
        + " crafts an imbuement:\n\t"
        + obj->short() + ": " + file_name(obj) + "\n\t"
        + "ID: " + id + "\n\t"
        + "mod: " + mod + "\n\t"
        + "power level: " + stone_lvl);

    this_player()->remove_prop(CRAFT_STATUS);

    stone->remove_object();
    return 1;
} /* do_insert */


/*
 * Function name:        stone_power_lvl
 * Description  :        Determine the power level of a stone based
 *                       on its quality level
 * Arguments    :        object stone - the stone object
 * Returns      :        int 0 - if "cracked" or "blemished"
 *                           1 - if "ordinary"
 *                           2 - if "unblemished"
 *                           3 - if "glittering"
 */
public int
stone_power_lvl(object stone)
{
    switch(stone->query_stone_quality())
    {
        case "ordinary":
            return 1;
            break;
        case "unblemished":
            return 2;
            break;
        case "glittering":
            return 3;
            break;
        default:
            return 0;
            break;
    }

    /* Should never happen, but just in case. */
    return 0;
} /* stone_power_lvl */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this container or
 *                       when an object is about to change its weight,
 *                       volume, or light status.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: where it went
 *
 * We make sure players grab a stone from a socket if they are teleported
 * out.
 */
public void
leave_inv(object ob, object to)
{
    if (ob->query_prop(CRAFT_STATUS))
    {
        return_stone(ob);
    }

    ::leave_inv(ob, to);

    return;
} /* leave_inv */
