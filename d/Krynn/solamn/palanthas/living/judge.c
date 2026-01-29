/* created by Aridor 06/19/93 */


#include "/ss_types.h"
#include <macros.h>
#include "../local.h"


inherit CITIZEN;


/*prototypes*/
string my_answer();

EMOTE_HOOK

void
create_krynn_monster()
{
    set_name("jodico");
    set_race_name("dwarf");
    set_adj("silent");
    add_adj("calm");
    add_name("judge");

    set_long("This is the judge of Palanthas. You actually "
           + "wonder about this fact since he looks like anything "
           + "but a judge.\n");

    set_stats(({90, 64, 95, 60, 61, 90}));
    set_hp(5000);

    add_ask("form","The silent calm dwarf says: "
       +    "Show me the form and i'll tell you what to do.\n");
    add_ask("sign form",VBFC_ME("sign_form_with_form"));
    add_ask("to sign form",VBFC_ME("sign_form_with_form"));
    set_default_answer(VBFC_ME("my_answer"));
    set_introduce(1);
    add_emote_hook("bow", 1.0, &command("bow"));
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
    object the_form;
    string *slots;
    if (!str)
    {
        NF("Sign what?\n");
        return 0;
    }
    if (str != "form")
    {
        NF("I can't sign that!\n");
        return 0;
    }
    the_form = present("form", TP);
    if (!the_form)
    {
        command("say You don't have a form I could sign!");
        return 1;
    }
    slots = the_form->query_form_slots();
    if (member_array("Jodico (Judge)", slots) >= 0)
    {
        command("say I already signed this form!");
        return 1;
    }
    if (member_array("Chivo (Tax Collector)", slots) >= 0)
      {
	command("emote reads the form.");
	if (the_form->set_form_slot("Jodico (Judge)"))
	  command("emote signs the form.");
	else
	  command("say I'm sorry, but there "
             +  "is no space for me left to sign the form.");
	return 1;
      }
    else
      {
	command("say There must be a signature missing, I cannot sign "
              + "the form like this.");
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
	if (member_array("Jodico (Judge)", slots) >=0)
	  {
	    command("say I already signed this form!");
	    return 1;
	  }
	if (member_array("Chivo (Tax Collector)", slots) >=0)
	  {
	    command("say I can sign this form for you if you ask me to.");
	    return 1;
	  }
	command("say I need a signature from the tax collector, then I "
		+  "hope I can sign your form.");
        return 1;
      }
    NF("Show what?");
    return 0;
}


sentence_prisoner(object chief, object pris)
{
  if (!chief || !pris)
    return;
  if (!random(6))
    {
      command("say I have my specially peaceful day today. You are released!");
      chief->release_prisoner();
    }
  else
    {
      command("say You have commited a crime within the city limits.");
      command("say Not knowing that fighting is prohibited within the city is no reason to be released.");
      command("say I sentence you, " + capitalize(pris->query_real_name()) + ", to an indefinite time in prison.");
      chief->put_prisoner_into_jail();
    }
}
