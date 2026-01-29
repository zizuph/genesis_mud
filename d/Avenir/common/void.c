// -*-C++-*-
// file name:	/d/Avenir/common/void.c
// creator(s): 	Lilith, May 1998
// revisions:	Lilith, Nov 2021: added cleanup_loot to reset room.
// purpose:	If you need a void room for something, use this.
// note:	
// bug(s):	
// to-do:


inherit "/std/room";

void
reset_room()
{
	cleanup_loot();
}
   
void
create_room()
{
    set_long("The whirling darkness of the Void.\n");
    set_short("whirling, dark void");

    reset_room();
}
