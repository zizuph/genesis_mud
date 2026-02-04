/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * study.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

public void
create_room()
{
    ::create_room();
 
    set_short("Kings study");
    set_long("This is the room in which the king spends a great " +
	     "deal of his time.  He reads books here, takes naps here, " +
	     "plays games here, and does the Kingdoms business from " +
	     "here.  It has many ornate furnishings, paintings, " +
	     "and rugs.\n");
 
    add_item(({"furniture", "furnishings", "paintings", "painting",
              "rugs", "rug"}),
	     "These items are lovely, museum quality pieces that " +
	     "may one day be worth the value of the castle itself.\n");
 
    add_item(({"game", "games"}), 
	     "Spread throuought this study is a chess board, a pegs board, " +
	     "an elaborate nine-pin lane, and a Towers of Hanoi.  They are " +
	     "all very nice.\n");
 
    INSIDE;
 
    add_exit(TOWER_DIR + "nw_tower2",  "northwest", 0);
    add_exit(CASTLE_DIR + "l_hall2_3", "east",      0);

    FIX_EUID;
    clone_object(CASTLE_DIR + "obj/desk")->move(TO);
    reset_room();
}
 
void
reset_room()
{
    object desk, book, letter;
 
    desk = (present("desk", TO));
    if (desk)
        desk->reset_object();
 
    if (!(present("ribos_letter", TO)))
    {
        letter = clone_object(CASTLE_DIR + "obj/letter");
        letter->move(TO);
    }
 
    if (!(present("ribos_book", TO)))
    {
        book = clone_object(CASTLE_DIR + "obj/book");
        book->move(TO);
    }
}
