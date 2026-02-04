//-*-C++-*-
// file name:      
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
    add_name(({"quill pen", "pen"}));
    set_name("quill");
    set_short("fragile old quill");
    set_adj(({"fragile", "old"}));
    set_long("This old quill was once used for writing. Its end "+
        "is stained with the faint remnants of black ink. It "+
        "appears to be very fragile and it is doubtful it could "+
        "withstand the pressure necessary for writing.\n");
   
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

    me->catch_msg("As you handle the old quill, you "+
        "catch the psychic scent of someone else's thoughts... "+
        "someone who handled this quill quite often...\n"+ 
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

    me->catch_msg("\nI count decades as if they were days, "+
        "and even they have gotten away from me.\n\n");

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

    me->catch_msg("\nI do not know what mortal Age this is, "+
        "and I find that I no longer care...\nThis solitude "+
        "has infected me with apathy.\n\n");
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

    me->catch_msg("\nThe Fount exists but does not truly live.\n"+
        "I am completely, utterly, alone....\n\n");
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

