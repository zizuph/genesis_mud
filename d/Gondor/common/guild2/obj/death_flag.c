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
 * Modification log:
 */

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

int     set_up = 0;
string  initiate,
        sponsor;

void 
create_object()
{
    set_name("_morgul_death_flag");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    set_no_show();
}

int 
set_initiate(string p1, string p2)
{
    if(!stringp(p1) || !stringp(p2))
        return 0;

    initiate = p1;
    sponsor = p2;
    set_up = 1;
}

void 
set_up_flag(object pledge)
{
    set_up = 1;

    if(!stringp(initiate) || !stringp(sponsor))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    if (MASTER_OB(TP) == "/d/Genesis/login/ghost_player")
        return;

    write("\nA dark power pulls your new body away to Minas Morgul!\n\n");
    TP->move_living("in a cloud of sulphur", MORGUL_MASTER);
    (MORGUL_MASTER)->add_mage(initiate, sponsor);

    set_alarm(0.0, 0.0, remove_object);
}

void 
init()
{
    ::init();

    if(!set_up)
        set_alarm(0.0, 0.0, &set_up_flag(TP));
}

string 
query_auto_load()
{
    return MASTER + ":" + initiate + "," + sponsor;
}

void 
init_arg(string arg)
{
    sscanf(arg, "%s,%s", initiate, sponsor);
}

