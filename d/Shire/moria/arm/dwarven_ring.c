/* The lost dwarven ring!!!! */

/*
 * The dwarven Ring is one 'adapted' slightly, since it is not quite
 * after the books. However, the books state that Sauron gathered most
 * of the dwarven Rings of Power, and that the Dragons consumed the
 * rest of them. However, this is an indication of that the powers of
 * Middle-Earth did not quite know the history of the Dwarven Rings,
 * thus one of them *might* be hidden and found in the Mines of Moria.
 *
 * Magical abilities: 
 * 1. Additional resistance vs. the elements. 
 * 2. Increases the SS_ALCHEMY          by 28.
 *                  SS_SPELLCRAFT       by  7.
 *                  SS_ELEMENT_EARTH    by 14.
 *                  SS_FORM_ENCHANTMENT by 14.
 *                  SS_APPR_VAL         by  7.
 * 3. The ruby inset is actually a mana storer.
 *    It can store up to 777 mana points.
 * 4. Spells:
 *      parthomir : 'compose jewel'
 *         Actually stores mana within the ring.
 *      kuithmir  : 'body jewel'
 *         Get mana from ring.      
 */

inherit "/std/armour";

#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

string *resistance;
int *strength;

create_armour()
{
    set_name("ring");
    add_name("_the_lost_ring");
    add_adj(({"mithril","ruby","inset"}));
    set_short("mithril ring inset with a ruby");
    set_long(
	"This is a mithril ring inset with a ruby.\n");
    add_item(({"ring's ruby", "ruby of ring", "ruby of the ring"}),
	"The ruby is firmly placed in the ring.\n");

    set_ac( 20 );
    set_at( A_R_FINGER );
    set_am( ({ 0, 0, 0}) );
    set_af( this_object() );

    set_shield_slot(A_BODY|A_L_ARM|A_R_ARM|A_LEGS|A_HEAD);

    add_prop(OBJ_I_WEIGHT, 25); /* 25 g and mithril! */
    add_prop(OBJ_I_VALUE,  14*12*12); /* Expensive? Yes!	*/
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "artifact" }));
    add_prop(MAGIC_AM_ID_INFO,
	({
	    "It seems to be very well made and yields protection.\n", 1,
	    "This seems to be the long lost dwarven ring!\n", 30,
	    "This is one of the Seven Rings of Power made in the Second Age.\n", 50
	}) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    resistance = ({ MAGIC_I_RES_FIRE,
		    MAGIC_I_RES_COLD,
		    MAGIC_I_RES_MAGIC,
		    MAGIC_I_RES_DEATH,
		    MAGIC_I_RES_LIGHT,
		    MAGIC_I_RES_EARTH
     });
    strength   = ({ 75, 75, 25, 25, 50, 100 });
}

int *
query_slots()
{
    return ({ A_R_FINGER });
}

add_magic_res(string *res, int *str, object ob)
{
    int i;
    for(i=0;i<sizeof(res);i++)
    {
	add_prop(res[i], ({ str[i], 1 }) );
	ADD_PROP(ob, res[i], 1);
    }
}

remove_magic_res(string *res, object ob)
{
    int i;
    for(i=0;i<sizeof(res);i++)
    {
	ADD_PROP(ob, res[i], -1);
	remove_prop(res[i]);
    }
}

disappear(object tp)
{
    object *can_see = FILTER_CAN_SEE(FILTER_LIVE(all_inventory(ENV(tp))), tp)-({tp});
    can_see->catch_msg(QCTNAME(tp)+" disappears right in front of you!\n");
}

in_view(object tp)
{
    object *can_see = FILTER_CAN_SEE(FILTER_LIVE(all_inventory(ENV(tp))), tp)-({tp});
    can_see->catch_msg(
	"Suddenly, "+QTNAME(tp)+" comes into view!\n");
}

int
wear(object ob)
{
    object tp=environment(ob);

    add_magic_res(resistance, strength, tp);
    tp->catch_msg("As you put the ring on your finger, you see that "+
	"the world now is much shadowier.\n");

    disappear(tp);
    ADD_PROP(tp, LIVE_I_SEE_INVIS, 75);
    ADD_PROP(tp, OBJ_I_INVIS, 75);
    return 1;
}

int
remove(object to)
{
    object tp=query_worn();
    if(!living(tp)) return 0;

    remove_magic_res(resistance, tp);
    ADD_PROP(tp, LIVE_I_SEE_INVIS, -75);
    ADD_PROP(tp, OBJ_I_INVIS, -75);
    tp->catch_msg(
	"As you remove your ring from your finger, you now see the world as "+
	"it used to be once more.\n");
    call_out("in_view", 0, tp);
    return 1;
}
