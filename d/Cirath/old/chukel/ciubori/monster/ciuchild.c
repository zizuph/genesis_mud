/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/ciuchild.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/monster";
inherit "/std/act/action";

#include "defs.h"
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>

void
create_monster()
{
  	set_name("nisse");  	
  	set_race_name("human");
  	set_gender(0);

  	set_adj("ciubori");
  	set_short("ciubori child");
  	set_pshort("ciubori children");
  
  	set_long("This is one of the many citizens of Ci'u'bori. This city "+
           	"has many children playing and shouting in the streets, which "+
           	"could both be nice and annoying to some people.\n");

  	set_stats(({ random(20), random(30), random(20), random(20), random(20),30}));
  	set_skill(SS_DEFENCE, 10 + random(10));
  	set_skill(SS_UNARM_COMBAT,10 + random(10));

  	set_alignment(50 + random(50));

  	set_act_time(6);
  	add_act("jump");
  	add_act("scream");
  	add_act("tickle all");
  	add_act("emote runs armound shouting.");
  	set_chat_time(4);
  	add_chat("Hiya!");
  	add_chat("Can I have some candy from you?");
  	set_cchat_time(6);
  	add_cchat("Help!");
  	add_cchat("Mommy said I should beware of strangers!");
  	set_cact_time(6);
  	add_cact("sob");
  	add_cact("emote screams out loud."); 
  	add_ask("candy","I like candy! Gimme some!\n");
}

query_knight_prestige(){return -100;}

void
arm_me()
{
  	clone_object(CIU_ARM + "ciushirt")->move(TO);
  	clone_object(CIU_ARM + "ciutrousers")->move(TO);
  	clone_object(CIU_WEP + "ciustick")->move(TO);
  	command("wear all");
  	command("wield all");
}
