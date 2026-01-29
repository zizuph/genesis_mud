// file name:        /d/Avenir/common/dead/obj/shelf_pool.c
// creator(s):       Lilith, May 2021
// updates:          Lilith, Oct 2021: added 'words'
// purpose:          Shelf near the pools
// note:             Will eventually be used to put crystalline skulls 
//                   on to close/end pahloor raids or something similar
//                   if the area gets enough traffic to make it worth
//                   the effort.
// bug(s):           
// to-do:

#pragma strict_types

inherit "/std/container";

#include "../dead.h"

string word;

public void set_word(string str)  {    str = word;      }
public string query_word()        {    return word;     }

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
	
public string
external_within(void)
{
    object *obs = all_inventory(TO);
    int size = sizeof(obs);
    string str = " A small, circular shelf of natural stone lies near "
	    +"the pool's edge";
    
    if (!size)
	return str + ".";
    else
	return str + ", upon which you can see " + COMPOSITE_DEAD(obs) + ".";
}

/*
 * Function name: within
 * Description:   Give a description of items in this container
 */
public string 
within(void)
{
    object *obs = all_inventory(TO);
    int size = sizeof(obs);

    if (!size)
	    return "Other than a circular indentation that contains a bit "+
        "of water, the stone shelf is empty. ";
    else
	    return "You can see " + COMPOSITE_DEAD(obs) + " sitting in some water "+
        "on the stone shelf. ";
    return "";
}

string
my_long()
{
	string str = "";
	if (!word)
        set_word(randword());		
    return "A circular rock has been chiseled flat, forming a shelf "+
	  "of sorts at the pool's edge. Along the lip of the slightly "+
	  "cupped surface, you can see the word '"+ word +"' has been "+
	  "engraved. ";  
}

public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name(({"stone", "rock", "shelf", "stone shelf", "_skull_shelf"}));
    set_adj(({"circular"}));
    set_short("circular stone near the pool's edge");
    set_long(my_long);

    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_MAX_WEIGHT, 10000+5000);
    add_prop(CONT_I_MAX_VOLUME, 10000+5000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It does not move.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
	string obWord, toWord;

    if (ob->id("_av_crystal_skull"))
	{
		write("You hear a 'snick' sound as you let go of the skull and it "+
		    "settles snugly into the circular depression on the surface of "+
			"the stone.\n");
		say("You hear a snicking sound come from the stone shelf.\n"); 
		obWord = ob->query_word();
		toWord = TO->query_word();
		if (obWord == toWord)
		{ 
	        tell_room(ENV(TO), "You hear a loud rumbling sound and the water and "+
			    "stone around you vibrate for long moment.\n");
	    }
	return;
	}
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
}

/* putting this here mostly for future use */
public int
prevent_enter(object ob)
{
    return 0;
}

/* Putting this here for future use */
public int
prevent_leave(object ob)
{
    return 0;
}
