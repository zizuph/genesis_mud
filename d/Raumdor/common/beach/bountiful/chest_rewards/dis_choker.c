/*  /d/Raumdor/common/beach/bountiful/chest_rewards/dis_choker.c
 *
 *  Magically increases disipline by a small amount.
 *
 *  Nerull, 2021
 *
 */

inherit "/std/armour";
inherit "/lib/keep";
#include "../defs.h";
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <const.h>
#include <wa_types.h>

object wearer;

int drain_alarm = 0;

void
create_armour()
{
    set_name("choker");

    set_adj("thin");
    add_adj("lead");

    set_short("thin lead choker");
    set_pshort("thin lead chokers");

    set_long("The choker is made of thin treads of "
    +"lead in the shape of a spiderweb and in the "
    +"center of the web sits a small jade spider.\n");

    set_at(A_NECK);
    set_ac(1);
    set_af(this_object());

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 30,"enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This item enhances the wearer "
    +"with a small bonus to disipline.\n",20 }));

    add_prop(OBJ_S_WIZINFO, "This item adds "
    + 15
    +" points of disipline to the wearer.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE, 12000);
}


void
drain_man(object wearee)
{
    wearee->catch_msg("You feel a slight mental drain.\n");
    wearee->add_mana(-2);

    return;
}


/*
* Function name: wear_message()
* Description  : Tells the wearer and the environment about the changes.
*/
void
wear_message()
{
    if (environment(this_object()) != wearer)
    return;

    wearer->catch_msg("You feel slightly braver.\n");

    tell_room(environment(wearer), QCTNAME(wearer) 
    +" feels slightly braver.\n", wearer);
}


mixed
wear(object what)
{
    this_player()->set_stat_extra(SS_DIS, 
    (this_player()->query_stat_extra(SS_DIS) 
    + 15));

    wearer = this_player();

    set_alarm(0.1, 0.0, "wear_message");

    drain_alarm = set_alarm(60.0, 60.0, &drain_man(wearer));

    return 0;
    
}


mixed
remove(object what)
{
    if (wearer)
    {
        wearer->set_stat_extra(SS_DIS, 
        (this_player()->query_stat_extra(SS_DIS)
        - 15));

        wearer->catch_msg("You feel less brave.\n");

        tell_room(environment(wearer), QCTNAME(wearer)
        + " feels less brave.\n", wearer);
    
        wearer = 0;
    }
    
    remove_alarm(drain_alarm);
    
    return 0;
}


void
leave_env(object ob, object from)
{
    if (wearer)
        remove(this_object());

    ::leave_env(ob, from);
}