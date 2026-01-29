/*
 * /d/Gondor/guilds/rangers/soul/rhear.c
 *
 * Included in the soul. Ability to hear into other rooms. Options are to
 * hear in a specified direction (including 'here'), where one can hear
 * the number and size of beings in that direction, with a small amount
 * of error based on the rhear skill, appraise monster skill and a
 * random factor. Nothing can be heard if there is fighting. If one omits 
 * the argument, all of the rooms will be listened to. However, if there
 * is fighting in any of the rooms, nothing will be heard at all. The size
 * of the beings will not be able to be determined either if listening to
 * all rooms around you.
 *
 * Originally coded by Elessar in May 1992
 *
 * TODO: The test_size() function needs to be worked on a little bit.
 *       Details are in the comments in the function.
 *
 * Modification log:
 *
 * 13 April 2001 Gwyneth: Recode and move. OK, so the code of the recode 
 *                        isn't that much nicer to read than the original 
 *                        version, but it does some things differently.
 *                        Among others, it checks rooms through doors. It
 *                        gives the direction of the things you hear when
 *                        you give no argument to rhear.
 */

#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define RHEAR_SKILL(x)  ((x)->query_skill(SS_HEARING))

mapping odd_dirs = ([ "up" : "above", "down" : "below", "out" : "outside", 
                      "in" : "inside" ]);
mapping dir_map = ([ "n" : "north", "s" : "south", "e" : "east", "w" : "west",
                     "nw" : "northwest", "ne" : "northeast", "d" : "down",
                     "sw" : "southwest", "se" : "southeast", "u" : "up" ]);

public int rhear(string str);
public string test_size(object monster);
public void info_one_dir(object room, string dir);
public int check_living_present(object room);
public int test_if_detect(object who);

/* Function name: rhear
 * Description  : Ability to hear into an adjacent room, or all the rooms
 *                around you if high enough skill.
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
rhear(string str)
{
    int    heard, index, size, j, total_heard;
    object room, *doors, *beings;
    string *adjacent_rooms = ({}), dirstr, *exit_arr = ({}), msg = "",
           *door_pass, *obv_exits;
    mapping exit_map = ([]);

    /* No rhear when the Ranger is fighting. */
    if (this_player()->query_attack())
    {
        notify_fail("You are too busy fighting!\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    room = environment(this_player());
    beings = FILTER_LIVE(all_inventory(room)) - ({ this_player() });
    beings = filter(beings, objectp @ &->query_attack());

    /* No rhear when there is fighting in the same room. */
    if (sizeof(beings))
    {
        notify_fail("Nothing can be heard above the clamour of the battle!\n");
        return 0;
    }

    /* Rhear in all the adjacent rooms. */
    if (!strlen(str))
    {
        if (room->query_prop(ROOM_I_INSIDE))
        {
            notify_fail("You must specify the direction you are " +
                "attempting to listen to when you are inside.\n");
            return 0;
        }

        if (RHEAR_SKILL(this_player()) < 60)
        {
            notify_fail("You do not yet have the skill. Specify the " +
                "direction you are attempting to listen to.\n");
            return 0;
        }

        write("You stretch yourself upon the ground, with your ear " +
            "pressed against the turf. There you lie motionless for a " +
            "while.\n");
        say(QCTNAME(this_player()) + " stretches " +
            this_player()->query_objective() + "self upon the ground, " +
            "pressing " + this_player()->query_possessive() + " ear to the " +
            "turf. There " + this_player()->query_pronoun() + " lies " +
            "motionless for some time.\n");

        exit_arr = room->query_exit_cmds();
        adjacent_rooms = room->query_exit_rooms();
        obv_exits = room->query_obvious_exits();

        if (sizeof(exit_arr))
            exit_map = mkmapping(exit_arr, adjacent_rooms);

        /* Find adjacent rooms through doors */
        if (sizeof( doors = filter(all_inventory(room), &operator(==)
          (DOOR_OBJECT) @ &function_exists("create_object", )) ))
        {
            /* This will make only one pass command be mapped
               to the door's other room. */
            for (index = 0, size = sizeof(doors); index < size; index++)
            {
                door_pass = doors[index]->query_pass_command();

                /* Let's find the best command to use. We don't want
                   to hear: You hear nothing from the w. You hear nothing
                   from the west. As some doors define both as pass cmds. */
                for (j = sizeof(door_pass) - 1; j >= 0; j--)
                {
                    if (member_array(door_pass[j], m_indexes(dir_map)) != -1)
                        door_pass -= ({ door_pass[j] });
                }

                exit_map += mkmapping(({ door_pass[0] }), 
                            ({ doors[index]->query_other_room() }));
                obv_exits += door_pass;
            }
                    
        }

        /* Since they are doing a generic rhear, do not show them the
           obvious exits. */
        exit_arr = m_indexes(exit_map);
        for (index = sizeof(exit_arr) - 1; index >= 0; index--)
        {
            if (member_array(exit_arr[index], obv_exits) == -1)
                exit_map = m_delete(exit_map, exit_arr[index]);
        }

        /* The new exit array */
        exit_arr = m_indexes(exit_map);
        
        /* This for loop goes through each adjacent room. It prints out
           a message for each direction with a small chance of inaccuracy.
           If there is fighting in any adjacent room, a message saying that
           the sound of fighting in that direction prevents you from hearing
           anything else. To find the size of the beings in adjacent rooms,
           one must rhear in that specific direction.
        */
        for (index = 0, size = sizeof(exit_arr); index < size; index++)
        {
            dirstr = (
                member_array(exit_arr[index], m_indexes(odd_dirs)) != -1 ? 
                odd_dirs[exit_arr[index]] : 
                "the " + exit_arr[index]);

            /* Make sure the room loads */
            if (catch(exit_map[exit_arr[index]]->teleledningsanka()))
            {
                msg += "You hear nothing from " + dirstr + ".\n";
                continue;
            }

            room = find_object(exit_map[exit_arr[index]]);

            if (!objectp(room))
            {
                msg += "You hear nothing from " + dirstr + ".\n";
                continue;
            }

            /* Find livings in adjacent room with a chance of inaccuracy. */
            heard = check_living_present(room);

            /* Keep track of total heard so that a single message can 
               be printed if there is nothing in any adjacent rooms.
            */
            total_heard += heard;

            switch(heard)
            {
            case 0:
                /* No livings in this adjacent room. */
                msg += "You hear nothing from " + dirstr + ".\n";
                break;

            case -1:
                /* Fighting in one adjacent room. Alert the Ranger to
                   this fact, and don't tell about any other room.
                */
                write("The sound of fighting from " + dirstr +
                    " prevents you from hearing anything else.\n");
                return 1;

            default:
                /* Let the Ranger know (with some error from
                 * check_living_present) the number of livings in 
                 * a certain direction.  */
                msg += "You think you hear the sound of " + LANG_WNUM(heard) + 
                    (heard > 1 ? " beings" : " being") + 
                    " from " + dirstr + ".\n";
                break;
            }
        }

        /* Nothing in any adjacent rooms */
        if (!total_heard)
            write("You hear only the sound of the grass growing and " +
                "the wind blowing.\n");
        else
            write(msg);

        this_player()->add_mana(-4);
        return 1;
    }

    if (str == "here")
    {
        this_player()->add_mana(-4);

        /* Give information about the livings in this room. */
        info_one_dir(room, str);
        return 1;
    }

    /* Allow the use of nw instead of northwest, for example. */
    if (member_array(str, m_indexes(dir_map)) != -1)
        str = dir_map[str];

    /* All possible exits in this room. */
    exit_arr = room->query_exit_cmds();

    adjacent_rooms = room->query_exit_rooms();

    if (sizeof(exit_arr))
        exit_map = mkmapping(exit_arr, adjacent_rooms);

    if (sizeof( doors = filter(all_inventory(room), &operator(==)
      (DOOR_OBJECT) @ &function_exists("create_object", )) ))
    {
        for (index = 0, size = sizeof(doors); index < size; index++)
        {
            door_pass = doors[index]->query_pass_command();
            exit_map += mkmapping(door_pass, 
                        ({ doors[index]->query_other_room() }));
        }
    }

    /* Does the entered string match an exit in this room? */
    index = member_array(str, m_indexes(exit_map));

    if (index == -1)
    {
        if (member_array(str, m_values(dir_map)) == -1)
        {
            /* Not a standard direction or an exit in this room. */
            write("You get confused, and can't seem to find that " +
                "direction.\n");
        }
        else
        {
            /* Standard direction, but not a usable one in this room. */
            write("You hear nothing there.\n");
        }

        return 1;
    }

    /* Make sure the room loads */
    if (catch(exit_map[str]->teleledningsanka()))
    {
        write("You hear nothing there.\n");
        return 1;
    }
    
    this_player()->add_mana(-4);

    /* Give information about the livings in the indicated direction. */
    info_one_dir(find_object(exit_map[str]), str);

    return 1;
}

/* Function name: test_size
 * Description  : Gives the size of the monster in question.
 * Arguments    : object monster
 * Returns      : string - The size of the monster in a descriptive format.
 */
public string
test_size(object monster)
{
    int livsize, detect, rhear, random_mod, seed;
    string sizestr;

    livsize = (monster->query_prop(OBJ_I_WEIGHT) +
               monster->query_prop(OBJ_I_VOLUME)) / 1900;

    /* Make it consistent for the monster, but give them a chance of
       succeeding, or not, on other monsters. */
    seed = atoi(OB_NUM(monster) + OB_NUM(this_player()));

    /* Higher rhear means more chance of random success. */
    rhear = RHEAR_SKILL(this_player());
    random_mod = 50 - random((rhear/2), seed);
    if (random_mod < 10)
        livsize += random_mod;
    else if (random_mod < 20)
        livsize -= random_mod;

    livsize = (livsize <= 0 ? 0 : livsize);

    /* Max of 100 (with max Ranger skills and 0 monster skills), 
       min of -100 resist (with 0 Ranger skills and 100 monster skills) */
    detect = ( rhear * 3 ) / 4;
    detect += this_player()->query_skill(SS_AWARENESS) / 3;
    detect -= ( monster->query_skill(SS_SNEAK) + 
               monster->query_skill(SS_HIDE) ) / 2;

    log_file("rhear", "Rhear skill: " + rhear + ", random_mod: " + random_mod +
        ", livsize: " + livsize + ", seed: " + seed + ", detect: " + detect +
        ".\n");
    switch(livsize)
    {
    case 0..50:
        sizestr = "tiny";
        detect -= 90;
        break;
    case 51..75:
        sizestr = "small";
        detect -= 60;
        break;
    case 76..100:
        sizestr = "medium sized";
        detect -= 30;
        break;
    case 101..150:
        sizestr = "normal sized";
        break;
    case 151..300:
        sizestr = "large";
        detect += 30;
        break;
    case 301..500:
        sizestr = "huge";
        detect += 60;
        break;
    default:
        sizestr = "gigantic";
        detect += 90;
        break;
    }

    if (detect > 0)
        return ("a " + sizestr + " " + monster->query_race_name());
    else 
        return ("something " + sizestr);

}

/* Function name: info_one_dir
 * Description  : Prints out information on the number and size of the
 *                the livings in a specified room with some chance of
 *                error.
 * Arguments    : object room - the room to test
 *                string dir - the direction listened in
 */
public void 
info_one_dir(object room, string dir)
{
    int index, size;
    mixed *beings = FILTER_LIVE(all_inventory(room)), *fighting;
    string dir_str, floor;

    beings -= ({ this_player(), 0 });
    if (dir == "here")
    {
        dir_str = dir;
        write("You concentrate, and listen for sounds here.\n");
    }
    else
    {
        floor = (room->query_prop(ROOM_I_INSIDE) ? "floor" : "turf");
        dir_str = (member_array(dir, 
                   m_indexes(odd_dirs)) != -1 ? odd_dirs[dir] : "the " + dir);
        write("You stretch yourself upon the ground, with your ear " +
            "pressed against the " + floor + ", listening for sounds from " + 
            dir_str + ".\n");
    }

    if (!sizeof(beings))
    {
        if (dir == "here")
            write("You hear nothing here, except your own breath.\n");
        else
            write("You hear nothing from " + dir_str + ".\n");

        return;
    }

    beings = filter(beings, test_if_detect);

    fighting = filter(beings, objectp @ &->query_attack());
    if (sizeof(fighting))
    {
        write("You hear the sounds of fighting!\n");
        return;
    }

    for (index = 0, size = sizeof(beings); index < size; index++)
        write("You hear " + test_size(beings[index]) + " moving.\n");

    return;
}

/* Function name: check_living_present
 * Description  : Checks on the livings in the indicated room and 
 *                returns a value based on what it finds with chance
 *                of error based on the skill.
 * Arguments    : object room - the room to test
 * Returns      : 0 - no livings in the room
 *               -1 - fighting in the room
 *               or number of livings detected in the room with some error
 */
public int 
check_living_present(object room)
{
    mixed *fighting,
          *beings = FILTER_LIVE(all_inventory(room));

    beings -= ({ this_player(), 0 });

    if (!sizeof(beings))
        return 0;

    beings = filter(beings, test_if_detect);

    /* This filters each element of the beings array through
       the equivalent of objectp(being[index]->query_attack()),
       basically finding an array of all livings in the room
       that are fighting. 
    */
    fighting = filter(beings, objectp @ &->query_attack());
    if (sizeof(fighting))
        return -1;
    else
        return (sizeof(beings));
}

/* Function name: test_if_detect
 * Description  : Checks if the living will be detected by the ranger
 * Arguments    : object who - the living to test
 * Returns      : 1 if detected, 0 if not
 */
public int 
test_if_detect(object who)
{
    int result, seed = atoi(OB_NUM(who) + OB_NUM(this_player()));

    /* Don't let them hear invisible wizards! */
    if (who->query_wiz_level() && who->query_invis())
        return 0;
    else
        result = (((who->query_prop(CONT_I_WEIGHT) / 1000) +
            RHEAR_SKILL(this_player())) - (random(20, seed) + 100 +
            who->query_skill(SS_HIDE)) / 10);

    result = (result > 0 ? 1 : 0);
    return result;
}

