/*
 * The bank in the Solamnian Guild
 *
 * Made by Nick
 * modified by Teth, Dec 6 1996.
 */
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit IN_BASE;
inherit "/lib/bank";
//inherit "/d/Krynn/common/warfare/recruit_base";

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */
void
create_vin_room()
{
    object xx;
    config_default_trade();
    set_short("The Vingaard Keep Bank");
    set_long("This is the Vingaard Keep Branch of the Palanthian " +
        "Bank. A teller sits behind a barred window, performing " +
        "the necessary functions of the bank. This bank is used " +
        "to handle the coffers of the Solamnian Knights, and is " +
        "also used quite frequently by the militia. There is a " +
        "poster near the teller's window, and nearby is a " +
        "sturdy plaque on the wall. An exit leads south back to the " +
        "streets of Vingaard Keep.\n");
    /*
      AI( ({"notice", "notice of war"}), "To support the war effort, you"
      + " can 'raise' funds here.\n");
    */
    AI(({"plaque","sturdy plaque"}),"A sturdy plaque with " +
        "forthright information on how to exchange money.\n");
    ACI(({"plaque","sturdy plaque","information",
              "forthright information"}),"read","@@standard_bank_sign");
    AI("poster","The poster states the current exchange rates " +
        "for minimizing one's coins.\n");
    ACI("poster","read","The exchange rates are:\n\n" +
        "Knight of Solamnia       - 15%\n"+
        "Palanthian Militia       - 15%\n"+
        "Solamnian Militia        - 15%\n"+
        "Solanthian Militia       - 15%\n"+
        "\nGeneral populace         - 25%\n\n"+
        "War donations            - No rates! See the notice of war\n\n");
    AI("teller","The teller is masked by the dark window and bars, " +
        "so it is impossible to get a good look.\n");
    AI(({"barred window","window","teller's window"}),"A dark " +
        "window, perhaps it would be easier to see through from " +
        "the other side. It has bars placed in front of it.\n");
    AI(({"bars","bar"}),"Every bar is made of sturdy Solamnic " +
        "steel.\n");
    AI(({"floor","ceiling","wall"}),"It is composed of fortified " +
        "hematite.\n");
    AI("walls","They are made of fortified hematite.\n");

    config_trade_data();

    AE(VROOM + "ss5", "south", 0);

    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_bank_id(802, "Vingaard Keep");
    xx->set_short("deposit");
    xx->set_no_show_composite(1);
    xx->move(this_object());
}


int
hook_allowed_to_raise_funds(object who)
{
    return 1;
}

fee()
{
    if (MEMBER(TP))
    {
        set_bank_fee(15);
        config_trade_data();
        return;
    }
    set_bank_fee(25);
    config_trade_data();
    return;
}

void
init()
{
    ::init();
    bank_init();
}

change(string str)
{
    fee();
    return ::change(str);
}

test(string str)
{
    fee();
    return ::test(str);
}

minimize(string str)
{
    fee();
    return ::minimize(str);
}

standard_bank_sign()
{
    fee();
    return ::standard_bank_sign();
}

void
bank_hook_minimized(string pay_text, string got_text)
{
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
    write("You minimize " + pay_text + " and now have " +
        got_text + " on you.\n");
}

