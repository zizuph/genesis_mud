// file name:        /d/Avenir/smis/examples/mod1.c
// creator(s):       Denis, Jul'96
// revision history: 
// purpose:          Example module with load and reset notification and
//		     a simple command.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include "../../smis.h"

inherit SMIS_MODULE;

/*
 * Function name: create_module
 * Description:   
 * Arguments:     
 * Returns:       
 */
void create_module()
{
    // Identifier of a module. Should be unique (at least within the
    // manager you are going to register the module);
    set_module_id("mod1");

    // The module description. Should be informative :)
    set_module_description("Test module 1");

    // Lets consider the module to be of types and example.
    set_module_types(({"example"}));

    // We want to receive notification message about the creation of
    // the /d/Avenir/smis/std/smis_room object.
    set_create_notification( ({ "/d/Avenir/smis/lib/smis_room" }) );

    // Lets also receive its reset notification.
    set_reset_notification( ({ "/d/Avenir/smis/lib/smis_room" }) );

    // We want to allow the other domains to register the module in their
    // domain.
    set_module_open(1);
}

/*
 * Function name: notify_object_created
 * Description:   Is called when objects, specified by set_create_notification
 *		  are created. Good place to add_actions for a room
 *		  or something similar.
 * Arguments:     o_created - The object that was created;
 *		  s_created - The filename of the object created;
 */
void notify_object_created(object o_created, string s_created)
{
    find_player("denis")->
	catch_tell("MOD1: Just loaded '" + s_created + "'.\n");
}

/*
 * Function name: notify_object_reset
 * Description:   This function is called when an object, which we asked
 *		  with set_reset_notification, resets.
 * Arguments:     o_reset - Object, which is reset;
 *		  s_reset - The filename of o_reset;
 */
void notify_object_reset(object o_reset, string s_reset)
{
    find_player("denis")->
        catch_tell("MOD1: Just reset '" + s_reset + "'.\n");
}

/*
 * Function name: perform_empty_command
 * Description:   Is called when this_player() entered just
 *		  'smis [<domain>] <this module id>' without additional args.
 * 		  Good place to print the list of commands an little help.
 * Returns:       1 - command ok.
 */
int perform_empty_command(string str)
{
    write(gCaption + "\nTest module.\n\n" +
          " - test        Plain test command.\n" + gBottom);
    return 1;
}

/*
 * Function name: perform_test_command
 * Description:   Will be called when player has entered
 *		  'smis [<domain>] <this module id> test <...>'.
 * Arguments:     str - The additinal arguments for test command
 * Returns:       
 */
int perform_test_command(string str)
{
    // This is significant only if the module isn't public (open)
    // (we called the set_open function in create_module...)
    // If the module wasn't open, this would wade off the unwanted
    // people...
    SMIS_CHECK_CALLER;

    write(gCaption + "\nYou entered: '" + str + "'.\n\n" + gBottom);

    return 1;
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
