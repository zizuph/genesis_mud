#pragma strict_types
//  /bazaar/Obj/misc/letter.c
//  
//  * Lucius, Feb 2009: Recoded, much improved and should be less
//            error prone.
//
inherit "/std/object";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

private static int opened, unread;
private static string gMessage, gSender;


public string
query_sender(void)	{ return gSender; }

public void
set_sender(string str)
{
    if (!strlen(str))
	return;

    remove_adj(lower_case(gSender));
    gSender = capitalize(str);
    add_adj(lower_case(gSender));

    set_short("letter from " + gSender);
    set_pshort("letters from " + gSender);
}

public string
query_message(void)	{ return gMessage; }

public void
set_message(string str)
{
    if (!strlen(str))
	return;

    gMessage = str;
}

public void
create_object(void)
{
    gMessage = "Nothing.\n";
    gSender = "Someone";
    unread = 1;

    set_name("letter");
    set_pname("letters");
    set_long("@@my_long");
    set_short("letter from " + gSender);
    set_pshort("letters from " + gSender);

    add_adj("unread");
    add_adj("unopen");
    add_adj("unopened");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
}

public mixed
command_read(int more)
{
    if (!opened)
	return "The letter is closed and sealed.\n";

    if (unread)
    {
	unread = 0;
	add_adj("read");
	remove_adj("unread");
    }

    function read_it = (more ? this_player()->more : write);

    read_it("The "+ short() +" reads:\n" +
	" ___________________________________\n" +
	gMessage + "\n" +
	" ___________________________________\n");

    say(QCTNAME(this_player()) + " reads over a letter.\n");
    return 1;
}

public string
my_long(void)
{
    if (!opened)
    {
	return ("It is a letter that has been closed and "
	  + "sealed with red wax.\nScrawled on the "
	  + "back is: From "+ gSender + ".\n");
    }

    mixed res = command_read(0);

    if (strlen(res))
	return res;
    else
	return "";
}

public nomask int
avenir_letter_check(void)	{ return 1; }

public int
parse_me(string str, function func)
{
    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) +" what?\n");
	return 0;
    }

    string what, whom;
    /* Our syntax and api differ from standard. */
    object *obs = filter(all_inventory(this_player()),
	    &->avenir_letter_check());

    str = lower_case(str);

    if (sscanf(str, "%s from %s", what, whom) == 2)
    {
	/* We add the sender name as an adverb, so simply
	 * transpose the syntax instead of trying to parse.
	 */
	string *arr = explode(what, " ");
	string *new_arr = arr[0..-2];

	new_arr += ({ whom });
	new_arr += arr[-1..];

	str = implode(new_arr, " ");
    }

    if (!sizeof(obs = FIND_STR_IN_ARR(str, obs)))
    {
	notify_fail(capitalize(query_verb()) +" what?\n");
	return 0;
    }

    mixed *res = map(obs, func);
    string *fail = filter(res, strlen);

    /* Only print failures if all failed. */
    if (sizeof(fail) == sizeof(res))
	write(implode(fail, ""));

    return 1;
}

public mixed
letter_open(void)
{
    if (opened)
	return "The " + short() + " has already been opened.\n";

    opened = 1;

    add_adj("open");
    add_adj("opened");
    remove_adj("unopen");
    remove_adj("unopened");

    write("You break the seal on the " + short() +
	" and open it.\n");
    say(QCTNAME(this_player()) + " breaks the seal on" +
	" a letter and opens it.\n");

    return 1;
}

public int
do_open(string str)
{
    return parse_me(str, &->letter_open());
}

public mixed
letter_burn(void)
{
    if (unread)
	return "You should read the "+ short() +" first!\n";

    write("You burn the "+ short() +"!\n");
    say(QCTNAME(this_player()) + " sets a letter in " +
	this_player()->query_possessive() + " hand into flames.\n" +
	"After a short while the letter has vanished into thin air.\n");

    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public int
do_burn(string str)
{
    return parse_me(str, &->letter_burn());
}

public int
do_read(string str)
{
    return parse_me(str, &->command_read(0));
}

public void
destruct_me(void)
{
    object env = environment();

    if (living(env))
	return;

    if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env,
	    "The letter blows away with the wind.\n");
    }

    remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(5.0, 0.0, destruct_me);
}

public void
init(void)
{
    if (this_player() != environment())
	return;

    add_action(do_read, "read");
    add_action(do_open, "open");
    add_action(do_burn, "burn");
}
