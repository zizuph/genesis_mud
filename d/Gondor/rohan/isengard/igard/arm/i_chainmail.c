/*
 *  IGARD_ARM + "i_chainmail.c"
 *  Standard Isengard Chainmail
 *    Modified from: /d/Gondor/common/arm/gchainmail.c
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
    set_name(({"chainmail", "chain mail", "mail"}));
    set_pname("chainmails");
    add_pname("mails");
    set_short("dusky white chainmail");
    set_pshort("dusky white chainmails");
    set_adj("white");
    add_adj("dusky");
    add_adj("chain");
    set_long("The dusky white chainmail is made of small interlocking "
        + "rings of iron. It seems well-made and sound, and fits over "
        + "the torso when worn. A large badge is affixed to the front.\n");
    add_item(({"badge", "large badge"}), "Affixed "
        + "to the dusky white chainmail is a large badge depicting a "
        + "white hand. This armour is worn by the servants of Saruman the "
        + "Wise.\n");
    add_item(({"rings of iron"}), "Many small rings of iron are linked "
        + "together to form this well-made chainmail.\n");
    add_item(({"hand", "white hand", "red hand"}), "Now that you look "
        + "closely at the hand on the badge, it seems more red than white.\n");
    set_default_armour(25, A_BODY, 0, 0);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25)+random(200)-100);
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

    write("You pull the dusky white chainmail over your head. The white "
        + "iron rings jingle softly as the armour settles about your "
        + "shoulders.\n");
    say(QCTNAME(TP) + " pulls the dusky white chainmail over "
        + TP->query_possessive() + " head. The white iron rings jingle softly "
        + "as the armour settles about " + TP->query_possessive()
        + " shoulders.\n");

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

    wearer->catch_tell("White iron rings jingle softly as you pull the "
        + "dusky white chainmail off your shoulders and over your head.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " removes " + POSSESSIVE(wearer) + " dusky white "
        + "chainmail.\n", 
        ({wearer}));

    if(wearer->query_prop(FRIEND_OF_IGARD))
    {
        wearer->remove_prop(FRIEND_OF_IGARD);
    }

    worn = 0;
    return 1;
}
