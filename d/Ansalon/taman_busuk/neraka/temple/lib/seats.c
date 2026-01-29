/* Stralle @ Genesis 040331
 *
 * This spawned from an idea that you should be able to sit in the
 * armchairs in one of the offices inside the temple. Why not make
 * it into an inheritable object able to be used elsewhere as well?
 *
 * Use:
 *  inherit "this_object";
 *
 *  set_chairs(({"large high-backed chair", "small armchair",
 *       "small armchair"}));
 *
 *  void
 *  leave_inv(object ob, object to)
 *  {
 *     ::leave_inv(ob, to);
 *     seats_leave_inv(ob, to);
 *  }
 *
 *  void
 *  init()
 *  {
 *     ::init();
 *     init_seats();
 *  }
 *
 * Bugs:
 *  Only twenty chairs of the same name (last wording) can be set.
 *  I don't see this as a problem as no one in his right mind would
 *  want twenty similar chairs. If you think otherwise, you are
 *  welcome to try to persuade me to do something about that.
 */
#pragma strict_types

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

string *gChairs;
object *gOccupied;

int do_rise(string arg);

/* Function name: set_chairs
 * Description:   Sets what chairs there are.
 * Arguments:     string - the single description of the chair
 *                string * - the array of descriptions of the chairs
 */
void
set_chairs(mixed chairs)
{
    /* Never know what wizards might do, such as setting chairs
     * while they are occupied :)
     */
    if (sizeof(gOccupied))
        gOccupied->command("$rise");

    if (stringp(chairs))
        gChairs = ({ chairs });
    else if (pointerp(chairs))
        gChairs = chairs;

    if (sizeof(gChairs))
        gOccupied = allocate(sizeof(gChairs));
}

/* Function name: seats_leave_inv
 * Description:   Should be called from leave_inv() in the environment.
 * Arguments:     object ob - the object leaving
 *                object to - to where am I moving
 */
void
seats_leave_inv(object ob, object to)
{
    object old_tp;

    if (member_array(ob, gOccupied) >= 0)
    {
        /* Using ob->command("$rise"); doesn't seem to work */
        old_tp = this_player();
        set_this_player(ob);
        do_rise("");
        set_this_player(old_tp);
    }
}

/* Function name: parsify_string
 * Description:   Turns a string into something parse_command() can
 *                understand by enclosing the last word in the string
 *                by apostrophes and every other word in brackets.
 * Arguments:     string what - the string to parsify
 * Returns:       string - the parsified string
 */
string
parsify_string(string what)
{
    string *arr;
    int i;
    
    if (!what || !strlen(what))
        return 0;
    
    arr = explode(what, " ");
    i = sizeof(arr) - 1;
    arr[i] = "'" + arr[i] + "'";
    while (i--)
        arr[i] = "[" + arr[i] + "]";
    
    return implode(arr, " ");
}

int
parse_cmd_chair(string arg)
{
    int i;

    for (i = 0 ; i < sizeof(gChairs) ; i++)
    {
        if (parse_command(arg, ({}), "[in] [the] " +
            parsify_string(gChairs[i])))
            return i;
    }

    return -1;
}
        
/* Function name: parse_what_chair
 * Description:   Try to parse what chair we are trying to sit in.
 * Arguments:     string arg - the argument fed to the command
 * Returns:       int - the index for which chair in gChairs or -1
 */
int
parse_ord_chair(string arg)
{
    int i, num, *names;
    string *arr, *arr2;

    if (!arg || !strlen(arg))
        return -1;
    
    /* Check for second chair, third chair and so on.
     */
    arr = explode(arg, " ");
    /* If fail, check for names through parse_command
     */
    if (!sizeof(arr) || sizeof(arr) < 2)
        return parse_cmd_chair(arg);

    /* Need to remove any prepositions
     */
    if ((i = member_array("in", arr)) >= 0)
        arr = exclude_array(arr, i, i);
    if ((i = member_array("the", arr)) >= 0)
        arr = exclude_array(arr, i, i);

    /* This won't match 'twenty first' though. See comment in fileheader
     */
    num = LANG_ORDW(arr[0]);
    /* If fail, check for names through parse_command
     */
    if (!num)
        return parse_cmd_chair(arg);

    for (i = 0, names = ({ }) ; i < sizeof(gChairs) ; i++)
    {
        arr2 = explode(gChairs[i], " ");
        if (arr[sizeof(arr) - 1] == arr2[sizeof(arr2) - 1])
            names += ({ i });
    }

    if (num > sizeof(names))
        return -1;

    return names[num - 1];

    return -1;
}
    
int
do_sit(string arg)
{
    int i;

    if (!arg || !strlen(arg))
    {
        notify_fail("Sit in what?\n");
        return 0;
    }
    
    if ((i = parse_ord_chair(arg)) < 0)
    {
        notify_fail("Sit in what?\n");
        return 0;
    }

    if (member_array(this_player(), gOccupied) >= 0)
    {
        notify_fail("You are already occupying " +
            gChairs[member_array(this_player(), gOccupied)] + ".\n");
        return 0;
    }

    if (objectp(gOccupied[i]))
    {
        notify_fail("The " + gChairs[i] + " is already occupied by " +
            gOccupied[i]->query_the_name(this_player()) + ".\n");
        return 0;
    }

    write("You sit down in the " + gChairs[i] + ".\n");
    say(QCTNAME(this_player()) + " sits down in the " + gChairs[i] + ".\n");

    gOccupied[i] = this_player();
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in " +
        LANG_ADDART(gChairs[i]));
    /* Need to add something in the environment that this_player()
     * is indeed sitting in the chair. LIVE_S_EXTRA_SHORT ?
     * function to return a string about the chairs conditions for use
     * in vbfc in an add_item() ? Doing it the easy way for now.
     */
    
    return 1;
}

int
do_rise(string arg)
{
    int i;

    if (!arg || !strlen(arg))
    {
        if ((i = member_array(this_player(), gOccupied)) < 0)
        {
            notify_fail("Rise from what? Are you about levitate?\n");
            return 0;
        }
        
        write("You rise from the " + gChairs[i] + ".\n");
        say(QCTNAME(this_player()) + " rises from the " + gChairs[i] + ".\n");
        
        gOccupied[i] = 0;
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

        return 1;
    }
    
    notify_fail("Rise what?\n");
    return 0;
}

/* Function name: seats_init
 * Description:   Make a call to this function in your init() in order
 *                to make this work
 */
void
seats_init()
{
    add_action(do_sit, "sit");
    add_action(do_rise, "rise");
}
