// /d/Avenir/common/outpost/obj/seats/basket_swing.c
// Lilith, Jan 2022
// uses the seating lib developed by Lucius and Zielia

#include <macros.h>
#include <language.h>
#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");


#define SS_NORMAL      0        /* Person is sitting upright and normally. */
#define SS_STRETCH     1        /* Person is stretched out.                */

int moving_alarm = 0;

public void
create_seating(void)
{
    set_name("swing");
	add_name("basket swing");
    add_adj(({"wide","basket"}));
    set_short("wide basket swing");
    set_long("A large, wide basket hangs from the ceiling "+
    "by a thick chain. It looks like it could easily accomodate a "+
    "few people. The base of the basket is covered in layers of "+
    "furs, while a satin bolster cushions the circular perimeter.\n");

    set_seat_names(({"basket", "swing"}));

    set_seat_id("_basket_swing");

    set_max_seat(4);    // 4 can sit in it.
    set_lay_num(2);     // laying down takes up 2 seating spaces
    set_shift_seat(1);  // no dumping on the floor
    set_allow_kinky(1); // someone can sit on someone else's lap
}

public void
ss_allow_move_stretch(void)
{
    write("You stretch out on the soft furs lining the swing and "+ 
	"rest your head against the satin bolster.\n");
    say(QCTNAME(TP) +" stretches out on the furs lining the "+ 
    short() +"\n", ({ TP }));
}


public void
ss_seated(int state)
{
    string verb = query_verb();

    switch(state)
    {
    case SS_NORMAL:
        write("The "+ short() +" sways gently as you "+ verb +
        " down in it.\n");
        say("The "+ short() +" sways gently as "+ QCTNAME(TP) +" "+
        LANG_PWORD(verb) +" down in it.\n");
        break;

    case SS_STRETCH:
        write("The "+ short() +" sways slightly as you "+ verb +
        " down in it. The silky furs caress your flesh as you "+
        "stretch out in it.\n");
        say("The "+ short() +" sways slightly as "+ QCTNAME(TP) +
        " stretches out in it.\n");
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
        "a bit.\n");
    say(QCTNAME(TP) + " carefully exits the "+ short() +", causing "+
        "it to sway just a bit.\n");
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

void
tell_spin()
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
            "The "+ short() +" completes a rotation and continues to spin "+
            "lazily around.\n");
        moving_alarm = set_alarm((itof(50 + random(30))), 0.0, tell_spin); 	
	}
}

public int
f_rock(string str)
{

    if (str == "basket" || str == "swing" || str == "basket swing")
    {
        write("You push the basket swing just enough to make it rock "+
            "back and forth over the water.\n");
        say(QCTNAME(TP)+ " rocks the basket swing, making it rock "+
            "back and forth over the water.\n");
	    if (moving_alarm)
            remove_alarm(moving_alarm);
        moving_alarm = set_alarm((itof(20 + random(30))), 0.0, tell_rock);        		
        return 1;
    }
	
	notify_fail("Push what? The swing?\n");
    return 0;
}

public int
f_spin(string str)
{
    if (str == "basket" || str == "swing" || str == "basket swing")
    {
        write("You give the basket swing a push that sends it "+
            "spinning at a leisurely pace.\n");
        say(QCTNAME(TP)+ " gives the "+ short() +" a push that "+
            "sends it spinning at a leisurely pace.\n");
	    if (moving_alarm)
            remove_alarm(moving_alarm);
        moving_alarm = set_alarm((itof(20 + random(30))), 0.0, tell_spin);  		
	    return 1;
    }
	
    notify_fail("Spin what? The swing?\n");
    return 0;
}

public int
f_stop(string str)
{

    if (str == "basket" || str == "swing" || str == "basket swing")
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
	add_action(  f_rock, "swingrock");  
	
	add_action(  f_spin, "spin"  );  
    add_action(  f_spin, "swingspin");	
	
	add_action(  f_stop, "stop"  );
}