/*
 *   /d/Gondor/arnor/armour/mithril_armour.c
 *   coded by Tigerlily, June 4, 2005 for the 
 *      massive troll--/d/Gondor/arnor/npc/massive_troll.c
 *   It has some magical properties such as lightness and
 *       strength, since it is made from mithril
 *   It has a small amount of magic resistance and resistance
 *       to fire (see props)
 *
 *   12-feb-2007, Toby: Balanced weight of the chainmail and 
 *                      set_am to protect less if hit by blunt.
 *                          ({ impale, slash, bludgeon })
 *                      Added description for removing it and
 *                      fixed the wear description to comply 
 *                      with new weight.
 *                      Weight: 19kg (full suit) * 0.6 = 11.6
 *                      Putting it just under since it is 
 *                      mithril and very hard to get.
 *   04-okt-2008, Eowul: Removed the name mithril and set is ass
 *                       adjectives instead to fit the short.
 *   2018-06-05, Cotillion: Fixed resistance
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  

int ac = 45+random(3);

void
create_armour()
{
    set_name("chainmail");
    set_adj(({"great", "mithril"}));
    set_short("great mithril chainmail");
    set_pshort("great mithril chainmails");
    set_long("This armour is made from interlocking links of "+
        "silvery mithril, relatively light for its size yet amazingly " +
        "strong. Its design allows it to cover the body and arms.\n");
    set_adj(({"great", "mithril", "chainmail" }));
    set_default_armour(20, A_BODY | A_ARMS, ({-1, 3, -2}), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( ac, A_BODY | A_ARMS ) - 6750);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) + random(300));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({ "The chainmail appears ancient and shiny eventhough worn by a troll. ", 20,
           "It has a remarkable lightness and lustre to it and it covers more parts " +
           "of the body then most chainmails do. ", 40,
           "Furthermore the chainmail is made from mithril and is quite strong " +
                "and light for its size. It humms to your senses and you realize " +
                "it is enchanted.", 60,
           "It protects the wearer from magical attacks and from fire. ", 75,
           "\n", 0, }));
    add_prop(OBJ_S_WIZINFO, "The chainmail gives a little protection from magic and fire.\n");
    set_wf(this_object());
}

static mapping resistances = ([ MAGIC_I_RES_FIRE : 20, MAGIC_I_RES_MAGIC: 20 ]);

int
query_magic_protection(mixed prop, object for_who)
{
    if (for_who == this_object())
        return ::query_magic_protection(prop, for_who);
    else 
        return resistances[prop];
}


/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    object tp = this_player();

    write("The rings of mithril tinkle merrily as you put on " +
        "the wonderfully worked mithril chainmail. It feels a little " +
        "lighter then a chainmail of this huge size should. ");
    set_default_armour(ac, A_BODY | A_ARMS | A_LEGS , ({-2, 3, -4}), 0);
    tp->update_armour(obj);
    tp->add_magic_effect(this_object());
    return 0;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    object tp = this_player();

    write("The rings of mithril tinkle merrily as pull off " +
        "the wonderfully worked mithril chainmail and it " +
        "collapses into a little pile in your inventory. ");
    set_default_armour(20, A_BODY | A_ARMS | A_LEGS , ({-2, 3, -4}), 0);
    tp->update_armour();
    query_worn()->remove_magic_effect(this_object());
    return 0;
}

