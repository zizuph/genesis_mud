/*
 *    Igneous' Trickster Armour shadow
 *
 *    Infects armour with some of the Trickster Mischief (Itchpowder, 
 *    sneezepowder, stinkspalsh) so when a person wears it they become
 *    infected with it.
 *
 *    Copyright (C) Chad Richardson Jan 15/96
 */

inherit "/std/shadow";

#include <language.h>
#include "/d/Shire/trickster/trickster.h"
#include "/d/Shire/common/defs.h"

//    Prototypes
void remove_trick_armour_shadow();

object old_af;
string trap_setter, trap_type;
int  trap_qual, old_search_fun, old_search_time;

void
set_trap_qual(int qual)
{
    trap_qual = qual;
}

void
set_trap_setter(string name)
{
    trap_setter = lower_case(name);
}

void
set_trap_type(string type)
{
    trap_type = lower_case(type);
}

void
set_up_trap()
{
    old_search_fun = shadow_who->query_prop(OBJ_S_SEARCH_FUN);
    old_search_time = shadow_who->query_prop(OBJ_I_SEARCH_TIME);
    shadow_who->add_prop(OBJ_I_SEARCH_TIME,4);
    shadow_who->add_prop(OBJ_S_SEARCH_FUN, "uncover_trick");
    old_af = shadow_who->query_af();
    shadow_who->set_af(TO);
}

public varargs string
long(mixed for_obj)
{
    int aware;
    string   extra;

    aware = TP->query_skill(SS_AWARENESS) - trap_qual;
    if (aware >= 33)
	extra = CAP(LANG_THESHORT(shadow_who)) + " seems "+
	"to have been tampered with.\n";
    else
	extra = "";
    return shadow_who->long(for_obj) + extra;
}

public string
wear(object what)
{
    object affliction;

    if (TP->query_real_name() == trap_setter)
    {
	return "Now why would you want to spring your trap after going "+
	"to all that trouble of setting it up?\n";
    }
    switch (trap_type)
    {
    case "stink":
	affliction = clone_object(STINK_OBJ);
	affliction->start_stinking(TP);
	affliction->move(TP);
	TP->catch_msg("You notice a horrible smell coming from the "+
	  shadow_who->short()+" as you wear it.\n");
	break;
    case "sneeze":
	affliction = clone_object(SNEEZE_OBJ);
	affliction->start_sneezing(TP);
	affliction->move(TP);
	TP->catch_msg("A bit of powder falls in your face as you wear the "+
	  shadow_who->short()+".\n");
	break;
    default:
	affliction = clone_object(ITCH_OBJ);
	affliction->start_itching(TP);
	affliction->move(TP);
	TP->catch_msg("You feel a slight twitch as you wear the "+
	  shadow_who->short()+".\n");
	break;
    }
    set_alarm(0.5,0.0,&remove_trick_armour_shadow());
    return shadow_who->wear(what);
}

void
remove_trick_armour_shadow()
{
    remove_shadow();
}

void
uncover_trick(object searcher, string dummy)
{
    string what, how;

    switch (trap_type)
    {
    case "sneeze":
	what = "sneezing powder";
	how = "shake";
	break;
    case "stink":
	what = "smelly liquid";
	how = "cleaning";
	break;
    default:
	what = "itching powder";
	how = "shake";
	break;
    }
    set_alarm(1.0,0.0,remove_shadow);
    tell_room(ENV(searcher),QCTNAME(searcher)+" found something "+
      "in the "+shadow_who->short()+".\n",({searcher}));
    return "You find some "+what+" in the "+shadow_who->short()+
    "!  You give the "+shadow_who->short()+" a good "+how+
    " which removes the "+what+" from it.\n";
}

int
query_trickster_shadow()
{
    return 666;
}

void
remove_shadow()
{
    if (old_search_fun)
	shadow_who->add_prop(OBJ_S_SEARCH_FUN,old_search_fun);
    else
	shadow_who->remove_prop(OBJ_S_SEARCH_FUN);
    if (old_search_time)
	shadow_who->add_prop(OBJ_I_SEARCH_TIME,old_search_time);
    else
	shadow_who->remove_prop(OBJ_I_SEARCH_TIME);
    shadow_who->set_af(old_af);
    destruct();
}
