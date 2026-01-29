
/*
 * Created By : Ibun 090125
 */
#pragma strict_types
inherit "/std/object.c";
#include <stdproperties.h>     /* Where the properties are defined. */
#include <wa_types.h>          /* Where weapon and armour defs are. */
#include <ss_types.h>          /* Where the skill defines are.      */
#include <tasks.h>             /* For using resolve_task in wear()  */
#include <formulas.h>          /* Where the formulas for value, */
 
int time;
void destroy_me();
void set_time();

void
create_object()
{
    set_name("_jail_object");
    set_short("jail object");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_S_WIZINFO,
        "This object selfdestructs when the player has " +
        "been in jail for 20mins and he may leave.\n");
    set_no_show();
    setuid();
    seteuid(getuid());
    set_time();
}

void
set_time()
{
    set_alarm(1200.0, 0.0, &destroy_me());
    time = time();
}


void
destroy_me()
{
    remove_object();
}
 
int
query_time_left()
{
    return (1200 - (time() - time));
}
