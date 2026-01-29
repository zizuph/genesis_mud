/*
 * /d/Gondor/common/guild2/obj/death_flag.c
 *
 * This object marks an initiate to the guild of the Morgul Mages.
 * It will transport the initiate back to the guild after
 * his or her ritual death which is the requirement for joining
 * the guild.
 *
 * Created: Olorin, 5-jan-1994
 *
 * Altered by Elmore to fit the Death Knights of Krynn.
 *
 */

#pragma save_binary
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>

inherit "/std/object";

#include "/d/Ansalon/common/defs.h"
#include "../local.h"


void 
create_object()
{
    set_name("_krynn_dk_death_flag");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    set_no_show();
}

void 
set_up_flag()
{
    if (TP->query_ghost())
        return;

    TP->move_living("M",GUILD_ROOM + "dknight_start");
    tell_object(TP,"Remember to go back to the barracks in Dargaard Keep and 'start here'.\n");
    remove_object();
}

void 
init()
{
    ::init();

    add_action("do_down_command", "", 1);
    set_alarm(2.5, 0.0, &set_up_flag(TP));
}


public int
do_down_command(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"d","down"});

    if (TP->query_wiz_level())
   	    return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
	      return 0;
    else
        return 1;
}

string 
query_auto_load()
{
    return MASTER;
}
