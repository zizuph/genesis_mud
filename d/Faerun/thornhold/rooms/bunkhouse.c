/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;

int rest(string str);

void
create_house()
{
    set_short("The Thornhold Bunkhouse");
    set_long("This spartan stone room is the bunkhouse adjacent to " +
             "the Thornhold alehouse. Several bunks line the walls, " +
             "providing a place for a restful night's sleep for " +
             "travellers and merchants that frequent the hold. The " +
             "beds are wooden bunks with straw-stuffed mattresses, "+
             "but they lack blankets. If you have acquired bedding " +
             "from the alehouse proprietress, you can <sleep here> "+
             "for the night. You can find her south, in the alehouse " +
             "common room.\n");

    add_item(({ "bunk", "bed", "beds", "bunks", "wooden bunks" }),
            "The beds are wooden framed with clean, straw-stuffed " +
            "mattresses, but they lack blankets. The proprietress " +
            "of the alehouse might be able to lend you some bedding.\n");
    
    add_item(({ "thornhold", "Thornhold", "hold",
		"fortress", "fort" }),
		"You are standing bunkhouse of " +
		"Thornhold.\n");
	
	add_item(({ "common room" }), "You see the common room to the " +
		"south.\n");
		
	add_rug("octagonal");

    add_cmd_item("sign", ({"read", "exa", "examine"}), "@@read_sign@@");
	
    add_exit(ROOM_DIR + "alehouse",  "south");


    reset_room();
}

string read_sign()
{
    return "If you've acquired bedding from Kalla Stoneshaft you may " +
           "choose to <sleep here>. When you next reawaken, you will " +
           "awaken here, ready to depart with the next caravan.\n";
}

public void
init()
{
    ::init();
    add_action("rest","sleep");
    add_action("rest","start");
}

void
reset_room()
{
   ::reset_room();
}

int 
rest(string str)
{
    object ob;

    if(!(ob=present("bunkhouse_inn_key",TP)))
    {
        write("You don't have any bedding!\n");
        return 1;
    }

    NF("Sleep where?\n");
    if(str != "here") return 0;

    ob->remove_object();

    TP->set_temp_start_location(ROOM_DIR + "bunkhouse");
    LOG_FILE("bunkhouse_start", "started in the Thornhold bunkhouse.");

    write("Looking around, you find a place to sleep. You will awake " +
        "here next time.\n");
    return 1;
}

