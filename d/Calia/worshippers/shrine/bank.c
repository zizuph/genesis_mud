
inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"

#define NUM sizeof(MONEY_TYPES)

void
create_room()
{
    set_short("Shrine Bank");
    set_long("You have entered a banking chamber in the Shrine.  "+
        "Here you can rid yourself "+
        "of encumbering coins by depositing them in the care of the "+
        "Gnomes of Genesis.  There is a small plaque on the western wall "+
        "that you may read.  Right below that plaque is a sign.  Behind "+
        "a glass wall you see a gnome sitting on a chair waiting to "+
        "help you with your banking needs. You notice a carved archway "+
        "in the southeast corner.\n");

    add_item(({"archway","southeast corner","southeast"}),
        "The archway emits a faint glow as it opens into " +
        "the chamber beyond.\n");
    add_item("gnome","The gnomes seems to be quite comfortable in his "+
        "glass room.  He has many gizmos and gadgets around him to "+
        "occupy his time when there are no customers to help.\n");

    add_item(({"gizmo","gizmos","gadget","gadgets"}),"You don't recognize "+
        "any of the gizmos or gadgets that the gnome is fiddling with.\n");



    clone_object("/d/Genesis/obj/deposit")->move(this_object(),1);

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read","@@standard_bank_sign");

    config_default_trade();
    set_bank_fee(30);
    config_trade_data();
    set_money_give_out(({100000,100000,100000,100000}));
    set_money_give_reduce(({0,0,0,0}));
    set_money_give_max(100000);

    add_exit(WOR_SHRINE+"common","up",0,1);
    add_exit(WOR_SHRINE+"library","southeast",0,1);

}

init()
{
    ::init();
    bank_init();
}

void
bank_hook_minimized(string pay_text, string get_text)
{
    write("You minimize your "+pay_text+" and get "+get_text+".\n");
    say(QCTNAME(this_player())+" minimized "+this_player()->query_possessive()+
        " coins.\n");
}

string
tax()
{
    return "30 percent";
}
