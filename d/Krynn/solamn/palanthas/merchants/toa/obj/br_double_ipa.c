/* 
 * Drinks from the Draft Pub in the Tower of Arms of Palanthas
 * 
 * Mortis 9.2014
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"
#include <macros.h>
#include "../../../local.h"

create_drink()
{
    set_soft_amount(20);
    set_alco_amount(30);
    set_name("ipa");
    add_name(({"IPA", "ale"}));
    add_adj(({"pale", "blowing", "rock", "blowing rock"}));
    set_short("pint of Blowing Rock IPA");
    set_pshort("pints of Blowing Rock IPA");
    set_long("A classic and malty pint of Indros pale ale from the mountains "
    + "east of Palanthas. It is served on tap at the Tower of Arms' Draft "
    + "Pub.\n");
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 50);
}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
    NF("Smell what?\n");

    if (!str)
    return 0;

    if (str != "ale" && str != "pale ale" && str != "rock ipa"
        && str != "blowing ipa" && str != "blowing rock ipa"
        && str != "ipa" && str != "pale ale" && str != "IPA"
        && str != "pint")
    return 0;

    TP->catch_msg("The Blowing Rock pale ale is a classic ale with a great "
    + "malt balance with a fragrance reminding you of apple trees and high "
    + "mountain forests.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " pint of Blowing "
    + "Rock pale ale to " + HIS(TP) + " nose sniffing it for a moment "
    + "as " + PRONOUN(TP) + " inhales its aroma.\n", ({TO, TP}));

    return 1;
}

void
special_effect(int numofdrinks)
{
    TP->catch_msg("The Blowing Rock IPA goes down smoothly and  "
    + "flavourfully leaving only the slightest aftertaste with a hint of "
    + "applewood. That is one flavourful beverage!\n");
}
