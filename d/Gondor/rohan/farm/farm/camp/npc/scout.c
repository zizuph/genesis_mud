#pragma strict_types
#pragma save_binary

inherit "/std/act/attack";
inherit "/std/monster";
#include "/d/Gondor/defs.h"
#include "defs.h"
#include "/d/Gondor/rohan/farm/farm/camp/defs.h"
inherit  "/d/Gondor/rohan/farm/farm/camp/lib/base_dunlending";	
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>


/*
 * Defines for guard_type();
 */
#define CLONE_SCOUT 	0
#define CLONE_GUARD 	1
#define CLONE_CAPTAIN	2
#define CLONE_ARCHER	3
#define CLONE_RANDOM	(random(4))

void
create_camp_guard() 
{
	set_guard(CLONE_SCOUT);
//	set_stats( ({160, 200, 175, 140, 140, 175}), 20);
    
  /*   string bracers,
            greaves,
            helm,
            body,
            faulds,
            boots,
            weapon;
  
        weapon =    (CAMP_WEP_DIR + "weapon_regular");
        bracers =   (CAMP_ARM_DIR + "d_bracers_common");
        greaves =   (CAMP_ARM_DIR + "d_greaves_common");
        body =      (CAMP_ARM_DIR + "d_chainmail_common");
        helm =      (CAMP_ARM_DIR + "d_helm_common");
        if(!random(50))
        {
        faulds =    (CAMP_ARM_DIR + "d_faulds");
        }
        equip( ({weapon, bracers, greaves, body, helm}) );
        if(strlen(faulds))
        {
            equip(faulds);
        }
    
	*/
}