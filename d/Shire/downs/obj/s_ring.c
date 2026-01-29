/* Holiday crown of ivy worn on the head
 * June 1999 by Finwe
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";


#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

// Global Vars

void
create_object()
{
/*
 * creates x,y, and z as integers, 
 * and color, size, and type as string variables
 */
    int x;
    string *signet;
/*
 * sets up arrays for different adjectives and types of crabs
 */ 
    signet = ({"a sailing ship",
               "a grove of trees",
               "a sun and rising moon",
               "two upright horses facing each other",
               "a lightning bolt",
               "two crossed swords",
               "a scepter and crook crossed",
               "a raging bear",
               "a rising moon",
               "a rising sun"});

    x = random(sizeof(signet));
write ("-->"+x+"\n");
    set_name("ring");
    add_adj(({"ancient" ,"signet"}));
    add_name("_shire_wight_signet_");
    set_short("ancient signet ring");
    set_long("This "+short()+" was once worn by a royal person. It was used to sign documents and indicated the wearer's rank and authority. The ring is made of gold with a flat top, bearing relief of "+signet[x]+".\n");

    set_slots(A_ANY_FINGER);
    set_layers(0);
    set_looseness(2);

    set_keep(1); 

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  10);
    add_prop(OBJ_I_VALUE,   800+random(350));

}


/*
 * We need to override leave_env() so that we can be sure to remove
 * the item if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}


void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
}

