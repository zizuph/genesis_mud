/*
 *
 *  Modification log:
 *
 *     2008-01-09, Toby: Fixed for new bank support.
 */


#pragma strict_types
inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

object  deposit;

public void
create_gondor()
{
    set_short("the branch of the money-deposit service in Minas Tirith");
    set_long("You are in a side-room of the Bank of Gondor. This is the\n"+
        "branch of the Gnomes of Genesis money-deposit in Minas Tirith,\n"+
        "opened quite recently as a service to the travellers of Genesis\n"+
        "who have found their way to Gondor in Middle-Earth. The service is\n"+
        "quite special, as gnomes are not that common in Minas Tirith, but\n"+
        "this might be the first step towards a better relationship.\n"+
        "The main bank is back east.\n");
    add_exit("/d/Gondor/minas/rooms/mtbank","east",0,0);
    add_prop(ROOM_I_INSIDE,1);

    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_bank_id(1803, "Minas Tirith");
    deposit->move(this_object());
}
