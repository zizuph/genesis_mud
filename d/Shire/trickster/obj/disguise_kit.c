#pragma save_binary 
#pragma strict_types 

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/trickster/trickster.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>

#define DISGUISE_PROP "_trickster_as_last_disguise"

//   Protoypes
int get_second_adj(string adjective2,string adjective);

string *adjectivelist = ({"white-haired","gray-haired",  
  "black-haired","blond-haired","brown-haired","red-haired",
  "green-haired","blue-haired","orange-haired","purple-haired",
  "dark-haired", "light-haired","chestnut-haired","long haired",
  "blond-bearded","red-bearded","green-bearded","blue-bearded",
  "orange-bearded","purple-bearded","thinly-bearded","fork-bearded",
  "long bearded","gray-bearded","black-bearded","white-bearded",
  "brown-bearded","mustachioed","hook-nosed","Roman-nosed","red-nosed",
  "big-nosed","pug-nosed","potato-nosed","knob-nosed","pointy-eared",   
  "furry-eared","jug-eared"});
int disguises = 0;

void
create_object()
{
    set_name("kit");
    add_name("trickster_disguise_kit");
    set_short("disguise kit");
    set_long("This is a disguise kit used by Tricksters to disguise themselves "+
      "as someone else if they so choose. Within this wonderous kit "+
      "is various coloured hair which one could use for wigs, beards "+
      "and mustaches. There are also various items which can be used as "+
      "a fake nose, ears or other various parts for a proper "+
      "disguise.\n@@disguise_amount@@.\n");

    add_item(({"hair","wig","beard","mustaches"}),
      "This looks like fine animal hair dyed various colours which can "+
      "be used as wigs, beards or mustaches for a disguise.\n");
    add_adj(({"disgusie","trickster"}));

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 200);
    remove_prop(OBJ_I_VALUE);  // Has no value 
    add_prop(OBJ_M_NO_DROP,"You don't want to drop your disguise kit!\n");
    add_prop(OBJ_M_NO_GIVE,"You crazy!?!  You don't want to give this away!\n");
}
string
disguise_amount()
{
    return (!disguises ? "You lack the material to make a disguise "+
      "at the moment" : "You have enough material to make "+disguises+
      " disguises in your kit");
}

void
init()
{
    ::init();
    add_action("intro_me","introduce");
    add_action("intro_me","present");
    add_action("disguise","disguise");
    add_action("join","join");
    add_action("invite","invite");
}

string
query_auto_load()
{
    return MASTER+":"+disguises;
}

void
init_arg(string s)
{
    if (!stringp(s))
	return;
    disguises = atoi(s);
}

void
set_disguises(int amount) 
{
    disguises = amount;
}

void
add_disguises(int amount)
{
    disguises += amount;
}

int
query_disguises()
{
    return disguises;
}

int
disguise(string adjective)
{
    object *people;
    string *originaladjs;

    if (!IS_MEMBER(TP) && !TP->query_wiz_level())
    {
	notify_fail("You fail to understand how to use this "+short()+
	  " so you throw it away!\n");
	remove_object();
	return 0;
    }
    if (TP->query_disguise_shadow() == 666)
    {
	TP->remove_disguise_shadow();
	say(QCTNAME(TP)+" removes "+HIS_HER(TP)+" disguise.\n");
	write("You just removed your disguise.\n");
	return 1;
    }
    if (TP->query_disguised())
    {
	NF("You seem to be wearing a disguise already, you'll have to "+
	  "remove the other disguise before you can wear this one.\n");
	return 0;
    }
    people = FILTER_LIVE(all_inventory(environment(TP))); 
    people = FILTER_CAN_SEE(people, TP);
    if (sizeof(people) > 1 && !TP->query_wiz_level())
    {
	notify_fail("You can't disguise yourself with people in the room!\n");
	return 0;
    }
    if (!adjective)
    {
	NF("You need to be a tad more descriptive to disguise yourself.\n");
	return 0;
    }

    if (!disguises)
    {
	notify_fail("You do not have enough material here to make a disguise!\n");
	return 0;
    }
    if (adjective == "last")
    {
	if (TP->query_prop(DISGUISE_PROP))
	{
	    get_second_adj(TP->query_prop(DISGUISE_PROP)[1],
	      TP->query_prop(DISGUISE_PROP)[0]);
	    return 1;
	}
	else
	{
	    notify_fail("But you have no last disguise!\n");
	    return 0;
	}
    }

    originaladjs = TP->query_adjs();
    if (sizeof(originaladjs))
	if (member_array(originaladjs[0],adjectivelist) == -1)
	    adjectivelist += ({originaladjs[0]});
    if (sizeof(originaladjs) == 2)
	if (member_array(originaladjs[1],adjectivelist) == -1)
	    adjectivelist += ({originaladjs[1]});

    //  Wizards can disguise themselves as whatever they want!!
    if (member_array(adjective,adjectivelist) == -1 && !TP->query_wiz_level())
    {
	notify_fail("That is an invalid adjective!\n");
	return 0;
    }
    write("Ok, now pick the second adjective you wish to be "+
      "disguised as.\n");
    input_to("get_second_adj", 0, adjective);
    return 1;
}

int
get_second_adj(string adjective2, string adjective) 
{

    object disguise;
    if (adjective2 == "")
    {
	write("You need to be a tad more descriptive to disguise yourself.\n");
	return 1;
    }
    //  Wizards can disguise themselves as whatever they want!!!
    if (member_array(adjective2,adjectivelist) == -1 && !TP->query_wiz_level())
    {
	write("That is an invalid adjective!\n");
	return 1;
    }
    say(QCTNAME(TP)+" puts on a disguise, attempting to fool "+
      "people that "+HE_SHE(TP)+" is "+LANG_ADDART(adjective)+" "+adjective2+
      " "+TP->query_gender_string()+" "+TP->query_race_name()+
      (TP->query_wiz_level() ? (" wizard") : "") + ".\n");
    write("You carefully disguise yourself as "+LANG_ADDART(adjective)+" "+
      adjective2+" "+TP->query_gender_string()+" "+TP->query_race_name()+
      (TP->query_wiz_level() ? (" wizard") : "") + ".\n");
    setuid(); seteuid(getuid());
    disguise = clone_object(DISGUISE);
    disguise->shadow_me(TP);
    disguise->set_disguise(({adjective,adjective2}));
    disguises -= 1;
    TP->add_prop(DISGUISE_PROP,({adjective,adjective2}));
    return 1;
}

int
invite(string str)
{
    object teammate;

    if (TP->query_disguise_shadow() == 666)
    {
	teammate = present(str, ENV(TP));
	if (TP->query_is_fooled(teammate))
	{
	    TP->add_not_fooled_by_disguise(teammate);
	    TP->catch_msg("You reveal your true identity to "+QTNAME(teammate)+
	      " as you invite "+HIM_HER(teammate)+" to join your team.\n");
	    teammate->catch_msg(QCTNAME(TP)+" reveals "+HIS_HER(TP)+" true "+
	      "identity to you as "+HE_SHE(TP)+" invites you to join "+
	      HIS_HER(TP)+" team.\n");
	}
    }   
    return 0;
}

int
join(string str)
{
    object leader;

    if (TP->query_disguise_shadow() == 666)
    {
	leader = present(str, ENV(TP));
	if (TP->query_is_fooled(leader))
	{
	    TP->add_not_fooled_by_disguise(leader);
	    TP->catch_msg("You reveal your true identity to "+QTNAME(leader)+
	      " as you attempt to join "+HIS_HER(leader)+" team.\n");
	    leader->catch_msg(QCTNAME(TP)+" reveals "+HIS_HER(TP)+" true "+
	      "identity to you as "+HE_SHE(TP)+" attempts to join your "+
	      "team.\n");
	}
    }
    return 0;
}

int
intro_me(string str)
{
    string intro_to, intro_who;
    int index;
    object *targets, *livings;

    if (TP->query_disguise_shadow() == 666)
    {
	if (!str)
	    return 0;

	if (sscanf(str, "%s to %s", intro_who, intro_to) != 2)
	{
	    intro_who = str;
	}
	if (intro_who == "me" || intro_who == "myself")
	{
	    livings = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
	    if (strlen(intro_to))
	    {
		targets = PARSE_THIS(intro_to, "[the] %l") - ({TP});
	    }
	    else
	    {
		targets = FILTER_CAN_SEE(livings, TP);
	    }
	    if (!sizeof(targets))
		return 0;
	    index = -1;
	    TP->catch_msg("You reveal your true identity to all those whom "+
	      "you just introduced to.\n");
	    while (++index < sizeof(targets))
	    {
		if (TP->query_is_fooled(targets[index]))
		{
		    TP->add_not_fooled_by_disguise(targets[index]);
		    targets[index]->catch_msg(QCTNAME(TP)+" reveals "+
		      HIS_HER(TP)+" true identity to you when "+
		      HE_SHE(TP)+" introduces "+HIM_HER(TP)+"self to "+
		      "you.\n");
		}
	    }
	}
    }
    return 0;
}
