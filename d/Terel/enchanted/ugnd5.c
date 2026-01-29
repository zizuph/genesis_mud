/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ugnd5.c
 *
 * This room is underground. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM; 

#include "enchanted.h"

/*
 * Function name: reset_room
 * Description:   reset the coffin.
 */
public void
reset_room()
{
    object coffin, pearl, sword;
    
    coffin = present("coffin");
    if (!coffin) {
        coffin = clone_object(ENCHANT_DIR + "obj/coffin");
        coffin -> move(TO);
        pearl = clone_object(ENCHANT_DIR + "obj/pearl");
        pearl -> add_prop("q_solver", pearl->query_name());
        pearl -> move(coffin);
        coffin -> add_prop(CONT_I_CLOSED, 1);
        coffin -> add_prop(CONT_I_LOCK,   1);
    } else {
	pearl = present("pearl", coffin);
	if (!pearl) {
            pearl = clone_object(ENCHANT_DIR + "obj/pearl");
            pearl -> add_prop("q_solver", pearl->query_name());
            coffin -> add_prop(CONT_I_CLOSED, 0);
            coffin -> add_prop(CONT_I_LOCK,   0);
            pearl -> move(coffin);
            coffin -> add_prop(CONT_I_CLOSED, 1);
            coffin -> add_prop(CONT_I_LOCK,   1);
	}
    }
    if (!present("sword")) {
        sword = clone_object(ENCHANT_DIR + "weapon/eg_sword");
        sword -> set_random_type();
        sword -> move(TO);
    }
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Underground room");
    set_long("You are standing in an underground room. The air is " +
	     "not exactly refreshing.\n");

    INSIDE;
    DARK;

    add_exit(ENCHANT_DIR + "ugnd4", "southwest", 0);

    reset_room();
}
