// file name:        /d/Avenir/common/dead/barrow/barrow_placer.c
// creator(s):       Lilith, Aug 2021
// revision history: 
// purpose:          Module that places mobs and objs in the Barrow
// note:             This makes it easier to update clone locations 
//                   for the whole area in one place.
// bug(s):           
// to-do:

#include <macros.h>
#include "../dead.h"
#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit SMIS_MODULE_PLACER;

// Could have put these in dead.h but they are only used here.
#define RAT       MON +"rat"
#define RUSHLIGHT OBJ +"rushlight"
#define COOKFIRE  OBJ +"cookfire"
#define CRATE     OBJ +"bogl_crate"
#define SHOVEL    OBJ +"shovel"
#define BOGL      MON +"bogl"
#define COOK      MON +"bogl_cook"
#define SMITH     MON +"bogl_smith"
#define WISE      MON +"bogl_wisewoman"

void create_placer()
{

    /* Prevents computation of the list of rooms this module operates
       on: keeps rooms from cluttering the decision tables. */
   disable_notifications_autoset();
	
    set_module_id("barrowp");
    set_module_description("Placer module for the bogl barrow");

    set_location_npc(BARROW  + "barrow1",   BOGL);
    set_location_npc(BARROW  + "barrow10",  BOGL);
    set_location_npc(BARROW  + "barrow9",   BOGL);
    set_location_npc(BARROW  + "barrow2",   BOGL);	
    set_location_npc(BARROW  + "barrow8 ",  BOGL);
    set_location_npc(BARROW  + "barrow_armr", SMITH);
	
    set_location_npcs(BARROW + "barrow13",   ({ BOGL, BOGL, COOK}));
    set_location_npcs(BARROW + "barrow15",   ({ BOGL, BOGL, RAT }));
    set_location_npcs(BARROW + "barrow16",  ({ BOGL, WISE }));
    set_location_npcs(BARROW + "barrow4",   ({ BOGL, BOGL, BOGL }));
    set_location_npcs(BARROW + "barrow5",   ({ BOGL, BOGL, BOGL }));
    set_location_npcs(BARROW + "barrow6",   ({ BOGL, BOGL, BOGL }));

    set_location_object(BARROW + "barrow17",    CRATE); 
    set_location_object(BARROW + "barrow7",     RUSHLIGHT); 
    set_location_object(BARROW + "barrow13",    COOKFIRE); 
    set_location_object(BARROW + "barrow4",     RUSHLIGHT);
	set_location_object(BARROW + "barrow_armr",   SHOVEL);

    set_location_objects(BARROW + "barrow18", ({ CRATE, RUSHLIGHT }));


}

