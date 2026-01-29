inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define RING_ID     "champion_ring_object"
#define ARMOUR_CLASS 1

object wearer;

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
champion_list()
{
    return(read_file("/d/Ansalon/log/champion_club/champion_log", 1, 10000));
}

void
create_armour()
{
    set_name("ring");
    set_adj("obsidian");
    add_adj("engraved");
    add_pname(RING_ID + "s");
    add_name(RING_ID);
    set_short("engraved ring of obsidian");
    set_long("This thick band of cloudy obsidian is a ring awarded to those mighty " +
      "warriors who are Champions of the Arena, the last one standing in the " +
      "most glorious of gladiatorial tournaments. Engraved on its surface in elaborate, " +
      "yet fine, script are the names and dates of those other warriors who have " +
      "also earnt the title of the 'Mightiest of Warriors in the Realm'.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, "There is no way you would part with your most " +
      "prized possession!\n");
    add_prop(OBJ_M_NO_DROP, "There is no way you would part with your most " +
      "prized possession!\n");

    set_af(TO);

    seteuid(getuid(TO)); 

    add_item(({"enscription","list","names"}),
      "You study the list of names of Arena Champions enscribed " +
      "on your ring of obsidian:\n\n@@champion_list@@\n");

}






void
init()
{
    if (!interactive(TP))
	return;

    ADA("cross");
    ADA("display");
    ADA("discard");
    ADA("read");
}


int
read(string str)
{
    if(str == "script" || str == "list" || str == "names" || str == "dates")
    {

	write("You study the script, and realise you can examine the list of names " +
	  "enscribed on the ring.  You also realise that as an Arena Champion you can " +
	  "'display' your ring, as well as 'cross' your arms smuggly.  If you " +
	  "feel you don't need this ring to prove your prowess, you can always 'discard' " +
	  "it.\n");

	return 1;
    }
       
    return 0;

}

int
display(string str)
{
    if(str == "ring")
    {
	tell_object(E(TO),"You display your engraved ring of obsidian, showing all that " +
	  "you are a Champion of the Arena!\n");
	say(QCTNAME(TP) + " displays " +HIS(TP) + " engraved ring of obsidian, " +
	  " showing you that " +HE(TP)+ " is a Champion of the Arena!\n");
	return 1;
    }
    return 0;
}


int
cross(string str)
{
    if(str == "arms")
    {
	tell_object(E(TO),"You cross your arms smuggly, knowing that as an Arena Champion, " +
	  "there are few problems you can't face.\n");
	say(QCTNAME(TP) + " crosses " +HIS(TP)+ " arms smuggly, knowing that as an Arena " +
	  " Champion there are few problems " +HE(TP)+ " cannot face.\n");
	return 1;
    }
    return 0;
}


int
discard(string str)
{
    if(str == "ring")
    {
	set_alarm(1.0,0.0,"destroy3");
	return 1;
    }
    return 0;
}

void
destroy()
{
    tell_object(E(TO), "You fumble with your ring of obsidian, and " +
      "lose it on the ground somewhere.\n");
    remove_object();
}

void
destroy2()
{
    tell_object(E(TO),"Deciding that you only need one " +
      "ring of obsidian, you discard the other.\n");
    remove_object();
}

void
destroy3()
{
    tell_object(E(TO),"Deciding you no longer wish to keep " +
      "the ring of obsidian, you discard it.\n");
    remove_object();
}

void
destroy4()
{
    remove_object();
}

enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
    {
	oblist = FIND_STR_IN_OBJECT("all " + RING_ID + "s",dest);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy2");
    }
    ::enter_env(dest,old);
}

string
show_subloc(string subloc, object me, object for_obj)
{

    if(me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
    if (for_obj == me)
        return "You are marked as a Champion of the Arena.\n";
    else
        return C(PRONOUN(me)) + " is marked as a Champion of the Arena.\n";
}

mixed
wear(object what)
{
    TP->add_subloc("_arena_champion_club", TO); 
    wearer = TP;
 
    return 0;
}
mixed
remove(object what)
{
    wearer->remove_subloc("_arena_champion_club"); 
    wearer = 0; 
    return 0;
}