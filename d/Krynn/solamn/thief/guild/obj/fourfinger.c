/* the trainer of the thieves, by Aridor 03/24/94*/

#include "../guild.h"
inherit M_FILE

#include <macros.h>
#include <ss_types.h>
#define JOINROOM   GUILDR + "join"
#define TRAINROOM  GUILDR + "train"

int no_intro = 0;
int inaug = 0;

void
create_krynn_monster()
{
    set_name("stony");
    set_living_name("stony");
    set_adj("blond-haired");
    add_adj("one-armed");
    set_title("Fourfingers, the Master Burglar of the Cabal of Hiddukel");
    set_gender(0);
    set_long("This is a blond-haired, one armed man who has passed his " +
	     "best years. You are certain he is an expert at whatever " +
	     "he is. His right arm is missing and he only has four fingers " +
	     "on his left hand, making him unable to continue his profess" +
	     "ion. He now puts his effort into teaching aspiring Master " +
	     "Burglars the art of Thievery.\n");
    set_race_name("human");
    default_config_mobile(90);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);
    set_skill(SS_BACKSTAB, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_PICK_POCKET, 80);
    set_skill(SS_FR_TRAP, 80);
    set_skill(SS_HIDE, 80);
    set_skill(SS_SNEAK, 80);
    set_skill(SS_OPEN_LOCK, 80);
    set_skill(SS_ACROBAT, 80);
    set_skill(SS_TRADING, 100);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);

    set_alignment(-100);
    set_knight_prestige(1000);

    trig_new("%s 'introduces' %s","introduce_me");
}

int
tattoo_new_member(object who)
{
    if (E(TO) != find_object(TRAINROOM))
      return 0;
    move_living("south",JOINROOM);
    who->catch_msg("As you get yourself ready to join, " + query_art_name(who)
		   + " rushes in from the north.\n");
    tell_room(E(TO),QCNAME(TO) + " rushes in from the north.\n",who);
    set_alarm(1.0,0.0,"do_the_tattooing",who);
    return 1;
}

void
introduce_me()
{
    if (no_intro)
      return;
    no_intro = 1;
    set_alarm(3.0,0.0,"intro_me");
}

void
intro_me()
{
    command("introduce me");
    no_intro = 0;
}


void
do_the_tattooing(object who)
{
    switch (inaug)
      {
	case 2:
	  who->catch_msg("The human whispers to you: Welcome to the Cabal " +
			 "of Hiddukel.\n");
	  who->catch_msg("The human whispers to you: Heed the rules of " +
			 "the guild and you will be well rewarded.\n");
	  tell_room(E(TO),"The human whispers something to " + QTNAME(who) +
		    ".\n",who);
	  break;
	case 4:
	  who->catch_msg("The human reaches into one of his pockets and " +
			 "gets out a large syringe!\n");
	  tell_room(E(TO),QCTNAME(TO) + " reaches into one of his pockets " +
		    "and then grabs hold of " + QTNAME(TP) + ".\n", who);
	  break;
	case 7:
	  who->catch_msg("With a swift motion, he snaps your head back and " +
			 "you feel PAIN running down from your shoulder " +
			 "through your body into your legs.\n");
	  break;
	case 8:
	  who->command("scream");
	  break;
	case 13:
	  who->catch_msg("Just as sudden " + query_the_name(who) +
			 " releases you and the pain subsides immediately. " +
			 "What remains is an itchy feeling on your shoulder.\n");
	  tell_room(E(TO), QCTNAME(TO) + " does something to " + QTNAME(TP) +
		    " and then suddenly releases " + QTNAME(TP) + " again.\n",
		    who);
	  break;
	case 16:
	  who->catch_msg(query_The_name(who) + " hands you a key ring.\n");
	  who->catch_msg("He says: This is your token of membership of " +
			 "the Cabal of Hiddukel. Keep it well for it is " +
			 "also the key to enter the guildrooms easily.\n");
	  tell_room(E(TO), QCTNAME(TO) + " whispers something to " +
		    QTNAME(who) + ".\n", who);
	  break;
	case 18:
	  command("congratulate " + who->query_name());
	  break;
	case 21:
	  tell_room(E(TO),"Effortlessly, " + QTNAME(TO) + " leaves north.\n");
	  move_living("M",TRAINROOM);
	  tell_room(E(TO),QCTNAME(TO) + " arrives again.\n");
	  inaug = -1;
	  break;
	default:
      }
    inaug++;
    if (inaug)
      set_alarm(1.0,0.0,"do_the_tattooing", who);
}
