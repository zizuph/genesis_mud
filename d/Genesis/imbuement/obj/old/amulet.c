/*
 * Amulet of newbieness
 *
 * Lavellan 2010/12/14
 */

#pragma strict_types
#include "../imbuement.h"
#include <macros.h>
#include <wa_types.h>
#include <composite.h>

inherit "/std/object";
inherit "/lib/wearable_item";

/* Definitions */

/* Global Variables */
object      shadow;

/* Prototypes */
public void     create_object();
public void     leave_env(object from, object to);
public void     appraise_object(int num);
public mixed    wear(object obj);
public mixed    remove(object obj);


public void
create_object()
{
    set_name("amulet");
    add_adj("shiny");
    add_adj("steel");
    set_long("It looks like an amulet. Hmmmm.\n");

    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better keep your amulet!\n");
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_WEIGHT, 15);

    set_looseness(50);
    set_layers(1);
    set_slots(A_NECK);
    set_wf(this_object());
    
    seteuid(getuid());
} /* create_object */


public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
} /* leave_env */


public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
} /* appraise_object */


public mixed
wear(object obj)
{
    if (!interactive(this_player()))
        return 0;
    mixed * weaps = this_player()->query_weapon(-1);
    if (sizeof(weaps))
        return "You can't manage to get the chain untangled whilst wielding " +
            COMPOSITE_DEAD(weaps) + "!\n";
    shadow->remove_shadow();
    shadow = clone_object(IMBUE_DIR + "obj/amulet_shadow");
    shadow->worn(this_player());
    return 0;
} /* wear */


public mixed
remove(object obj)
{
    if (!interactive(this_player()))
        return 0;
    shadow->removed();
    return 0;
} /* remove */
