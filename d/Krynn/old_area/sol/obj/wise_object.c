/* created by Aridor 12/01/94
 * 
 * The pin of the Wise People of Genesis
 * It's the guild (club) object.
 *
 */


inherit "/std/object";
inherit "/cmd/std/command_driver";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

#define WISE_ID        "krynn_wise_object"

int worn = 0;


string 
query_auto_load() 
{
    return MASTER_OB(TO) + ":";
}

void
init_arg(string arg)
{ 
}

string
query_color(object owner)
{
    int age;

    if (!owner)
      return "";

    age = REALAGE(owner);
    if (age > 51840000)
      return "platinum";
    else if (age > 43200000)
      return "gold";
    else if (age > 34560000)
      return "silver";
    else if (age > 25920000)
      return "bronze";
    else if (age > 17280000)
      return "copper";
    else if (age > 8640000)
      return "brass";
    else
      return "";
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

    //set_at(131072);
    //set_af(TO);
}

int
query_worn()
{
    return worn;
}

int
wear(string str)
{
    int i;
    mixed oblist;

    if (query_worn() || !strlen(str))
    {
        notify_fail("Wear what?\n");
        return 0;
    }

    i = parse_command(str,TP,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
      return 0;

    write("You wear the plain " + query_color(TP) + " pin on your chest.\n");
    say(QCTNAME(TP) + " wears a plain " + query_color(TP) + " pin on " +
	POSSESSIVE(TP) + " chest.\n");
    TP->add_subloc("the_wise_club", TO);
    set_no_show_composite(1);
    worn = 1;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

varargs int
remove(string str,object who = TP)
{
    int i;
    mixed oblist;
    
    if (!query_worn())
      return 0;
    
    i = parse_command(str,who,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
      return 0;
    
    who->catch_msg("You remove the plain " + query_color(who) + " pin from your chest.\n");
    tell_room(E(who),QCTNAME(who) + " removes a plain " + query_color(who) + " pin from " +
	      POSSESSIVE(who) + " chest.\n",who);
    who->remove_subloc("the_wise_club");
    set_no_show_composite(0);
    worn = 0;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

string
my_long()
{
    return "This is a plain " + query_color(E(TO)) + " pin identifying you as " +
      "a Wise Person Of Genesis. Do 'help pin' to see what you can " +
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
    ADA("remove");
    ADA("wcalm");
    ADA("wcounsel");
    ADA("wear");
    ADA("wpatient");
    ADD("wsmile","wpsmile")
    ADA("wrelax");
    
    add_adj(query_color(TP));
}


string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You are wearing your plain pin.\n";
    
    if (for_obj == me)
      return "You are wearing your plain " + query_color(me) + " pin.\n";
    else
      return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	" plain " + query_color(me) + " pin, identifying " + OBJECTIVE(me) +
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
		"- wpatient          Advise someone to be patient.\n" +
		"- wpsmile           Smile showing your wisdom.\n" +
		"You can wear and remove the pin, too.\n");
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

int
wsmile(string str)
{
    object *pers;
    if (!str)
    {
	write("You smile, knowing the ways of the world.\n");
	say(QCTNAME(TP) + " smiles with the wisdom of the ages in " + HIS(TP) +
	    " eyes.\n");
	return 1;
    }
    pers = parse_this(str, "[at] %l");
    NF("Wsmile at who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " smiles at " + COMPOSITE_LIVE(pers) +
	      " with the wisdom of the ages in " + HIS(TP) + "eyes.\n",
	      pers + ({TP}));
    TP->catch_msg("You smile at " + QCOMPLIVE + ", knowing the ways of the world.\n");
    pers->catch_msg(QCTNAME(TP) + " smiles at you with the wisdom of the ages in " +
		    HIS(TP) + " eyes.\n");
    return 1;
}


void
destroy()
{
    tell_object(E(TO), "Accidentally, you drop the pin, and you just cannot " +
		"find it again.\n");
    remove_object();
}

leave_env(object from, object to)
{
    remove("pin",from);
    ::leave_env(from,to);
}

enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
      {
	  oblist = FIND_STR_IN_OBJECT("all " + WISE_ID + "s",dest);
	  oblist -= ({ 0, TO });
	  if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy");
      }
    ::enter_env(dest,old);
}
