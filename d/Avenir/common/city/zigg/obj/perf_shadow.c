/*
 * - shadow.c
 *
 * Shadow for perfumes so that you can smell the perfume
 * when you smell a person/player.
 *
 */
#pragma no_shadow
#pragma strict_types

#include <language.h>
inherit "/std/shadow";

#define NO_BOTTLES
#define NO_PERFUMES

#include "perfume.h"


private static string oil;
private static string *data;
private static object emotes;


public void
remove_shadow(void)
{
    emotes->remove_object();
    ::remove_shadow();
}

public void
set_perfume_oil(string str, string *arr)
{
    oil = str;
    data = arr;

    emotes->set_perfume_oil(oil, data);
}

public string
query_perfume_oil(void)			{ return oil; }

public void
remove_perfume(void)			{ remove_shadow(); }

public varargs int
shadow_me(mixed to_shadow)
{
    int res = ::shadow_me(to_shadow);

    if (res)
    {
	setuid();
	seteuid(getuid());

	emotes = clone_object(PERFUME_EMOTES);
	emotes->move(shadow_who);
    }

    return res;
}

/*
 * This is a pseudo-function called by the emote "smell".
 */
public void
hook_smelled(string str)
{
    this_player()->catch_tell("You catch a "+
	one_of_list(data[AROMA]) +" scent of "+
	LANG_ADDART(data[SCENT]) +" "+
	(shadow_who->query_gender() ? "perfume" : "cologne") +
	".\n");
}

/*
 * Capture some emote hooks and give off a whiff of our scent.
 *
 *  oblist->emote_hook(query_verb(), this_player(), adverb, all_oblist,
 *	cmd_attr, 1);
 */
public void
emote_hook(string emote, object actor, string adverb,
    		object *oblist, int attr, int target)
{
    if (!target || !query_interactive(actor))
    {
	shadow_who->emote_hook(emote, actor, adverb, oblist, attr, target);
	return;
    }

    switch(emote)
    {
    case "nuzzle":
	actor->catch_tell("You catch a whiff of "+ LANG_ADDART(data[SCENT]) +
	    " "+ (shadow_who->query_gender() ? "perfume" : "cologne") +".\n");
	break;
    }

    shadow_who->emote_hook(emote, actor, adverb, oblist, attr, target);
}
