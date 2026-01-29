/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/unci.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/monster";

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Cirath/common/introfnc.h"

create_monster()
{
	set_name("Unci");
    	set_living_name("Unci");
    	set_short("pub owner");
    	set_long("She's working with something behind the bar.\n");
    	set_race_name("human");
    	set_gender(1);
    	add_act(({"say Welcome","say What do you want to order?"}));
    	add_act("emote starts working with something behind the bar.");
    	add_act(({"say Lotsa weird people come here...","smile mysteriously"}));

    	set_act_time(10);

    	set_skill(SS_UNARM_COMBAT,100);

    	set_gender(0);
    	set_stats(({random(75) + 50,random(75) + 50,random(75) + 50,random(75) + 50,random(75) + 50,random(75) + 50}));
    	set_alignment(170);

}
