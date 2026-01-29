/* A scroll for players to use
 * if they want a message they
 * can physically deliver hand
 * to hand instead of by
 * messenger.
 *
 * Raymundo, Jan 2020
 */

#pragma save_binary
 
#include "/d/Shire/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>

#define BLANK_PARCHMENT "_i_have_a_blank_parchment_"

inherit "/std/object";

string text_header, text_body;
string adjective = "";
int x = 0;

//I don't want the scroll to save unless it's been completely written.
int _recover_scroll_ = 0;



create_object()
{
    set_name("scroll");
    add_name("paper");
    add_name("_a_scribed_scroll");
    add_adj("blank");
	
    set_pname("scrolls");
    
    set_short("@@my_short");
    
    set_long("@@my_long");
	
	add_item( ({"header", "heading"}), "@@exa_header@@");
	add_item( "body", "@@exa_body@@");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_VOLUME, 400);
}

void
init()
{
	::init();
	add_action("do_adjective", "select");
	add_action("dictate_header", "dictate");
	add_action("do_read", "read");
	add_action("do_destroy", "destroy");
	add_action("do_feel", "feel");
	add_action("do_feel", "touch");
	add_action("do_scribe", "scribe");
}

int
do_scribe()
{
	write("You're not well-trained enough to scribe this scroll. Why don't "
		+ "you <dictate> what you want and leave the scribing to the "
		+ "professionals.\n");
		return 1;
}
string
my_short()
{
	if(!strlen(adjective) && !strlen(text_body))
	{
		return"blank scroll";
	}
    if (!strlen(text_body) && strlen(adjective) >> 0)
	return "blank " + adjective + " scroll";
    else
	return "scribed " + adjective + " scroll";
}

string
my_long()
{	if(!strlen(adjective))
	{
		return("This is a basic, blank parchment. At the moment, "
			+ "you can't even tell what type of paper it's made of! "
			+ "You should select a variety of paper.\n");
	}
    if (!strlen(text_body))
	return "This is a blank " + adjective 
		+ " scroll. Perhaps you should have it scribed...\n";
    else
	return "This " + adjective + " scroll has been written by an expert scribe. "
		+ "You should be "
		+ "able to read it. The " + adjective + " looks like it was made by "
		+ "a real professional who cares deeply about quality. It feels "
		+ "nice in your hands.\n"
		+ "You could destroy the parchment if you were done "
		+ "with it.\n";
}

int
dictate_header(string str)
{
	if(!strlen(adjective))
	{
		write("You need to select a type of paper before you can dictate the "
			+ "text.\n");
		return 1;
	}
	if(str == "body")
	{
		if(!strlen(text_header))
		{
			write("You need to dictate the header before you can dictate the "
				+ "body.\n");
			return 1;
		}
		if(strlen(text_body) > 0)
		{
			write("The scroll already contains body text.\n");
			return 1;
		}
		write("Enter your body.\n");
		text_body = "";
		write("-->");
		input_to("write_body");
		return 1;
	}
	else if(str == "header")
	{
		if(strlen(text_header) > 0)
		{
			write("The scroll already has a header.\n");
			return 1;
		}
	write("Enter your header.\n");
	text_header = "";
	write("-->");
	input_to("write_header");
	return 1;
	}
	else
	{
		notify_fail("Dictate body or dictate header?\n");
		return 0;
	}
}

void
scribe_header()
{
	if(text_header == "")
	{
		write("Dictation aborted.\n");
		return;
	}
	write("You finish your dictation. You hand your scroll to the scribe, "
		+ "and the scribe writes what you said down. Then he gives you back "
		+ "your scroll.\n");
	return;
}

void
write_header(string str)
{
	if(str == "**")
	{
		scribe_header();
		return;
	}
	if(str == "~q")
	{
		text_header = "";
		write("Dictation aborted.\n");
		return;
	}
	
	text_header += (str + "\n");
	write("-->");
	input_to("write_header");
	return;
}

void
scribe_body()
{
	if(text_body == "")
	{
		write("Dictation aborted.\n");
		return;
	}
	write("You finish dictating the body of your scroll. You hand your "
		+ "scroll to the scribe who writes your dictaition down and then "
		+ "hands the scroll back.\n");
		
	remove_adj("blank");
	add_adj("scribed");

	/* Here we remove the BLANK_PARCHMENT prop so that players can
	 * leave the shop. Also, we adjust the _recover_scroll_ so that
	 * the scroll will save. This way we don't have people running 
	 * around with heaps of scrolls. I want them to have to revisit
	 * the shop sometimes.
	 */
	 
	TP->remove_prop(BLANK_PARCHMENT);
	_recover_scroll_ = 1;
	return;
}

void
write_body(string str)
{
	if(str == "**")
	{
		scribe_body();
		return;
	}
	if (str == "~q")
	{
		text_body = "";
		write("Dictation aborted.\n");
		return;
	}
	
	text_body += (str + "\n");
	write("-->");
	input_to("write_body");
	return;
}

//sets what type of paper it is.
int
do_adjective(string str)
{
	if(adjective != "")
	{
		write("You have already chosen the paper type.\n");
		return 1;
	}
	if(str == "vellum")
	{
		adjective =("vellum");
		write("You select a vellum scroll.\n");
		add_adj(adjective);
		add_name(adjective);
		return 1;
	}
	if(str == "parchment")
	{
		adjective = ("parchment");
		write("You select a parchment scroll.\n");
		add_adj(adjective);
		add_name(adjective);
		return 1;
	}
	if(str == "papyrus")
	{
		adjective = ("papyrus");
		write("You select a papyrus scroll.\n");
		add_adj(adjective);
		add_name(adjective);
		return 1;
	}
	if(str == "rag paper")
	{
		adjective = ("rag paper");
		write("You select a rag paper scroll.\n");
		add_adj(adjective);
		add_name(adjective);
		return 1;
	}
	else
	{
		notify_fail("That is not a type of paper we carry here.\n "
		+ "We have vellum, parchment, papyrus, and rag paper.\n");
		return 0;
	}
}
//You can read it if it's been written on.
int
do_read(string str)
{
	if( !strlen(text_body) | !strlen(text_header) | !strlen(adjective))
	{
		notify_fail("The scroll is not complete enough to be read.\n");
		return 0;
	}
	if(str == adjective | str == "scroll" | str == "scribed " +adjective + " scroll" | str == adjective + " scroll")
	{
		write("You read the " + adjective + " scroll.\n"
			+ "======================================================================\n" 
			+ text_header + "\n"
			+ "----------------------------------------------------------------------\n"
			+ text_body + "\n"
			+ "======================================================================\n");
		return 1;
			
	}
	else
	{
		return 0;
	}
}
	
//Returns the header add_item
string
exa_header()
{
	if(!strlen(text_header))
	{
		return("There is no header yet. You could dictate one, though.\n");
	}
	else
	{
		return("You see a heading on the " + adjective + " scroll. It reads:\n"
			+ "----------------------------------------------------------------------\n" 
			+ text_header + "\n"
			+ "----------------------------------------------------------------------\n");
	}
}

//returns the body add_item
string
exa_body()
{
	if(!strlen(text_body))
	{
		return("No one has dictated any text for the body yet. You could, though.\n");
	}
	else
	{
		return("There is actually quite a lot of text in the body section of the "
			+ adjective + " scroll. You'd be best off reading it.\n");
	}
}

//destorys the paper
int
do_destroy(string str)
{

	if(str == adjective | str == "scroll" | str == "scribed scroll")
	{
		if(x == 0)
		{
			write("Are you sure you want to destroy the scroll? <destroy "
				+ "scroll> again to confirm.\n");
			x = 1;
			return 1;
		}
		if(x == 1)
		{
			write("You destroy the " + adjective + " scroll, ripping it "
				+ "into tiny pieces so that no one will ever be able to "
				+ "read it again!\n");
			say(QCTNAME(TP) + " destroys the " + adjective + " scroll by "
				+ "ripping it into tiny, tiny, oh so tiny pieces.\n");
			TP->remove_prop(BLANK_PARCHMENT);
			remove_object();
			return 1;
		}
	}
	else
	{
		notify_fail("Destroy what? The scroll?\n");
		return 0;
	}
}

//Emote for feeling the scroll
int
do_feel(string str)
{
	if(str == "scroll" | str == adjective)
	{
		write("You feel the " + adjective + " scroll in your hands. It's "
			+ "supple and soft.\n");
		say(QCTNAME(TP) + " holds the " + adjective + " scroll in his hands, "
			+ "appreciating its quality.\n");
		return 1;
	}
	else
	{
		notify_fail("Feel what? The scroll?\n");
		return 0;
	}
}
string query_recover()
{
    /*
	if(_recover_scroll_ == 1)
	{
	return MASTER + ":";
	}
    */
}

