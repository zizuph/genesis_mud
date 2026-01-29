/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ugnd4.c
 *
 * This room is underground. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

object w1, w2;

/*
 * Function name: reset_room
 * Description:   clone monsters at each reset.
 */
public void
reset_room()
{
    if (!present("worm")) {
        w1 = clone_object(ENCHANT_DIR + "monster/glow_worm");
        w1 -> move(TO);
        w2 = clone_object(ENCHANT_DIR + "monster/glow_worm");
        w2 -> move(TO);
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
    
    add_prop(ROOM_I_HIDE,   89);

    add_exit(ENCHANT_DIR + "ugnd3", "west",      0);
    add_exit(ENCHANT_DIR + "ugnd5", "northeast", "@@go_ne");

    reset_room();
}

go_ne()
{
    if (!w1 && !w2) return 0;
    write("A worm stopped you.\n");
    say(QCTNAME(TP) + " tried to go northeast, but failed.\n");
    return 1;
}
