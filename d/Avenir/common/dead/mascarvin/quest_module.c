// file name:        /d/Avenir/common/dead/mascarvin/quest_module.cabs
// creator(s):       Lilith, 29 April 2021
// revisions: 
// purpose:          SMIS quest module for Mascarvin's Catacomb Quest
// note:             add this to the preload.c       
// bug(s):           
// to-do:            

#pragma strict_types
#include <macros.h>
#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/smis/modules.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/defs.h"
#include "defs.h"

inherit SMIS_MODULE_QUEST;

string *lfrooms = LF_ROOMS;
string *hfrooms = HF_ROOMS;
string *pkrooms = PK_ROOMS;
string *shrooms = SH_ROOMS;

void 
create_quest()
{

    set_module_dynamic(1);
    set_module_id("tjanaq");
    set_module_description("Tjana's quest, on the Holm.");
    set_quest_long_description(
        "The quest is to find the pieces of the statue of Tjana, "+
        "reassemble it, and then offer it at an appropriate "+
        "altar.\n");

    set_quest_bit(TJANAQ_GROUP, TJANAQ_BIT);
//    add_quest_variant("I'm not sure what other variants might be",
//        TJANAQ_QUEST_XP, 0, 0);

    set_create_notification(({ STUMP_ROOM }));
    set_location_object(STUMP_ROOM, HOLM_OBJ + "tshard1");    
    set_location_object(ONEOF(lfrooms), HOLM_OBJ + "tshard2");
    set_location_object(ONEOF(hfrooms), HOLM_OBJ + "tshard3");
    set_location_object(ONEOF(shrooms), HOLM_OBJ + "tshard4");
    set_location_object(ONEOF(pkrooms), HOLM_OBJ + "tshard5");
    // travelling merchant has the other piece

    /* Nothing beneath this line of code */
    SMIS_MANAGER->register_smis_module(this_object());
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
