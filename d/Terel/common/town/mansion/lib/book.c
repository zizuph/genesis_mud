inherit "/std/object.c";

#include "lib_defs.h"

#define CYCLE     25 + random(11)
#define LIFETIME 150

int aid1 = 0, aid2 = 0, time_left = LIFETIME;
string the_text = "";

public void
set_text(string which_file)
{
    the_text = LIBRARY + "books/" + which_file;
}

public string
choose_name()
{
    switch (random(8))
    {
        case 0: return "book";
        case 1: return "tome";
        case 2: return "pamphlet";
        case 3: return "volume";
        case 4: return "manual";
        case 5: return "scroll";
        case 6: return "manuscript";
        case 7: return "text";
    }
    return "book";
}

public string
choose_color()
{
    switch (random(9))
    {
        case 0: return "red";
        case 1: return "blue";
        case 2: return "yellowed";
        case 3: return "green";
        case 4: return "white";
        case 5: return "brown";
        case 6: return "black";
        case 7: return "gilded";
        case 8: return "pink";
    }
    return "yellowed";
}

public string
choose_adj()
{
    switch (random(12))
    {
        case  0: return "ancient";
        case  1: return "old";
        case  2: return "dusty";
        case  3: return "tall";
        case  4: return "thin";
        case  5: return "thick";
        case  6: return "decrepit";
        case  7: return "leather-bound";
        case  8: return "dog-eared";
        case  9: return "moth-eaten";
        case 10: return "tattered";
        case 11: return "well-read";
    }
    return "old";
}

public object
carrier()
{
    if (environment() && living(environment()))
        return environment();
    return 0;
}

public void
destroy_book()
{
    if (aid1) {
        remove_alarm(aid1);
        aid1 = 0;
    }
    aid2 = 0;
    if (carrier())
        carrier()->catch_msg("The " + short() +
                             " disintegrates completely.\n");
    remove_object();
}

public void
cycle_msg()
{
    add_prop(OBJ_I_VALUE, query_prop(OBJ_I_VALUE)/2);
    if (carrier())
        carrier()->catch_msg("You notice that the " + short() +
                             " is rapidly disintegrating.\n");
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (to && living(to)) {
        aid1 = set_alarm(itof(CYCLE/2), itof(CYCLE), cycle_msg);
        aid2 = set_alarm(itof(time_left), -1.0, destroy_book);
    }
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (from && living(from)) {
        if (aid1) {     /* We must remove the cycle alarm */
            remove_alarm(aid1);
            aid1 = 0;
        }
        if (aid2) {     /* Let's also remove the dest alarm */
            time_left = ftoi(get_alarm(aid2)[2]);
            remove_alarm(aid2);
            aid2 = 0;
        }
    }
}

public void
create_object()
{
    set_name(choose_name());
    set_adj(choose_color());
    add_adj(choose_adj());
    set_long("This " + short() + " has not well withstood the test " +
             "of time; you doubt it will long withstand even gentle " +
             "handling. The words are faded and you cannot even make " +
             "out the title.\n");

    add_prop(OBJ_I_VOLUME, random(6000) + 500);
    add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_VOLUME)/2);

    add_prop(OBJ_I_VALUE, 0);
}

public int
do_read(string str)
{
    object ob;
    
    notify_fail("Read what?\n");
    if (!str)
        return 0;
    
    if (!parse_command(str, TP(), "%o", ob))
        return 0;
    
    if (ob != TO())
        return 0;
            
    say(QCTNAME(TP()) + " reads from the " + short() + ".\n");
    if (strlen(the_text) && file_size(the_text) > 0) {
        seteuid(getuid());
        clone_object(MORE_OBJ)->more(the_text, 3);
    } else {
        if (strlen(the_text))
            write(the_text);
        else
            write("You examine the " + short() + " carefully, but it " +
              "is a hopeless study--the pages have faded with the " +
              "passage of the years, until not a word remains legible.\n");
    }
    return 1;
}

public void
init()
{
    ::init();
    
    if (environment() == TP())
        add_action(do_read, "read");
}
