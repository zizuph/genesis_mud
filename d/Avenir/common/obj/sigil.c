/*
 * ~sigil.c
 *
 * by Lucius
 *
 * An object to create random sigil-based objects for npc's
 * to wear that display their Sybarun lineage.
 *
 * This object must be moved to the npc *PRIOR* to calling make_sigil().
 *
 * >>> object ob = clone_object("/path/to/sigil");
 * >>> ob->move( <where> );
 * >>> ob->make_sigil();
 *
 * make_sigil() can take a string argument for a specific item,
 * else one is randomly chosen from those available.
 *
 *  Revisions:
 *     Lilith May 2022: updated the subloc to print the House name as well.
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

#define SUBLOC  "__av_sigil_object"

/*
 * "Id" : "name", "pname",
 * 	  "short", "pshort",
 * 	  ({ "adj1", "adj2" }),
 * 	  "long description"
 */
private static string item, text, house;
private static mapping items = ([
	"pin" : ({ "pin", "pins",
	    "painted sigil pin", "painted sigil pins",
	    ({ "painted", "sigil" }),
	    "This is a painted pin worn by Sybarites that displays "+
	    "their house affiliation. This one is painted to "+
	    "depict %s.",
	    " is wearing a pin painted to show %s",
	}),
]);

/* Should prevent the sigil object showing up in corpses. */
private void
init_sigil(void)
{
    add_prop(OBJ_I_NO_GET,  1);
    add_prop(OBJ_I_NO_DROP, 1);
}

public void
make_sigil(string str = "")
{
    mixed data;

    if (!strlen(str) || !items[str])
	item = one_of_list(m_indexes(items));
    else
	item = lower_case(str);

    data = items[item];

    set_name(data[0], 1);
    set_pname(data[1]);
    set_short(data[2]);
    set_pshort(data[3]);
    set_adj(data[4]);

    if (!strlen(environment()->query_my_house()))
	remove_object();

    house = environment()->query_my_house();
    text = environment()->query_sigil_text();
    set_long(sprintf(data[5], text));

    set_alarm(2.0, 0.0, init_sigil);
}

static void
create_object(void)
{
    set_short("sigil");
    set_name("av::sigil");

    add_prop(OBJ_I_NO_STEAL, 1);

    add_prop(OBJ_I_VALUE,  1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (to->query_npc())
	to->add_subloc(SUBLOC, this_object());
    else
	set_alarm(1.0, 0.0, remove_object);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    from->remove_subloc(SUBLOC);
}

public string
show_subloc(string sub, object on, object for_obj)
{
    if ((sub != SUBLOC) || on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    /* This is for npc's only, so we need only one format. */

    return capitalize(on->query_pronoun()) +
	sprintf(items[item][6], text) +", the sigil of House "+ house +".\n";
}
