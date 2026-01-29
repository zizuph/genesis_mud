/*
 *  IGARD_ARM + "i_shield.c"
 *  Standard Isengard Shield
 *    Modified from: /d/Gondor/common/arm/gshield.c
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
    set_name("shield");
    set_pname("shields");
    set_short("white iron shield");
    set_pshort("white iron shields");
    set_adj("iron");
    set_adj("white");
    set_long("The dusky white iron shield was constructed in the forges of "
      + "Isengard. It bears the symbol of the White Hand on its face.\n");
    add_item(({"symbol", "hand", "white hand", "face"}), "The symbol of the White "
      + "Hand is the insignia of Saruman the White, master of Isengard.\n");
    set_default_armour(21, A_SHIELD, 0, 0);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 880);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21)+random(10)-20);
    add_prop(IGARD_ARMOUR, 1);
    set_af(TO);
    seteuid(getuid(TO));

}


mixed
wear(object what)
{

    if (what != TO)
        return 0;

    write("You slip your arm through the white iron shield. It fits "
        + "comfortably.\n");
    say(QCTNAME(TP) + " slips " + TP->query_possessive() + " arm through "
        + "the white iron shield.\n");

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

    wearer->catch_tell("You remove the white iron shield from your arm.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " removes " + POSSESSIVE(wearer) + " white iron "
        + "shield from " + POSSESSIVE(wearer) + " arm.\n", 
        ({wearer}));

    worn = 0;
    return 1;
}

