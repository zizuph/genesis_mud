/*
 * What         : A blackened leather champron.
 * Used by      : Minotaur on the bloodsea.
 * Description  : A head armour for minotaurs, replacement for the bandana they cannot use.
 */

#pragma strict_types
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

object who_wore_it;
int drain_alarm = 0;

void
create_object()
{
    set_name("champron");
    add_name("helm");
    add_name("helmet");
    set_adj(({"blackened","leather"}));
    set_short("blackened leather champron");
    set_long("Multiple leather pieces have been strapped together "+
             "to make up this head piece. This piece differs from "+
             "the regular champrons in that it is bigger and " +
             "that it has one large diamond set in place. " +
             "The thin leather pieces doesn't appear to be able "+
             "to offer much protection.\n" +
             "It looks like it is in prime condition.\n");

    set_slots(A_HEAD);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(1, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1)+random(500));
    
    add_prop(OBJ_S_WIZINFO,
        "This head piece is made to be worn on the heads of minotaurs. "+
        "It offers no protection, but it does carry a magical effect. " +
        "It grants the wearer dark vision, similar to that of the bandana "+
        "found on the sparkle/flotsam boat that minotaurs cannot benefit from. "+
        "It grants this effect for some mana cost.\n");
    
    set_keep(1);

    set_layers(1);
    set_looseness(0);

    set_wf(TO);

    add_item("diamond", "The champron has a large diamond set in the blackened leather. "+
                        "It appears that by wearing this head piece, one of your eyes would "+
                        "look straight into the diamond.\n");
}

void
mana_drain(object player)
{
    if(sizeof(player->query_enemy(-1)) > 0)
    {
        if(player->query_mana() < 10)
        {
            player->catch_msg("You need a break from focusing through the diamond of the "+short()+".\n");
            player->command("remove champron");
        }
        else
        {
            player->catch_msg("You feel a mental drain from focusing through the diamond of the "+short()+".\n");
            player->add_mana(-10);
        }
    }
}

/*
 * Function name: wear
 * Description  : Checks if the wearer is a minotaur, other races are
 *                unable to use the armour. If the wearer is a minotaur
 *                a custom wear-message is shown and the "mino_ac_obj"
 *                is cloned to the living, giving AC.
 */
 
mixed
wear(object what)
{

    if(wearer->query_race_name() != "minotaur")
    {
        return "This head piece doesn't fit you.\n";     
    }

    if(wearer->query_mana() < 10)
    {
        return "You are too mentally drained to use the "+short()+".\n";
    }


    tell_room(environment(wearer), QCTNAME(wearer) +
              " carefully wears a "+ short() +" on " + 
              HIS(wearer) + " head.\n", wearer);

    wearer->catch_msg("You carefully wear the " + short() + " on your head.\n");

    wearer->add_prop(LIVE_I_SEE_DARK, wearer->query_prop(LIVE_I_SEE_DARK)+1);
    who_wore_it = wearer;
    drain_alarm = set_alarm(0.0, 60.0, &mana_drain(wearer));
    return 1;
}

/*
 * Function name: remove
 */
 
mixed
remove(object what)
{       
    // Want to make sure we dont decrease the prop on the wrong person.
    if(wearer && who_wore_it == wearer)
    {
        wearer->add_prop(LIVE_I_SEE_DARK, wearer->query_prop(LIVE_I_SEE_DARK)-1);
    }
    who_wore_it = 0;
    remove_alarm(drain_alarm);
    drain_alarm = 0;
    return 0;
}

/*
 * Function name: leave_env
 */
public void
leave_env(object from, object to)
{

    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
