/*
 *  IGARD_ARM + "igard_gchainmail.c"
 *  Disguise armour sold in Isengard - Standard Gondor Armour
 *    Modified from: /d/Gondor/common/arm/gchainmail.c
 *
 *    Last modified by Alto, 29 November 2001
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

int      worn;

mixed    wear(object what);
mixed    remove(object what);

public void
create_armour() 
{
  set_name(({"chainmail","chain mail","mail"}));
  set_pname("chainmails");
  add_pname("mails");
  set_short("silver chainmail");
  set_pshort("silver chainmails");
  set_adj("silver");
  add_adj("chain");
  set_long("The silver chainmail is made of shiny metal rings.\n"+
    "A black tunic covers most of the torso, and a white tree is\n"+
    "embroidered on the front. This is standard Gondorian armour.\n");
  set_default_armour(25,A_BODY,0,0);
  add_prop(MTIRITH_ARMOUR, 1);
  add_prop(OBJ_I_WEIGHT,9500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,30000);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
  set_af(TO);
  seteuid(getuid(TO));

}


mixed
wear(object what)
{
    object head_armour   = TP->query_armour(4); 
    object body_armour   = TP->query_armour(2);

    string hee, he;

    if (what != TO)
        return 0;

    write("As you pull the chainmail over your shoulders, you wonder "
        + "if it might help you blend in with the people of Minas "
        + "Tirith.\n");
    say(QCTNAME(TP) + " pulls the chainmail over "
        + TP->query_possessive() + " head.\n");

    if (objectp(head_armour) && head_armour->query_prop(MTIRITH_ARMOUR))
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

    wearer->catch_tell("You pull the chainmail off your shoulders.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " removes " + POSSESSIVE(wearer) + " chainmail.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_MTIRITH))
    {
        wearer->remove_prop(FRIEND_OF_MTIRITH);
    }

    worn = 0;
    return 1;
}
