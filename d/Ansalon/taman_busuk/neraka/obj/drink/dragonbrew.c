/*
 * Ashlar, 8 Jun 97
 *
 * This drink is addictive, in the sense that the drinker will get periodic
 * messages telling him he should have another drink. This is accomplished
 * by cloning an addiction object ~neraka/obj/bdadd into the player. This
 * addiction goes away when the player quits, or at armageddon.
 * The addiction has no effects, positive or negative, other than the
 * messages.
 */

inherit "/std/drink";
#include <stdproperties.h>
#include "../../local.h"
#include "/d/Ansalon/common/defs.h"

create_drink()
{
    set_soft_amount(220);
    set_alco_amount(45);    // nominal value 213 cc
    set_name("dragonbrew");
    add_name("brew");
    add_name("glass");
    set_adj("black");
    add_adj("dragon");

    set_short("glass of Black Dragonbrew");
    set_pshort("glasses of Black Dragonbrew");

    set_long("The Dragonbrew is black or dark brown, much in the manner " +
        "of muddy water. It is chilled, but there are wisps of smoke " +
        "coming from the drink.\n");
   
    add_prop(OBJ_I_WEIGHT, 220);
    add_prop(OBJ_I_VOLUME, 220);

}

void
special_effect(int numofdrinks)
{
    object add;
    

    if (add=present("_bd_add_", TP))
    {
        add->satisfy();
        write("Ahh, that was just what you needed.\n");
    }
    else
    {
        seteuid(getuid());
        add = clone_object(NOBJ + "bdadd");
        add->move(TP,1);
        add->satisfy();
    	write("Hmm... The Dragonbrew was quite tasty, despite how it looked.. " +
            "In fact, you wouldn't mind another of them..\n");
    }
        
}

