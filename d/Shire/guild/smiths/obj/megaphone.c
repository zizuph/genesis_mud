
/*

  Blacksmith Design Contest Winner - Designed by Nome

  Megaphone works like shout but goes two rooms and tells
  which direction the person is projecting from.
  Great for teams who get lost or taunting your enemy from afar.

  Code mainly snarfed from 'shout'.

  Palmer 2006-Aug-3

*/

inherit "/cmd/std/command_driver";
inherit "/std/object";
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <flags.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#define DEPTH 2


create_object()
{
    set_name("megaphone");
    set_short("iron megaphone");
    set_long("This conical shaped iron megaphone will let you <project> your voice very far. It has a leather strap attached to it for easy carrying.\n");
    
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_M_NO_SELL, "You wouldn't dare. This item is unique.\n");
    seteuid(getuid(this_object()));
}

void
init()
{
    add_action("do_project", "project");
    ::init();
}


/* **************************************************************************
 * project_name
 */

/*
 * Function name: project_name
 * Description  : Called through VBFC to find the name/description of the
 *                person who does the projecting.
 * Returns      : string - the name/description of the living.
 */
string
project_name()
{
    object pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == VBFC_OBJECT)
    {
        pobj = previous_object(-1);
    }
    if (pobj->query_met(this_player()))
    {
        return this_player()->query_name();
    }
    return capitalize(LANG_ADDART(this_player()->query_gender_string())) +
        " " + this_player()->query_race_name() + " voice";
}


int
do_project(string str)
{
    object *rooms;
    object troom;
    object *oblist;
    string cap_str, *to_room_files, *room_files, direction;
    mixed  tmp;
    int    use_target = 0;
    int    index;
    int    size;
    int    i, sz, dir;
    string preposition;

    if (!strlen(str))
    {
        notify_fail("Project what?\n", 0);
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot use the megaphone.\n");
        return 1;
    }
 
    if ((strlen(str) > 60) &&
        (!this_player()->query_wiz_level()) &&
        (!this_player()->query_npc()))
    {
        notify_fail("Even this megaphone is not big enough to project all that.\n");
        return 0;
    }

    /* Note that [at][to] in a beautiful way tests both 'at' and 'to', while
     * wildmatch normally tests per letter, and not per word! */   
    if (wildmatch("[at][to] *", str))
    {
        preposition = extract(str, 0, 1);
        /* Project at all people. */
        /* We already tested for at/to, so no repeat check necessary. */
        if (wildmatch("?? all *", str))
        {
            str = extract(str, 7);
            oblist =
                FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
        }
        /* Project to my team. */
        else if (wildmatch("?? team *", str))
        {
            str = extract(str, 8);
            oblist = this_player()->query_team_others() &
                all_inventory(environment(this_player()));
        }
        /* Find out who we project to. */
        else if (parse_command(lower_case(cap_str = str),
            environment(this_player()), "[at] [to] [the] %i %s", oblist, str))
        {
            str = extract(cap_str, -(strlen(str)));
            oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player() });
        }
    }

    if (pointerp(oblist) && !sizeof(oblist))
    {
        notify_fail("Project [what] at/to whom?\n");
        return 0;
    }

    /* Sanity check. */
    if (!(troom = environment(this_player())))
    {
        return 0;
    }

    room_files = environment(this_player())->query_exit_rooms();
    rooms = FIND_NEIGHBOURS(troom, DEPTH);

    index = -1;
    size = sizeof(rooms);
    // Default in case we can't figure out common exits
    direction = "nearby";
    while(++index < size)
    {
        to_room_files = rooms[index]->query_exit();


        // One room away
        dir = member_array(file_name(environment(this_player())), to_room_files);
        if (dir != -1)
                direction = to_room_files[dir + 1]; 
        else 
        {
            // Two rooms away
            for (i = 0, sz = sizeof(room_files); i < sz; i++)
            {
                dir = member_array(room_files[i], to_room_files);
                if (dir != -1)
                    direction = to_room_files[dir + 1]; 
            }
        }

        tell_room(rooms[index], "@@project_name:" + file_name(this_object()) + "@@" + " projects from the " + direction + ": " + str + "\n", this_player());
    }

    if (sizeof(oblist))
    {
        if (this_player()->query_option(OPT_ECHO))
            actor("You project " + preposition, oblist, ": " + str);
        else
            write("Ok.\n");
        all2act(" projects " + preposition, oblist, ": " + str);
        target(" projects " + preposition + " you: " + str, oblist);
    }
    else
    {
        all(" projects: " + str);
        if (this_player()->query_option(OPT_ECHO))
            write("You project: " + str + "\n");
        else
            write("Ok.\n");
    }

    return 1;
}

