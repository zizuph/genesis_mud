// file name:        /d/Avenir/common/dead/obj/crystalline_skull.c
// creator(s):       Lilith, May 2021
// revision history: Lilith, Oct 2021: fixed bug in do_activate
// purpose:          If you break it, you get 30 secs add_attack_delay.
//                   Currently a red-herring. Interacts with the pool_shelf.c 
//                   Players will run into more of these in the 
//                   Meet Mascarvin quest.
// note:             cloned by myth-sized revenants (revenant_m.c)
// bug(s):           
// to-do:

inherit "/std/object";
inherit "/lib/keep";
inherit "/lib/item_expiration";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/sys/cmdparse.h"

#define RECHARGE_DELAY 1800.00
#define DISCHARGE_DELAY 900.00
#define NORMAL     0
#define ACTIVATED  1
#define DISCHARGED 2

string word;
int state, recharge_alarm, discharge_alarm;
public void set_word(string str)  {    str = word;      }
public string query_word()        {    return word;     }
public void set_mystate (int i)   {    state = i;       }
public int  query_mystate()       {    return state;    }

string 
randword()
{
	string str = one_of_list(({  "t'aeris",  "hla'jeran",  "tsa-dara",  
	     "ilaris", "m'tenit",  "ry'alt",  "flar-Idrys",  "hl'endh", 
         "pr'aith",  "chrai'ni", "st'aeris",  "maedon" }));
    word = str;
    set_word(str);
    return str;                                                                 
}

void config_mystate()
{
	if (query_mystate() == ACTIVATED)	
    {	
        set_short("translucent crystalline skull");
        add_adj(({"pulsing", "translucent"}));
        if (query_adj() == "dull")
			remove_adj(({"opaque", "dull"}));
		if (query_adj() == "empty")
		    remove_adj(({"empty", "transparent"}));
		return;
	}
	if (query_mystate() == DISCHARGED)
	{
		set_short("transparent crystalline skull");
	    add_adj(({"empty", "transparent"}));
	    if (query_adj() == "pulsing")
		   remove_adj(({"pulsing", "translucent"}));
	    if (query_adj() == "dull")
           remove_adj(({"opaque", "dull"}));
        return;	   
    }    
	if (query_mystate() == NORMAL)	
	{
		set_short("opaque crystalline skull");
	    add_adj(({"opaque", "dull"}));
 	    if (query_adj() == "pulsing")
		   remove_adj(({"pulsing", "translucent"}));  
		if (query_adj() == "empty")
		    remove_adj(({"empty", "transparent"}));	  
        return;
    }		
}

string
my_cloud()
{
	string str = "";
	if (query_mystate() == NORMAL)	
    { 
        str = "Peering through the grime, you can see that there is a "+
		   "cloudiness within that makes the skull opaque.";	
	}
	if (query_mystate() == ACTIVATED)	
    {   
	    if (!word)
            set_word(randword());	
        str = "Within the crystalline skull the word '"+query_word() +"' has "+
		    "been formed by the pulsing vapor inside.";
	}
    if (query_mystate() == DISCHARGED)
    {   
         str = "There is nothing to see.";		 
    }

    return str +"\n";  
}

string
my_short()
{
	string str = "";
	if (query_mystate() == NORMAL)	
    { 
        str = "opaque";	
	}
	if (query_mystate() == ACTIVATED)	
    {   
        str = "translucent";
	}
    if (query_mystate() == DISCHARGED)
    {   
         str = "transparent";		 
    }

    return str +" crystalline skull";  
}

string
my_long()
{
	string str = "";
	if (query_mystate() == NORMAL)	
    { 
        str = "There might be something inside but it is hard to see "+
            "because the exterior is opaque with grime.";	
	}
	if (query_mystate() == ACTIVATED)	
    {   
        str = "It appears recently cleaned so you can see "+
		    "something cloudy pulsing inside. You can feel something "+
			"inside you answering its power, too.";
	}
    if (query_mystate() == DISCHARGED)
    {   
         str = "A recent cleaning reveals that it is transparent, "+
            "and though hollow, it doesn't look like there is anything "+
         	"inside it right now.";		 
    }

    return "This is a rather large skull that looks like it is made "+
	       "of glass or crystal of some sort. "+ str +"\n";  
}

void
create_object()
{
    set_name("skull");
    add_name(({"_av_crystal_skull"}));
    set_adj(({"crystalline","crystal"}));
	add_adj(({"dull", "opaque"}));
    set_short(my_short);
    set_long(my_long);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "transformation" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"You sense a latent magical aura surrounding it.\n", 10 }));
	add_prop(OBJ_S_WIZINFO, "This is a red-herring and has no purpose "+
	    "at this time.\n");
	add_item(({"cloud","cloudiness","pulsing cloud","vapor","pulsing",
	    "something cloudy", "something"}), my_cloud);

}


/* Break it, pay the consequences */
int
do_break(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail("Break what?\n");
        return 0;
    }

    if (!parse_command(arg, deep_inventory(ENV(TP)), "%i", ob))
    {
        notify_fail("Break what?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);
    if (!sizeof(ob) || ob[0] != TO)
    {
        notify_fail("Break what?\n");
        return 0;
    }

    write("You break the " + short() + " against the ground.\n");
    say(QCTNAME(TP) + " smashes " + LANG_ASHORT(TO) +
        " against the ground.\n");

    write("A vaporous skull rises before you and grins, sending "+
      	"a shudder of terror through you.\n");
    say(QCTNAME(TP) + " looks on in horror at the grinning vaporous "+
	   "skull that rises from the shards.\n");
	   
    // 60 second attack delay for the person who broke it.
	TP->add_attack_delay(30);
	if (discharge_alarm)
		remove_alarm(discharge_alarm);
	if (recharge_alarm)
		remove_alarm(recharge_alarm);
    set_alarm(1.0, 0.0, remove_object);
    return 1;
}

public void energized()
{
    state = NORMAL;
    config_mystate();
    remove_alarm(recharge_alarm);
	if (living(ENV(TO)))
		(ENV(TO))->catch_msg("The crystalline skull seems to have "+
	    "returned to its original state.\n"); 		
}

public void discharged()
{
    state = DISCHARGED;
    remove_alarm(discharge_alarm);
    config_mystate();
	if (living(ENV(TO)))
		(ENV(TO))->catch_msg("The pulsing cloud inside the crystalline "+
	    "skull fades away.\n"); 			
}	

int
do_activate(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail(capitalize(query_verb())+" what?\n");
        return 0;
    }

    if (!parse_command(arg, deep_inventory(ENV(TP)), "%i", ob))
    {
        notify_fail(capitalize(query_verb())+" what?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);
    if (!sizeof(ob) || ob[0] != TO)
    {
        notify_fail(capitalize(query_verb())+" what?\n");
        return 0;
    }

	if (query_mystate() == NORMAL)	
    { 
        write("You "+query_verb()+" the cystalline skull, which causes it "+
            "to brighten and pulse with power. ");	
	    set_mystate(ACTIVATED);
		config_mystate();
	    if (!word)
            set_word(randword());	
        write("Something begins to form inside the crystalline skull, "+
            "spelling the word '"+query_word()+"' in pulsing letters.\n");
		discharge_alarm = set_alarm(DISCHARGE_DELAY, 0.0, discharged);
        recharge_alarm = set_alarm(RECHARGE_DELAY, 0.0, energized);
        return 1;			
    }
	if (query_mystate() == ACTIVATED)	
    {   
        write("You "+query_verb()+" the cystalline skull, and you can see "+
		    "the pulsing cloud within it more clearly.\n");
		return 1;
	}
    if (query_mystate() == DISCHARGED)
    {   
        write("You "+query_verb()+" the cystalline skull, making it easier "+
		    "to see that it is completely transparent and empty.\n");
		return 1;
    }
    	
}

void
init()
{
    ::init();
	add_action(do_activate, "rub");
	add_action(do_activate, "polish");
	add_action(do_activate, "clean");
			
    add_action(do_break, "break");
    add_action(do_break, "smash");
    add_action(do_break, "shatter");
    add_action(do_break, "crush");
}
 
public string
query_recover()
{
    return MASTER + ":";
}
