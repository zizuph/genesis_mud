/*
 * leftover2.c 
 *
 * took the leftover.c and changed it to make
 * some special leftovers. - Azazel
 * 
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

int simple_names;	/* Setup of simple names or not */
string l_organ, l_race; /* Race and organ name */

public void
create_leftover()
{
    simple_names = 1;
    add_name("leftover");
    add_pname("leftovers");

}

public void
leftover_init(string organ, string race)
{
    l_organ = organ;
    l_race = race;

    if (simple_names)
    {
	set_adj(race);
	set_name(organ);
	set_pname(LANG_PWORD(organ));
	set_long("This is the torn and bloody remains of " +
	    LANG_ADDART(race + " " + organ) + ".\n");
    }
}

public nomask void
create_object() 
{ 
    simple_names = 0;
    add_prop(OBJ_I_VALUE, 5);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    create_leftover();
    check_recoverable(1);
}


public string
query_race()
{
    return l_race;
}

public string
query_organ()
{
    return l_organ;
}


