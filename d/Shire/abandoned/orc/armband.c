/* Guild Item for Orc Racial Guild
 * Finwe, Nov 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <formulas.h>
#include <files.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/orc/orc.h"

int armband;
    
void
create_object()
{
    set_name("armband");
    add_adj(({"dirty","ragged"}));
//    add_name("_orc_race_guild_armband_");
//    add_name(GUILD_EMBLEM_ID);
    set_short("dirty, ragged armband");
    set_long("This is a strip of coarse material that orcs use " +
        "to tie around their arms and identify themselves. The " +
        "armband is dirty and stained with dried blood. The " +
        "ends are ragged and frayed.\n");
    /* The anklet can be worn on either ankle */
    set_slots(A_L_ARM);

    /* We won't make the anklet take up any space on the ankle.
     * That way, we can wear several and not have to worry about
     * not being able to wear clothing or armour over them.
     */
    set_layers(1);

    /* We allow  3 layers to be worn under the armband*/
    set_looseness(3);


    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
    armband = 0;
}


/*
void
init()
{
    ::init();
    add_action(armband_on, "tie");
    add_action(armband_on, "untie");
}
*/

/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string 
query_auto_load() 
{
    return MASTER + ":"; 
}


/* 
 * Function name: enter_env
 * Description  : Prevents a player from carrying more than one
 *                of these items.
 * Arguments    : object dest - destination environment
 *                object old  - original environment
 */
public void
enter_env(object dest, object old)
{
    object *obs;
    int i, change, size;

}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/wearable_item.c into any object
 *                other than /std/armour.c you MUST also define the function
 *                appraise_object() as copy of this function. It MUST make
 *                the call to appraise_wearable_item() as well. If you omit
 *                this, then the player will not be able to appraise this
 *                item properly.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
