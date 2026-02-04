//-*-C++-*-
// file name:      bowl.c 
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
    add_name(({"flower bowl", "flower-bowl", "porcelain bowl"}));
    set_name("bowl");
    set_short("bowl of dried flowers");
    set_long("This porcelain bowl is nearly perfectly round. There is a "+
        "hole in the top through which flowers have been inserted.\n ");
    add_item(({"flowers", "wildflowers", "everlasting wildflowers"}), 
        "Everlasting wildflowers have dried up. Perfectly preserved, "+
        "they nevertheless look as if they would crumble to dust with "+
        "the slightest touch.\n");
    add_cmd_item(({"flowers", "wildflowers", "everlasting wildflowers", "flower"}), 
        ({"get", "pick", "take"}),
        "Handling the flowers would surely destroy them. They were placed "+
        "here for a reason by another of your kind, and that seems "+
        "compelling reason enough for you to leave them be.\n");
   
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

    me->catch_msg("As you handle the bowl of dried flowers you "+
        "catch the psychic scent of someone else's thoughts... "+
        "someone who handled this bowl quite often...\n"+ 
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

    me->catch_msg("I have begun venturing out from this "+
        "crypt. I can travel far in mist form, and have "+
        "discovered something interesting.\n");

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

    me->catch_msg("\nIt appears that when I drink "+
        "someone's blood, I can somehow borrow some of his "+
        "qualities.\n\n");

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

    me->catch_msg("\nHow exciting! I actually experienced "+
        "a thrill when one of my meals tried to knife me "+
        "and by virtue of the knowlege gained from his "+
        "own blood, I easily disarmed him.\n\n");
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

