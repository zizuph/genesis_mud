#pragma save_binary
#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include "defs.h"
#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include <language.h>

#define GURU_SAVE VAMP_LOG_DIR + "guru_trainees"
#define FOUND_GTRAIN_BUTTONS "_found_gtrain_buttons"
#define FOUND_GTRAIN_DOOR    "_foudn_gtrain_door"
#define COMBINATION ({ 2, 4, 1, 0 })

object *guru_trainees = ({});

static string *buttons_pushed = ({});

int is_guru_trainee(object who);

/* The light in this room never changes */
/*
void update_light(int recursive) { }

void update_internal(int l, int w, int v)
{
    ::update_internal(0, w, v);
}
*/

int search_time()
{
    if (is_guru_trainee(this_player()))
    {
       return 0;
    }

    return (this_player()->query_skill(SS_AWARENESS) + 
            this_player()->query_stat(SS_INT) + 
            this_player()->query_stat(SS_WIS)) / 25;
}

/* This isn't worth a quest bit, so I'll just use a simple
 * little system to save the names of the people who find
 * their way through this room.
 */
void load_guru_trainees()
{
    restore_object(GURU_SAVE);

    if (!guru_trainees)
    {
        guru_trainees = ({});
    }

    filter(guru_trainees, &call_other(SECURITY, "exist_player"));
    save_object(GURU_SAVE);
}

void add_guru_trainee(object who)
{
    guru_trainees += ({ who->query_real_name() });
    save_object(GURU_SAVE);
}

int is_guru_trainee(object who)
{
    return (member_array(who->query_real_name(), guru_trainees) >= 0);
}

void load_door()
{
    object door;

    setuid();
    seteuid(getuid());

    door = clone_object(DOOR_OBJECT);

    door->set_door_name("door");
    door->set_open(0);
    door->add_name("gdoor");
    door->add_name("door");
    door->set_door_id("gdoor");
    door->set_open_desc("An open door.\n");
    door->set_closed_desc("A closed door.\n");
    door->set_locked(1);
    door->set_no_pick();
    door->set_pass_command(({ "north", "n", "enter door" }));
    door->set_fail_open(({ "The door is already open.\n", "You can't seem to " +
                           "find a way to open it!\n"}));
    door->move(this_object(), 1);
}

void create_vamp_room()
{
    set_short("Dark archway");
    set_long("An extremely dark archway.  It is impossible " +
        "to make out anything here.\n");

    add_prop(ROOM_I_LIGHT, -99);

    add_prop(OBJ_I_SEARCH_TIME, search_time);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_item("door", "");
    add_item(({ "buttons", "indentations" }), "");
    add_item(({ "arch", "archway" }), "");

    add_exit("train", "east");

    load_guru_trainees();

    load_door();
}

string reveal_door()
{
    this_player()->add_prop(FOUND_GTRAIN_DOOR, 1);
    return "You feel around in the dark, and finally find " +
        "a door at the north end of the passage.\n";
}

string reveal_buttons()
{
    this_player()->add_prop(FOUND_GTRAIN_BUTTONS, 1);
    return "Next to the door, you feel a " +
        "series of indentations.\n";
}

string reveal_buttons2()
{
    return "You feel six small buttons lined up vertically.\n";
}

string search_door()
{
    return "Feeling along the surface of the door, you find no " +
        "knob or key hole.\n";
}

string do_search(object who, string str)
{
    set_this_player(who);

    if ((str == "buttons") || (str == "indentations"))
    {
        if (is_guru_trainee(who))
        {
            return reveal_buttons2();
        }

        if (who->query_prop(FOUND_GTRAIN_BUTTONS) ||
            ((who->query_skill(SS_AWARENESS) > 80) &&
            (who->resolve_task(TASK_FORMIDABLE,
            ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0)))
        {
            add_guru_trainee(who);
            return reveal_buttons2();
        }

        return "";
    }

    if (str == "door")
    {
        if (is_guru_trainee(who))
        {
            return search_door() + reveal_buttons();
        }

        if (!who->query_prop(FOUND_GTRAIN_DOOR))
        {
            return "";
        }

        if ((who->query_skill(SS_AWARENESS) > 70) &&
            (who->resolve_task(TASK_DIFFICULT,
            ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0))
        {
            return search_door() + reveal_buttons();
        }

        return search_door();
    }

    if (member_array(str, ({ "here", "room", "arch", "archway" })) < 0)
    {
        return "";
    }

    if (is_guru_trainee(who))
    {
        return "";
    }

    if ((who->query_skill(SS_AWARENESS) > 80) &&
        (who->resolve_task(TASK_FORMIDABLE,
        ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0))
    {
        return reveal_door() + reveal_buttons();
    }
    else if ((who->query_skill(SS_AWARENESS) > 50) &&
        (who->resolve_task(TASK_DIFFICULT,
        ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0))
    {
        return reveal_door();
    }

    return "";
}

void reset_buttons()
{
    buttons_pushed = ({});
}

void open_door()
{
    write("The door slides open from the bottom, and you pass through.\n");
    this_player()->move_living(" through the doorway", GRAVEYARD_DIR + "gtrain", 1);
}

int push(string str)
{
    string *num = ({ "one", "two", "three", "four", "five", "six" });
    string *ordnum = ({ "first", "second", "third", "fourth", "fifth", "sixth" });
    string which;
    int i;

    notify_fail(capitalize(query_verb()) + " what?\n");

    if (!strlen(str))
    {
        return 0;
    }

    if ((parse_command(str, ({}), "[the] %s 'button' / 'indentation'", which) &&
        ((i = member_array(which, ordnum)) >= 0)) ||
        (parse_command(str, ({}), "'button' / 'indentation' %s", which) &&
        (((i = member_array(which, num)) >= 0) || 
        ((i = LANG_NUMW(which) - 1) >= 0))))
    {
        if (!is_guru_trainee(this_player()))
        {
            if (!this_player()->query_prop(FOUND_GTRAIN_BUTTONS))
            {            
                return 0;
            }

            write("You can't make out the buttons well enough without " +
                "examining them more carefully.\n");
            return 1;
        }

        buttons_pushed += ({ i });

        write("You press the " + ordnum[i] + " button.\n");

        if (sizeof(buttons_pushed) == sizeof(COMBINATION))
        {
            for (i = 0; i < sizeof(buttons_pushed); i++)
            {
                if (buttons_pushed[i] != COMBINATION[i])
                {
                    reset_buttons();
                    write("You hear a quiet click.\n");
                    return 1;
                }
            }

            reset_buttons();
            open_door();
        }

        return 1;        
    }

    return 0;
}

// We want to be able to search some things in the dark
int search(string str)
{
    if (!strlen(str))
    {
        str = "here";
    }

    if ((str == "here") || item_id(str) ||
        (sscanf(str, "here for %s", str) && item_id(str)))
    {
        write("You start to search.\n");
        search_object(str);
        return 1;
    }

    return 0;
}

void init()
{
    ::init();
    reset_buttons();
    add_action(search, "search");
    add_action(push, "push");
    add_action(push, "press");
}
