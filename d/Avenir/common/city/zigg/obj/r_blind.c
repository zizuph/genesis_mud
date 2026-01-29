// blind_obj ("r_blind.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Blind object for Ry'nal's special attack
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

private static int set = 0;
private static int blind = 0;
private static object ob;

#define CHECK_MIST(x)  \
    (file_name(environment(x)) == (ZIG_RL3 + "makeovers"))

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"blind_obj","rynal::blind"}));
}

public void
blind_me(void)
{
    if (!blind && CHECK_MIST(ob))
    {
	if (!set)
	{
	    ob->catch_tell("The mist surrounding you seems to "+
		"thicken, blinding you with a hazy white blanket of fog.\n");
	}
	else
	{
	    ob->catch_tell("A misty white cloud immediately "+
		"envelops you, blinding your vision.\n");
	}

	ALTER_PROP(ob, LIVE_I_BLIND, 100);
	blind = 1;
    }
}

public void
unblind_me(void)
{
    if (blind)
    {
	ALTER_PROP(ob, LIVE_I_BLIND, -100);
	blind = 0;
    }
}

public void
remove_object()
{
    if (IS_CLONE)
    {
	unblind_me();

	if (CHECK_MIST(ob))
	    ob->catch_tell("The mist thins and you can see again.\n");
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!IS_CLONE)
	return;

    ob = ENV(TO); 

    set_alarm(2.0, 0.0 , &blind_me());
    set_alarm(60.0, 0.0 , &remove_object());
}

public string
query_recover(void)	{ return 0; }
