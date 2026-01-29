/*
 *  IGARD_ARM + "i_helmet.c"
 *  Standard Isengard Helmet
 *    Modified from: /d/Gondor/common/arm/ghelmet.c
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
    set_name(({"helmet"}));
    set_pname("helmets");
    set_short("white iron helmet");
    set_pshort("white iron helmets");
    set_adj(({"dusky", "iron", "white"}));
    set_long("The dusky white iron helmet was constructed in the forges of "
        + "Isengard. It bears the symbol of the White Hand on its front.\n");
    add_item(({"symbol", "hand", "white hand"}), "The symbol of the White "
        + "Hand is the insignia of Saruman the White, master of Isengard.\n");
    set_default_armour(25,A_HEAD,({-1,1,0}),0);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) * (120 - random(21)) / 100);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,1200);
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

    write("You push the white iron helmet into place on your head.\n");
    say(QCTNAME(TP) + " pushes the white iron helmet into place on "
        + TP->query_possessive() + " head.\n");

    if (objectp(body_armour)   && body_armour->query_prop(IGARD_ARMOUR) &&
      objectp(arms_armour)   && arms_armour->query_prop(IGARD_ARMOUR) &&
      objectp(legs_armour)   && legs_armour->query_prop(IGARD_ARMOUR))
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

    wearer->catch_tell("You grasp the white iron helmet and pull it "
        + "from your head.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " grasps " + POSSESSIVE(wearer) + " white iron "
        + "helmet and pulls it from " + POSSESSIVE(wearer) + " head.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_IGARD))
    {
        wearer->remove_prop(FRIEND_OF_IGARD);
    }

    worn = 0;
    return 1;
}

