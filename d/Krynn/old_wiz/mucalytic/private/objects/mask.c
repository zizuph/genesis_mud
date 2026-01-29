/* One of Mucalytic's descriptions. 13th of September 1995. */

inherit "/std/object";

#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define TO              this_object()
#define TP              this_player()
#define C(str)          capitalize(str)
#define PRONOUN(x)      x->query_pronoun()
#define POSSESSIVE(x)   x->query_possessive()

void create_object()
{
    set_name("mask");
    set_adj("carved");
    add_adj("ebony");
    set_long("The mask gives a sublocation description.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 550);
    add_prop(OBJ_M_NO_STEAL, C(LANG_THESHORT(TO))+" glows dully as you try "+
                                                  "to steal it.\n");
    add_prop(OBJ_M_NO_GIVE, C(LANG_THESHORT(TO))+" glows dully as you try "+
                                                 "to give it away.\n");
    add_prop(OBJ_M_NO_DROP, "You seem unable to drop "+(LANG_THESHORT(TO))+
                            ".\n");
    add_prop(OBJ_M_NO_SELL, "You feel compelled to keep "+(LANG_THESHORT(TO))+
                            ".\n");
}

void init()
{
    ::init();

    TP->add_subloc("mucalytics_features", TO);
}

string show_subloc(string subloc, object me, object for_obj)
{
    if(me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return("You have a tired but vigilant look in your eyes.\n");

    if(for_obj == me)
        return("You have a tired but vigilant look in your eyes.\n");
    else
        return(C(PRONOUN(me))+" has a tired but vigilant look in "+
         POSSESSIVE(me)+" eyes.\n");
}

string query_auto_load()
{
    return MASTER;
}
