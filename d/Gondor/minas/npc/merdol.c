/*
 *  /d/Gondor/minas/npc/merdol.c
 *  The shopkeeper in the armoury in Minas Tirith
 *
 *  Modification log:
 *  - Minor mods, whodunit code. Olorin, 6-jun-1995
 *  - Modified to buy an antique sword found in the Emyn Muil,
 *                               Gorboth, 30-dec-1998
 *  - Changed inheritance from /d/Gondor/emyn-muil/antique_dealer.c
 *  - to /d/Gondor/minas/npc/antique_dealer.c
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/minas/npc/antique_dealer.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

/*
 *  Global variables
 */
static int     report_alarm,
               report_stage;

void
create_dunadan() 
{
    set_living_name("merdol");
    set_name("merdol");
    add_name(({"owner", "shopkeeper", "shopowner"}));
    set_race_name("human");
    set_adj(({"slender","young"}));
    set_dunedain_house("Hador");

    set_long(BSN("This is Merdol the shopkeeper, who runs the Arms "
      + "Shoppe in Minas Tirith. He is probably quite competent with "
      + "numbers - trade is his speciality."));
    default_config_npc(32);
    set_base_stat(SS_CON,75);
    set_skill(SS_WEP_SWORD, random(10)+80);
    set_skill(SS_DEFENCE,   random(10)+60);
    set_skill(SS_PARRY,     random(10)+50);
    set_skill(SS_AWARENESS, random(10)+50);
    set_skill(SS_TRADING,   90);
    set_alignment(50 + random(100));

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"dagger", "ornate dagger", }), VBFC_ME("ask_dagger"));
    add_ask( ({ "sword", "antique sword", "antique", "antiques",
                "old sword", "rusty sword", "rusty old sword",
                "old rusty sword" }),
                antique_ask);

    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Merdol.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy an excellent weapon?");

    set_act_time(20);
    add_act("pace");
    add_act("gleam");

    set_cchat_time(6);
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

    set_equipment( ({ WEP_DIR + "rndsword", ARM_DIR + "rndarmour", }) );
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

varargs void
do_intro(object tp = TP)
{
    ::do_intro(tp);
    command("say I run the best armour shop in Minas Tirith! ");
}

varargs void
do_bow(object tp = TP)
{
    if (objectp(tp))
        command("salute " + TP->query_real_name());
    command("say What can I do for you?");
    command("say Perhaps you want to buy some excellent equipment?");
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!interactive(actor))
	return;

    switch(emote)
    {
    case "bow":
	set_alarm(2.0, 0.0, &do_bow(TP));
	break;
    case "wellmet":
	set_alarm(2.0, 0.0, &command("wellmet"));
	break;
    case "smile":
	set_alarm(2.0, 0.0, &command("smile at " + actor->query_real_name()));
	break;
    case "sigh":
	set_alarm(2.0, 0.0, &command("comfort " + actor->query_real_name()));
	break;
    case "wave":
	if (!strlen(adverb) || (adverb == "happily"))
	    adverb = "goodbye";
	set_alarm(2.0, 0.0, &command("wave "+adverb+" to " + actor->query_real_name()));
	break;
    }
}
	
int     query_knight_prestige() { return -5; }

string
default_answer()
{
    command("peer "+TP->query_real_name());
    command("say I'm sorry, but I don't know what you're talking about.");

    return "";
}

int
end_report()
{
    remove_alarm(report_alarm);
    report_alarm = 0;
    report_stage = 0;

    return 0;
}

int
report_dagger(object tp, object dagger, string buyer)
{
    int     ob_num;
    string *suspects,
            seller;

    if (!objectp(tp) || !present(tp, ENV(TO)))
        return end_report();

    switch(report_stage++)
    {
        case 0:
            command("gasp");
            command("say But how did all that blood come onto it?");
            break;
        case 1:
            command("say Was it used in a crime?");
            command("ponder");
            break;
        case 2:
            MT_PW5_SUSPECT->load_me();
            suspects = MT_PW5_SUSPECT->query_suspect_name(-1);
            suspects -= ({ MT_PW5_MASTER->query_murderer_name() });

            sscanf(OB_NUM(dagger), "%d", ob_num);
            seller = suspects[random(sizeof(suspects), ob_num)];
            command("say "+CAP(seller)+" sold the dagger to me a few weeks ago.");
            break;
        case 3:
            command("say And it didn't take long and I could sell it again.");
            command("say That was no surprise, of course.");
            command("say Weapons forged by Herumegil are in great demand.");
            break;
        case 4:
            command("say But I do remember who bought the dagger from me!");
            break;
        case 5:
            command("say You know, I remember asking myself, "
              + "'What does someone like "+CAP(buyer)+" want to do with a "
              + "nice dagger like this?'");
            tp->add_prop(MT_PW5_I_MERDOL_TESTIMONY, 1);
            break;
        case 6:
            command("say You know, it would be a shame if one used it as eating knife, wouldn't it?");
            break;
        case 7:
            command("say Not that "+CAP(buyer)+" has any use for a good eating knife.");
            command("say He is so broke, he can't afford to buy meat for dinner, so "
              + "what need would he have for a good eating knife?");
            command("snicker");
            break;
        case 8:
            command("say Well, I hope this information was of some use.");
            command("smile "+tp->query_real_name());
            break;
        default:
            return end_report();
            break;
    }

    return 1;
}

string
ask_dagger()
{
    int     ob_num,
            price;
    object  dagger,
            tp = TP,
            shop = ENV(TO);
    string  question = query_question(),
            murderer;

    FIX_EUID

    // is the whodunnit quest active?
    MT_PW5_MASTER->load_me();
    if (!MT_PW5_MASTER->query_pw5_status())
        return default_answer();

    // does the player have the dagger?
    if (!objectp(dagger = present(MT_PW5_MURDER_WEAPON, tp)))
    {
        command("say Which "+question+" are you talking about?");
        command("peer "+tp->query_real_name());
        return "";
    }

    command("say That is an excellent "+dagger->short()+" you have there.");
    command("smile");
    if ((price = shop->query_buy_price(dagger)) > 0)
        command("say I could offer you "+shop->text(shop->split_values(price))
          + " for your "+dagger->short()+".");

    // has the evidence been tampered with?
    if (!dagger->query_bloody())
        return "";

    // abort if the alarm is still active!
    if (report_alarm && sizeof(get_alarm(report_alarm)))
        return "";
    report_stage = 0;

    MT_PW5_MASTER->load_me();
    murderer = MT_PW5_MASTER->query_murderer_name();

    report_alarm = set_alarm(2.0, 2.0, &report_dagger(tp, dagger, murderer));

    return "";
}

void
return_object(object obj, object to)
{
    if (react_to_antique(obj, to))
    {
        return;
    }

    if (obj->id("coin"))
    {
        command("say Why, thank you!");
        command("say I always appreciate a little tip!");
        command("snicker");
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
       command("drop " + OB_NAME(obj));
    }
}

void
return_dagger(object obj, object to)
{
    int     ob_num;
    string  murderer;

    if (!(obj->id(MT_PW5_MURDER_WEAPON)))
    {
        return_object(obj, to);
        return;
    }

    command("emote inspects the "+obj->short()+".");
    command("say That is an excellent "+obj->short()+".");
    command("smile");

    // has the evidence been tampered with?
    if (!obj->query_bloody())
    {
        return_object(obj, to);
        return;
    }

    // is the whodunnit quest active?
    MT_PW5_MASTER->load_me();
    if (!MT_PW5_MASTER->query_pw5_status())
    {
        return_object(obj, to);
        return;
    }

    // abort if the alarm is still active!
    if (report_alarm && sizeof(get_alarm(report_alarm)))
    {
        return_object(obj, to);
        return;
    }

    report_stage = 0;

    murderer = MT_PW5_MASTER->query_murderer_name();
    report_alarm = set_alarm(2.0, 2.0, &report_dagger(to, obj, murderer));

    set_alarm(20.0, 0.0, &return_object(obj, to));
    return;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    // Is this the murder weapon?
    if (ob->id(MT_PW5_MURDER_WEAPON))
        set_alarm(0.5, 0.0, &return_dagger(ob, from));
     else
        set_alarm(0.5, 0.0, &return_object(ob, from));
}


/*
 * function name:        init_living
 * description:          a patch for the automatic attack if this
 *                       mobile can do that. in this case, we use it
 *                       to check whether Merdol notices any antiques
 *                       that the player might be carrying.
 */
public void
init_living()
{
    ::init_living();

    set_alarm(1.0, 0.0, &check_for_antique(TP));
} /* init_living */
