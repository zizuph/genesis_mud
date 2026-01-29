#include <macros.h>
#include <language.h>
#include "zigg.h"

inherit (ZIG_LIB + "seating");


#define SS_NORMAL      0        /* Person is sitting upright and normally. */
#define SS_STRETCH     1        /* Person is stretched out.                */


public void
create_seating(void)
{
    set_name("hammock");
    add_adj(({"wide","webcloth"}));
    set_short("wide webcloth hammock");
    set_long("The hammock is a light, sprang woven webbing that opens effortlessly "+
    "to accommodate the user. It is hand woven by artisans out of thin "+
    "strands of webcloth that are silky and incredibly strong. The strands "+
    "forms tiny cells that support the body in effortless bliss and "+
    "allow the air to circulate around you. They come together at each "+
    "end of the hammock, forming thicker cords which wrap around the "+
    "linden trees to suspend it.\n");

    set_seat_names("hammock");

    set_seat_id("__zigg_garden_hammock");

    set_max_seat(2);
    set_lay_num(1);

    set_shift_seat(1);
    set_allow_kinky(1);
}

public void
ss_allow_move_stretch(void)
{
    write("The webcloth molds to your body as you lie back in the "+
        short() +", cradling your body and allowing you to float in total "+
        "security.\n");
    say(QCTNAME(TP) +" lies back and stretches out in the "+ short() +
        "\n", ({ TP }));
}


public void
ss_seated(int state)
{
    string verb = query_verb();

    switch(state)
    {
    case SS_NORMAL:
        write("The "+ short() +" rocks gently as you "+ verb +" down on "+
        "it.\n");
        say("The "+ short() +" rocks gently as "+ QCTNAME(TP) +" "+
        LANG_PWORD(verb) +" down in it.\n");
        break;

    case SS_STRETCH:
        write("The "+ short() +" rocks gently as you "+ verb +" down on "+
        "it and stretch out. The webcloth molds to your body as you sink "+
        "into the hammock, cradling your body and allowing you to "+
        "float in total security.\n");
        say("The "+ short() +" rocks gently as "+ QCTNAME(TP) +" "+
        LANG_PWORD(verb) +" down in it and stretches out.\n");
        break;
    }
}


public void
ss_stand(void)
{
    write("You carefully arise from the "+ short() +", causing it to swing "+
        "slightly.\n");
    say(QCTNAME(TP) + " arises from the "+ short() +", causing it to swing "+
        "slightly.\n");
}

public int
f_rock(string str)
{
    if (str == "hammock")
    {
        if(query_seated(TP))
        {
            write("You rock the hammock slowly, making it sway as though "+
                "stirred by a gentle breeze.\n");
            say(QCTNAME(TP)+ " rocks the hammock slowly, making it sway as "+
                "though stirred by a gentle breeze.\n");
            return 1;
        }
        else
        {
            notify_fail("You should sit in it first.\n");
            return 0;
        }
    }
    notify_fail("Rock what? The hammock?\n");
    return 0;
}


/* Add actions to the player. */
public void
init(void)
{
    ::init();

    add_action(  f_rock, "rock"  );
}