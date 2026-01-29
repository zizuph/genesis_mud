/*
 *  /d/Gondor/minas/npc/quest/captain.c
 *
 *  A guard for the whodunnit quest
 *  This guard is investigating in the house of Gimilzor
 *
 *  30-may-1995, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

public int      prop_check(object tp);

static  int     Report_Status_Id = 0,
                Report_Count     = 0;
static  string  Report_Question  = 0;

public void
create_monster()
{
    ::create_monster();

    set_name(({"dior", "captain", "soldier"}));
    set_title("Captain of the Guard");
    set_long(BSN("This is a captain in the city guard."));
    remove_adj("lean");
    remove_adj("friendly");
    add_adj("dark-haired");

    default_config_npc(75);

    set_skill(SS_WEP_SWORD,   80);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_2H_COMBAT,   75);
    set_skill(SS_PARRY,       85);
    set_skill(SS_DEFENCE,     85);

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alignment(250 + random(250));

    set_act_time(20);
    add_act("sigh");
    add_act("emote examines the floor closely.");
    add_act("emote searches the walls for hints.");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"help"}), VBFC_ME("ask_help"));
    add_ask(({"gimilzor"}), VBFC_ME("ask_gimilzor"));
    add_ask(({"loan", "loans", "debtor", "money", }), VBFC_ME("ask_loan"));
    add_ask(({"murder", "murderer", "investigation", }), VBFC_ME("ask_murder"));
    add_ask(({"corpse", "body", }), VBFC_ME("ask_corpse"));
    add_ask(({"heir", "heirs", "gimilzor's heirs", "family", "relatives", }), VBFC_ME("ask_family"));
    add_ask(({"garden"}), VBFC_ME("ask_garden"));
    add_ask(({"study"}), VBFC_ME("ask_study"));
    add_ask(({"drain", "drains", "northeast drain", }), VBFC_ME("ask_drain"));
    add_ask(({"sewers", "sewer", }), VBFC_ME("ask_sewer"));
    add_ask(({"key", }), VBFC_ME("ask_key"));
    add_ask(({"safe", "wallsafe", }), VBFC_ME("ask_safe"));
    add_ask(({"safe key", "wallsafe key", "key for safe", "key for wallsafe", }),
        VBFC_ME("ask_safe_key"));
    add_ask(({"dagger", "murder weapon", }), VBFC_ME("ask_dagger"));
    add_ask(({"door", "open door", }), VBFC_ME("ask_door"));
}

public void
do_intro(object tp = TP)
{
    if (!objectp(tp))
        return;
    if (tp->query_npc() || !present(tp, ENV(TO)) || tp->query_met(query_real_name()))
        return;
    command("present me to "+tp->query_real_name());
}

public string
default_answer()
{
    object  tp = TP;

    command("peer " + tp->query_real_name());
    command("say I don't know what you are talking about.");

    if (!(tp->query_prop(MT_PW5_I_HUNTHOR_SENT_ME)))
        return "";

    if (!TP->query_prop(MT_PW5_I_SEEN_BLOOD) && 
        (TP->query_prop(MT_PW5_I_FOUND_MOTIVE) != 3))
    {
        command("say Why don't you look around in the house?");
        command("say Perhaps you can find something we didn't.");
    }
    else if (!TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command("say Did you find something upstairs?");
        command("say We still don't have the slightest hint where to search for the murder weapon!");
    }
    else if (TP->query_prop(MT_PW5_I_FOUND_MOTIVE) != 3)
    {
        command("say Found something in the garden?");
        command("say Perhaps Hunthor can help you now.");
        command("say But we still haven't found the motive for the murder.");
    }
    else if (!(TP->query_prop(MT_PW5_I_FOUND_WEAPON) & 4))
    {
        command("say You seem to have found more than one hint.");
        command("say Well, but we still need to find the murder weapon.");
        command("say Perhaps Hunthor can help you now.");
    }
    else
    {
        command("say If we only knew who was the owner of the dagger.");
        command("say Then we could arrest him!");
        command("say If you have found out who it was, arrest him and bring him to Hunthor.");
    }

    return "";
}

public int
prop_check(object tp)
{
    int solved;

    if (!tp->query_prop(MT_PW5_I_HUNTHOR_SENT_ME) ||
        tp->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT))
    {
        command("say What are you doing here?");
        command("say Leave at once, you are interrupting a criminal "+
	    "investigation!");
        command("unlock door with MT_h1_ncrc4_key");
        command("open door");
        tp->command("$s");
        command("close door");
        command("lock door with MT_h1_ncrc4_key");
        return 0;
    }

    if (Report_Status_Id && sizeof(get_alarm(Report_Status_Id)))
    {
        command("say Slowly, slowly, I'm talking about "+Report_Question+", now.");
        command("say You can ask more questions later.");
        return 0;
    }

    return 1;
}

public void
end_report()
{
    remove_alarm(Report_Status_Id);
    Report_Status_Id = 0;
    Report_Count = 0;
    Report_Question = 0;
}

public string
ask_corpse()
{
    if (!prop_check(TP))
        return "";

    command("say The family is preparing it for burial.");
    command("say It was not a pretty sight.");
    command("say The murderer cut him up with a dagger.");
    command("say He spilled out all his entrails.");
    command("tremble");
    return "";
}

public string
ask_family()
{
    if (!prop_check(TP))
        return "";

    Report_Count = 0;
    Report_Question = "the family of the deceased";
    Report_Status_Id = set_alarm(0.0, 2.0, "report_family", TP);
    return "";
}

public string
ask_murder()
{
    if (!prop_check(TP))
        return "";

    Report_Count = 0;
    Report_Question = "the status of the murder investigation";
    Report_Status_Id = set_alarm(0.0, 2.0, "report_murder", TP);
    return "";
}

public string
ask_gimilzor()
{
    if (!prop_check(TP))
        return "";

    Report_Count = 0;
    Report_Question = "Gimilzor";
    Report_Status_Id = set_alarm(0.0, 2.0, "report_gimilzor", TP);
    return "";
}

public string
ask_loan()
{
    if (!prop_check(TP))
        return "";

    Report_Count = 0;
    Report_Question = "the loans";
    Report_Status_Id = set_alarm(0.0, 2.0, "report_loan", TP);
    return "";
}

public string
ask_drain()
{
    string  question = query_question();

    if (!prop_check(TP))
        return "";

    if (!TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command("say "+question+"? Which "+question+"?");
        command("say I don't know anything about any drain.");
        return "";
    }
    command("say The drains?");
    command("ponder");
    command("say They must lead down into the sewers.");
    command("think the sewers and the whereabouts of the murder weapon.");
    command("say You might be on the right track here.");
    command("say Perhaps someone should go down there and look for the murder weapon.");
    command("ponder");
    return "";
}

public string
ask_sewer()
{
    if (!prop_check(TP))
        return "";

    if (TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command("say The sewers?");
        command("ponder");
        command("say I think Hunthor might be able to help you here.");
    }
    else
    {
        command("shrug");
        command("say They are under the city and full of water and rats.");
        command("say What about them?");
        command("peer "+TP->query_real_name());
    }
    return "";
}

public string
ask_garden()
{
    if (!prop_check(TP))
        return "";

    if (TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command("say Did you find something in the garden?");
        command("say Perhaps the murderer hid there while the patrol was upstairs in the study?");
        command("say He could have hidden the murder weapon there!");
        command("say Good point! I think we should search the garden for the weapon!");
    }
    else
    {
        command("say The garden?");
        command("say It's beyond the hall there.");
        command("point north");
    }
    return "";
}

public string
ask_study()
{
    if (!prop_check(TP))
        return "";

    if (TP->query_prop(MT_PW5_I_FOUND_MOTIVE))
    {
        command("say Did you find anything interesting in the study?");
        command("say Perhaps one of the people whom Gimilzor gave a "
          + "loan killed him.");
        command("shrug");
        command("say But there are so many of them, and even though Gimilzor "
          + "is dead, they will still have to repay the loans.");
    }
    else
    {
        command("say The study?");
        command("say It's upstairs.");
        command("point up");
    }
    return "";
}

public void
report_murder(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        Report_Count = 999;

    switch (Report_Count++)
    {
        case 0:
            command("say Ah, Hunthor sent you to help us?");
            command("say Well, we haven't found out much yet that isn't obvious.");
            break;
        case 1:
            command("say This morning, before sunrise, the guard patrol heard "
              + "someone shout for help from the first floor of this house.");
            break;
        case 2:
            command("say They entered through the door, which was not locked, and "
              + "went into the study upstairs.");
            command("say There they found the dead body of Gimilzor, the owner and "
              + "sole resident of the house.");
            break;
        case 3:
            command("sigh");
            break;
        case 4:
            command("say While they were upstairs, the murderer must have been hiding "
              + "somewhere on the premises.");
            command("say We assume he left while the guards were upstairs.");
            break;
        case 5:
            command("swear");
            break;
        case 6:
            command("say Why didn't they think of guarding the door instead of "
              + "running upstairs all at once?");
            break;
        case 7:
            command("say So now all we have is a corpse. And what we lack are "
              + "witnesses, a motive, the murder weapon, and the murderer himself, "
              + "of course.");
            break;
        case 8:
            command("say If you want to help us, you're welcome to look around in "
              + "the house.");
            command("say The study is upstairs. Some relatives were here just "
              + "some minutes ago and removed the corpse to prepare it for burial.");
            break;
        case 9:
            break;
        case 10:
            command("say We haven't found anything in the rest of the house yet.");
            break;
        default:
            end_report();
            break;
    }
}

public void
report_gimilzor(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        Report_Count = 999;

    switch (Report_Count++)
    {
        case 0:
            command("say You want to know more about the victim?");
            command("peer "+tp->query_real_name());
            break;
        case 1:
            command("say Looking for a motive for the murder, aren't you?");
            break;
        case 2:
            command("think");
            command("say Well, Gimilzor was a quite well to-do.");
            command("say And it was old money, too.");
            command("say He belonged to the most ancient and most respected family in the city.");
            break;
        case 3:
            command("say He seemed to believe that his wealth gave him a duty to help others who have less.");
            command("say So when people asked him for a loan, he rarely rejected them.");
            break;
        case 4:
            command("say This became rather common knowledge, and he ended up giving "
              + "loans to a lot of people.");
            command("shrug");
            break;
        default:
            end_report();
            break;
    }
}

public void
report_loan(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        Report_Count = 999;

    switch (Report_Count++)
    {
        case 0:
            command("say Oh, there were quite a lot of loans.");
            command("say And to a lot of different people.");
            break;
        case 1:
            command("say Though I don't think the debtors will profit from this death.");
            break;
        case 2:
            command("say After all, Gimilzor had IOUs from all of them, and his heirs "
              + "are more likely to insist on repayment than he is said to have been.");
            break;
        case 3:
            command("say He frequently extended a loan if he assumed that the debtor "
              + "was genuinely trying to repay the loan but was unable to do so.");
            break;
        case 4:
            command("say On the other hand, he always insisted on eventual repayment.");
            command("say He never gave away money except as a loan.");
            break;
        case 5:
            command("say It's strange, isn't it?");
            break;
        case 6:
            command("say Some people thought he was very generous because he gave those loans and helped others.");
            break;
        case 7:
            command("say Others seem to have hated him because he had given them money and "
              + "insisted on repayment once the loan had expired.");
            break;
        case 8:
            command("say How do they say?");
            command("say 'To make an enemy, help someone.'");
            command("shiver");
            break;
        default:
            end_report();
            break;
    }
}

void
report_family(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        Report_Count = 999;

    switch (Report_Count++)
    {
        case 0:
            command("say Well, there's an elder brother.");
            break;
        case 1:
            command("say That brother and the brother's family are all the relatives Gimilzor had.");
            break;
        case 2:
            command("say The brother will also inherit everything.");
            break;
        case 3:
            command("ponder");
            break;
        case 4:
            command("say You don't think the brother could have anything to do with the murder, do you?");
            command("eyebrow "+tp->query_real_name());
            break;
        case 5:
            command("say You'd better forget such ideas.");
            command("say The brother is Captain in the Guard of the " +
		    "Tower and a Counsellor of the Steward.");
            break;
        default:
            end_report();
            break;
    }
}

public string
ask_help()
{
    if (!prop_check(TP))
        return "";

    command("peer "+TP->query_real_name());
    command("say Help? You want help? With what?");
    return "";
}

public void
arm_me()
{
    object  key;

    ::arm_me();

    key = clone_object("/std/key");
    key->set_key("MT_h1_ncrc4");
    key->add_name("MT_h1_ncrc4_key");
    key->move(TO, 1);

}

public int
open_door()
{
    command("unlock door with MT_h1_ncrc4_key");
    command("open door");

    set_alarm(20.0, 0.0, &command("close door"));
    set_alarm(21.0, 0.0, &command("lock door with MT_h1_ncrc4_key"));

    return 1;
}

string
ask_door()
{
    if (!prop_check(TP))
        return "";

    if (!TP->query_prop(MT_PW5_I_SEEN_BLOOD) && 
        (TP->query_prop(MT_PW5_I_FOUND_MOTIVE) != 3))
    {
        command("say Leaving already?");
        command("shrug");
        command("say Well, I didn't expect you to find more than we did.");
    }
    else if (!TP->query_prop(MT_PW5_I_SEEN_BLOOD))
    {
        command("say You must have found something upstairs.");
        command("say If we had just some hint where to search for the murder weapon!");
    }
    else if (TP->query_prop(MT_PW5_I_FOUND_MOTIVE) != 3)
    {
        command("say Found something in the garden?");
        command("say Perhaps Hunthor can help you now.");
        command("say But we still haven't found the motive for the murder.");
    }
    else if (!(TP->query_prop(MT_PW5_I_FOUND_WEAPON) & 4))
    {
        command("say You seem to have found more than one hint.");
        command("say Well, but we still need to find the murder weapon.");
        command("say Perhaps Hunthor can help you now.");
    }
    else
    {
        command("say If we only knew who was the owner of the dagger.");
        command("say Then we could arrest him!");
    }

    set_alarm(2.0, 0.0, &command("say I'll unlock the door for you."));
    set_alarm(4.0, 0.0, open_door);

    return "";
}

void
move_back()
{
    if (file_name(ENV(TO)) == (MINAS_DIR + "houses/h1ncrc4"))
        return;

    move_living("down", MINAS_DIR + "houses/h1ncrc4");
}

void
init_living()
{
    if (prop_check(TP))
        set_alarm(2.0, 0.0, "do_intro", TP);

    ::init_living();

    if (file_name(ENV(TO)) != MINAS_DIR + "houses/h1ncrc4")
        set_alarm(5.0 + 15.0 * rnd(), 0.0, move_back);
    set_alarm(5.0, 0.0, "command", "close door");
    set_alarm(6.0, 0.0, "command", "lock door with MT_h1_ncrc4_key");
}

string
ask_key()
{
    if (!prop_check(TP))
        return "";

    command("say Key? What key?");
    command("say If you want to leave, just ask me about the door.");

    return "";
}

string
ask_safe()
{
    object  study,
            safe;
    string  question = query_question();

    if (!prop_check(TP))
        return "";

    (MINAS_DIR + "houses/h4ncrc4")->load_me();
    study = find_object(MINAS_DIR + "houses/h4ncrc4");

    // Someone has found the safe in the study:
    if (objectp(present("safe", study)))
    {
        command("say The wallsafe?");
        command("say Well, I guess Gimilzor kept some documents in there.");
        command("say But we haven't been able to open it yet.");
        return "";
    }

    command("say "+question+"? Which "+question+"?");
    command("peer "+TP->query_real_name());

    return "";
}

string
ask_safe_key()
{
    object  study,
            safe;
    string  question = query_question();

    if (!prop_check(TP))
        return "";

    (MINAS_DIR + "houses/h4ncrc4")->load_me();
    study = find_object(MINAS_DIR + "houses/h4ncrc4");

    // Someone has found the safe in the study:
    if (objectp(present("safe", study)))
    {
        command("say The key for the wallsafe?");
        command("say Yeah, I would like to know where that key is, too!");
        command("say We might find something interesting in the safe "
          + "if we were able open it!");
        return "";
    }

    command("say "+LANG_ADDART(question)+"?");
    command("say I don't know anything about that!");
    return "";
}

void
return_object(object obj, object to)
{
    if (obj->id("coin"))
        return;

    command("say I don't think I need that.");
    to->catch_msg(QCTNAME(TO)+" gives the "+obj->short()+" back to you.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" gives "+LANG_ADDART(obj->short())+
        " to "+QTNAME(to)+".\n", to);
    if (obj->move(to))
       obj->move(to, 1);
}

void
return_dagger(object obj, object to)
{
    if (!(obj->id(MT_PW5_MURDER_WEAPON)))
    {
        return_object(obj, to);
        return;
    }

    command("emote inspects the "+obj->short()+".");

    // has the evidence been tampered with?
    if (!obj->query_bloody())
    {
        return_object(obj, to);
        return;
    }

    command("ponder the blood on the dagger");
    command("say Yes, this could be the murder weapon.");
    command("think");
    command("say Well, we will have to find out who owned this dagger.");

    to->add_prop(MT_PW5_I_FOUND_WEAPON, to->query_prop(MT_PW5_I_FOUND_WEAPON) | 4);

    to->catch_msg(QCTNAME(TO)+" gives the "+obj->short()+" back to you.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" gives "+LANG_ADDART(obj->short())+
        " to "+QTNAME(to)+".\n", to);
    if (obj->move(to))
       obj->move(to, 1);

    command("say Herumegil made the dagger, perhaps he knows something?");
}

void
return_key2(object key, object tp)
{
    command("open safe");
    command("get all from safe");
    command("down");
    if (objectp(tp) &&
	ENV(tp) == ENV(TO))
    {
	if (present("ledger", TO))
	{
            command("say Look what I found in the wallsafe!");
            command("give ledger to "+tp->query_real_name());
	}
	else
	{
            command("sigh");
            command("say I didn't find anything.");
            command("shrug");
	}
	command("say I'm afraid the key broke when I opened the wallsafe.");
    }

    if (present("ledger", TO))
    {
        command("up");
        command("put ledger in safe");
        command("close safe");
        command("lock safe with key");
    }
    key->remove_object();
}

void
return_key(object key, object tp)
{
    object	study;
    string	key_owner,
		name;

    key_owner = key->query_prop(MT_PW5_S_OWNER);
    name = tp->query_real_name();
    add_prop(MT_PW5_S_KEY_SOURCE, name);
    if (tp->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT))
    {
	log_file("murder", ctime(time())+" "+
	    tp->query_real_name()+
	    " gave key to dior, has done quest already.\n");
    	prop_check(tp);	/* for msg */
	key->remove_object();
        return;
    }
    if (key_owner != name)
    {
	log_file("murder", ctime(time())+" "+name+
	    " gave "+
	    (strlen(key_owner) ? key_owner : "nobody" )+
	    "'s key to Dior.\n");
    }

    if (!prop_check(tp))
    {
	key->remove_object();
        return;
    }

    (MINAS_DIR + "houses/h4ncrc4")->load_me();
    study = find_object(MINAS_DIR + "houses/h4ncrc4");

    command("emote inspects the key.");
    command("ponder");
    command("think");
    // Someone has found the safe in the study:
    if (!objectp(present("safe", study)))
    {
        command("say What's this key for?");
        command("peer " + tp->query_real_name());
        set_alarm(0.5, 0.0, &return_object(key, tp));
        return;
    }
    command("say You think this might be the key to Gimilzor's wallsafe?");
    command("up");
    command("unlock safe with key");
    set_alarm(2.0, 0.0, &return_key2(key, tp));
}

void
return_ledger(object ledger, object tp)
{
    command("emote inspects the ledger.");
    command("read ledger");
    command("ponder yet more paperwork");
    command("sigh");
    command("shrug");
    command("say Well, this is nothing new.");
    command("say We already knew that a lot of people owed money to him.");
    command("think");
    command("say Well, I don't think this helps us.");
    command("give ledger to " + tp->query_real_name());
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob))
        return;
    if (!living(from))
        return;

    // Is this the murder weapon?
    if (ob->id(MT_PW5_MURDER_WEAPON))
        set_alarm(0.5, 0.0, &return_dagger(ob, from));
    // Is it the wallsafe key?
    else if (ob->query_key() == "Gimilzors_wallsafe_key")
        set_alarm(0.5, 0.0, &return_key(ob, from));
    else if (ob->id("ledger"))
        set_alarm(0.5, 0.0, &return_ledger(ob, from));
    else
        set_alarm(0.5, 0.0, &return_object(ob, from));
}

string
ask_dagger()
{
    object  tp = TP,
            dagger;
    string  what = query_question();

    if (TP->query_prop(MT_PW5_I_FOUND_WEAPON) & 4)
    {
        command("shrug");
        command("say I don't know anything more than you do.");
        command("say We have to know who is the owner of the dagger.");
        if (TP->query_prop(MT_PW5_I_FOUND_MOTIVE) == 3)
            command("say Then we could arrest him!");
        else
            command("say We also still need to learn what the motive was!");
        return "";
    }
    else
    {
        if (objectp(dagger = present(MT_PW5_MURDER_WEAPON, tp)))
        {
            command("peer " + tp->query_real_name());
            command("say Did you find the murder weapon?");
            command("say May I please have a look at it?");
        }
        else if (what == "dagger")
        {
            command("say "+CAP(what)+"? Which "+what+"?");
        }
        else
        {
            command("say The murder weapon?");
            command("say We're looking for it, but to be honest, "
              + "we don't have a clue where it might be.");
        }
    }
    return "";
}

