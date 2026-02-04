#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"
inherit HILLS_PATH + "default_hills";

object kobold;
object kobold2;
object kobold3;

public void
create_room()
{
    ::create_room();

	add_my_desc("Through some trees you spot a path leading southwest.\n");
	add_item(({"trees","small trees"}),
	 "The trees being old conifers that have mostly rotted away, however\n"
	 + "a few trees look a little sturdier than others.\n");
	add_item(({"sturdy trees","sturdy tree","sturdier trees","sturdier tree",
               "branches","low branches","low hanging branches"}), 
 	 "You see a path on the other side of the trees. The branches hang\n"
     +"low, but perhaps you can to continue <southwest> through them?\n");		
	add_item("path", "It leads southwest, away from the hills.\n");	
	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_a1","east",0);
    add_exit(HILLS_PATH + "hills_b0","north",0);
    add_exit(HILLS_PATH + "hills_b1","northeast",0);
    add_exit("/d/Terel/common/swamp/sw1", "southwest", "@@leave_kobolds", 0);

    reset_room();
}

void
reset_room()
{
    if(!kobold)
    {
       kobold = clone_object(NPC + "newKobold");
       kobold->move(TO);

       kobold2 = clone_object(NPC + "newKobold");
       kobold2->move(TO);

       kobold3 = clone_object(NPC + "newKobold");
       kobold3->move(TO);
    }

}


public int
leave_kobolds()
{
	write ("You manage to squeeze through the branches.\n\n");
    return 0;
}