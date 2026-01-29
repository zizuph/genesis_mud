
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <money.h>

inherit AM_FILE

#define GIVEN_QUEST "_given_ansalon_merchant_quest"
#define RESCUED_MERCHANT "_i_rescued_the_sanction_merchant"
#define PLAINS "/d/Ansalon/estwilde/plains/"
#define KOBJ "/d/Ansalon/kalaman/obj/"

#define WEP KOBJ + "weapon/rapier"
#define ARM1 KOBJ + "armour/m_armour"
#define ARM2 KOBJ + "armour/robe"

string *random_loc = ({PLAINS + "4a",PLAINS + "5g", PLAINS + "6d",
  PLAINS + "7a",PLAINS + "8c",PLAINS + "8i"});

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{

    set_name("t'nahcrem");
    add_name("merchant");
    set_race_name("human");
    set_adj("rich");
    add_adj("agitated");
    set_short("agitated rich merchant");
    set_long("This merchant standing before you is dressed in the finest clothing " +
      "money can buy, and you have no doubt that he is very wealthy. "+
      "Still, he looks rather agitated by something.\n");
    set_stats(({120,80,130,70,80,92}));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENSE,65);
    set_skill(SS_AWARENESS,75);
    set_skill(SS_PARRY,45);
    set_introduce(1);
    set_alignment(1000);
    set_knight_prestige(-20);
    set_title("the Wealthy Merchant of Ergoth");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());

    set_default_answer("The agitated rich merchant says: Please! There "+
      "is no time for questions! Find my medallion!\n");
}

void
arm_me()
{
    clone_object(WEP)->move(TO);
    clone_object(ARM1)->move(TO);
    clone_object(ARM2)->move(TO);
    command("wear all");
    command("wield all");
}

void
return_response(object who)
{
    set_alarm(1.0,0.0, &command("say Have you returned with my "+
	"medallion?"));
    set_alarm(1.5,0.0, &command("smile eager"));
}

void
quest_spool(object who)
{
    clone_object(KOBJ + "min_remains")->move(ONE_OF(random_loc), 1);
    who->remove_prop(RESCUED_MERCHANT);
    who->add_prop(GIVEN_QUEST, 1);
    set_alarm(1.0,0.0, &command("say Ah! My saviour has arrived!"));
    set_alarm(1.5, 0.0, &command("shake " +who->query_real_name()));
    set_alarm(2.0, 0.0, &command("say I suppose you have come for that "+
	"reward I promised you... which you shall get of course, all in "+
	"good time..."));
    set_alarm(2.5,0.0, &command("say The thing is, I have a slight "+
	"problem..."));
    set_alarm(3.0,0.0, &command("say And being the resourceful "+
	"person you seem to be, I think you would be perfect in "+
	"helping me solve this problem."));
    set_alarm(3.5,0.0, &command("say As you could probably guess, " +
	"I am a very rich merchant, making the majority of my "+
	"money through selling rare and precious items..."));
    set_alarm(4.0,0.0, &command("say In particular, the " +
	"blue-tinted scry crystals."));
    set_alarm(4.5,0.0, &command("emote smiles secretly."));
    set_alarm(5.0,0.0, &command("say Now, these crystals could "+
	"only be found in the Doom Mountain range between " +
	"Sanction and Neraka in a secret location that only I "+
	"and a few dwarves know of."));
    set_alarm(5.5,0.0, &command("say On my last trip to gather these " +
	"crystals, I ran into a patrol of the Dragonarmies, who thought " +
	"me a spy."));
    set_alarm(6.0,0.0, &command("smile grimly"));
    set_alarm(6.5,0.0, &command("say Myself and my minotaur guards " +
	"fled, but in my haste, I tripped and sprained my ankle..."));
    set_alarm(7.0,0.0, &command("say So I gave my guards orders to "+
	"return to Kalaman with the crystals as well as my prized " +
	"possession, the Medallion of the Istarian Merchant."));
    set_alarm(8.5,0.0, &command("say I was captured, and locked in that "+
	"god awful cage that you found me in..."));
    set_alarm(9.0,0.0, &command("say After you freed me, I returned to "+
	"Kalaman, only to find that my guards never made it back."));
    set_alarm(9.5,0.0, &command("sigh"));
    set_alarm(10.0, 0.0, &command("say I have a suspicion that they " +
	"ran into dwarves of the Neidar clan, who have no love for minotaurs "+
	"or their ilk, and were slain."));
    set_alarm(10.5,0.0, &command("say If so, then I hold the slim hope "+
	"that my precious items still lie on one of their corpses somewhere "+
	"on the Estwilde plains."));
    set_alarm(11.0,0.0, &command("say Now, I care little for the "+
	"return of those scry crystals... but I MUST have my medallion "+
	"returned to me... Return it to me, and I will be eternally " +
	"grateful."));
    set_alarm(11.5,0.0, &command("say I will await your return with "+
	"great anticipation."));
}

void
calculate_experience(object who)
{
    int xp_base = 2000;

    if(who->test_bit("ansalon",0,15))
    {
	who->catch_msg("Nice job, but no experience second time.\n");
	return;
    }
    who->catch_msg("You feel more experienced!\n");
    if(who->query_wiz_level())
	who->catch_msg("xp: "+ xp_base + "\n");

    who->add_exp(xp_base, 0);
    who->set_bit(0,15);

    A_QUEST_LOG("quest","Kalaman Merchant Quest", who, xp_base);
    return;
}

void
given_medallion(object from)
{
    object money;
    string who = from->query_real_name();

    command("gasp");
    command("say You found my medallion!");
    command("wear all");

    calculate_experience(from);

    command("say And now, my gift to you! Spend it well!");
    money = MONEY_MAKE_GC(200);
    money->move(TO);
    if(!CAN_SEE(TO, from))
    {
	command("say Seeing you insist on hiding in the "+
	  "shadows, I'll leave my gift here.");
	command("drop coins");
    }
    else
	command("give coins to "+who);

    command("say Well, I am off to increase my fortunes!");
    command("wave");
    command("emote leaves down.");
    TO->remove_object();
}

void
give_it_back(object ob, object from)
{
    command("hmm");
    command("say Thank you.. I am sure I could get a good price for this, "+
      "but it is not what I am desperately looking for.");
    command("say Please, find my medallion!");
}

void
broken_crystal_reply()
{
    command("say Dammit! Its broken!");
    command("say And they are worth a fortune to!");
}

void
scry_crystal_reply()
{
    command("say Ah! You found a scry crystal!");
    command("say They are worth quite a bit... thankyou for that!");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_dont_react_to"))
	return;
    if(ob->id("_scry_crystal"))
    {
	set_alarm(1.0,0.0, &scry_crystal_reply());
	return;
    }
    if(ob->id("_broken_crystal"))
    {
	set_alarm(1.0,0.0, &broken_crystal_reply());
	return;
    }
    if(ob->id("_kalaman_merc_medallion"))
    {
	set_alarm(1.0,0.0, &given_medallion(from));
	return;
    }
    if(ob->query_no_show())
	return;

    set_alarm(1.0,0.0, &give_it_back(ob, from));
    return;
}
