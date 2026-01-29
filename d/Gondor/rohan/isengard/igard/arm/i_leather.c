/*
 *  IGARD_ARM + "i_leather.c"
 *  Standard Isengard Leather Armour
 *    Modified from: /d/Gondor/common/arm/releather.c
 *
 *    Last modified by Alto, 11 October 2001
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
    set_name("armour");
    set_pname("armours");
    set_short("white leather armour");
    set_pshort("white leather armours");
    set_adj("leather");
    add_adj("poor");
    add_adj("white");
    add_adj("dusky");
    set_long("The dusky white leather armour is made from the hide of Rohan "
        + "horses. It seems rather hastily made, and as such would offer "
        + "less protection than it otherwise might. A large badge is affixed "
        + "to the front.\n");
    add_item(({"badge", "large badge"}), "Affixed "
        + "to the dusky white leather armour is a large badge depicting a "
        + "white hand. This armour is worn by the servants of Saruman the "
        + "Wise.\n");
    add_item(({"hand", "white hand", "red hand"}), "Now that you look "
        + "closely at the hand on the badge, it seems more red than white.\n");
    set_default_armour(7, A_BODY, ({ 0, 1, -1}), 0);
    add_prop(OBJ_I_WEIGHT, 3800);
    add_prop(OBJ_I_VOLUME, 1100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(7) + random(24));

    add_prop(IGARD_ARMOUR, 1);
    set_af(TO);
    seteuid(getuid(TO));

}


mixed
wear(object what)
{
    if (what != TO)
        return 0;

    write("You shove your arms through the white leather armour.\n");
    say(QCTNAME(TP) + " shoves " + TP->query_possessive() + " arms through "
        + TP->query_possessive() + " white leather armour.\n");

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

    wearer->catch_tell("You peel the white leather armour from your body.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " peels off " + POSSESSIVE(wearer) + " white "
        + "leather armour.\n", 
        ({wearer}));

    worn = 0;
    return 1;
}

