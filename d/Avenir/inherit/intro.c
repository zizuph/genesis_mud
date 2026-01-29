// file name:   /d/Avenir/inherit/intro.c
// creator(s):  Denis, Jul'96
// last update: Lucius Oct 2008
// purpose: 	provides a good intro system for all npc's
// note:	based on old /d/Avenir/common/outpost/intro.c by Kazz
// bug(s):	
// to-do:	
#pragma strict_types
#pragma no_clone

/* From /sys/macros.h -- no need to include the whole thing. */
#define OB_NUM(ob)    (explode(file_name(ob) + "#0", "#")[1])
#define OB_NAME(ob)   ("ob_" + OB_NUM(ob))

/*
 * Override this function in your files to do what you like.
 */
static void
return_intro(object who, string oname)
{
    /* Intro right back by default. */
    command("$introduce me to "+ oname);
}

private nomask void
pre_return_intro(object who)
{
    /* Intro no longer necessary. */
    if (!objectp(who) || who->query_met(this_object()))
	return;

    /* No longer in the same room. */
    if (environment() != environment(who))
	return;

    return_intro(who, OB_NAME(who));
}

public void
add_introduced(string name)
{
    object who = find_player(name);

    /* Only continue if a player and unmet. */
    if (!objectp(who) || who->query_met(this_object()))
	return;

    set_alarm(itof(1 + random(3)), 0.0, &pre_return_intro(who));
}
