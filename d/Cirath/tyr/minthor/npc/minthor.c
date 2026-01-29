inherit "/d/Cirath/std/monster";
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#include "/d/Cirath/common/introfnc.h"
#include "../defs.h"
#include <money.h>
#define _QUEST_BRACELET_ "_quest_bracelet_"
#define HAS_ASKED "_has_asked"

int bracelet;
string long;
object minthor;

void
create_monster()
{
   set_name("maximus");
   set_title(" Minthor, Patriarch of the Minthor Clan and Senator "
	+"of Tyr");
   set_race_name("human");
   set_adj("older");
   add_adj("noble");
   set_gender(0);
   set_short("older noble human");
   set_long("This older gentleman is obviously the patriarch of "
	+"the Minthor House.  He is wearing beautifully tailored "
	+"clothing, yet he seems to be very unhappy. His cheeks "
	+"are streaked from the tears you see pouring down his face "
	+"even now.  As you walked in the room, he stood up from "
	+"his seat on a small divan and moved towards you.\n");
   set_alignment(100);
   set_stats(({110,120,130,100,100,110}));
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
    add_ask("join","You need to talk to some of the nobles who "
	+"are too poor to afford their own guards.  I don't "
	+"deal with those Militia types.\n");
    add_ask("militia","They are beneath me.  I will have nothing "
	+"to do with them.\n");
   set_act_time(3);
   add_act("say I need someone's help finding my wife's murderer.");
   add_act("say Being rich was nice, now things look so bleak.");
   add_act("say Are you here to help?");
   add_act("emote sobs sadly.");
   set_cact_time(6);
   add_cact("say Come on then, die!");
   add_cact("say You killed my wife and have come back for me! No "
	+"matter what you do to me, you and your Veiled Alliance "
	+"can rot!");
   add_cact("emote smashes your skull with his mace.\n "
	+"You feel mortally wounded.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_ask(({"help","task","job"}),"He smiles at you and says:\n "
	+"Thank you for coming.\n "
	+"I will give you all the details I have, which aren't many, "
	+"but hopefully it will give you some direction to go in. "
	+"Two weeks ago I was far away in the city of Kabal with "
	+"business partners.  We concluded our business there and I "
	+"returned home.  When I got home, to my shock, I was told "
	+"that my wife had been murdered in the night and some "
	+"things were stolen by a thief.  Needless to say, this did "
	+"not feel correct to me, so I investigated it somewhat myself. "
	+"Within the first week, we had recovered everything that was "
	+"missing except the bracelet.  Whoever has the bracelet is the "
	+"murderer.  Please find out who did this and why.  Bring me "
	+"her bracelet and your report and you will be rewarded handsomely. "
	+"This task will be dangerous.  Good Luck.\n");
   add_ask("bracelet","It is a beautifully crafter bracelet I gave my "
	+"wife as a gift.  It has an inscription in it.  Please find it.\n");



}

void
arm_me()
{
   clone_object(TZ_MINTHOR + "wep/lm_mace")->move(TO);
   command("wield all");
   clone_object(TZ_MINTHOR + "arm/lm_mail")->move(TO);
   clone_object(TZ_MINTHOR + "arm/lm_cloak")->move(TO);
   command("wear all");
    command("wear mail");
   MONEY_MAKE_PC(random(10))->move(this_object(),1);
}


bracelet_return()
{
    bracelet = 1;
}
public void
enter_inv(object ob, object from)
{
        ::enter_inv(ob,from);

        if (!from) return;
     if(TP->query_prop(HAS_ASKED))
    set_alarm(1.0,0.0,"no_ask",ob,from);

    if (ob->query_prop(_QUEST_BRACELET_))
                    set_alarm(1.0, 0.0, "got_bracelet",ob,from);
        else
                set_alarm(1.0, 0.0, "got_else", ob, from);
}

no_ask()
{
    command("say What is this?  It was you?  You killed "
+"my wife!  You murdering scum!");
    command("kill "+ query_the_name(TP)+"\n");
    command("kill "+ query_the_name(TP)+"\n");
    command("shout HELP!! Murderer!!");
}
void
got_bracelet(object ob, object from)
{
        if (!interactive(from))
                return;

        set_this_player(from);
     if (QH_QUERY_QUEST_COMPLETED(from, "minthor_murder"))
        {
                write(query_The_name(from) + " looks puzzled.\n");
                TP->catch_msg("You don't feel more experienced.\n");
                ob->remove_object();
        }
        else
        {
                write("Lord Minthor gasps as he listens to your "
	             +"report.  His shoulders sag and you hear a "
	 	     +"sob escape his mouth.\n");
		write("He then looks you in the eye and says: "
		     +"A father's work is never done.  I don't "
		     +"know what I should do about this situation. "
		     +"I guess I should thank you.\n");
		write("He turns his head away, and you can hear him "
	 	     +"speaking to himself: My own daughter.  My sweet "
		     +"little girl.  Daddy will make everything better.\n");
                TP->catch_msg("You feel more experienced.\n");
                 QH_QUEST_COMPLETED(from,"minthor_murder");
                ob->remove_object();
                set_alarm(2.0,0.0,"remove_the_object",ob);
        }
}

void
remove_the_object(object ob)
{
        command("say Leave me. I must ponder the difficult choices "
		+"before me.");
        command("emote walks hurriedly from the room.");
        if(minthor = present("maximus", environment(TP)))
        {
                minthor -> remove_object();
        }
}

void
got_else(object ob, object from)
{
        command("say What is this?");
        command("drop "+ob->query_name());
}

