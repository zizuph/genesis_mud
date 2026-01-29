#pragma save_binary

#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "/d/Shire/common/defs.h"

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_power(110);
    set_type(MAIDEN);

    set_name("belladonna");
    set_title("Bath Attendant for the Adventuresome Hobbits");
    set_family_name("Bunce");
    set_living_name("_b_bunce_");
    add_name(({"attendant","bathwoman"}));
    set_race_name("hobbit");
    set_adj(({"old","kindly"}));
    set_gender(1);

    set_long("This old woman reminds you of your grandmother.\n"+
      "And who knows, maybe she is, so be nice to her, she is here "+
      "to help you.  Ask her about bathing if you need instructions.\n");

    disable_all_noise();
    set_chat_time(6);
    add_chat("How warm would you like your bath water?");
    add_chat("Do you need any more soap, dear?");
    add_chat("Bathing cleans the body and frees the mind");
    add_chat("I don't look it now, but when I was young I had adventures too.");
    add_chat("I can never keep enough fresh towels on hand it seems.");
    add_chat("Don't forget your belongings, you put them in the stand.");
    add_chat("Where have you been adventuring lately?");
    add_chat("I never married, I enjoy adventuring too much.");
    add_chat("Have you ever been to Rivendell? I have.");
    add_chat("What's the harm in a little bath water? Don't be afraid.");
    add_chat("The fire needs more wood I think.");

    set_act_time(5);
    add_act("emote stokes the fire up some more.");
    add_act("tap");
    add_act("ponder where the clean towels are");
    add_act("emote starts heating another pot of water.");
    add_act("emote gathers some towels from the hamper and takes them for cleaning.");

    add_ask(({"for bath","help","about bath","bath","about bathing"}),VBFC_ME("ask_bath"));
    add_ask(({"soap","for soap","about soap"}),VBFC_ME("ask_soap"));
    set_default_answer(VBFC_ME("default_answer"));

}

string
default_answer()
{
    command("say I don't know what you are talking about, dear.");
    return "";
}

string
ask_soap()
{

    if(TP->query_prop("got_extra_soap"))
    {
	command("say One extra soap per bather!");
	command("giggle misc");
	return "";
    }


    if(!TP->query_prop("i_am_wet") && !TP->query_prop("i_have_bathed"))
    {
	command("say You should enter the tub first, you wouldn't want to bathe "+
	  "dry would you?");
	return "";
    }

    if(!TP->query_prop("i_am_wet") && TP->query_prop("i_have_bathed"))
    {
	command("say You've already dried off, you've had your bath!");
	return "";
    }


    if(TP->query_prop("i_am_bathing") && !TP->query_prop("got_extra_soap"))
    {
	command("say Have another soap, dear.");
	TP->add_prop("got_extra_soap",1);
	TP->catch_msg("Belladonna hands you another soap.\n");
	say("Belladonna hands "+QCTNAME(TP)+" another soap.\n");
	return "";
    }

}


void
arm_hobbit()
{
    object tunic;

    FIXEUID
    tunic = clone_object(MICH_DIR + "arm/h_cloak");
    tunic->move(TO);
    command("wear all");
}


string ask_bath()
{

    if((TP->query_prop("i_am_wet")) && (TP->query_prop("i_am_bathing")))
    {
	command("say Well, you seem to have the hang of it...");
	command("say When you're done bathing you can stand up, ");
	command("say And I'll bring you a towel, or you can splash "); 
	command("say as long as you like, I'll keep the water hot.");
	command("smile kind");
	return "";
    }

    if((TP->query_prop("i_am_wet")) && (!TP->query_prop("i_am_bathing")))
    {
	command("say You should dry yourself, silly.");
	command("smile merrily");
	return "";
    }

    if(!(TP->query_prop("i_am_wet")) && TP->query_prop("i_have_bathed"))
    {
	command("say You look dry.  Put your towel in the hamper and you can go.");
	return "";
    }

    if(!(TP->query_prop("i_am_wet")) && (!TP->query_prop("i_have_bathed")))
    {
	command("say Well, it goes like this. Enter bathtub and you will take "+
	  "off your clothes and put them on the stand.  Then I'll bring over the "+
	  "hot water and soap and you can get to washing yourself.");
	command("smile");
	return "";
    }


}
