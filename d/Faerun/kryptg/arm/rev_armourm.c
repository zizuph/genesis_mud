/*
 * The magical armour worn by the revenants of Kryptgarden.
 * It is based on /doc/examples/armour/magical_boots.c
 * which was coded originally by Lilith in 1997
 * -- Finwe, Oct 2007
 */

//inherit "/std/armour.c";
//inherit "/lib/keep";
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "burnished"
#define ADJ2        "steel"
#define ARMOUR      "body-armour"
#define BOD_TYPE    A_TORSO | A_ARMS
#define AC_MOD      0,0,0

int ac =  45;

void wear_on();

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 

    set_long("This is a " + query_short() + ". It's molded to fit around the torso snugly and protect the arms. The armour was forged from plates of hardened steel and ancient looking. It is still polished and free from knicks and scratches.\n");

    set_at(BOD_TYPE);
    set_ac(ac);

    set_am(({ 0, 0, 0}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);

    set_af(this_object());

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) + 100);

    add_prop(OBJ_M_NO_BUY,
        "The " + query_short() + " is too valuable to sell.");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({
        "This " + query_short() + " is enchanted. ", 10,
        "It has been enchanted by ancient magics. ", 30,
        "The " + query_short() + " protects the wearer from magic attacks.\n", 50}));

    add_prop(OBJ_S_WIZINFO,
        "This " + query_short() + " protects the wearer from MAGIC_I_RES_MAGIC, 15.\n");
}

/*
 * Function name:  query_magic_protection     (see /std/object.c)
 * Description:    This function should return the amount of
 *                 protection versus an attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee - Magic protection for who or what?
 */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR) && (protectee == query_worn()))
    {
        if (prop == MAGIC_I_RES_MAGIC)
            return ({ 15, 1});
    }
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}

mixed
wear(object ob)
{
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }


    if (wearer->query_mana() <= 300)
    {
        return "You are too mentally exhausted to wear the "+ short() +
            ".\n";
    }

    wearer->add_mana(-100);
    wearer->add_magic_effect(this_object());
    set_alarm(1.0,0.0,"wear_on");
    return 0;
}

/*
 * Function name: remove (This is excerpted from /std/armour.c)
 * Description  : This function might be called when someone tries to
 *                    remove this armour. To have it called, use set_af().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object ob)
{
    wearer->remove_magic_effect(this_object());

    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        wearer->catch_tell("You slump from as the power of the " + query_short() + " is " +
            "lifted from you.\n");
    }

    return 0;
}


void wear_on()
{
    write("Magic courses through your body as you put the " + query_short() + " on.\n");
    return ;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
