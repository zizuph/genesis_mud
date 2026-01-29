/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/scum.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/monster";
inherit "/std/act/action";

#include "defs.h"
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include </sys/money.h>
#include "/d/Cirath/common/introfnc.h"

void
create_monster()
{
  	set_name("grinolle");
  	set_race_name("human");
  	set_gender(0);

  	set_adj("suspicious-looking");
  	add_adj("disgusting");
  	set_short("disgusting suspicious-looking scum");
  	set_long("This human is obviously not one of the nicer "+
    		"elements of this city. His clothes are dirty "+
    		"and his whole appearance is nauseaus.\n");

  	set_stats(({ 40,50,50,20,20,50}));
  	set_skill(SS_WEP_KNIFE, 40);
  	set_skill(SS_DEFENCE, 40);
  	set_skill(SS_PARRY, 40);
 
  	set_alignment(-50 - random(50));

  	set_act_time(6);
  	add_act("spit");
  	add_act("cough");
  	add_act("fart");
  	set_chat_time(4);
  	add_chat("Do you want to see something interesting:)");
  	add_chat("Damn! I'm out of smoke!");
  	add_chat("He, he, he...");
  	set_cchat_time(6);
  	add_cchat("You sod!");
  	set_cact_time(6);
  	add_cact("chuckle");

  	add_ask("smoke","Yeah, I'm out of smoke and by that I "+
    		"mean _real_ smoke, not that shit normal smokes. The "+
    		"problem is that I can't get out of the city. Some"+
    		"one has to help me get it.\n");
  	add_ask("help","Yeah, off course you can help me! Bring "+
    		"some smoke will ya. My brother has lots of it! Just "+
    	"tell him that I sent you (he'll propably don't "+
    		"believe you anyway).\n");
}

query_knight_prestige(){return 50;}

void
arm_me()
{  
  	MONEY_MAKE_CC(random(10)+2)->move(TO,1);
  	clone_object(CIU_ARM + "scumarmour")->move(TO);
  	clone_object(CIU_ARM + "scumtrousers")->move(TO);
  	clone_object(CIU_WEP + "scumknife")->move(TO);
  	command("wear all");
  	command("wield all");
}
