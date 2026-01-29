/*
 *  IGARD_ARM + "i_greaves.c"
 *  Standard Isengard Greaves
 *    Modified from: /d/Gondor/common/arm/gleggings.c
 *
 *    Last modified by Alto, 07 October 2001
 *
 */

#pragma strict_types

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

mixed    wear(object what);
mixed    remove(object what);

int worn;

void
create_armour()
{
    set_name("greaves");
    add_name(({ "pair of greaves" }));
    set_pname("greaveses");
    set_adj("white");
    add_adj("iron");
    set_short("pair of white greaves");
    set_pshort("pairs of white greaves");
    set_long("The pair of dusky white iron greaves was constructed in the "
      + "forges of Isengard, as indicated by the small White Hand insignia "
      + "embossed into the metal.\n");
    add_item(({"insignia", "hand", "white hand"}), "The symbol of the White "
      + "Hand is the insignia of Saruman the White, master of Isengard.\n");

    set_default_armour(20, A_LEGS, ({ 1, 1, -2 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VOLUME, 2000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(100)-50);
    add_prop(IGARD_ARMOUR, 1);

    set_af(TO);
    seteuid(getuid(TO));

}


mixed
wear(object what)
{
    object head_armour   = TP->query_armour(4); 
    object body_armour   = TP->query_armour(2);
    object arms_armour   = TP->query_armour(16); 
    object legs_armour   = TP->query_armour(8);

    if (what != TO)
        return 0;

    write("You slip the pair of white iron greaves over your shins. They "
        + "seem to fit rather well.\n");
    say(QCTNAME(TP) + " slips " + TP->query_possessive() + " pair of white "
        + "iron greaves over " + TP->query_possessive() + " shins.\n");

    if (objectp(head_armour) && head_armour->query_prop(IGARD_ARMOUR) &&
      objectp(body_armour)   && body_armour->query_prop(IGARD_ARMOUR) &&
      objectp(arms_armour)   && arms_armour->query_prop(IGARD_ARMOUR))
    {
        if (ENEMY)
        {
        worn = 1;
        return 1;
        }

        TP->add_prop(FRIEND_OF_IGARD, 1);
    }

    worn = 1;
    return 1;
}

mixed
remove(object what)
{
    object wearer = query_worn();

    if (what != TO || !TP)
        return 0;

    if (wearer->query_hp() == 0)
        {
        worn = 0;
        return 1;
        }

    wearer->catch_tell("You remove the pair of white iron greaves from "
       + "your shins.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " removes the pair of white iron greaves from "
       + POSSESSIVE(wearer) + " shins.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_IGARD))
    {
        wearer->remove_prop(FRIEND_OF_IGARD);
    }

    worn = 0;
    return 1;
}


