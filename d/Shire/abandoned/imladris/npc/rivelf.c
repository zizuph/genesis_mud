inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

/**************** Guild specific defines and includes ****************/
#include "/d/Shire/imladris/guild/guild.h"
#define LW_SOUL 			"/d/Shire/imladris/spell/lw/lw"
#define CW_SOUL				"/d/Shire/imladris/spell/cw/cw"
#define HEALER_SOUL_FILE	"/d/Shire/imladris/guild/soul"
/**************** End of guild spec defines/includes *****************/

int alarm_id;

create_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("bregolas");
   set_race_name("elf");
   set_adj(({"happy","smiling"}));
   set_gender(G_MALE);
   set_long("Bregolas is a young elf, at age 30, still almost a "+
      "child. His happy, smiling face makes visitors to Rivendell "+
      "feel very welcome.\n");
   set_stats(({30,50,40,58,60,30}));
   MAKE_MONEY;
   set_alignment(100);
   
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,50);
   
   add_prop(CONT_I_WEIGHT, 60*1000);
   add_prop(CONT_I_HEIGHT, 120);
   set_gender(G_MALE);
   
   set_chat_time(1);    
   add_chat("I'm so happy to see you! Are you a friend of Elronds?");
   add_chat("Meeting travelers always makes me so happy.");
   add_chat("Rivendell is such a wonderful place, have you been to Elrond's house yet?");
   add_chat("Will you write a poem or a song, to tell us all about "+
      "your adventures?");
   add_chat("I'm so happy, I feel like singing.");
   
   set_act_time(3);
   add_act("smile merri");
   add_act("bounce");
   add_act("emote seems like he is about to burst with happiness.");
   add_act("giggle merri ");
   add_act("emote sings a merry little tune.");
   add_act("introduce myself");
   
   set_cact_time(5);
   add_cact(({"scream","say STOP! WHY, tell me, WHY??!"}));
   add_cact("knee all");
   add_cact("emote yells: If you don't stop, I will call my father!");
   
   set_cchat_time(3);
   add_cchat("And I thought we would be friends.");
   add_cchat("You'll be sorry, when my father get's here.");
   add_cchat("You just wait, my father is bigger than you.");
   
   /*Triggers*/
   
   set_alarm(0.5,0.0,"arm_me");
   
}

arm_me()
{
   object knife,tunic,boots;
   
   FIXEUID;
   
   knife = clone_object(RIV_DIR + "wep/" + "eknife1");
   tunic = clone_object(RIV_DIR + "arm/" + "etunic1");
   /*    boots = clone_object(BREE_DIR + "arm/" + "boots");
   boots->move(TO);
   */
   knife->move(TO);
   tunic->move(TO);
   command("wear all");
	seteuid(getuid());
	add_cmdsoul(HEALER_SOUL_FILE);
	add_cmdsoul(LW_SOUL);
	add_cmdsoul(CW_SOUL);
	update_hooks();
   
}

void
attacked_by(object obj)
{
   ::attacked_by(obj);
   command("say I may be small, but I'm strong.");
   command("emote haltingly grips his small sharp knife!");
   command("wield all");
   command("wear all");
   
   alarm_id = set_alarm(10.0,20.0,"before_attack");
}

void
before_attack()
{
   if(TO->query_attack())
      {
      return;
   }
   command("unwield all");
   remove_alarm(alarm_id);
}

/* Here is some guild specific things too. */

#define GUILD_TAX 35

int
query_guild_tax_occ()
{
	return GUILD_TAX;
}

string
query_guild_title_occ()
{
	return "Hopeful Radiance of Imladris";
}

string
query_guild_style_occ()
{
	return GUILD_STYLE;
}

string
query_guild_name_occ()
{
	return GUILD_NAME;
}

int
query_spell_level()
{

	return 15;
}

int
spell_list_exp()
{
	return 300000;
}

