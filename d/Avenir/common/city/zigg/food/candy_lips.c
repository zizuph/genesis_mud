// candy_lips.c
// creator(s):   Zielia 2007
// last update:
// purpose:      added surprise for people who eat the Zigg candy.
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include "zigg.h"

#define TIME 300.0
#define SHADOW "/d/Avenir/common/city/zigg/food/candy_sh"
#define SOULDESC(x)	(this_player()->add_prop(LIVE_S_SOULEXTRA, x))

public static int timer;
public static string *flavors;
private object shadow;

public void
create_object(void)
{
    setuid();
    seteuid(getuid());
    set_no_show();
    set_name(({"candy breath", "breath", "Zig::Cbreath",}));
}

public string *
query_flavors(void)		{ return flavors; }

public void
set_flavors(string *arr)	
{ 
    flavors = arr; 
    
    if(objectp(shadow))
        shadow->set_flavors(flavors);
}

public void
remove_object(void)
{
    ENV()->remove_candy_sh();

    ::remove_object();
}

public void
reset_timer(void)
{
    if (timer)
	remove_alarm(timer);

    timer = set_alarm(TIME, 0.0, remove_object);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    shadow = TP->query_zig_candy_shadow();  

    if (!objectp(shadow))
    {
	shadow = clone_object(SHADOW);
    }
    
    shadow->set_flavors(flavors);
	
    if(!shadow->shadow_me(ENV(TO)))
    {
        shadow->remove_shadow(); 
    }
    
    reset_timer();
}

private static string *zones = ({
	"forehead", "cheek", "lips", "nose", "hand", "feet", "chin",
	"neck", "ear",
});

public int
f_kiss(string str)
{
    int size;
    object *oblist;
    string *how, *parts;
    string loc, flavor = one_of_list(flavors);

    if (!strlen(str))
    {
	notify_fail("Whom are you trying to kiss [how/where]?\n");
	return 0;
    }

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
	if (member_array(parts[size - 1], zones) != -1)
	{
	    loc = parts[size - 1];
	    str = implode(parts[..(size - 2)], " ");
	}
    }

    if (strlen(loc))
    {
	oblist = parse_this(str, "[the] %l [on] [the]",
	    ACTION_CONTACT | ACTION_INTIMATE);
    }
    else
    {
	how = parse_adverb_with_space(str, "gently", 1);
	oblist = parse_this(how[0], "[the] %i",
	  ACTION_CONTACT | ACTION_INTIMATE);
    }

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Kiss whom [how/where]?\n");
	return 0;
    }

    if (strlen(loc))
    {
	str = (sizeof(oblist) == 1 ?
	    HIS(oblist[0]) + " " + loc + "." :
	    "their " + loc + "s.");

	if (loc == "lips")
	{
	    actor("You kiss", oblist, " on " + str);
	    all2act(" kisses", oblist, " on " + str, "",
	      ACTION_CONTACT | ACTION_INTIMATE);
	    target(" tastes of "+ flavor +" as "+ HE(TP) +
		" kisses you on your "+ loc + ".",
		oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	}
	else
	{
	    actor("You kiss", oblist, " on " + str);
	    all2act(" kisses", oblist, " on " + str, "",
	      ACTION_CONTACT | ACTION_INTIMATE);
	    target(" kisses you on your " + loc + ".",
		oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	}
    }
    else
    {
	actor("You kiss", oblist, how[1] + ".");
	all2act(" kisses", oblist, how[1] + ".", how[1],
	  ACTION_CONTACT | ACTION_INTIMATE);
	target(" kisses you" + how[1] + one_of_list(({
	      ", the taste of "+ flavor +" clinging to "+ HIS(TP) +" lips",
	      " with lips that taste of "+ flavor,
	      ", the faint flavor of "+ flavor +" lingering on "+ HIS(TP) +
	      " lips"})) + ".",
	    oblist, how[1], ACTION_CONTACT | ACTION_INTIMATE);
    }

    return 1;
}

int
f_french(string str)
{
    object *oblist;
    oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);
    string flavor = one_of_list(flavors);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("French whom?\n");
        return 0;
    }

    actor("You give" + (sizeof(oblist) > 1 ? " each of" : ""), oblist,
        " a REAL kiss..it takes a long time..");
    all2act(" gives", oblist, " a deep and passionate kiss.\n" +
        "It seems to take forever...Sexy, eh?", "",
            ACTION_CONTACT | ACTION_INTIMATE);
    target(" gives you a deep and passionate kiss...\n" +
        "It seems to last forever and tastes like "+ flavor +".", oblist, "",
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
}

public int
f_lick(string str)
{
    object *oblist;
    string *how, flavor = one_of_list(flavors);

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 1);

    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	how[1] = NO_ADVERB;

    if (!stringp(how[0]))
    {
        write("You lick your lips" + how[1] +one_of_list(({
	    ", savoring the last traces of ", ", carefully cleaning the "+
	    "last bit of the ", ", receiving one last taste of the "}))+
	    flavor +" which clings to them.\n");
        allbb(" licks " + this_player()->query_possessive() + " lips" +
            how[1] + ".", how[1], ACTION_VISUAL);

	set_alarm(0.0, 0.0, remove_object);

        return 1;
    }

    oblist = parse_this(how[0], "[the] %i", ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Lick whom/what [how]?\n");
        return 0;
    }

    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
        how[1] = ADD_SPACE_TO_ADVERB("joyously");


    actor("You lick", oblist, how[1] + ".");
    all2actbb(" licks", oblist, how[1] + ".", how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" licks you" + how[1] + ".", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
}

public int
dmouth(string str)
{
    object *oblist;
    
    if (!TP->query_prop("_live_i_am_dancer_of_veils"))
    {
	return 0;
    }

    if (!strlen(str))
    {
        write("You moisten your lips with the tip of your tongue "+
            "in a blatant invitation to be kissed. Your lips taste "+
            "faintly of "+ one_of_list(flavors) +".\n");
        allbb(" runs the tip of her tongue along her lips, "+
            "leaving you with "+
	    "the impression that she wants to be kissed.");
	return 1;
    }
  
    oblist = parse_this(str, "[for] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dmouth for who?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
        str = (string)oblist[0]->query_objective();
    else
        str = "them";

    targetbb(" slowly traces the contours of her mouth "+
        "with the tip of her tongue in a blatant invitation "+
        "to be kissed!", oblist);
    actor("You slowly trace the contours of your mouth with the "+
        "tip of your tongue, blatantly inviting", oblist, " to "+
        "kiss you. Your lips taste faintly of "+one_of_list(flavors)+".\n");
    all2actbb(" seems to invite", oblist, " to kiss her by looking "+
        "steadily at "+str+ " while slowly "+
        "tracing the contours of her mouth with the tip of her "+
        "tongue.");
    return 1;
}

public int
dkiss(string str)
{
    object *oblist;

    if (!TP->query_prop("_live_i_am_dancer_of_veils"))
    {
	return 0;
    }
    
    if (!str)
    {
        NF("Dkiss whom?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
        NF("Dkiss whom?\n");
        return 0;
    }

    actor("You press your mouth to", oblist,"'s in a tender, "+
        "lingering kiss."); 
    target(" presses her mouth to yours in a tender, lingering kiss. "+
    	"Her silky-soft lips taste like "+one_of_list(flavors)+".",
        oblist);
    all2actbb(" presses her mouth to", oblist, "'s in a tender, "+
        "lingering kiss.");
    SOULDESC("looking dreamy-eyed");

    return 1;
}    


public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action(   f_kiss, "kiss"   );
    add_action( f_french, "french" );
    add_action(   f_lick, "lick"   );
    add_action(    dkiss, "dkiss"  );
    add_action(   dmouth, "dmouth" );
}
