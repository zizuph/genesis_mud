/*
 * /std/rope.c      
 *
 * A standard rope that we might be able to tie to different things.
 *
 * This is the first version and a simple one, if you want a more complicated
 * feel free to change this file.
 *
 * Nick
 * 
 * Updated vastly by Napture - but no-one seemed interested in my
 * additions....*sniff*
 *
 */
#define NAPTURES_ROPE

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <config.h>
#include <cmdparse.h>

object  tied_to;        /* The object this rope is tied to */
string  tied_to_text;   /* description of what the rope is tied to */

/*
 * Function name: init
 * Description:   Initialize commandverbs
 */
public void
init()
{
    ::init();

    add_action("tie_rope", "tie");
    add_action("tie_rope", "untie");
}

/*
 * Function name: create_rope
 * description:   Create the rope
 *                It doesn't need to be named 'rope', anything will do
 */
void
create_rope()
{
    set_name("rope");
    set_long("A standard rope.\n");
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
 * Description:   Reset.
 *                This function calls reset_rope within your rope.
 */
nomask void
reset_object() { this_object()->reset_rope(); }

/*
 * Function name: set_tied_to_text
 * Description:   Set the text to what the rope is tied to.
 *                This is set automatically in do_tie.
 *                If set to "", then QSHORT is applied.
 * Example:       set_tied_to_text("a long branch");
 * Note:          Does not want a full stop or return (\n).  But does want
 *                one of  "a", "an" or "the" (see Example).
 */
void set_tied_to_text(string str) { tied_to_text = str; }

/*
 * Function name: query_tied_to_text
 * Description:   Query what text this rope is tied to.
 *                If set to "", then QSHORT is applied.
 */
string query_tied_to_text() { return tied_to_text; }

/*
 * Function name: set_tied_to
 * Description:   Set the object this rope is tied to. This is the obvject
 *                checked for tie_object() and untie_object().
 * Note:          If the object is a room, then this rope is probably tied
 *                to something within the room (eg add_item).
 */
void set_tied_to(object ob) { tied_to = ob; }

/*
 * Function name: query_tied_to
 * Description:   Query which object this rope is tied to.
 * Note:          If the object is a room, then this rope is probably tied
 *                to something within the room (eg add_item).
 */
object query_tied_to() { return tied_to; }

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *                the rope if it's tied.  Default settings.
 * Returns:       The description.
 */
public varargs string
short(object for_obj)
{
    string str;

    str = "";
    if (tied_to)
	str = " tied to the " + QSHORT(tied_to);
    if (tied_to && tied_to_text)
        str = " tied to " + process_string(tied_to_text);

    return ::short(for_obj) + str;
}

public varargs string
plural_short(object for_obj)
{
    string str;

    str = "";
    if (::plural_short(for_obj))
    {
        if (tied_to)
            str = " tied to the " + QSHORT(tied_to);
        if (tied_to && tied_to_text)
            str = " tied to " + process_string(tied_to_text);

        return ::plural_short(for_obj) + str;
    }

    return ::plural_short(for_obj);
}

public varargs string
long(object for_obj)
{
    string str;

    str = "";
    if (tied_to)
	str = "It is tied to the " + QSHORT(tied_to) + ".\n";
    if (tied_to && tied_to_text)
        str = "It is tied to " + process_string(tied_to_text) + ".\n";

    return ::long(for_obj) + str;
}

/*
 * Function name: tie_rope
 * Description:   Try to tie/untie the rope.
 *                Used for both tying and untying.
 *                Calls a different function to do the actual tying 
 *                depending on the verb used (query_verb) plus "_it"
 *                (eg, "tie" calls "tie_it").
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

    if (sscanf(str, "%s to %s", name, rest) != 2)  {
        name = str;
        rest = "";
    }

    call_out("remove_tmp", 1, this_player());
    this_player()->add_prop(TEMP_STDROPE_CHECKED, 1);

    a = CMDPARSE_ONE_ITEM(name, "rope_access", "rope_access");
    if (sizeof(a) > 0)  {
        return call_other(a[0], vb + "_it", rest);
    }

    return 0;
}

/*
 * Function name: rope_access
 * Description:   test if object is a rope.  Mainly used internally within
 *	          /std/rope, but you may want to add extra tests.
 * Arguments:     ob: The object to test.
 * Returns:       1 if is a rope, 0 if not.
 */
int
rope_access(object ob)
{
    if ((environment(ob) == this_player() ||
                environment(ob) == environment(this_player())) &&
                (function_exists("create_object", ob) == 

#ifdef NAPTURES_ROPE
			"/d/Emerald/napture/inherits/rope_std"))
#else
			"/std/rope"))
#endif
        return 1;
    else
        return 0;
}

void
remove_tmp(object ob)
{
    ob->remove_prop(TEMP_STDROPE_CHECKED);
}

/*
 * Function name: tie_it
 * Description:   Perform the actual tie.
 * Note:          Requires the function tie_object() in the object being
 *                tied to.
 */
int
tie_it(string str)
{
    object what, *ob, env;
    int item, n;
    string str2;

    if (tied_to)
    {
      /* Can't use QSHORT() here, as the rope is already tied */
	notify_fail("But that is already tied to something!\n");
	return 0;
    }
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
        notify_fail("Can't find what object to tie the " +
                QSHORT(this_object()) + " to.\n");
        return 0;
    }

  /* Only checks the first object if in a list!!! */
    notify_fail("For some reason, you can't tie the " + 
	QSHORT(this_object()) + " to that.\n");
	
    if (ob[0]->tie_object(this_object(), str))
    {
        if (ob[0]->query_prop(ROOM_I_IS) || living(ob[0]))
            move(ob[0]);
        else
            move(environment(ob[0]));

	sscanf(str, "%s the %s", str, str2);
	str += str2; 
        if (item)
            set_tied_to_text("the " + str);
        else
            set_tied_to_text("the " + QSHORT(ob[0]));

        say(QCTNAME(this_player()) + " ties a " + QSHORT(this_object()) +
            " to " + tied_to_text + ".\n");
        write("Ok.\n");

        set_tied_to(ob[0]);

        add_prop(OBJ_M_NO_GET, "It is tied too firmly.\n");
        add_prop(OBJ_M_NO_DROP, "It is tied too firmly.\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: untie_it
 * Description:   Perform the actual untie.
 * Note:          Requires the function untie_object() in the object being 
 *                tied to.
 */
varargs int
untie_it(string str)
{
    if (!tied_to)
    {
        notify_fail("But the " + QSHORT(this_object()) + " is not tied " +
                "to anything.\n");
        return 0;
    }

    notify_fail("For some reason you can't untie the " +
	QSHORT(this_object()) + ".\n");
    if (tied_to->untie_object(this_object()))
    {
        if (living(tied_to))
            move(environment(tied_to));

        say(QCTNAME(this_player()) + " unties the " +
            QSHORT(this_object()) + ".\n");
        write("Ok.\n");
        tied_to = 0;
	tied_to_text = "";
        remove_prop(OBJ_M_NO_GET);
        remove_prop(OBJ_M_NO_DROP);
        return 1;
    }

    return 0;
}

/*
 * Function name: tie_object
 * Description:   Check if the rope can be tied on.
 *                This function (with untie_object()) should be put in 
 *                your object to check if objects can be tied to it.
 * Returns:       1: rope can be tied on.  0: cannot be tied.
 * 
 * If you want your object to accept ropes etc. to be tied to it, then this
 * function must be within your object.
 * However, at present, there are no checks in the rope to see if the
 * object it is tied to has been moved/destructed/picked up etc.  So you
 * must take care of this yourself.
 * A simple way would be to add a property during this function and check
 * that prop within the object itself.
 * This is not done here, so that you may change it as you see fit.
 */
varargs int
tie_object(object what, string to)
{
    if (what = this_object()) 
    {
	notify_fail("You can't tie the " + QSHORT(this_object()) + 
	    " to itself!\n");
	return 0;
    }
    return 1;
}

/* 
 * Function name: untie_object
 * Description:   Check if the rope can be untied.
 *                This is the other function (with tie_object()) to 
 *                include in your object.
 * Returns:       1: rope can be untied.
 */
varargs int
untie_object(object what, string from)
{
/* The rope should never get tied to itself, so this function should
 * not get used - within the rope code itself.
 */
    return 1;   /* No need to check if it can or cannot be untied */
}
