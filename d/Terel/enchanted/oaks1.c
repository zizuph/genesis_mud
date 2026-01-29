/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * oaks1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

int NUM;

reset_room()
{
    ::reset_room();
    NUM = 3;
}

create_room()
{
    ::create_room();
    set_short("Pine Forest");
    set_long("Grand and stately, these ancient oaks rise up like the " +
	     "forgotten fathers of some long lost family. The winds whisper " +
	     "through their mysterious depths, their acorns shaking " + 
	     "amongst the branches.\n");
   
    add_item("acorns", "The oaks are loaded with them, though many are\n"
	     + "high up in the branches.\n");
    add_cmd_item("acorn", "pick", "You cannot reach them.\n");
    add_item("oaks", "They look very old and are full of acorns.\n");
    
    add_exit(ENCHANT_DIR + "forest17", "southeast", 0);
    reset_room();
}

pick()
{
    object ob;
    NUM --;
    if(NUM < 1){
	write("All the acorns in reach have been picked.\n");
	return 1;
    }
    FIX_EUID;
    ob = clone_object("/d/Terel/mecien/valley/guild/quest/acorn");
    ob->move(TP);
    write("You pick an acorn from the grand oaks.\n");
    say(QCTNAME(TP) + " picks an acorn from the grand oaks.\n");
    return 1;
}
