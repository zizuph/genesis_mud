/**********************************************************************
 * - door1 .c                                                       - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types
#include "../inn.h"

inherit "/d/Khalakhor/std/door";

void
create_khalakhor_door()
{
	object lockob;
	set_name("door");
	add_name("door1");
	set_door_id(1);
	set_adj("oak");
	set_long("A heavy oak door that has the numeral '1' engraved "+
	"on a small brass plate.\n");
	set_open(0);
	lockob = add_default_lock();
	lockob->set_key(KEY1);
	lockob->lock();
}

/*
 * Function name : parse_command_adjectiv_id_list
 * Description   : function returns the possible adjectives of the object
 * Arguments     : void    - no arguments
 * Returns       : string* - adjectives list
 */
public string*
parse_command_adjectiv_id_list()
{
	return ((::parse_command_adjectiv_id_list() || ({ })) +
        (strlen(exit_dir) ? ({ exit_dir }) : ({ })));
}

