/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


inherit WAYM_LIB_DIR + "base_hobbit_hole.c";


void reset_shire_room();
int rug = 0;


void
create_hobbit_room()
{
	set_short("The Study");
	
	set_long("The study is one of the larger rooms in the smial. There "
		+ "is a large, antique rug " + "@@rug_status@@" 
		+ "It's almost as if having extra space around the "
		+ "desk is a luxury. Where you would normally expect to see a "
		+ "bookshelf, you see a life-sized statue of a hobbit instead, "
		+ "behind which is a painting.\n");
	
	add_item("statue", "The statue is of an elderly hobbit. He is dressed "
		+ "in a colonel's uniform, which is painted mustard yellow. The "
		+ "statue has a monocle over his right eye. Looking at his face, "
		+ "you see deep worry lines, as if command weighed heavily upon "
		+ "him. His boots are knee-high, and he is wielding a dagger "
		+ "(but for him it looks like a sword). You see a plaque down by "
		+ "his feet.\n");
	add_item("monocle", "The monocle looks distinguished. You can see "
		+ "why the Colonel was rumored to have several lady friends.\n");
	add_item( ({"line", "worry line", "worry lines"}), "Truly the "
		+ "burden of command must have been much to have created such "
		+ "deep worry lines, even in a statue.\n");
	add_item("uniform", "This is an impressive uniform. You can almost "
		+ "picture Colonel Mustard walking bravely down the street, "
		+ "back ramrod straight, every inch a three foot giant among "
		+ "hobbits.\n");
	add_item("boots", "The boots are knee-high, but they are stone "
		+ "colored. In life, they were probably black or brown. Would "
		+ "any man wear yellow boots?\n");
	add_item("dagger", "The dagger is nearly sword length in the hobbit's "
		+ "hand. You notice a small nick has been carved into the blade, "
		+ "likely because in life the Colonel's dagger had tasted the "
		+ "blood of his enemies.\n");
	add_item("study", "You are in the study, with the statue of Colonel "
		+ "Mustard. The statue holds a dagger.\n");
	add_item("bookshelf", "There is no bookshelf. Instead, there is a statue.\n");
	add_item("desk", "This is a large desk (for a hobbit), where much work "
		+ "could be done.\n");
	add_item( "painting", "The painting depicts a hobbit military officer, "
		+ "likely a younger version of the statue here, beside three large, "
		+ "snarling mastiffs. They are routing an Uruk-hai and some orcs "
		+ "that had tried to raid a smial. The Uruk-hai is clutching a "
		+ "bloody stump where his hand once was, and one of the mastiffs "
		+ "has a twisted black hand in its mouth.\n");
	
	add_walls();
	add_prop(OBJ_S_SEARCH_FUN, "search_floor");
	remove_item("floor");
	add_item("floor", "@@exa_floor@@");
	add_item( ({"footprint", "footprints", "foot print", "foot prints", "patch"}), 
		"@@footprints@@");
	add_item( ({"rug", "rugs"}), "@@exa_rug@@");
	add_item( "plaque", "@@exa_plaque@@");

	add_exit(WAYM_HOUSE_DIR + "h_4_2", "south");

}

void
reset_shire_room()
{
 rug = 0;	
}

void
init()
{
	::init();
	add_action("move_rug", "move");
	add_action("move_rug", "push");
	add_action("move_rug", "pull");
	add_action("read_plaque", "read");

}


/* Shows a hidden north exit into the tunnels
 * where, eventually, the player can complete
 * the quest. Also eliminates the exit after a period 
 * of time.
 */
 
void kill_exit()
{
    tell_room( (WAYM_HOUSE_DIR + "h_4_3"),("You hear a grinding sound "
		+ "as the floor closes, obscuring the exit once more.\n"));
    remove_exit("down");
    return ;
}   

public string
search_floor(object me, string arg)
{
	if(arg == "rug" && rug == 0)
	{
		return("You look more closely at the rug and realize it has been "
			+ "moved often. You could probably move the rug too, couldn't "
			+ "you.\n");
	}
	if(arg == "rug" && rug == 1)
	{
		return("You notice that the rug is still up against the wall in "
			+ "a heap.\n");
	}
	if(arg == "footprints" && rug == 1)
	{
			return("The footprints definitely look as if someone was "
				+ "walking downhill. Maybe you should look at the floor "
				+ "more closely too.\n");
	}
	if(rug == 0)
		return "";
    if (arg != "floor")
        return "";
    add_exit(WAYM_ROOM_DIR + "shops/parchment_shop", "down");
    set_alarm(90.0,0.0,"kill_exit");
    return "You hear a grating sound as the floor drops down becoming a ramp. "
		+ "You are able to go down the ramp.\n";
}

//Returns description of the floor, based on whether the rug
//has been moved or not.
string
exa_floor()
{
	if(rug == 0)
	{
		return("The floor is made of hard wood, maple you think. The "
			+ "craftsmanship is excellent, with hardly a gap or bump "
			+ "noticable anywhere. A large antique rug covers most of "
			+ "the floor.\n");
	}
	else
	{
		return("The floor is made of hard wood, maple you think. The "
			+ "craftsmanship is excellent, with hardly a gap or bump "
			+ "noticable anywhere. A large antique rug has been pushed "
			+ "over to the side of the room. Oddly, there are footprints "
			+ "where it used to be.\n");
	}
}

//Description of the footprints
string
footprints()
{
	if(rug == 0)
	{
		return("You see no footprints.\n");
	}
	else
	{
		say(QCTNAME(TP) + " bends down to examine something where the "
			+ "rug used to be.\n");
		return("You bend down and look closely at the footprints. "
			+ "The footprints seem to lead from "
			+ "just in front of the desk toward the door, but you notice "
			+ "they have more pressure on the heel than on the toe, as if "
			+ "someone were walking downhill, trying not to fall. "
			+ "Maybe you should have a closer look.\n");
	}
}

//description of the rug
string
exa_rug()
{
	if(rug == 0)
	{
		return("This is a large antique rug. It's very nice and takes up a "
			+ "good chunk of the floor. A real rug afficianado would want "
			+ "to get an up-close look at it, because this is a real gem of "
			+ "a rug.\n");
	}
	else
	{
		return("The rug is a very nice, very large antique rug. It seems it "
			+ "has been pushed up against the wall so that people can get "
			+ "a better look at the floor.\n");
	}
}

//Moves the rug back and forth
int
move_rug(string str)
{
	if(rug == 0)
	{
		if(str == "rug" | str == "large rug" | str == "antique rug" | str == "large antique rug")
		{
			write("You grab the rug and pull it over against the wall, "
				+ "revealing the floor beneath it.\n");
			say(QCTNAME(TP) + " pulls the rug over against the wall, "
				+ "revealing the floor beneath it.\n");
			rug = 1;
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
	if(rug == 1)
	{
		if(str == "rug" | str == "large rug" | str == "antique rug" | str == "large antique rug")
		{
			write("You pull the rug back in front of the desk where it "
				+ "belongs, being careful not to leave a mess.\n");
			say(QCTNAME(TP) + " pulls the rug back in front of the desk.\n");
			rug = 0;
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
}

//rug description for the long description of the room
string
rug_status()
{
	if(rug == 0)
	{
		return("taking up the center of the otherwise "
		+ "empty floor. ");
	}
	else
	{
		return("pushed up against the wall, leaving a large open patch "
			+ "of floor in front of the desk. ");
	}
}

//plaque contents
string
exa_plaque()
{
	return(""
	+ "********************************************\n"
	+ "*                                          *\n"
	+ "*      In Memory of our Dearest Uncle      *\n"
	+ "*   The Famous Self-Appointed Colonel who  *\n"
	+ "*    was affectionately called Mustard.    *\n"
	+ "*        He is always in our hearts.       *\n"
	+ "*                                          *\n"
	+ "********************************************\n");
}

//reads the plaque
int
read_plaque(string str)
{
	if(str == "plaque")
	{
		write(exa_plaque());
	return 1;
	}
	else
	{
		notify_fail("Read what? The plaque?\n");
		return 0;
	}
}