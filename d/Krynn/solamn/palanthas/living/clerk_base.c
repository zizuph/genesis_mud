/* created by Aridor 10/11/93 */

#include "/ss_types.h"
#include <macros.h>
#include "../local.h"

inherit M_FILE


/*prototypes*/
string my_answer();

string my_signature = "Clerk (A-Z)";
string invalid_signature = "";

set_my_signature(string sign) { my_signature = sign; }
set_invalid_signature(string sign) { invalid_signature = sign; }

EMOTE_HOOK

int
test_valid_purposes(string purpose)
{
    string dummy;
    return (sscanf(purpose,"%ssell%salcohol%sdrink%s",dummy,dummy,dummy,dummy) == 4);
}

int
test_valid_ftype(object the_form)
{
    return ((the_form->query_form_type() == 0)               ||
      (the_form->query_form_type() == "official authorization") ||
      (the_form->query_form_type() == "authorization"));
}

int
test_valid_form(object the_form)
{
    string dummy;
    string purpose = the_form->query_form_purpose();
    if (!purpose)
	purpose = "";
    return (the_form->query_form_seal()                    &&
      (sscanf(purpose,"%ssell%salcohol%sdrink%s",dummy,dummy,dummy,dummy) == 4));
}


void
create_clerk()
{

}

void
create_krynn_monster()
{
    add_name("clerk");

    set_long("This clerk is busy writing and sorting through his files.\n");

    set_stats(({10, 10, 10, 10, 10, 10}));
    set_hp(4000);

    set_chat_time(50);
    add_chat("If you have a form you can show me and i'll tell you what "
      + "to do.\n");
    add_chat("I hope I have off soon, these files are making me sad.");
    add_chat("I heard the supervisor is in a bad mood today.");
    add_chat("It seems the judge will have to work over-hours soon.");
    add_chat("I wonder what the supervisor does all day except signing "
      +  "a couple of forms.");
    add_chat("If you have a form you can show me and I'll tell you what "
      + "to do.\n");
    add_chat("I heard the judge is in a bad mood today.");
    add_chat("It seems the inquisitor will have to work over-hours soon.");
    add_chat("I wonder what the supervisor does all day except signing "
      +  "a couple of forms.");


    add_ask("form",VBFC_ME("show_and_tell"));
    add_ask("sign form",VBFC_ME("sign_form_with_form"));
    add_ask("to sign form",VBFC_ME("sign_form_with_form"));
    set_default_answer(VBFC_ME("my_answer"));
    set_introduce(1);
    add_emote_hook("bow",1.0,&command("bow"));

    create_clerk();
}

string
show_and_tell()
{
    command("say Show me the form and i'll tell you what to do.");
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

    if (!test_valid_ftype(the_form))
    {
	command("say It seems like the type of the form is invalid.");
	return 1;
    }
    if (!test_valid_form(the_form))
    {
	command("say I'm sorry, but I need the "
	  +  "purpose of the form and a seal on the form to be able "
	  +  "to sign the paper.");
	return 1;
    }
    slots = the_form->query_form_slots();
    if (member_array(my_signature, slots) >= 0)
    {
	command("say I already signed this form!");
	return 1;
    }
    if (member_array(invalid_signature, slots) >= 0)
    {
	command("hmm");
	command("ponder");
	command("say Strange, I wonder why you need the signature of " + invalid_signature
	  +  " AND me.");
	/*command("point north");*/
	return 1;
    }
    else
    {
	command("emote reads the form.");
	the_form->set_form_type("authorization");
	command("emote writes something on the form.");
	if (the_form->set_form_slot(my_signature))
	    command("emote signs the form.");
	else
	    command("say I'm sorry, but there is no space left for me to "
	      +   "sign the form.");
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
    string what, who, purpose;
    string *slots;

    seteuid(getuid(TO));
    if (!str)
    {
	NF("Show what to who?\n");
	return 0;
    }
    correct = sscanf(str, "%s to %s", what, who);
    if (correct == 0)
    {
	NF("Show what to who?\n");
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
    if (present(who, environment(TP)))
    {
	command("emote glances briefly at the form.");
	slots = the_form->query_form_slots();
	if (member_array(my_signature, slots) >=0)
	{
	    command("say I already signed this form!");
	    return 1;
	}
	purpose = the_form->query_form_purpose();
	if (!purpose)
	    purpose = "";
	if (test_valid_purposes(purpose))
	{
	    command("say I hope I can sign this form for you "
	      +  "if you ask me to.");
	    return 1;
	}
	command("say The purpose of the form is not legitimate to be signed.");
	return 1;
    }
    NF("Show what to who?\n");
    return 0;
}


