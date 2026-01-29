/*
 *  IGARD_ARM + "igard_ghelmet.c"
 *  Helmet for disguise - Standard Gondor Helmet
 *    Modified from: /d/Gondor/common/arm/ghelmet.c
 *
 *    Last modified by Alto, 07 October 2001
 *
 */

#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

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
  set_short("steel helmet");
  set_pshort("steel helmets");
  set_adj(({"tabarded", "steel", "guard", "shiny"}));
  set_long("The helmet was made by a good armourer in Minas Tirith.\n"+
    "It is the standard helmet for Gondor soldiers.\n");
  set_default_armour(25,A_HEAD,({-1,1,0}),0);
  add_prop(OBJ_I_VALUE, 30000);
  add_prop(OBJ_I_WEIGHT,2400);
  add_prop(OBJ_I_VOLUME,1200);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
  add_prop(MTIRITH_ARMOUR, 1);
  set_af(TO);
  seteuid(getuid(TO));

}

mixed
wear(object what)
{
    object head_armour   = TP->query_armour(4); 
    object body_armour   = TP->query_armour(2);

    if (what != TO)
        return 0;

    write("You push the helmet into place on your head.\n");
    say(QCTNAME(TP) + " pushes the helmet into place on "
        + TP->query_possessive() + " head.\n");

    if (objectp(body_armour)   && body_armour->query_prop(IGARD_ARMOUR))
    {
        TP->add_prop(FRIEND_OF_MTIRITH, 1);
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

    wearer->catch_tell("You grasp the helmet and pull it "
        + "from your head.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " grasps " + POSSESSIVE(wearer) + " helmet and pulls it from " 
       + POSSESSIVE(wearer) + " head.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_MTIRITH))
    {
        wearer->remove_prop(FRIEND_OF_MTIRITH);
    }

    worn = 0;
    return 1;
}

