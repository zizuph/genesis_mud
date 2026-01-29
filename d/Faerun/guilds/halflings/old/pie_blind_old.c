/*
 * This object was modified from the Ranger Blind.
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define BLIND_SUBLOC "halfling_blind_subloc"

/* Global variables */
static int     gTime,
               gCanSeeAlarm,
               gCanSeeAlarm,
               gDesting,
               gOldProp,
               gOldProp2;
static object  gBrawler,
               gVictim;

/* Prototypes */
public void    can_see_again();

public void
create_object()
{
    set_name("Halfling_Blind_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    set_no_show();
}

public void
set_time(int i)
{
    gTime += i;
}
