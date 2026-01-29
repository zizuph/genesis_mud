// -*-C++-*-
// file name:    /d/Avenir/common/clubs/mummer/obj/mummer_balloon
// creator(s):   Lilith 10 July 1997
// last update:  Lilith 04 Sept 1997
// purpose:      This is used in the mummer emote 'mtwist'
// note:         It is formed by twisting intestinal leftovers 
//               into balloon figures.
//               To add new figures, change the figure_type mapping
//               in the mummer_club.h
// bug(s):
// to-do:

/* Inherit the standard object file */
inherit "/std/object";
inherit "/lib/keep";

#include <language.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "../mummer_club.h"

string fig, from;
public void set_figure(string str)   {    fig = str;      }
public void set_from(string str)     {    from = str;     }
public string query_figure()         {    return fig;     }
public string query_from()           {    return from;    }

string
long_desc()
{
    string str;
    if (!from)
        from = "animal intestine";
    if (member_array(fig, figures) == -1)
    {
            str = "This figure is a humorous and surprisingly accurate "+
                  "simulacrum of "+ LANG_ADDART(fig) +".";
    }                 
    else
        str = figure_type[fig][1] +".";

    return  str + " It is the handiwork of a Mummer of Sybarus, "+
            "and is made from an inflated "+ from +".\n";
}

string
short_desc()
{
    return fig +" balloon figure";
}

int
pop_it()
{
    if (!query_figure())
    {
        write("You hear a loud 'pop!' and the balloon figure deflates.\n");
        say("You hear a loud pop.\n");
        set_alarm(1.0, 0.0, &remove_object());
        return 1;
    }
    return 0;
}

int 
pop_check(string str)
{
    if (!str)
        return 0;

    if (!present(this_object(), this_player()))
    {
       notify_fail("You would need to be holding it.\n");
       return 0;
    }

    write("You hear a loud 'pop!' and the "+ short() +" deflates.\n");
    say("You hear a loud pop.\n");
    set_alarm(1.0, 0.0, &remove_object());
    return 1;
}

void
create_figure()
{
    add_name(fig);
    add_name(lower_case(fig));
    add_name(lower_case(fig) +" balloon figure");
    add_adj(fig);
   
    set_short(VBFC_ME("short_desc"));
    set_long(VBFC_ME("long_desc"));
}

void
create_object()
{
    if (!IS_CLONE)
        return; 

    set_name("figure");
    add_name(({"balloon", "balloon figure"}));
    set_adj("balloon");
    set_keep(1);

    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
    set_alarm(2.0, 0.0, &pop_it());
}

void
init()
{
    ::init();

    add_action(pop_check, "pop");
    add_action(pop_check, "puncture");
}

public mixed
query_recover()
{
    return 0;
}
