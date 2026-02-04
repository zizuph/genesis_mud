/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * storage_room.c
 *
 * A generic storage room in the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950708
 * Updated by Lilith, Feb 2008. Quest has only reset once per Armageddon since 1995!
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

int i;
string fname;
object chest;

void
reset_room()
{
    fname = file_name(TO);
    i = fname[strlen(fname) - 1] - '0';
    FIX_EUID;

    if (present(chest))
        chest->remove_object();

    chest = clone_object(CASTLE_DIR + "obj/chest");
    chest->set_my_num(i);
    chest->fill_er_up();
    chest->move(TO);
}


void
create_room()
{
    
    ::create_room();
    
    set_short("A musty storage area");
    set_long("You are inside the King's Storage room.  Here is " +
	     "where he stores the many items that are precious to " +
	     "him, but that he does not have room to display.  " +
	     "Only the King and his most trusted aides " +
	     "are allowed to be here.  If you are caught, you " +
	     "could end up in the dungeon.\n");
 
    add_item(({"stones", "wall"}),
	     "These stones have been darkened by mildew, moisture, and the " +
	     "dust from years of silence and desertion.\n");
 
    INSIDE;
    DARK;

    reset_room();

}

