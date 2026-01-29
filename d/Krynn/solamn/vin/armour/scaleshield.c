/* The shield used by the guards in Vingaard Keep
 * by Teth, December 2, 1996
 * Modified June 19, 1998 to conform with updated man armour, Teth.
 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */
inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <formulas.h>

#include "../local.h"

#define DEBUG(x)  (find_player("boron")->catch_msg("Debug: " + x + "\n") )


public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj("solamnian");
    add_adj(({"light","steel","scale"}));
    set_short("light solamnian shield");
    set_pshort("light solamnian shields");
    set_ac(43 + (random(2)));
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This light shield is made of Solamnian steel. " +
      "It is stamped, 'Vingaard Keep Armoury'. " +
      "This shield would be quite useful to someone fending " +
      "off attacks, even protecting the body and legs of the " +
      "wearer. It is an excellent shield, one of the best " +
      "available for purchase anywhere in the lands.\n");

/*
    set_commodity_name ("scaleshield"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(53), 0);
*/
    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(VK_NOBUY, 1);

        DEBUG("got_hit entered");

}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    DEBUG("got_hit entered");

    if (hid == TS_HEAD)
    {
        DEBUG("Head got hit");
        att->hit_me(arm_ac, W_SLASH, TO, -1, A_HEAD);
    }

    return ::got_hit(hid, ph, att, dt, dam);

}


public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS, A_HEAD }) );
}
