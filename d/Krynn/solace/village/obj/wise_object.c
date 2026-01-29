/* created by Aridor 12/01/94
 * 
 * The pin of the Wise People of Genesis
 * It's the guild (club) object.
 *
 */


inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#define WISE_ID        "krynn_wise_object"


void
convert_me_to_new_version()
{
    object owner, newob;
    seteuid(getuid(TO));
    owner = E(TO);
    newob = clone_object("/d/Krynn/solace/new_village/obj/wise_object");
    newob->move(owner,1);
    write_file("/d/Krynn/solace/village/log/wise_log",
	       TP->query_name() + " converted to new object " + 
	       extract(ctime(time()), 4, 15) + "\n");
    set_alarm(0.1,0.0,"remove_object");
}

string 
query_auto_load() 
{
    return MASTER_OB(TO) + ":";
}

void
init_arg(string arg)
{ 
    set_alarm(5.0,0.0,"convert_me_to_new_version");
}

void
create_object()
{
    set_name("pin");
    add_pname(WISE_ID + "s");
    add_name(WISE_ID);
    set_adj("plain");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_DROP, "You cannot drop the pin.\n");
}


string
my_long()
{
    return "This is a plain pin identifying you as a Wise " +
      "Person Of Genesis. Do 'help pin' to see what you can " +
      "do with it.\n";
}


void
init()
{
    if (!interactive(TP))
      return;
    if (REALAGE(TP) < 8640000) /* 100 days!!! */
      set_alarm(3.0,0.0,"destroy");
    ADA("help");
    ADA("wpatient");
    ADA("wcalm");
    ADA("wcounsel");
    ADA("wrelax");
    /*add the club sublocation*/
    TP->add_subloc("the_wise_club", TO);
}


string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You are wearing your plain pin.\n";
    
    if (for_obj == me)
      return "You are wearing your plain pin.\n";
    else
      return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	" plain pin, identifying " + OBJECTIVE(me) +
	" as a Wise Person of Genesis.\n";

}

int
help(string str)
{
    if (str == "pin")
      {
	  write("The pin of the Wise People of Genesis can do this:\n" +
		"- help pin          This help.\n" +
		"- wcalm             Stay calm.\n" +
		"- wcounsel          Counsel someone something.\n" +
		"- wrelax            Relax.\n" +
		"- wpatient          Advise someone to be patient.\n");
	  return 1;
      }
    return 0;
}

int
wcalm(string str)
{
    NF("Use just wcalm, without argument.\n");
    if (str)
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " stays totally calm, despite the situation.\n", ({ TP }));
    TP->catch_msg("You stay calm, despite the situation.\n");
    return 1;
}

int
wcounsel(string str)
{
    object *pers;
    string str1, str2;
    NF("Wcounsel who what?\n");
    if (!str)
      return 0;
    if (sscanf(str, "%s %s", str1, str2) != 2)
      return 0;
    pers = FILTER_OTHER_LIVE(FIND_STR_IN_OBJECT(str1, E(TP)));
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " counsels " + COMPOSITE_LIVE(pers) + " " + str2 + "\n", pers + ({TP}));
    TP->catch_msg("You counsel " + QCOMPLIVE + " " + str2 + "\n");
    pers->catch_msg(QCTNAME(TP) + " counsels you " + str2 + "\n");
    return 1;
}

int
wrelax(string str)
{
    NF("Use just wrelax, without argument.\n");
    if (str)
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " relaxes, apparently knowing the ways " +
	      "of the world.\n", ({ TP }));
    TP->catch_msg("You relax, knowing the ways of the world.\n");
    return 1;
}

int
wpatient(string str)
{
    object *pers;
    if (!str || str == "me" || L(str) == TP->query_real_name())
      {
	  write("Be more patient, be more patient.\n");
	  say(QCTNAME(TP) + " mumbles something about patience.\n");
	  return 1;
      }
    pers = FILTER_OTHER_LIVE(FIND_STR_IN_OBJECT(str, E(TP)));
    NF("Wpatient who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " advises " + COMPOSITE_LIVE(pers) +
	      " to be patient.\n", pers + ({TP}));
    TP->catch_msg("You advise " + QCOMPLIVE + " to be patient.\n");
    pers->catch_msg(QCTNAME(TP) + " advises you to be patient.\n");
    return 1;
}

void
destroy()
{
    tell_object(E(TO), "Accidentally, you drop the pin, and you just cannot find it " +
		"again.\n");
    remove_object();
}
