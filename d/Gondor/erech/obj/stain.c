/*
 * stain.c
 *
 * By Skippern 2001
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "../erech.h"

#define SUBLOCS_OF_INTEREST ({ "hairstyles", "worn_a" })

/* Global variables */
static string       type = "";
static string       *list_sublocs;
static string       self_str, other_str;

void
create_object()
{
    set_name("stain");
    add_name("_a_stain_");
    set_short("stain");
    set_long("This stain should be invisible.\n");

    set_no_show();

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

int set_type(string str) { type = str; return 1; }
string query_type() { return type; }


public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *treeptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    list_sublocs = pl->query_sublocs();

    if (subloc != STAIN_S_SUBLOC)
    {
        pl->add_subloc(STAIN_S_SUBLOC, this_object());
        return pl->show_subloc(subloc, pl, for_obj);
    }

    // Make a test that sets the subloc and shows it.

    if (for_obj == pl)
    {
	return "You have a stain of "+type+" on your shirt.\n";
    }
    if (for_obj != pl)
    {
	return capitalize(pl->query_pronoun()) + " have a stain of " +
	    type + " on " + pl->query_objective() + " shirt.\n";
    }

    return "";
}

int
set_subloc_text()
{
    object    pl;
    int       i;

    pl = environment(this_object());
    list_sublocs = pl->query_sublocs();
    i = sizeof(list_sublocs);

    if (member_array(SUBLOCS_OF_INTEREST, list_sublocs) != -1)
    {
        write("For debugging....\n");
	// Something
    }
}





