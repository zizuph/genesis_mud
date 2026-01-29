#include "/d/Avenir/common/city/zigg/zigg.h"
//#include "/d/Avenir/include/macros.h"
inherit (ZIG_LIB + "seating");
#include <macros.h>

#define SS_NORMAL      0        /* Person is sitting upright and normally. */
#define SS_STRETCH     1        /* Person is stretched out.                */

int moving_alarm = 0;

public void
create_seating(void)
{
    set_name("hammock");
    add_adj(({"wide","rope","knotted", "two-person"}));
    set_short("wide rope hammock");
    set_long("This hammock is made of rope that is knotted fishnet-style. "+
    "It hangs unobtrusively between two poles and sways lightly in the "+
    "breeze. It looks like it is wide enough to accomodate two people.\n");

    set_seat_names("hammock");

    set_seat_id("_villa_garden_hammock");

    set_max_seat(2);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}

public void
ss_allow_move_stretch(void)
{
    write("The rope cradles your body as you lie back in the "+
        short() +".\n");
    say(QCTNAME(TP) +" stretches out in the "+ short() +
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
        "it and stretch out.\n");
        say("The "+ short() +" rocks gently as "+ QCTNAME(TP) +" "+
        LANG_PWORD(verb) +" down in it and stretches out.\n");
        break;
    }
}


public void
ss_stand(void)
{
	if (moving_alarm)
    {
        remove_alarm(moving_alarm);
		write("You stop the "+ short() +" and carefully exit it.\n");
		return;
	}
	
    write("You carefully exit the "+ short() +", causing it to sway "+
        "backwards a bit.\n");
    say(QCTNAME(TP) + " carefully exits the "+ short() +", causing "+
        "it to sway backwards a bit.\n");
}

void
tell_rock()
{
    remove_alarm(moving_alarm);
	if (random(5) == 0)
    {
        tell_room(environment(this_object()),
            "The "+ short() +" eases to a stop.\n");
		return;
	}
	else
	{
        tell_room(environment(this_object()),
            "The "+ short() +" rocks hypnotically back and forth.\n");
        moving_alarm = set_alarm((itof(20 + random(30))), 0.0, tell_rock); 	
	}
}

public int
f_rock(string str)
{

    if (str == "hammock")
    {
        write("You push the "+ short() +" just enough to make it rock "+
            "back and forth.\n");
        say(QCTNAME(TP)+ " rocks the "+ short() +"\n");
	    if (moving_alarm)
            remove_alarm(moving_alarm);
        moving_alarm = set_alarm((itof(20 + random(30))), 0.0, tell_rock);        		
        return 1;
    }
	
	notify_fail("Push what? The hammock?\n");
    return 0;
}


public int
f_stop(string str)
{

    if (str == "hammock")
    {
        write("You stop the movement of the "+ short() +".\n");
        say(QCTNAME(TP)+ " stops the movement of the "+ short() +".\n");
	    if (moving_alarm)
            remove_alarm(moving_alarm);
		return 1;
    }
  
    notify_fail("Stop what? The swing?\n");
    return 0;
}

/* Add actions to the player. */
public void
init(void)
{
    ::init();

    add_action(  f_rock, "rock"  );
    add_action(  f_rock, "push"  );
    add_action(  f_rock, "swing"  );	
	add_action(  f_stop, "stop"  );
}