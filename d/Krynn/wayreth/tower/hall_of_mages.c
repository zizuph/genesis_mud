/*
   Wayreth.

   hall_of_mages.c
   ---------------

   Coded ........: 95/06/14
   By ...........: Jeremiah

   Latest update : 17/07/23
   By ...........: Arman

*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit TOWERROOM;

#define LEFT_TEST            "_wohs_test_left_test"
#define FIRST_TASK           "_wohs_test_given_first_task"
#define SECOND_TASK          "_wohs_test_given_second_task"
#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"
#define COMPLETED_TEST       "_wohs_test_completed_test"
#define KEY                  "/d/Krynn/guilds/wohs/test/obj/heartroom_key"
#define TEST_ROOM_DIR        "/d/Krynn/guilds/wohs/test/room/"

object parsalian;

void
reset_tower_room()
{

    if(!objectp(parsalian))
    {
	parsalian = clone_object(WOHS_NPCS + "parsalian");
        parsalian->arm_me();
	parsalian->move(TO, 1);
    }

}

void
create_tower_room()
{
    set_short("The Hall of Mages");
    set_long("You are standing in a vast chamber carved of dark obsidian. " +
        "The room is so wide that its perimeter is lost in the " +
        "shadows, so high that its ceiling is obscured in darkness. " +
        "No pillars supports the room, no light illuminates it. Yet " +
        "light there is, although you're not able to name or point out " +
        "its source. It is a pale light, white, not yellow, but cold and " +
        "cheerless, giving no warmth.\n");

    add_item(({"chamber","vast chamber","hall","hall of mages","room"}),
        "This vast chamber is the Hall of Mages, where the Conclave " +
        "convenes to discuss the Orders' business, pass laws, and render " + 
        "judgment on important issues. It is also the place aspirants " +
        "begin the dangerous Test of High Sorcery, where they must prove " +
        "their mettle before becoming Wizards of High Sorcery.\n"); 
    add_item(({"dark obsidian"}), "This chamber is carved of dark " +
        "obsidian, much like the rest of the Tower of Wayreth.\n");
    add_item(({"pale light","light","cheerless light","white light"}),
        "A faint, sourceless white light - unnatural and cheerless - " +
        "barely provides enough illumination for you to see those " +
        "around you.\n");
    add_item(({"shadows","darkness"}),
        "The chamber is cloaked in shadows, with a faint, sourceless " +
        "white light barely providing enough illumination for you to " +
        "see those around you, let alone any details of the room.\n");
    add_item(({"ceiling"}), "The ceiling is cloaked in shadows, you " +
        "cannot see it.\n");

    add_cmd_item(({"shadows"}),"enter","@@enter_test");
    add_cmd_item("test","check","@@check_test");
    add_cmd_item("test","reset","@@reset_test");

    add_exit(WTOWER + "foretower", "northeast", 0);

    reset_tower_room();

}

/*
 * Function name:   safely_load_master_file
 * Description:     This safely loads the master file if it hasn't already
 *                  been loaded. Otherwise, it just returns the existing
 *                  master file. If the file is not loadable, then it
 *                  simply returns 0
 * Arguments:       (string) filename - Filename of the file to load
 * Returns:         (object) - Loaded master file
 */

public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/*
 * Function name:   reset_directory
 * Description:     This function removes all the objects in the rooms in the
 *                  specified directory that dont belong to native_directory.
 * Arguments:       (string) directory - The directory which you wish to clean
 * Returns:         (status) 1 - The specified directory is infact a directory
 *                               and has been cleaned.
 *                  (status) 0 - The specified directory is not a directory, no
 *                               action was taken.
 */
public status
reset_directory(string directory)
{
    object room_ob, *trash;
    
    if (file_size(directory) != -2)
        return 0;
    
    foreach(string room: get_dir(directory))
    {
        if (file_size(directory + room) <= 0)
            continue;
        
        if (objectp(room_ob = safely_load_master_file(directory + room)))
        {
            if (!room_ob->query_prop(ROOM_I_IS))
                continue;

            if (sizeof(filter(all_inventory(room_ob), &->query_wiz_level())))
                continue;
            
            room_ob->remove_object();
        }
    }
    return 1;
} /* reset_directory */

int
filter_taking_test(object ob)
{

    int in_test;

    if(!environment(ob))
    {
	// DEBUG("No environment(ob) " + ob->query_name());
    }
    else
    {
	// DEBUG("Successfully checked environment" + file_name(environment(ob)));
	in_test = wildmatch("/d/Krynn/guilds/wohs/test/room/*",
	  file_name(environment(ob)));
    }

    if (in_test)
	return 1;

    return 0;
}

int
ld_in_test(object ob)
{
    int in_test;

    in_test = wildmatch("/d/Krynn/guilds/wohs/test/room/*",
      ob->query_prop("_player_s_ld_in_room")); 
    // DEBUG("Link dead called: " +ob->query_prop("_player_s_ld_in_room"));

    if (in_test)
    {
	return 1;
    }

    return 0;
}

string
enter_test()
{
    if(TP->query_guild_name_occ() == WOHS_GUILD_NAME)
    {
	write("You wander around the shadows of the hall, reminiscing " +
            "of when you took the Test of High Sorcery.\n");
	say(QCTNAME(TP)+ " wanders thoughtfully around the Hall of " +
            "Mages, reminiscing of when " +HE(TP)+ " took the Test of " +
            "High Sorcery.\n");
	parsalian->command("smile knowing " +TP->query_real_name());
	return "";
    }


    if(!WOHS_MANAGER->query_invited_wohs_test(TP))
    {
        write("You wander the shadows of the massive Hall of Mages.\n");
	say(QCTNAME(TP)+ " wanders the shadows of the Hall of Mages.\n");
	return "";
    }

    if(TP->query_guild_level_occ() < 8)
    {
	notify_fail("You have not yet reached a level to be " +
	    "ready to sit the Test of High Sorcery. You must be an " +
	    "experienced Novitiate with the ability to cast greater " +
            "spells!\n");
	return 0;
    }

    if(TP->query_guild_member_lay())
    {
	notify_fail("To take the Test to become a Wizard of High " +
            "Sorcery you must commit completely to the Orders. You will " +
            "need to leave your layman guild before you can take the " +
            "Test.\n");
	return 0;
    }

    if(!sizeof(filter(users(), filter_taking_test)))
    {
	if(!sizeof(filter(all_inventory(find_object("/d/Genesis/obj/statue")), ld_in_test)))
	{
            reset_directory(TEST_ROOM_DIR);

            if(WOHS_MANAGER->query_player_started_wohs_test(TP))
            {
                write("You enter the shadows, continuing your Test...\n");

                mapping test_props = WOHS_MANAGER->query_wohs_test_props(TP);

                foreach (string prop, mixed value : test_props)
                {
                    TP->add_prop(prop, value);
                }

                if(TP->query_prop(COMPLETED_TEST))
                {
	            TP->move_living("west into the shadows", WOHS_TEST + 
                        "room/void1", 1, 0); 
	            WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
                    WOHS_MANAGER->add_wohs_test_props(TP, LEFT_TEST, 2);            
                    return "";
                }

                if(TP->query_prop(HEARTROOM_ACTIVATED))
                {
	            TP->move_living("west into the shadows", WOHS_TEST + 
                        "room/daltigoth_tower2", 1, 0); 
	            WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
                    WOHS_MANAGER->add_wohs_test_props(TP, LEFT_TEST, 2); 
                    clone_object(KEY)->move(TP, 1);
                    TP->catch_msg("A shadowy key appears in your " +
                        "inventory.\n");             
                    return "";
                }

                if(TP->query_prop(SECOND_TASK))
                {
	            TP->move_living("west into the shadows", WOHS_TEST + 
                        "room/daltigoth_tower2", 1, 0); 
	            WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
                    WOHS_MANAGER->add_wohs_test_props(TP, LEFT_TEST, 2);              
                    return "";
                }

                if(TP->query_prop(FIRST_TASK))
                {
	            TP->move_living("west into the shadows", WOHS_TEST + 
                        "room/daltigoth_tower2", 1, 0); 
	            WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
                    WOHS_MANAGER->add_wohs_test_props(TP, LEFT_TEST, 2);              
                    return "";
                }

	        TP->move_living("west into the shadows", WOHS_TEST + 
                    "room/passage1", 1, 0); 
	        WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
                WOHS_MANAGER->add_wohs_test_props(TP, LEFT_TEST, 2);              
                return "";
            }

	    WOHS_MANAGER->add_started_wohs_test(TP->query_real_name());
	    write("You move west into the shadows...\n");
	    TP->move_living("west into the shadows", WOHS_TEST + 
                "room/passage1", 1, 0);
	    return "";
	}
    }

    write(C(WOHS_MANAGER->query_started_wohs_test()) + " is currently " +
        "taking the Test of High Sorcery. You will need to wait until " +
        "their testing is over before you can begin your own.\n");
    return "";

}

string
check_test()
{

    if(!QUERY_IS_ARCHMAGE(this_player()) && 
       !QUERY_WHITE_COUNCIL(this_player()) && 
       !QUERY_RED_COUNCIL(this_player()) && 
       !QUERY_BLACK_COUNCIL(this_player()) &&
       !TP->query_wiz_level())
    {
       write("Only Archmages or the Conclave may check who is currently " +
           "taking the Test!\n");
       return "";
    }

    if(!sizeof(filter(users(), filter_taking_test)))
    {
	if(!sizeof(filter(all_inventory(find_object("/d/Genesis/obj/statue")), 
            ld_in_test)))
	{
	    write("No one is currently taking the Test of High Sorcery.\n");
	    return "";
	}
        write(C(WOHS_MANAGER->query_started_wohs_test()) + " is currently " +
            "taking the Test of High Sorcery, although appears to have " +
            "vanished temporarily into the void.\n");
        return "";
    }

    write(C(WOHS_MANAGER->query_started_wohs_test()) + " is currently " +
        "taking the Test of High Sorcery.\n");

    return "";
}

string
reset_test()
{

    if(!TP->query_wiz_level())
    {
       write("What?\n");
       return "";
    }

    if(sizeof(filter(users(), filter_taking_test)))
    {
       write("Someone is currently in a Test room. Best remove them " +
          "first before manually resetting the Test.\n");
       return "";
    }

    if(sizeof(filter(all_inventory(find_object("/d/Genesis/obj/statue")), 
        ld_in_test)))
    {
       write("Someone is linkdead who is currently running the Test.\n");
       return "";
    }

    write("You reset the Test of High Sorcery.\n");
    say(QCTNAME(TP)+ " resets the Test of High Sorcery.\n");

    reset_directory(TEST_ROOM_DIR);

    return "";
}
