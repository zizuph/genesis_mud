/*
 *  /d/Shire/guild/smiths/obj/repair_master.c
 *
 *  This is the object to keep track of all the data-manipulation and
 *  other important functionality of the abilities we are expanding
 *  for the Smith guild. They will now be able to gain mastery points
 *  for different types of weapons and individual magic weapons. Once
 *  they have sufficient knowledge points, they will be able to repair
 *  those items and possible even craft them.
 *
 *  Related file:
 *
 *      /d/Shire/guild/smiths/obj/tool_roll.c
 *
 *  Created August 2019, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma no_clone

inherit "/d/Emerald/lib/data_manager";

#include <composite.h>
#include <macros.h>
#include <time.h>
#include "../smiths.h"


/* Definitions */
#define            DATA_DIR       ("/d/Shire/guild/smiths/knowledge/")
#define            K_POINTS       "knowledge_points"

/* Global Variables */
public mapping     Knowledge_Map = ([]);

public mixed       query_knowledge()         { return Knowledge_Map; }


/* Prototypes */
public void        create_data_manager();



/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    setuid();
    seteuid(getuid());

    set_save_dir(DATA_DIR);
    set_garbage_dir(DATA_DIR + "old/");
} /* create_data_manager */
