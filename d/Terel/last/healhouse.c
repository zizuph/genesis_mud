// Healhouse.
//    updated by Lilith Feb 2022: added sign for the services
//      provided by Saclin.
//      added ROOM_I_INSIDE prop

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

string
do_sign()
{
	return 
    "I, Saclin Sirvan, perform the following:\n\n"+
	"  Service                        Fee\n"+
	"--------------------------------------\n"+
	"Mend broken bones .............. ask\n"+
    "Purge the plague ............... ask\n"+
	"Reveal a scrier ................ ask\n"+
	"--------------------------------------\n";
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Healer of Last");
    set_long("This is where the healer for the village lives. "+
	    "Here he tends to the injuries and illnesses "+
        "of the people of Last, and to those of strangers "+
        "who have the coin to pay for his services. There "+
        "is a table for people to lie on while the healer "+
        "tends to them, and a discreet sign on the wall.\n");

    add_item("table","A long wooden examining table.\n");
    add_item(({"sign", "discreet sign", "wall"}),
        "There is a discreet sign hanging on the wall. It "+
        "reads:\n"+ do_sign()+"\n");
    add_cmd_item(({"sign", "discreet sign", "wall"}), "read",
        do_sign());

    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(LAST_DIR + "lroad3", "southeast", 0);
	add_prop(ROOM_I_INSIDE, 1);
    add_npc(LAST_DIR + "npc/saclin", 1);

}

