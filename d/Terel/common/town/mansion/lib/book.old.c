inherit "/std/object.c";
#include "lib_defs.h"

string 		the_text;

void
init()
{
	::init();
	add_action("do_read","read");
}

void
set_text(string which_file)
{
        the_text = LIBRARY + "books/" + which_file;
}

string
choose_name()
{
	int i;

	i = random(6)+1;
	i = random(8)+1;
	switch (i) 
	{
		case 1: return "book"; break;
		case 2: return "tome"; break;
		case 3: return "pamphlet"; break;
		case 4: return "volume"; break;
		case 5: return "manual"; break;
		case 6:	return "scroll"; break;
		case 7: return "manuscript"; break;
		case 8: return "text"; break;
	}
	return "book";
}

string
choose_color()
{
	int i;
	
	i = random(8)+1;
	switch (i) 
	{
		case 1: return "red"; break;
		case 2: return "blue"; break;
		case 3: return "yellowed"; break;
		case 4: return "green"; break;
		case 5: return "white"; break;
		case 6:	return "brown"; break;
		case 7: return "black"; break;
		case 8: return "gilded";
	}
	return "yellowed";
}

string 
choose_adj()
{
	int i;

	i = random(11)+1;
	switch (i) 
	{
		case 1: return "ancient"; 
		case 2: return "old"; 
		case 3: return "dusty"; 
		case 4: return "tall"; 
		case 5: return "thin"; 
		case 6:	return "thick"; 
		case 7: return "decrepit"; 
		case 8: return "leather-bound";
		case 9:	return "dog-eared";
		case 10: return "moth-eaten";
		case 11: return "tattered";
	}
	return "old";
}

void
quarter_gone(object player)
{
	int currval;
	object ob;

	ob=TO();
	currval = ob->query_prop(OBJ_I_VALUE);
	ob->add_prop(OBJ_I_VALUE,currval / 2);
	if (environment(ob)==player)
		write(BS("You notice that the " + ob->query_name() 
		+ " is rapidly disintegrating.\n"));
	call_out("half_gone",30,player);
}

void 
half_gone(object player)
{	
	int currval;
	object ob;

	ob=TO();
	currval = ob->query_prop(OBJ_I_VALUE);
	ob->add_prop(OBJ_I_VALUE,currval / 2);
	if (environment(ob)==player)
		write(BS("The " + ob->query_name() 
		+ " continues to disintegrate.\n"));
	call_out("almost_gone",30,player);
}

void 
almost_gone(object player)
{
	int currval;
	object ob;

	ob=TO();
	currval = ob->query_prop(OBJ_I_VALUE);
	ob->add_prop(OBJ_I_VALUE,currval / 2);
	call_out("all_gone",30,player);
}

void 
all_gone(object player)
{
	object ob;

	ob=TO();
	if (environment(ob)==player)
		write(BS("The " + ob->query_name() + " has "
		+ "disintegrated away to nothing.\n"));
	ob->remove_object();
}

void
create_object()
{
	set_name(choose_name());
	set_adj(choose_color());
	set_adj(choose_adj());
	set_long(BS("This " + TO()->query_name() + " has not well withstood the test of time; "
	+ "you doubt it will "
	+ "long withstand even gentle handling. The words are faded "
	+ "and you cannot even make out the title. \n"));
	the_text = BS("You examine the "+TO()->query_name()+" carefully, but it is "
		+ "a hopeless study--the pages have faded with the "
		+ "passage of the years, until not a word remains legible.\n");

	add_prop(OBJ_I_VOLUME,random(6000)+500);
	add_prop(OBJ_I_WEIGHT,TO()->query_prop(OBJ_I_VOLUME)/2);

	add_prop(OBJ_I_VALUE,0);
	call_out("quarter_gone",30,TP());
}

int
do_read(string str)
{
	object 	ob;
   	
	seteuid(getuid(this_object()));
	if (str == TO()->query_name())   /* NOTE: replace this with a parse_command() */
	{
		say(BS(QCTNAME(TP())+" reads from the "+TO()->query_name()+".\n"));;
                clone_object(MORE_OBJ)->more(the_text, 3);
		return 1;
	}
	else
	{
		notify_fail("Read what?\n");
		return 0;
	}
}

