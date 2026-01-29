inherit "/std/object";

#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"

#define SP_CLEANSE_SKILL_LIST	({ SKILL_AVG, TS_INT, TS_WIS, SKILL_END, \
                                   SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                                   SKILL_WEIGHT, 50, SKILL_AVG, SS_FORM_ABJURATION, SS_ELEMENT_LIFE, SKILL_END })

public int do_something(string vb, string arg);
public int do_test(string arg);
public int do_stop(string arg);

int     alarm_id;
int     *x = allocate(51);
int     sum, tot;

void
create_object()
{
    set_name(({"object", "dummy", "test", }));
    set_adj(({"test", }));

    set_short("test object");
    set_long("A test object.\n");
}

void
init()
{
    ::init();

    add_action(do_test, "test");
    add_action(do_stop, "stop");
    add_action(&do_something("act", ), "act");
    add_action(&do_something("do", ), "do");
}

public int
do_something(string vb, string arg)
{
    string  verb = query_verb();

    write("Function do_something called with verb \""+verb
      + "\" and argument \"" + arg + "\".\n");
    write("Verb = \"" + vb + "\".\n");

    return 1;
}

int
do_test(string arg)
{
    float  val, sum = 0.0, mean;
    int    i, n;
    string  foo;

   sscanf(arg, "%d", n);
   write("\n\tn = " + n + ".\n\n");

    for (i = 0; i < n; i++)
    {
        sum += -log(rnd()) * 1.0;
    }

    write(n + ": " + ftoa(sum) + ", " + ftoa(sum/itof(n)) + "\n");
    return 1;
}

void
do_a_test(object tp, string str)
{
    tp->catch_msg("TEST EXECUTED!!!! " + str + "\n\n");
}

int
do_stop(string str)
{
    if (alarm_id && sizeof(get_alarm(alarm_id)))
    {
        write("Stopping the alarm now!\n");
        remove_alarm(alarm_id);
        alarm_id = 0;
        return 1;
    }
    notify_fail("Stop what?\n");
    return 0;
}

void
remove_object()
{
    find_player("olorin")->catch_msg(OB_NAME(TO)+ " destructed!\n");
    ::remove_object();
}
