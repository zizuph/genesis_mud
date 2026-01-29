/* 
 * Subloc for winners of Scavenger Hunts
 * Creator: Lilith, Nov 1997
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define S_H_SUBLOC  "_scavenger_hunt_subloc"

void
create_object()
{    
    set_name("scavenger hunt winner subloc");    
    add_name(({"subloc", "ribbon"}));    
    add_adj("black");
    set_short("black ribbon with blood-red lettering");
    set_long("This is a black satin ribbon. It is long, narrow, and "+
        "forked at the bottom. The words: \'Winner of the "+
        "All Hallows Eve Scavenger Hunt\' have been printed on it with "+
        "blood-red letters.\n");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);    
    add_prop(OBJ_S_WIZINFO, "This is the object controlling the subloc "+
        "for scavenger hunt winners.\n");
    add_item(({"letters", "words", "lettering", "blood-red lettering"}),
        "The words: \'Winner of the All Hallows Eve Scavenger Hunt\' "+
        "have been printed on the black ribbon with blood-red letters.\n");
    add_item(({"fork", "bottom"}), "It looks like a triangular piece "+
        "of satin was clipped from the bottom of the ribbon.\n");
}

void
enter_env(object dest, object old)
{    
    if (interactive(dest))
      dest->add_subloc(S_H_SUBLOC, this_object());

    ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
    if (interactive(from))
        from->remove_subloc(S_H_SUBLOC);
    ::leave_env(from, to);
}

string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    if (subloc != S_H_SUBLOC)
        return me->show_subloc(subloc, me, for_obj);
    if (me->query_prop("_temp_subloc_show_only_things"))
        return "";
    if (for_obj == me)
        str = "You are a proud winner of the All Hallows Eve "+
              "Scavenger Hunt.\n";    
    else
        str = capitalize(me->query_pronoun()) + " is a proud winner "+
              "of the All Hallows Eve Scavenger Hunt.\n";
    return str;
}

string
query_auto_load()
{ 
    return MASTER_OB(this_object()) + ":";
}

void
init_arg(string str) { }               
