#pragma strict_types

#include <macros.h>
#include "/d/Faerun/defs.h"

inherit "/std/food";

#define CHOCO_FLAVOUR ({ "white", "milk", "dark", "sweet dark", "bittersweet" })
#define CHOCO_TYPE    ({ \
	({"bunny", "bunnies"}), \
	({"rabbit", "rabbits"}), \
	({"sheep", "sheeps"}), \
	({"elf", "elves"}), \
	({"gnome", "gnomes"}), \
	({"dwarf", "dwarves"}), \
	({"goblin", "goblins"}), \
	({"minotaur", "minotaurs"}), \
	({"moose", "mooses"}), \
	({"bear", "bears"}), \
	({"pig", "pigs"}), \
	({"dog", "dogs"}), \
	({"cat", "cats"}), \
	({"squirrel", "squirrels"}), \
	({"mouse", "mice"}), \
	({"rat", "rats"}), \
	({"frog", "frogs"}), \
	({"wolf", "wolves"}), \
	({"ogre", "ogres"}), \
	({"lion", "lions"}) })
	

int flavour;
int type;
int missing = 0;	// missing parts - 0->complete, 1->headless

string *flavours = CHOCO_FLAVOUR;
mixed *types    = CHOCO_TYPE;

string *t;

string aan(string arg)
{
	if (sizeof(regexp(({arg}), "^[aeiouy]")))
		return "an " + arg;
	return "a " + arg;
}


void set_descriptions()
{
	t = types[type];
	
	if (missing == 0) {
		set_short(flavours[flavour] + " chocolate figurine of " + aan(t[0]));
		set_pshort(flavours[flavour] + " chocolate figurines of " + t[1]);
		
		set_long("This is a small, " + flavours[flavour] + " chocolate figurine of " + 
			aan(t[0]) + ". It is rather light, obviously hollow inside. You feel *extremely* " +
			"tempted to bite its head off!\n"); 
	} else {
		set_short(flavours[flavour] + " chocolate figurine of a headless " + t[0]);
		set_pshort(flavours[flavour] + " chocolate figurines of headles " + t[1]);		

		set_long("This is a small, " + flavours[flavour] + " chocolate figurine of a " + 
			"headless " + t[0] + ". It is rather light, obviously hollow inside.\n"); 
	}	
	
	set_name(t[0]);
	add_name("figurine");
	set_pname(t[1]);
	
}

int do_bite(string str)
{
	if (str != 0) {
		if (str != "head" && str != "head from figurine") {
			write("Bite what, a " + str + "? Perhaps you wanted to bite head from figurine?\n");
			return 1;
		}
		if (missing == 1) {
			write("As much as you would like to, there is no way to bite the head again!\n");
			return 1;
		}
		write ("You slowly raise figurine to your mouth and then quickly bite its head off!\n");
		tell_room (ENV(TP), QCTNAME(TP) + " slowly raises the figurine to " + HIS_HER(TP) + 
			" mouth and then quickly bites its head off!\n", TP);
		
		missing = 1;
		set_descriptions();
		
		return 1;
	}
	return 0;
}

void init()
{
    ::init();
    add_action(do_bite, "bite");
}


void create_food()
{
	flavour = random(sizeof(flavours));
	type    = random(sizeof(types));
	missing = 0;
	
	set_amount(50);
	

	set_descriptions();	
}
        
string query_recover()
{
	int val = missing + 10 * flavour + 100 * type;
//	find_player("kehr")->catch_tell("storing: " + MASTER + ":" + val + "\n");
    return MASTER + ":" + val;
}

void init_recover(string arg)
{
    int val;
    
    val = atoi(arg);
    
//	find_player("kehr")->catch_tell("recovering: " + MASTER + ":" + val + "\n");        
    
    missing = val % 10;		val = val / 10;
    flavour = val % 10;		val = val / 10;
    type = val;

    set_descriptions();
}
