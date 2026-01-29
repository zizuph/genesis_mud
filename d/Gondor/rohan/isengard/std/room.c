/*
 *	/d/Gondor/rohan/isengard/std/room.c
 *
 *	The master room for Isengard.
 *      This master supports variable room descriptions based on  
 *      the stage of the Ring Quest.
 *
 *      Olorin, 1996
 *              August 1997
 *
 *      Copyright (c) 1996 by Christian Markus and Brian Smaakjaer 
 *      Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../defs.h"

/*
 *     Prototypes:
 */

/*
 *     Global variables:
 */
        static object  Master;

/*
 * set and query function for global variables:
 */

/*
 * Function name: create_isengard
 * Description:   creator for rooms in Isengard
 */
public void
create_isengard()
{
}

/*
 * Function name: query_isen_desc
 * Description:   Give a stage dependent description of the room. 
 *                Has to be defined in the rooms. This is just a dummy
 *                function.
 * Argument:      stage - The the Isen_Stage variable.
 * Returns:       The room description for this stage.
 */
public string
query_isen_desc(int stage)
{
    string  desc = "";

    switch (stage)
    {
    case ROHAN_STAGE_PEACE..ROHAN_STAGE_PEACE_END:
	desc += "The circle of Isengard is peaceful and almost empty " 
	     +  "creatures. Only a few dunlendings are visible at the "
	     +  "gates.";
	break;
    case ROHAN_STAGE_HOSTILE..ROHAN_STAGE_HOSTILE_END:
	desc += "The circle of Isengard is filled with orcs and "
	     +  "dunlendings preparing for war. Dark clouds are "
	     +  "coming out of openings in the ground.";
	// fall thru
    case ROHAN_STAGE_WAR..ROHAN_STAGE_WAR_END:
	desc += " Some of the orcs are equipped with weapons that "
	     +  "must have been looted from dead Rohirrim.";
	break;
    case ROHAN_STAGE_BATTLE..ROHAN_STAGE_BATTLE_END:
	desc += "The circle of Isengard is void of life and has "
	     +  "been laid waste by what must have been a large "
	     +  "number of orcs.";
	break;
    case ROHAN_STAGE_DEFEAT:
	desc += "The circle of Isengard is filled by the victorious "
	     +  "army of Saruman which has returned to Isengard "
	     +  "the conquest of Rohan.";
	break;
    case ROHAN_STAGE_VICTORY:
	desc += "The Circle of Isengard has not yet fully recovered "
	     +  "from a giant flood that most have filled the bowl "
             +  "of Isengard almost completely. The gates are broken "
             +  "and in many places young trees are growing.";
	break;
    }
    return desc;
}

/*
 * Function name: long_desc
 * Description:   VBFC for the long description of the room
 */
private string
long_desc()
{
    int     isen_stage = Master->query_isen_stage();
    string  desc;

    desc = "";
    desc += query_isen_desc(isen_stage);

    // We still use break_string since I think the room descriptions
    // look much better that way:
    return BSN(desc);
}

/*
 * Function name: create_gondor
 * Description:   creator for rooms in Gondor
 */
nomask void
create_gondor()
{
    ISEN_MASTER->load_me();
    Master = find_object(ISEN_MASTER);

    set_long(long_desc);
    create_isengard();
}


