//-*-C++-*-
// file name:      blotter.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
inherit "/std/object";
#include <stdproperties.h>
#include "../guild.h";

private static int msg_id;

void start_msg(object me);
void do_msg1(object me);
void do_msg2(object me);
void do_msg3(object me);

void
create_object()
{
    add_adj(({"antique", "ink"}));
    set_name("blotter");
    set_short("antique ink blotter");
    set_long("This is an antique blotter used to absorb excess ink. "+
        "It is curved in such a way that it is easy to roll over "+
        "writing without smudging it.\n ");
   
    add_prop(OBJ_I_VOLUME, 100);   
    add_prop(OBJ_I_WEIGHT, 100);   
    add_prop(OBJ_I_VALUE, 100 + (random(100)));
}             

private void
start_msg(object me)
{
    if (!IS_VAMP(me))
    {
        remove_alarm(msg_id);
        return;
    }

    me->catch_msg("As you handle the blotter, you "+
        "catch the psychic scent of someone else's thoughts... "+
        "someone who handled this blotter quite often...\n"+ 
        "        ...Isabella...\n");

    msg_id = set_alarm(3.0, 0.0, &do_msg1(me));
}

private void
do_msg1(object me)
{  
    if (!IS_VAMP(me))
    {
        remove_alarm(msg_id);
        return;
    }

    me->catch_msg("\nAt times I long for death, for the end "+
        "of this existence. I lay in my coffin and dream of "+
        "destroying the Fount and myself.\n\n");

    msg_id = set_alarm(3.0, 0.0, &do_msg2(me));
}

private void
do_msg2(object me)
{  
    if (!IS_VAMP(me))
    {
        remove_alarm(msg_id);
        return;
    }

    me->catch_msg("\nBut I cannot. It is one thing to kill "+
        "myself or another. It is quite a different matter "+
        "to exterminate an entire people. I must persevere.\n\n");

    msg_id = set_alarm(3.0, 0.0, &do_msg3(me));
}

private void
do_msg3(object me)
{  
    if (!IS_VAMP(me))
    {
        remove_alarm(msg_id);
        return;
    }

    me->catch_msg("\nThe Eldest must survive, at all costs. "+
        "He is the Fount of our existance. Without Him, all "+
        "my kind die.\n\n");
    remove_alarm(msg_id);
}


public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!IS_VAMP(to))
	return;

    if (msg_id)
	return;

    msg_id = set_alarm(2.0, 0.0, &start_msg(to));

}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (msg_id)
      remove_alarm(msg_id);
}

