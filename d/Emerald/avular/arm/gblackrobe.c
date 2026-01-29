#include "../defs.h"

inherit "/std/armour.c";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>


void
create_armour()
{

    set_name("robe");
    set_adj("shimmering");
    add_adj("black");

    set_long("At first it appears to be nothing more than a very shiny, "+
        "black robe made from a tough animal hide. A second glance "+
        "reveals a shimmering, almost moving wave of darkness shifting "+
        "throughout the robe, making it dizzying to look at.\n");

    add_item( ({"darkness", "wave", "wave of darkness", "dark wave"}),
        "The darkness shifting and swaying throughout the black robe "+
        "is very dizzying. You have no idea what might be causing "+
        "the strange shifting and swirling, but you've no doubt that "+
        "its magical.\n");

    set_at(A_ROBE);

    set_ac(20);

    set_am(({ 2, 1, -3}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_ROBE)/2);
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(20, A_ROBE) / 5);

    set_af(this_object());

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) + 150);

    add_prop(OBJ_M_NO_BUY,
        "The robe is too valuable to sell for mere coins.");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 100, "conjuration" }));

    add_prop(MAGIC_AM_ID_INFO, ({
        "Something about this robe appears alien, almost otherworldly.", 10,
        "The material this robe is made from has been summoned magically "+
        "from another plane.", 40,
        "This robe appears to make the wearer less vulnerable to "+
        "magical attacks.\n", 60}));


    add_prop(OBJ_S_WIZINFO,
        "This robe is summoned from another plane, and is 100% "+
        "magical in nature. It provides the wearer a bonus in a "+
        "ton of magical resistances.\n");
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
        if (prop == MAGIC_I_RES_FIRE)
            return ({ 10, 1});
        if (prop == MAGIC_I_RES_ACID)
            return ({ 10, 1});
        if (prop == MAGIC_I_RES_MAGIC)
            return ({ 20, 1});
        /* wearer's of this robe, from the plane of darkness, are
         * far more vulnerable ot magically conjured light */
        if (prop == MAGIC_I_RES_LIGHT)
            return ({ -10, 1});
        if (prop == MAGIC_I_RES_COLD)
            return ({ 10, 1});
        if (prop == MAGIC_I_RES_ELECTRICITY)
            return ({ -10, 1 });
    }
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}

mixed
wear(object ob)
{
    /* Check to see if the boots are still enchanted */
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }

    /* Don't bother doing the "smart" check on NPCs.*/
    if (interactive(wearer))
    {
        if (wearer->resolve_task(TASK_DIFFICULT, ({TS_INT, SS_AWARENESS})) < 0)
        {
            return "As you attempt to wear the robe, you feel as though "+
                "something has probed your mind, and you suddenly feel "+
                "unworthy to don the garment.\n";
        }
    }

    wearer->add_magic_effect(this_object());

    wearer->catch_tell("A strange sense of peace and security "+
        "washes over you, and then vanishes.\n");

    return 0;
}

mixed
remove(object ob)
{

    wearer->remove_magic_effect(this_object());


    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        wearer->catch_tell("You feel a sudden, painful sense of "+
            "vulnerability, and then it is gone.\n");
    }

    return 0;
}


public int
disenchant_object(object disenchanter)
{

    /* Remove the magic effect if the item is worn */
    if (query_worn())
    {
        wearer->remove_magic_effect(this_object());
    }

    tell_room(environment(this_object()),
       "The robe suddenly vanishes in a brief flash of dark, blue light.\n");

    set_alarm(0.0,0.0,remove_object);

    return 1;
}
