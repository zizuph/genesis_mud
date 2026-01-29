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
    set_alco_amount(18);
    set_name("ale");
    add_name(({"pale ale"}));
    add_adj(({"pale", "blowing", "rock", "blowing rock"}));
    set_short("pint of Blowing Rock Pale Ale");
    set_pshort("pints of Blowing Rock Pale Ale");
    set_long("A classic and malty pint of pale ale from the mountains east "
    + "of Palanthas. It is served on tap at the Tower of Arms' Draft Pub.\n");
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

    if (str != "ale" && str != "pale ale" && str != "rock pale ale"
        && str != "blowing pale ale" && str != "blowing rock pale ale"
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
    TP->catch_msg("The Blowing Rock pale ale goes down smoothly and  "
    + "flavourfully leaving only the slightest aftertaste with a hint of "
    + "applewood.\n");
}
