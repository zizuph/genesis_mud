#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <stdproperties.h>

#define TREATY_MASTER    (ROOM + "meeting")

public mixed treaty;
public string name;

public void
create_object()
{
    reset_euid();

    set_name("treaty");
    set_long("@@read_treaty@@");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
}

public int
set_treaty_title(string title)
{
    set_short("treaty titled \"" + title + "\"");

    name = title;

    if (treaty = TREATY_MASTER->query_treaty(title))
	return 1;
    else
	return 0;
}

public int
tear(string str)
{
    notify_fail(CAP(query_verb()) + " what?\n");

    if (!strlen(str))
	return 0;

    str = lower_case(str);
    parse_command(str, ({}), "[up] [the] %s", str);

    if (!sizeof(FIND_STR_IN_OBJECT(str, TP)))
	return 0;

    if (FIND_STR_IN_OBJECT(str, TP)[0] != TO)
	return 0;

    write("You tear up " + LANG_THESHORT(TO) + " into shreds.\n");
    say(QCTNAME(TP) + " tears a piece of paper to shreads.\n");

    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public int
burn(string str)
{
    NF("Burn what?\n");
    if (!strlen(str))
	return 0;

    str = lower_case(str);
    parse_command(str, ({}), "[up] [the] %s", str);

    if (!sizeof(FIND_STR_IN_OBJECT(str, TP)))
	return 0;

    if (FIND_STR_IN_OBJECT(str, TP)[0] != TO)
	return 0;

    write("You set " + LANG_THESHORT(TO) + " on fire, and drop it to "+
	"the ground.\n");
    say(QCTNAME(TP) + " sets a piece of paper on fire, and drops it to "+
	"the ground.\n");

    tell_room(ENV(TP), "The paper burns away in a dark, almost black, "+
	"flame, leaving nothing behind.\n");

   set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public int
read(string str)
{
    string text;

    NF("Read what?\n");
    if (!strlen(str))
	return 0;

    str = lower_case(str);
    if (!sizeof(FIND_STR_IN_OBJECT(str, TP)))
	return 0;

    if (FIND_STR_IN_OBJECT(str, TP)[0] != TO)
	return 0;

    text = "The treaty reads:\n" + treaty[0] + "\n";

    if (!sizeof(treaty[3]))
    {
	text += "The treaty is unsigned.\n";
    }
    else
    {
	text += "The treaty has been signed by:\n";

	for(int i = 0; i < sizeof(treaty[3]); i++)
	    text += "\t" + treaty[3][i] + ", for the " + treaty[4][i] + "\n";
    }
    TP->more(text, 0, 0);
    return 1;
}

public string
read_treaty(void)
{
    if (!read(name))
	return "It seems to be blank.\n";

    return "";
}

public void
init(void)
{
    ::init();
    add_action(read, "read");
    add_action(burn, "burn");
    add_action(tear, "tear");
    add_action(tear, "rip");
}

public string
query_auto_load(void)
{
    if (strlen(name))
    {
	add_prop(OBJ_M_NO_DROP, 1);
	set_alarm(1.0, 0.0, &remove_prop(OBJ_M_NO_DROP));
	return MASTER + ":" + implode(explode(name, " "), "%");
    }
    return 0;
}

public void
init_arg(string arg)
{
    if (!strlen(arg) || !set_treaty_title(implode(explode(arg, "%"), " ")))
	set_alarm(0.0, 0.0, remove_object);
}
