inherit "/std/container.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object
#define MYS_SKILL       130001

int			lit,loaded, used;

string
query_auto_load()
{
	return MASTER_OB(TO());
}

void
init()
{
	::init();
	add_action("do_meditate","meditate");
	add_action("do_load","load");
	add_action("do_load", "llll");
	add_action("do_light","light");
	add_action("catch_put","put");
}

int
catch_put(string str)
{
    string discard;
    object ob;

    if (parse_command(str, TP(), "%s 'in' / 'into' %o", discard, ob))
	if (ob==TO())
	{
	    write("If you want to load the thurible with incense, use "
	    + "'load'.\n");
	    return 1;
	}
    return 0;
}

void
create_container()
{
	set_name("thurible");
	add_name("burner");
	add_adj("holy");
	set_long(BS("This is a small device, carefully crafted of brass "
	+ "and beautifully worked. It is designed to hold burning "
	+ "incense and to provide a focus for meditation. You may load "
	+ "the thurible with incense, light the incense, and meditate "
	+ "upon the ancients.\n"));
	add_prop(CONT_I_MAX_WEIGHT,250);
	add_prop(CONT_I_MAX_VOLUME,500);
	add_prop(CONT_I_WEIGHT,0);
	add_prop(CONT_I_VOLUME,0);
	add_prop(CONT_I_RIGID,1);
	add_prop(OBJ_M_NO_SELL,BS("You needn't sell the holy thurible. Once "
	+ "bought, it will remain with you always.\n"));
	add_prop(OBJ_M_NO_DROP,"You needn't drop the mystic thurible.\n");
	loaded = 0;
	lit = 0;
	used = 0;
}

int
do_load(string str)
{
    object ob1,ob2;

    if (parse_command(str,TP(),"%o 'with' %o",ob1,ob2))
    	if (ob1==TO())
	{
	    if (ob2->query_name()=="incense")
		if (!loaded)
		{
		    ob2->move(TO());
		    write("You load the "+ob2->query_name()+" into the "
		    + "thurible.\n");
		    loaded = 1;
		    return 1;
		}
		else
		{
		    notify_fail("The thurible is already loaded!\n");
		    return 0;
		}
	    else
	    {
		notify_fail("You may only load the thurible with the "
		+ "mystic incense.\n");
		return 0;
	    }
	}
    if (parse_command(str,TP(),"%o 'into' %o",ob1,ob2))
    {
	if (ob1->query_name()=="incense")
	{
	    if (ob2==TO())
		if (!loaded)
		{
		    ob1->move(TO());
		    write("You load the "+ob1->query_name()+" into the "
		    + "thurible.\n");
		    loaded = 1;
		    return 1;
		}
		else
		{
		    notify_fail("The thurible is already loaded!\n");
		    return 0;
		}
	    else
	    {
		notify_fail("Hmmm. Could you rephrase that?\n");
		return 0;
	    }
	}
	else
	{
	    notify_fail("Load what into what?\n");
	    return 0;
	}
    }
    notify_fail("Usage: load <incense> into thurible OR load thurible with <incense>\n");
    return 0;
}

int
do_light(string str)
{
	object ob1, ob2;

	if (!str) return 0;
	if (parse_command(str,TP(),"%o",ob1))
	{
		if (ob1==TO())
			if (ob2 = present("incense",TO()))
			{
				if (!lit)
				{
					write("You light the incense. Now you can meditate!\n"); 
					say(BS(QCTNAME(TP())+" does something with "+TP()->query_possessive()+" thurible.\n"));
					call_out("burn_out",60);
					lit = 1;
					return 1;
				}
				else
				{
					notify_fail("The incense in the thurible is already burning!\n");
					return 0;
				}
			}
			else
			{
				notify_fail("There is no incense in the thurible!\n");
				return 0;
			}
		else
		{
			if (ob1->query_name()=="incense")
				if (!lit)
				{
					write("You light the incense. Now you can meditate!\n");
					say(BS(QCTNAME(TP())+" does something with "+TP()->query_possessive()+" thurible.\n"));
					call_out("burn_out",60);
					lit = 1;
					return 1;
				}
				else
				{
					notify_fail("The incense in the thurible is already burning!\n");
					return 0;
				}
			else
			{
				notify_fail("What are you trying to light?\n");
				return 0;
			}
		}
	}
	notify_fail("What are you trying to light?\n");
	return 0;
}

burn_out()
{
    object ob;
    
    write("The incense in the thurible has burned away.\n");
    if (ob = present("incense",TO()))
    {
	ob->remove_object();
	write("The incense in the thurible has burned away.\n");
    }
    lit = 0;
    loaded = 0;
    used = 0;
}

int
do_meditate(string str)
{
	object incense;

	if (lit&&loaded)
	{
		incense = present("incense",TO());
		say(QCTNAME(TP())+" meditates upon "+TP()->query_possessive()
		+ " thurible.\n");
		if (incense->do_it(TP()))
		{
			TP()->catch_msg(incense->query_meditate_text());
			if (++used > incense->query_uses())
				burn_out();
			return 1;
		}
		else
		{
			notify_fail(BS("For some reason you cannot concentrate, and "
			+ "the meditation does you little good.\n"));
			return 0;
		}
	}
	notify_fail(BS("To meditate, you must first <load> the thurible "
	+ "with incense and <light> the incense.\n"));
	return 0;
}


