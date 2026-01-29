// Lapidis      /d/Avenir/common/bazaar/NPCS/lapidis.c
// creator(s):  Lilith, Dec 1997
// last update: 
// purpose:     To be shopkeeper for the lapidary shop.
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/bazaar/bazaar.h"
# include "/d/Avenir/include/guilds.h"
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit "/d/Avenir/inherit/monster";

int alarm_id;

void
create_monster()
{
	 set_name("imlis");
	 set_title("icu Sisaer, Sybarite Gemologist");
	 add_name(({"shopkeeper","keeper"}));
	 set_race_name("gnome");
	 set_gender(G_MALE);
	 set_adj("slender");
	 add_adj("myopic");
	 set_long("A gnome of indeterminate age with the myopic eyes " +
				 "of one who spends hours staring at small items. He " +
				 "is a gemologist well-known for his talents and fair-"+
				 "dealing.\n");

	 set_act_time(5);
	 add_act("emote studies a gem under the lens.");
	 add_act("emote lovingly polishes a gemstone.");
	 add_act("emote taps a tool against a gem.");
	 add_act("emote seems engrossed in his work.");
	 add_act("emote holds a gem up to the light.");
	 add_act("smile soft");

	 set_all_hitloc_unarmed(50);

	 set_stats(({70,70,70,70,70}));

	 set_skill(SS_UNARM_COMBAT,50);
	 set_skill(SS_BLIND_COMBAT,100);
	 set_skill(SS_PARRY,50);
	 set_skill(SS_DEFENCE,65);
	 set_skill(SS_AWARENESS,50);
	 set_skill(SS_WEP_SWORD,50);
	 set_skill(SS_WEP_POLEARM,50);
	 set_skill(SS_WEP_CLUB,50);
	 set_skill(SS_WEP_KNIFE,50);
	 add_prop(NPC_I_NO_RUN_AWAY,1);

	 set_alignment(0);
	 set_knight_prestige(-1);

	 set_mm_in("arrives.");
}

public void
arm_me()
{
	 object cloak;

	 seteuid(getuid());
	 MONEY_MAKE_SC(random(10))->move(this_object());

	 clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
	 clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
	 clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
	 clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);

	 cloak = clone_object(BAZAAR + "Obj/worn/mencloaks");
	 cloak->create_tailored();
	 cloak->move(TO, 1);
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
	 string  occ;
	 int     i;
	 i = random(6);

	 /* reset meet alarm */
	 alarm_id = 0;

	 if (!present(tp, environment(TO)))
		  return;

	if(tp->query_prop("_is_cat_"))
	{
		command("ack");
		command("shouts: NO CATS IN HERE!");
		command("emote says to his assistant: Get the butcher!");
		return;
	}

	 occ = tp->query_guild_name_occ();
	 if (occ == OUNION)
	 {
		  if (i == 2)
				command("bow respect "+ tp->query_real_name());
		  else
		  if (i == 4)
				command("say to "+ tp->query_real_name() +" I am "+
					 "honoured by your patronage!");
		  else
		  if (i == 5)
				command("say to "+ tp->query_real_name() +" May I sell "+
					 "you a gem?");
		  return;
	 }
	 if (tp->query_prop("_live_i_am_dancer_of_veils"))
	 {
		  if (i == 0)
				command("smile respect "+ tp->query_real_name());
		  else
		  if (i == 4)
            command("bow "+ tp->query_real_name());
        return;
    }       
    else
    {
        if (i == 3)
           command("say Welcome! Are you here to buy gems or sell them?");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (alarm_id)
        return;

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));        
        return;
    }
}  
