#pragma strict_types
 
inherit "/std/object";
 
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <wa_types.h>
 
#undef CAN_SEE_IN_ROOM
#define CAN_SEE_IN_ROOM(ob, ob2) (ob2 && ob2->query_prop(OBJ_I_LIGHT) > \
    ob->query_prop(LIVE_I_SEE_DARK))
#define TEMP_WINDOW_CHECKED "_temp_window_checked_"
 
static mixed other_window_room;
 
static int window_vals;
 
static mixed curtains,
             window_desc;
 
static object other_window;
 
/*
 * Function name: set_temp
 * Description:   set a 'no parse' prop, so only one window parses.
 */
private void
set_temp()
{
    object ob;
    ob = this_player();
    ob->add_prop(TEMP_WINDOW_CHECKED, 1);
    set_alarm(0.0, 0.0, &ob->remove_prop(TEMP_WINDOW_CHECKED));
}
 
/*
 * Function name: filter_no_see
 * Description:   get a list of objects who cannot see us, to exclude
 * Arguments:     ob - the object watching, see_who - the watched.
 * Returns:       1 if ob cannot see see_who
 */
public int
filter_no_see(object ob, object see_who)
{
    if (!living(ob))
        return 0;
    if (ob == see_who)
        return 1;
    return !CAN_SEE(ob, see_who);
}
 
/*
 * Function name: tell_viewers
 * Description:   Tell everyone who can see about something.
 * Arguments:     in_obj - the room to tell, arg - what to say
 *                about_obj - who this is about
 */
public void
tell_viewers(object in_obj, string arg, object about_obj = this_player())
{
    tell_room(in_obj, arg, filter(all_inventory(in_obj),
        &filter_no_see(, about_obj)));
}
 
/*
 * Function name: set_window_desc
 * Description:   set what this window will look like in the room
 * Arguments:     arg - the string to show with 'look'
 */
public void
set_window_desc(mixed arg)
{
    window_desc = arg;
}
 
/*
 * Function name: find_other_window
 * Description:   set the other_window variable properly
 * Returns:       no return, but throws an error if no other window.
 */
public void
find_other_window()
{
    object ob;
 
    if (objectp(other_window))
        return;
 
    reset_euid();
 
    if (!objectp(other_window_room))
        ob = find_object(other_window_room);
    else
        ob = other_window_room;
    if (!objectp(ob))
    {
        other_window_room->load_it();
        ob = find_object(other_window_room);
        if (!objectp(ob))
            throw("Could not load other window!\n");
    }
    ob = present("_window_to_" + MASTER_OB(environment()), ob);
    if (!objectp(ob))
        throw("Could not find other window!\n");
    other_window = ob;
    return;
}
 
/*
 * Function name: add_curtain
 * Description:   set some type of blockage for looking through
 * Arguments:     block_val - int, function, or vbfc -- if final
 *                val is 1, player cannot look into room with this
 *                window. Other window must set curtain for two
 *                way block
 */
public void
add_curtain(mixed block_val)
{
    curtains = block_val;
}
 
/*
 * Function name: view_from_window
 * Description:   Show us something from the other side
 * Arguments:     view_room - the room we are looking in from
 * Returns:       A description, including items in room.
 */
public string
view_from_window(mixed view_room)
{
    string ret, tmp;
    object *ob;
    mixed cur;
 
    cur = check_call(curtains);
    if (cur)
        if (stringp(cur))
            return cur;
        else
            return "You can't see anything. Something on the other " +
                "side is blocking your view.\n";
 
    reset_euid();
    if (view_room->query_prop(OBJ_I_LIGHT) >= environment()->
        query_prop(OBJ_I_LIGHT))
        tell_viewers(environment(), "You see " + QTNAME(this_player()) +
            " looking in from the " + short() + ".\n");
 
    if (!CAN_SEE_IN_ROOM(this_player(), environment()))
        return "You cannot see into the darkness.\n";
 
    ret = environment()->query_window_view();
    if (!ret)
        ret = capitalize(environment()->short() + ".\n");

    ob = FILTER_LIVE(all_inventory(environment()));
    tmp = COMPOSITE_LIVE(ob);
    if (tmp != "someone")
        ret += capitalize(tmp) + ".\n";
 
    if (pointerp(ob))
        ob = all_inventory(environment()) - ob;
    else
        ob = all_inventory(environment());
    tmp = COMPOSITE_DEAD(ob);
    if (tmp != "something")
        ret += capitalize(tmp) + ".\n";
 
    if (!strlen(ret))
        return "You see nothing special.\n";
 
    return ret;
}
 
/*
 * Function name: set_other_room
 * Description:   set the room which should contain the other side of
 *                this window.
 * Arguments:     room - the name of the other room, or an objectp
 */
public void
set_other_room(mixed room)
{
    other_window_room = room;
    if (objectp(room))
        room = MASTER_OB(room);
    add_name("_window_to_" + room);
}
 
/*
 * Function name: look_through_window
 * Description:   parsing function
 * Arguments:     arg - the command string
 * Returns:       do_look_through_window() in window specified in arg.
 * N.B.:          This function uses the prop TEMP_WINDOW_CHECKED,
 *                to avoid multiple parsings.
 */
public int
look_through_window(string arg)
{
    mixed windows;
    object tp;
 
    if (!strlen(arg))
        return 0;
 
    if (this_player()->query_prop(TEMP_WINDOW_CHECKED))
        return 0;
    else
        set_temp();
    if (!parse_command(arg, environment(), "'in' / 'through' / 'into' / " +
        "'inside' [the] %i", windows))
        return 0;
    windows = NORMAL_ACCESS(windows, 0, 0);
 
    if (!sizeof(windows))
        return 0;
    // Save some time by not parsing multiple times for multiple windows.
    return windows[0]->do_look_through_window();
}
 
/*
 * Function name: do_look_through_window
 * Description:   perform the actual look through this window
 * Returns:       Should always return 1
 */
public int
do_look_through_window()
{
    find_other_window();
    write(other_window->view_from_window(environment()));
    tell_viewers(environment(), QCTNAME(this_player()) + " looks in the " +
        short() + ".\n", this_player());
    return 1;
}
 
/*
 * Function name: climb_through_window
 * Description:   parsing function, as look_through_window
 * Arguments:     arg - the command string
 * Returns:       do_climb_through_window in desired window.
 */
public int
climb_through_window(string arg)
{
    mixed window;
 
    notify_fail("Climb where?\n");
 
    if (!strlen(arg))
        return 0;
    if (this_player()->query_prop(TEMP_WINDOW_CHECKED))
        return 0;
    else
        set_temp();
    if (!parse_command(arg, environment(), "'through' / 'into' / 'in' " +
        "[the] %i", window))
        return 0;
 
    window = NORMAL_ACCESS(window, 0, 0);
    if (!sizeof(window))
        return 0;
 
    return window[0]->do_climb_through_window();
}
 
/*
 * Function name: do_climb_through_window
 * Description:   Perform the actual climb -- hurt us if broken glass and
 *                    we fail skill check.
 * Returns:       Always 1
 */
public int
do_climb_through_window()
{
    int success;
 
    find_other_window();
    if ((window_vals & 17) == 1)
    {
        write("You bump your head against the " + short() + ".\n");
        tell_viewers(environment(), QCTNAME(this_player()) + " bumps " +
            this_player()->query_possessive() + " head against the " +
            short() + ".\n");
        tell_viewers(environment(other_window), "You hear a thump " +
            "at the " + other_window->short() + ".\n");
        return 1;
    }
 
    if (window_vals & 8)
    {
        write("You are too large to climb through the " + short() +
            ".\n");
        tell_viewers(environment(), QCTNAME(this_player()) + " tries to " +
            "climb through the " + short() + ", but is too large.\n");
        return 1;
    }
 
    tell_viewers(environment(), QCTNAME(this_player()) + " climbs through " +
        "the " + short() + ".\n");
    write("You climb through the " + short() + ".\n");
 
    this_player()->move_living("M", environment(other_window), 1);
    other_window->do_arrive_through_window();
 
    if ((window_vals & 18) == 2)
    {
        success = this_player()->resolve_task(TASK_DIFFICULT, ({ TS_DEX,
            SS_CLIMB, SKILL_WEIGHT, 75, SS_ACROBAT }));
 
        if (success < 0)
        {
            write("You cut yourself on the way through.\n");
            this_player()->heal_hp(success * 6);
            this_player()->add_tmp_skill(SS_CLIMB, -5, 9);
            // Hard to climb with cuts.
        }
        // We won't kill any players for climbing through a broken window.
    }
    return 1;
}
 
/*
 * Function name: do_arrive_through_window
 * Description:   tell this room about arrival
 */
public void
do_arrive_through_window()
{
    tell_viewers(environment(), QCTNAME(this_player()) + " arrives " +
        "through the " + short() + ".\n");
}
 
/*
 * Function name: break_window
 * Description:   parsing function, as look_through_window
 * Arguments:     arg - the command string
 * Returns:       do_break_window in specified object
 */
public int
break_window(string arg)
{
    mixed with_obj, window;
 
    if (!strlen(arg))
        return 0;
    if (this_player()->query_prop(TEMP_WINDOW_CHECKED))
        return 0;
    else
        set_temp();
    if (parse_command(arg, environment(),
        "[the] %i 'with' / 'using' [the] %i", window, with_obj))
        with_obj = NORMAL_ACCESS(with_obj, 0, 0);
    else if (parse_command(arg, environment(), "[the] %i", window))
        with_obj = this_player()->query_weapon(W_RIGHT);
    else
    {
        notify_fail(capitalize(query_verb()) + " what? [with what?]\n");
        return 0;
    }
 
    if (pointerp(with_obj))
        with_obj = (sizeof(with_obj) ? with_obj[0] : 0);
 
    if (with_obj && environment(with_obj) != this_player())
    {
        write("You are not holding the " + with_obj->short() + ".\n");
        return 1;
    }
    window = NORMAL_ACCESS(window, 0, 0);
    if (!sizeof(window))
        return 0;
 
    return window[0]->do_break_window(with_obj);
}
 
/*
 * Function name: do_break_window
 * Description:   perform the actual break, cut them if sloppy
 * Arguments:     with_obj - the object (if any) with which to break
 * Returns:       Always 1
 */
public int
do_break_window(object with_obj)
{
    int success;
 
    find_other_window();
    if (!(window_vals & 1))
    {
        write("There is nothing to break in the " + short() + ".\n");
        return 1;
    }
 
    this_player()->reveal_me(1);
    if (window_vals & 4)
    {
        write("You beat on the " + short() + (with_obj ? " with " +
            "your " + with_obj->short() : "") + ", but it fails to break.\n");
        tell_viewers(environment(), QCTNAME(this_player())  + " tries to " +
            "break the " + short() + ".\n");
        return 1;
    }
 
    window_vals &= 14; // Windows which are broken are no longer open,
                      // and cannot ever be opened. Q.
    write("You smash the " + short() + (with_obj ? " with your " +
        with_obj->short() : "") + ".\nSparkles of glass fly into the air.\n");
    tell_viewers(environment(), QCTNAME(this_player()) + " smashes the " +
        short() + (with_obj ? " with the " + with_obj->short() : "") +
        ".\nSparkles of glass fly into the air.\n");
    other_window->remote_break_window();
 
    if (!with_obj && !this_player()->query_armour(A_HANDS))
    {
        success = this_player()->resolve_task(TASK_FORMIDABLE,
            ({ SKILL_WEIGHT, 300, SS_UNARM_COMBAT, TS_DEX }));
        if (success < 0)
        {
            write("You cut yourself on the glass.\n");
            this_player()->heal_hp(success * 3);
        }
    }
 
    add_prop(OBJ_I_BROKEN, 1);
    return 1;
}
 
/*
 * Function name: remote_break_window
 * Description:   someone broke the other side, break this one too
 */
public void
remote_break_window()
{
    window_vals &= 14;
    tell_room(environment(), "The " + short() + " shatters, broken " +
        "from the other side.\n");
    add_prop(OBJ_I_BROKEN, 1);
}
 
/*
 * Function name: change_window_val
 * Description:   change the window value. Use this to open/shut the
 *                window etc. Not used in this file.
 */
public void
change_window_val(int newval)
{
    window_vals = newval;
}
 
/*
 * Function name: query_window_val
 * Description:   Return the window value
 * Returns:       Binary value as follows:
 *                    1 - window is whole (no climb through)
 *                    2 - jagged glass (only if broken)
 *                    4 - unbreakable
 *                    8 - too small to climb through
 *                   16 - open
 *                   32 - openable
 */
public int
query_window_val()
{
    return window_vals;
}
 
/*
 * Function name: init
 * Description:   add window commands to us
 */
public void
init()
{
    ::init();
    add_action(&look_through_window(), "look");
    add_action(&look_through_window(), "l");
    add_action(&climb_through_window(), "climb");
    add_action(&break_window(), "break");
    add_action(&break_window(), "smash");
}
 
/*
 * Function name: create_object
 * Description:   initialize window
 */
public nomask void
create_object()
{
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "Get what?\n");
    this_object()->create_window();
}
 
/*
 * Function name: create_window
 * Description:   Make the window.
 * N.B.:          mask this function
 */
public void
create_window()
{
    set_name("window");
    set_window_desc("There is a window here.\n");
    set_long("This is an ordinary looking window.\n");
}
 
/*
 * Function name: enter_env
 * Description:   we are entering, add our desc, if we have one
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
 
    if (strlen(window_desc))
        to->add_my_desc(window_desc, this_object());
}
 
/*
 * Function name: leave_env
 * Description:   Bye bye! Remove our desc
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
 
    from->remove_my_desc(this_object());
}
