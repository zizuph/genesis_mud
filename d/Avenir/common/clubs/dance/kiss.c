//-*-C++-*-
// file name:    /d/Avenir/common/clubs/dance/kiss.c
// creator(s):   Lilith, 28 July 1997
// revised:
// purpose:      To leave a kiss-mark on the targets of the dancer
//               dmark emote.  
// note:         It can be wiped, rubbed, or washed off, and should
//               remove itself after a time.
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

#include <macros.h>


void
enter_env(object dest, object old)
{
    if (interactive(dest))
        dest->add_subloc("kiss_subloc",this_object());
    ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
    if (interactive(from))
        from->remove_subloc("kiss_subloc");
    ::leave_env(from, to); 
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != "kiss_subloc")
        return me->show_subloc(subloc, me, for_obj);
    
    if (me->query_prop("_temp_subloc_show_only_things"))
        return "";
    
    if (for_obj == me)
        return "";
    else
        str =  "has the imprint of a red lipstick kiss on "+
            me->query_possessive() +" cheek";
    
    return capitalize(me->query_pronoun()) +" "+ str + ".\n";
}

void
start_countdown()
{
    set_alarm(2000.0, 0.0, &remove_object());
}

int
dwipe(string str)
{

    if (!str || !strlen(str))    
        return 0;
  
    if (!parse_command(str, ({ }),
        "[a] / [the] 'kiss' / 'lipstick' / 'mark' / 'imprint' "+
        "'off' / 'from' [face] / [cheek]"))
        return 0;    
    
    write("You reach up and "+ query_verb() +" the kiss-mark "+
        "off your cheek.\n");
    say(QCTNAME(this_player()) +" wipes the kiss-mark off of "+ 
        this_player()->query_possessive() +" cheek.\n");

    set_alarm(2.0, 0.0, &remove_object());
    return 1;
}

void
create_object()
{
    set_no_show();
    set_name("_dancer_kiss");
    start_countdown();
}

void
init()
{
    ::init();
    add_action(dwipe, "wipe");
    add_action(dwipe, "rub");
    add_action(dwipe, "wash");
}

