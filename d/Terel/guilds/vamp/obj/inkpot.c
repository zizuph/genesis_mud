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
    add_name(({"pot", "ink pot"}));
    set_name("inkpot");
    set_short("glass inkpot");
    set_long("This is a glass inkpot with the dried remnants of "+
        "ink at the bottom.\n");
   
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

    me->catch_msg("As you handle the inkpot, you "+
        "catch the psychic scent of someone else's thoughts... "+
        "someone who handled this inkpot quite often...\n"+ 
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

    me->catch_msg("\nHe dreams...\nHe dreams and even awake, "+
        "everything around Him has the quality of dreams.\n\n");

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

    me->catch_msg("\nMy only source of blood, I have drunk "+
        "from Him until surely I am but an extension of Him "+
        "and His power.\n\n");

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

    me->catch_msg("\nWhen I feed, I have visions, and the "+
        "visions have told me much of what my Sire did not...\n\n");
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

