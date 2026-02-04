/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define SUBLOC "aura_subloc"
#define TO     this_object()
#define ETO    environment(TO)

public void wmsg(string msg, int remove_flag);
public void set_duration(int dur);

int duration;

void
create_object()
{
   set_name("aura");
   set_adj("sacred");
   set_no_show();
   add_prop(OBJ_I_LIGHT, 10);
   add_prop(OBJ_M_NO_DROP, 1);
   duration = 20;
}

public void
set_duration(int dur)
{
    duration = dur;
    if (duration < 6) duration = 6;
    if (duration > 4000) duration = 4000;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (living(to)) {
	    to->add_subloc(SUBLOC, TO);
	    set_alarm(2.0*itof(duration)/3.0, -1.0, "wmsg",
	              "Your sacred aura looks a bit fainter.\n", 0);
	    set_alarm(itof(duration), -1.0, "wmsg",
	              "Your sacred aura fades away.\n", 1);
    } else {
	    remove_object();
    }
}

public void
wmsg(string msg, int remove_flag)
{
    if (living(ETO)) ETO->catch_msg(msg);
    if (remove_flag) remove_object();
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from)) {
        from->remove_subloc(SUBLOC);
    }
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == carrier)
        str = "You are surrounded by a mysterious, flaming blue aura.\n";
    else
        str = capitalize(carrier->query_pronoun()) +
              " is surrounded by a mysterious, flaming blue aura.\n";
              
    return str;
}
