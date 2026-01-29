/*
 *  Shire's standard room.  This file should be inherited by all
 *  rooms within the shire!
 *
 *  Copyright (C)  Chad Richardson,   Feb 97
 *
 *  Please also read the files in /d/Shire/std/room/ to find all about 
 *  the Shires base room functionality.  Important and easy set ups are
 *  are within that directory to make your life easier.
 *  -Igneous-
 */
inherit  "/std/room";
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Shire/std/room/search";
inherit "/d/Shire/std/room/cmd_parse";
inherit "/d/Shire/std/room/exitmsg";
inherit "/d/Gondor/common/lib/time";

#include "/d/Shire/sys/sunlight.h"
#include "/d/Shire/sys/defs.h"


//  Prototypes
nomask public int query_sunlight();


/*
 * Function name : Create_shire_room
 * Description   : This is the create function to be used when creating
 *                 rooms in the Shire.  
 */
public void
create_shire_room() {}

/*
 * Function name : Create_room
 * Description   : creates the room with all the Standard things we wish to
 *                 have in the Shire.  
 * TODO          : Make this function nomask when I know that all the rooms
 *                 that inherit this file don't use create_room.
 */
public void
create_room()
{
    // These are here for mortals... They usually report wierd long and
    // short desceptions.
    set_short("Shire base room");
    set_long("This is the Shire's Base Room which should be inherited "+
      "by every room in the Shire.\n");

    //  The domains sunlight level.
    add_prop("_room_i_sunlight", query_sunlight);
    create_shire_room();
}

/*
 * Function name : Reset_shire_room
 * Description   : If you want to reset a room in the Shire use this function.
 */
void
reset_shire_room() {}

/*
 * Function name : Reset_room
 * Description   : Takes care of reseting certain things used in the Shire,
 *                 such as herbs and other searches
 * TODO          : Make this function nomask when I know that all the rooms
 *                 that inherit this file don't use reset_room.

 */
void
reset_room()
{
    if (sizeof(query_herb_files()))
	this_object()->reset_shire_herbs();
    if (query_prop(OBJ_S_SEARCH_FUN) == "shire_search_fun")
	this_object()->reset_shire_search();
    reset_shire_room();
}

/*
 * Function name : Query_sunlight
 * Description   : Sets up the Sunlight level of the domain.... used mainly
 *                 as support for the Vampire guild.
 */
nomask public int
query_sunlight()
{
    string time = CLOCK->query_time_of_day();
    int level = 0;

    if (query_prop(ROOM_I_INSIDE))
	return 0;

    switch(time)
    {
    case "night":
	return SUNLIGHT_NIGHT;
    case "evening":
    case "early morning":
	level = SUNLIGHT_DIM;
	break;
    case "afternoon":
    case "morning":
	level = SUNLIGHT_NORMAL;
	break;
    case "noon":
	level = SUNLIGHT_BRIGHT;
	break;
	//  Should never go to default
    default:
	level = 1;
	break;
    }


    //   If a weather master is ever created modify level due to
    //   It being sunny or cloudy out.

    return level;
}

/* 
 * Function name : Init (masked)
 * Description   : sman init for more detals. It's masked here for 
 *                 cmd_parse support.
 */
public void
init()
{
    ::init();

    add_action(check_time, "time");
    init_cmdparse();
}

/*
 * Function name : Enter_inv 
 * Description   : sman enter_inv for more details.  It's masked here
 *                 for room_tell support.
 */
public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}



