/* created by Aridor 06/19/93 */


#include "/ss_types.h"
#include <macros.h>
#include "../local.h"
#include <money.h>

inherit "/lib/trade.c";
inherit M_FILE


/*prototypes*/
string my_answer();

EMOTE_HOOK

void
create_krynn_monster()
{
    default_config_trade();
    set_name("chivo");
    set_race_name("dwarf");
    set_adj("greedy");
    add_adj("fat");
    add_name("collector");
    add_name("taxcollector");
    add_name("tax collector");
    add_name("tax-collector");

    set_long(BS("This is the tax collector of Palanthas. You are not "
           + "very surprised about this fact, since he looks just as "
           + "greedy as he is.", SL));

    set_stats(({90, 64, 155, 60, 61, 90}));
    set_hp(7000);

    add_ask("form","The greedy fat dwarf says: "
       +    "Show me the form and i'll tell you what to do.\n");
    add_ask("sign form",VBFC_ME("sign_form_with_form"));
    add_ask("to sign form",VBFC_ME("sign_form_with_form"));
    add_ask(({"ransom fee","fee","ransom money","money","ransom"}),
	    VBFC_ME("reply_to_fee"));
    add_cmd_item(({"ransom fee","fee","money","ransom","ransom_money"}),
		 "pay",VBFC_ME("pay_the_fee"));
    set_default_answer(VBFC_ME("my_answer"));
    set_introduce(1);
    add_emote_hook("bow",1.0,&command("bow"));

}


reply_to_fee()
{
  command("say Do you know someone who has been jailed in Palanthas?? If you don't it is probably useless to pay the fee.");
  command("say But in order to get your friend released, you need to pay the ransom fee of 1 platinum coin.");
  command("say Then I can sign the form you need for the chief.");
  return "";
}

pay_the_fee()
{
    int *money;
    seteuid(getuid(TO));
    if (sizeof(money = pay(1728,TP,"platinum gold silver copper",0,0)) == 1)
        return 0;
    write("You pay the ransom fee of 1 platinum coin.\n");
    TP->add_prop("_has_payed_ransom",1);
    return "";

}

init_living()
{
    add_action("sign_form","sign");
    add_action("examine_form","show");
}


string
my_answer()
{
    set_alarm(1.0,0.0,"command","shrug");
    set_alarm(3.0,0.0,"command","say I cannot help you with that.");
    return "";
}

int
sign_form(string str)
{
    int ok;
    object the_form;
    string *slots, dummy;
    if (!str)
    {
        NF("Sign what?\n");
        return 0;
    }
    if (str != "form")
    {
        command("say I can't sign that!\n");
        return 1;
    }
    the_form = present("form", TP);
    if (!the_form)
    {
        command("say You don't have a form I could sign!");
        return 1;
    }
    slots = the_form->query_form_slots();
    if (member_array("Chivo (Tax Collector)", slots) >= 0)
    {
        command("say I already signed this form!");
        return 1;
    }
    dummy = the_form->query_form_purpose();
    if (dummy)
      ok = (sscanf(dummy, "%srelease%s",dummy, dummy) == 2);
    if (TP->query_prop("_has_payed_ransom") && ok)
      {
	command("emote reads the form.");
	the_form->set_form_slot("Ransom fee paid.");
	if (the_form->set_form_slot("Chivo (Tax Collector)"))
	  command("emote signs the form.");
	else
	  command("say I'm sorry, but there "
	       +  "is no space for me left to sign the form.");
	return 1;
      }
    else
      {
	if (!TP->query_prop("_has_payed_ransom"))
	  {
	    command("say You have to pay the ransom money first, I cannot " +
		    "sign the form unless you do.");
	    command("say Do you really know someone who has been jailed in " +
		    "Palanthas? If you don't I believe it's useless to pay " +
		    "the fee.");
	  }
	if (!ok)
	  command("say Oh, the purpose of the form has to be filled in " +
		  "mentioning the release of a prisoner.");
	return 1;
      }
    NF("Sign what?");
    return 0;
}


string
sign_form_with_form()
{
    sign_form("form");
    return "";
}


int
examine_form(string str)
{
    object the_form;
    int correct;
    string what, who;
    string *slots;

    seteuid(getuid(TO));
    if (!str)
    {
        NF("Show what?\n");
        return 0;
    }
    correct = sscanf(str, "%s to %s", what, who);
    if (correct == 0)
      {
	NF("Show what?");
	return 0;
      }
    if (correct == 1)
      {
	if (present(what, TP))
	{
	  NF("Show " + what + " to who?\n");
	  return 0;
	}
	if (present(who, environment(TP)))
	  {
	    NF("Show what to " + who + "?\n");
	    return 0;
	  }
	NF("Show what to who?\n");
      }
    the_form = present("form", TP);
    if (the_form && present(who, environment(TP)))
      {
	command("emote glances briefly at the form.");
	slots = the_form->query_form_slots();
	if (member_array("Chivo (Tax Collector)", slots) >=0)
	  {
	    command("say I already signed this form!");
	    return 1;
	  }
	if (TP->query_prop("_has_payed_ransom"))
	  {
	    command("say I can sign this form for you if you ask me to.");
	    return 1;
	  }
	command("say Do you know someone who has been jailed in Palanthas? If you don't it is probably useless to pay the ransom fee.");
	command("say You have to pay the ransom money first in order to free your friend, I cannot sign "
              + "the form unless you have paid.");
        return 1;
      }
    NF("Show what?");
    return 0;
}

