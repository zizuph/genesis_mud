/*
 * /std/chain.c
 *
 * A standard rope that we might be able to tie to different things.
 *
 * This is the first version and a simple one, if you want a more complicated
 * feel free to change this file.
 *
 * Nick
 *
 * Added check_call in short, plural_short, and long. Mortricia June 1996.
 * Added also the verb stuff.
 */
/* #pragma save_binary */
#pragma strict_types

inherit "/d/Terel/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <config.h>
#include <cmdparse.h>
#include <language.h>

/*
 * Prototypes
 */
int tie_rope(string str);

object  tied_to;        /* The object this rope is tied to */
string  tied_to_text;   /* description of what the rope is tied to. */
string  tie_verb = "lock";
string  tied_verb = "locked";

/*
 * Function name: init
 * Description:   Initialize commandverbs
 */
public void
init()
{
    ::init();

    add_action(tie_rope, tie_verb);
    add_action(tie_rope, "un" + tie_verb);
}

/*
 * Function name: create_rope
 * description:   Create the rope
 */
void
create_rope()
{
    set_name("chain");
    set_long("A standard chain.\n");
}

/*
 * Function name: create_object
 * Description:   Create the object
 */
nomask void
create_object()
{
    add_prop(OBJ_I_WEIGHT, 1000); /* 1 kg */
    add_prop(OBJ_I_VOLUME, 1000); /* 1 l */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */

    create_rope();
}

/*
 * Function name: reset_object
 * Description:   Reset
 */
nomask void
reset_object() { this_object()->reset_rope(); }

/*
 * Function name: set_tied_to_text
 * Description:   Set the text to what the rope is tied to
 */
void set_tied_to_text(string str) { tied_to_text = str; }

/*
 * Function name: set_tie_verb
 * Description:   Set the verb that ties and unties this rope
 */
void set_tie_verb(string str)
{
    tie_verb = str;
}

/*
 * Function name: set_tied_verb
 * Description:   Set the teid-name of the verb that ties and unties this rope
 */
void set_tied_verb(string str) { tied_verb = str; }

/*
 * Function name: query_tied_to_text
 * Description:   Query what text this rope is tied to
 */
string query_tied_to_text() { return tied_to_text; }

/*
 * Function name: set_tied_to
 * Description:   Set the object this rope is tied to
 */
void set_tied_to(object ob) { tied_to = ob; }

/*
 * Function name: query_tied_to
 * Description:   Query what object this rope is tied to
 */
object query_tied_to() { return tied_to; }

/*
 * Function name: short
 * Description:   We change the short description of
 *                the rope if it's tied, default settings.
 * Argument:      the object for which the desc should be seen
 * Returns:       The description.
 */
public varargs string
short(object for_obj)
{
    string str = "";

    if (tied_to)
        str = " " + tied_verb + " to the " + tied_to_text;

    return ::short(for_obj) + check_call(str, for_obj);
}

/*
 * Function name: plural_short
 * Description:   We change the plural short description of
 *                the rope if it's tied, default settings.
 * Argument:      the object for which the desc should be seen
 * Returns:       The description.
 */
public varargs string
plural_short(object for_obj)
{
    string str = "";

    if (::plural_short(for_obj))
    {
        if (tied_to)
            str = " " + tied_verb + " to the " + tied_to_text;
        return ::plural_short(for_obj) + check_call(str, for_obj);
    }

    return ::plural_short(for_obj);
}

/*
 * Function name: long
 * Description:   We change the long description of
 *                the rope if it's tied, default settings.
 * Argument:      the object for which the desc should be seen
 * Returns:       The description.
 */
public varargs string
long(object for_obj)
{
    string str = "";

    if (tied_to)
        str = "It is " + tied_verb + " to the " + tied_to_text + ".\n";

    return ::long(for_obj) + check_call(str, for_obj);
}


/*
 * Function name: tie_rope
 * Description:   Try to tie/untie the rope
 */
static int
tie_rope(string str)
{
    string vb, name, rest;
    object *a;

    if (this_player()->query_prop(TEMP_STDROPE_CHECKED))
        return 0;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!str)
        return 0;

    if (sscanf(str, "%s to %s", name, rest) != 2)
    {
        if (sscanf(str, "%s with %s", name, rest) != 2)
        {
            name = str;
            rest = "";
        }
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDROPE_CHECKED));
    this_player()->add_prop(TEMP_STDROPE_CHECKED, 1);

    a = CMDPARSE_ONE_ITEM(name, "rope_access", "rope_access");
    if (sizeof(a) > 0)
    {
        return call_other(a[0], vb + "_it", rest);
    }

    notify_fail(capitalize(vb) + " " + LANG_THESHORT(this_object()) +
                " to what?\n");
    return 0;
}

int
rope_access(object ob)
{
    if ((environment(ob) == this_player() ||
         environment(ob) == environment(this_player())) &&
                (function_exists("create_object", ob) == "/d/Terel/std/chain"))
        return 1;
    else
        return 0;
}

/*
 * Function name: tie_it
 * Description:   Perform the actual tie
 */
int
lock_it(string str)
{
    object *ob, env;
    int item;

    env = environment(this_player());
    if (!sizeof(ob = FIND_STR_IN_OBJECT(str, this_player())))
        if (!sizeof(ob = FIND_STR_IN_OBJECT(str, env)))
            if (env->item_id(str))
            {
                item = 1;
                ob = ({ env });
            }

    if (!sizeof(ob))
    {
        notify_fail("Can't find what object to " + tie_verb + " the " +
                QSHORT(this_object()) + " to.\n");
        return 0;
    }

    if (ob[0]->tie_object(this_object(), str))
    {
        if (ob[0]->query_prop(ROOM_I_IS))
            move(ob[0]);
        else
            move(environment(ob[0]));

        if (item)
            set_tied_to_text(str);
        else
            set_tied_to_text(QSHORT(ob[0]));

        say(QCTNAME(this_player()) + " " + tie_verb + "s " +
            QSHORT(this_object()) + " to the " +
            tied_to_text + ".\n");
        write("Ok.\n");

        set_tied_to(ob[0]);

        add_prop(OBJ_M_NO_GET, "It is " + tied_verb + " too hard.\n");
        add_prop(OBJ_M_NO_DROP, "It is " + tied_verb + " too hard.\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: untie_it
 * Description:   Perform the actual untie
 */
varargs int
unlock_it(string str)
{
    if (!tied_to)
    {
        notify_fail("But the " + QSHORT(this_object()) + " is not " +
                    tied_verb + " to anything.\n");
        return 0;
    }

    if (tied_to->untie_object(this_object(), str))
    {
        if (living(tied_to))
            move(environment(tied_to));

        say(QCTNAME(this_player()) + " un" + tie_verb + "s the " +
            QSHORT(this_object()) + ".\n");
        write("Ok.\n");
        tied_to = 0;
        remove_prop(OBJ_M_NO_GET);
        remove_prop(OBJ_M_NO_DROP);
        return 1;
    }

    return 0;
}
