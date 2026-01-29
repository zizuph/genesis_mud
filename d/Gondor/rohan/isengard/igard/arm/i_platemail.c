/*
 *  IGARD_ARM + "i_platemail.c"
 *  Standard Isengard Platemail
 *    Modified from: /d/Gondor/morgul/obj/normalplate.c
 *      Stern, 21-apr-2000, this platemail is a non magic platemail
 *        for some morgul npcs that used to have a magical plate.
 *      Last modified by Alto, 11 October 2001
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
    set_name(({"platemail", "plate", "plate mail"}));
    set_pname("platemails");
    add_pname("mails");
    add_name("mail");
    set_short("dusky white platemail");
    set_pshort("dusky white platemails");
    set_adj("white");
    add_adj("dusky");
    add_adj("plate");
    set_long("The dusky white platemail is made of large panels of "
        + "iron, bolted and welded in such a way that it protects the "
        + "torso quite effectively. A large hand is outlined over its "
        + "breast.\n");
    add_item(({"hand", "large hand"}), "The hand is the symbol of Saruman "
        + "the Wise. This armour is worn by his favoured servants.\n");

    set_default_armour(40,A_BODY,({0, 0, 0}),0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(40)+random(800)-300);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR( 40, A_BODY)+random(600)-250);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);

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

    string hee, he;

    if (what != TO)
        return 0;

    write("You hoist the dusky white platemail over your head and position "
        + "it properly about your chest and back.\n");
    say(QCTNAME(TP) + " hoists the dusky white platemail over "
        + TP->query_possessive() + " head and positions it properly about " 
        + TP->query_possessive() + " chest and back.\n");

    if (objectp(head_armour) && head_armour->query_prop(IGARD_ARMOUR) &&
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

    wearer->catch_tell("You pry the dusky white platemail off your body.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " pries " + POSSESSIVE(wearer) + " dusky white "
        + "platemail off " + POSSESSIVE(wearer) + " body.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_IGARD))
    {
        wearer->remove_prop(FRIEND_OF_IGARD);
    }

    worn = 0;
    return 1;
}
