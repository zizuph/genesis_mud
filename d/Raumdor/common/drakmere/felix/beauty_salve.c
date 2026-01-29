/*
 * - beauty_salve.c
 * - beauty_shadow.c
 *
 * This item is a beauty salve for players to apply unto their skin
 * to heal in an attempt to make themselves more appealing to the eye.
 *
 * Repeated applications will improve your looks, however, applying
 * too much will destroy your looks.
 *
 * Coded by Lucius@Genesis.
 */
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define COUNT 4
#define DELAY 8.0
#define SHADOW "/d/Raumdor/common/drakmere/felix/beauty_shadow"

private int cnt, alarm;
private string *msgs = ({
    "The salve cools a bit as it flows into your skin.\n",
    "You feel your skin smoothing out a bit as the salve does it's work.\n",
   });


public void
setup_extra(string *extra, object who)
{
}

public string
command_read(int more)
{
    return "The label reads: \n"+
        "\tThis is a salve used explicitly as a topical solution to\n"+
        "\tremove unwanted wrinkles. Do not ingest! To use this salve,\n"+ 
        "\tsimply 'rub' or 'apply' it onto your skin.\n";
}

static void
create_object()
{
    set_name("salve");
    add_name("__beauty_salve");

    set_adj(({ "milky-white" }));
    set_long("The jar holding this salve is chill to the touch, but not "+
	"overly cold.  Inside, a milky-white white substance seems to almost "+
	"float about.  Around the bottle an elegant label has been attached "+
        "with flowing script.\n");
    add_item("jar", "A glass jar with a milky-white substance inside.\n");
    add_item("label", command_read);
    add_cmd_item(({"label"}), ({"read"}), ({ command_read }));
        

    add_prop(OBJ_M_NO_SELL,  1);
    add_prop(OBJ_M_NO_BUY,   1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 8500);
}

private void
apply_salve()
{
    object shadow, old_tp;

    if (++cnt < COUNT)
    {
        tell_object(environment(), one_of_list(msgs));
        return;
    }

    remove_alarm(alarm);
    alarm  = 0;
    old_tp = this_player();
    set_this_player(environment());

    if (objectp(shadow = environment()->beauty_salve_shadow()))
    {
	shadow->apply_salve(1);
    }
    else
    {
	if (catch(shadow = clone_object(SHADOW)) || !objectp(shadow))
	{
	    write("A chill permeates your skin and you feel something "+
		"has gone awry, please make a bug report.\n");
	    remove_object();
	    return;
	}

	shadow->shadow_me(environment());
	shadow->apply_salve(0);
    }

    write("You no longer feel the salve working it's way into your skin "+
	"and assume it's work must be done.\n");
    say("You suddenly notice that "+ QTPNAME(this_player()) +" seems "+
	"different then a few moments ago.\n");

    set_this_player(old_tp);
    remove_object();
}

public int
f_apply(string str)
{
    int i, idx, scars;
    string verb = query_verb();

    if (alarm)
	return 0;

    if (!strlen(str) || !parse_command(str, ({}), 
	    "[the] 'salve' [onto] / [into]  [your] / [my] 'skin'"))
    {
        notify_fail(capitalize(verb) +" the salve onto your skin?\n");
        return 0;
    }

    write("You "+ verb +" the "+ short() +" onto your skin.\n");
    say(QCTNAME(this_player()) + " "+ verb +"s the "+ short() +
	" onto "+ this_player()->query_possessive() +" skin.\n");

    set_no_show();
    alarm = set_alarm(DELAY, DELAY, apply_salve);
    return 1;
}

public void
init()
{
    ::init();
    add_action(f_apply, "apply");
    add_action(f_apply, "rub");
}

public void
remove_object()
{
    if (alarm)
	remove_alarm(alarm);
    ::remove_object();
}
