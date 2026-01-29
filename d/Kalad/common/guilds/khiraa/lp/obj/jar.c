/*
 * A leather pouch to contain herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993, changed it from container to /std/receptacle
 * /Mercade, 7 January 1994, fixed recovery of the pouch.
 * Olorin, 8-feb-96: added protection against stealing
 * Olorin, 11-feb-96: pouches will add a subloc if tied to the belt
 * Olorin, 14-Feb-97: Fixed message and move error when trying to insert
 *                    non-herb objects, following example by Khail in herbjar.
 * Modified for the Lich Priesthood of the Khiraa, Sarr
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Kalad/defs.h"

string gLabel;

static mixed   check_insert();
public string  short_func();

public void 
set_label(string str)
{
    gLabel = str;
}


public void
create_container()
{
    set_name("jar");
    set_adj("glass");
    set_short(short_func);

    set_pshort("glass jars");
    set_long("This is a small jar made of clear glass. It is good for "+
    "holding small spell components like herbs and leftovers.\n");

    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         0);
    add_prop(CONT_I_TRANSP,        1);
    add_prop(CONT_I_WEIGHT,      300);
    add_prop(CONT_I_VOLUME,      300);
    add_prop(CONT_I_MAX_WEIGHT, 8000);
    add_prop(CONT_I_MAX_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,         72);

    add_prop(CONT_M_NO_INS, check_insert);
}

static mixed
check_insert()
{
    int     i = 1;
    object  obj;

    while (objectp(obj = previous_object(--i)))
    {
        if (obj == TO)
	{
	    if (IS_HERB_OBJECT(previous_object(i-1))
                || IS_LEFTOVER_OBJECT(previous_object(i-1)))
		return 0;
	    else
		return "You can only put herbs and leftovers in the "+short()+".\n";
	}
    }
    return "You can only put herbs and leftovers in the "+short()+".\n";
}


string
short_func()
{
    string str;
    if (sizeof(all_inventory(TO)))
        str = "glass jar containing herbs";
    else
        str = "glass jar";
    if(gLabel)
        str += " labeled '"+gLabel+"'";
    return str;
}


string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}

