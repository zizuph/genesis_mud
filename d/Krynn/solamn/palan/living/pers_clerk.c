/* created by Aridor 06/19/93 */

#include "/ss_types.h"
#include <macros.h>
#include "../local.h"
#include DELIVERY

inherit M_FILE
inherit DELIVERY_OFFICE;

#define CHALK "/d/Krynn/solamn/thief/obj/chalk"

/*prototypes*/
string my_answer();

EMOTE_HOOK

void
reset_monster()
{
    reset_office();
}

void
create_krynn_monster()
{
    set_name("soya");
    set_race_name("human");
    set_adj("brown-haired");
    add_name("clerk");
    add_name("secretary");
    set_gender(1);

    enable_reset();

    set_long("This woman is the secretary here. She is responsible for "
          +  "keeping up with the internal paperwork of the palace.\n");

    set_stats(({30, 34, 25, 40, 31, 20}));
    set_hp(2000);

    set_chat_time(80);
    add_chat("If you have a form you can show me and i'll tell you what "
           + "to do.");
    add_chat("I wonder how I'll ever find anything again in here.");
    add_chat("I heard the inquisitor is in a bad mood today.");
    add_chat("It seems the judge will have to work over-hours soon.");
    add_chat("I wonder what the supervisor does all day except signing "
          +  "a couple of forms.");
    add_chat("I wonder what the clerks does all day.");
    add_chat("You can 'ask for a delivery tour' if you want to earn some " +
	     "money.");
    add_chat("If you have a packet for me, just 'deliver' it.");
    add_chat("You can 'return' a packet which is not destined for me, but " +
	     "which you want to get rid of.");
    
    add_ask("form","The brown-haired human says: "
       +    "Show me the form and i'll tell you what to do.\n");
    add_ask("sign form",VBFC_ME("sign_form_with_form"));
    add_ask("to sign form",VBFC_ME("sign_form_with_form"));
    set_default_answer(VBFC_ME("my_answer"));
    set_introduce(1);
    add_emote_hook("bow",1.0,&command("bow"));
    add_emote_hook("smile",1.0,&command("nod"));

    set_office("the Personnel Office in the palace in Palanthas",5);
    add_content(CHALK);
}


init_living()
{
    add_action("sign_form","sign");
    add_action("examine_form","show");
    init_office();
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
    int value1, value2;
    string *slots;
    string chstr;

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
    if (member_array("Soya (Personnel Department)", slots) >= 0)
    {
        command("say I already signed this form!");
        return 1;
    }
    if (member_array("Erland (Office N-Z)", slots) >= 0)
      {
	value1 = 77;
	value2 = 91;
      }
    if (member_array("Uland (Office A-M)", slots) >= 0)
      {
	value1 = 64;
	value2 = 78;
      }
    if (value1)
      {
	command("emote reads the form.");
	chstr = the_form->query_form_name();
	if (stringp(chstr) && C(chstr)[0] > value1 &&
	    C(chstr)[0] < value2)
	  {
	    if (the_form->set_form_slot("Soya (Personnel Department)"))
	      {
		command("emote signs the form.");
		command("say I must make a copy of the form to keep in "
		      + "the archive.");
		command("emote starts to copy the form.");
		set_alarm(3.0,0.0,"archivize");
	      }
	    else
	      command("say I'm sorry, but there is no "
		    +  "space left for me to sign the form.");
	    return 1;
	  }
	else
	  {
	    command("sigh");
	    command("say Stupid Erland! He never learns checking the "
                +   "name before signing a form! I'm sorry I cannot "
                +   "sign this form for you.");
	    return 1;
	  }
      }
    else
      {
	command("say There must be a signature missing, I cannot sign "
              + "the form like this.");
        return 1;
      }
    NF("Sign what?\n");
    return 0;
}


string
sign_form_with_form()
{
    sign_form("form");
    return "";
}


archivize()
{
  command("emote has finished copying the form and puts the copy into "
    + "a file.");
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
	NF("Show what?\n");
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
	return 0;
      }
    the_form = present("form", TP);
    if (the_form && present(who, environment(TP)))
      {
	command("emote glances briefly at the form.");
	slots = the_form->query_form_slots();
	if (member_array("Soya (Personnel Department)", slots) >=0)
	  {
	    command("say I already signed this form!");
	    return 1;
	  }
	if ((member_array("Uland (Office A-M)", slots) >= 0) ||
	    (member_array("Erland (Office N-Z)", slots) >= 0))
	  {
	    command("say I hope I can sign this form for you "
		    +  "if you ask me to.");
	    return 1;
	  }
	command("say I need a signature from the public office, then I "
		+  "hope I can sign your form.");
        return 1;
      }
    NF("Show what?\n");
    return 0;
}

void
print_message(string str)
{
    command("say " + str);
}
