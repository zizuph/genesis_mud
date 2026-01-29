


#include <stdproperties.h>
#include <filepath.h>
#include <language.h>
#include <std.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>

inherit "/std/object";

int
is_wiz(object ob)
{
    return ob->query_wiz_level();
}

/*
 * Function name: init
 * Description:   Initialize some gem related actions.
 */
init()
{
    ::init();
    add_action("mywiz", "mywiz");
}

/* Change wiz name to something more appropriate. */
string
wizit(string name)
{
    int len;
    int i;
    int c;

    if (name == "mrpr") /* I'm very sensitive about vowels in my name */
        return name;

    len = strlen(name);
    for(i = 0; i < len; i++) {
	c = name[i];
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
	    break;
    }
    /* i points to a vowel, or at the end of the string */
    i++;	/* skip vowel */
    if (i >= len)
	i = 0;	/* use whole name if nothing left */
    return "ma" + name[i..len-1];
}

/* **************************************************************************
 * wiz / wize - gozzip on the wizline
 *
 * With the command "wiz" you can talk on the wizline and "wize" will let
 * you emote on the wizline with the same function. This is IMHO the quickest
 * and least memory using way of implementing the line :-)
 */
int
mywiz(string str)
{
    object *list;
    int    i, busy;

    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    list = filter(users() - ({ this_player() }), "is_wiz", this_object());
    str = "@ " + capitalize(this_player()->query_real_name()) +
        ((query_verb() == "wiz") ? ": " : " ") + str + "\n";

    for (i = 0; i < sizeof(list); i++)
    {
	busy = (int)list[i]->query_prop(WIZARD_I_BUSY_LEVEL);
	if (!((busy & 1) || (busy & 128)))
	{
	    list[i]->catch_msg(str);
	}
    }

    busy = (int)this_player()->query_prop(WIZARD_I_BUSY_LEVEL);
    if ((this_player()->query_get_echo()) &&
	(!((busy & 1) || (busy & 128))))
    {
	write(str);
    }
    else
    {
	write("Ok.\n");
    }

    return 1;
}


