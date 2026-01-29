inherit "/std/object";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

query_auto_load()
{
  return MASTER;
}

create_object()
{
  set_name("pin");
  set_adj("boring");
  add_name("sulker_pin");
  set_short("boring pin");
  set_long("This is the pin that tells everyone that you are a "+
    "member of the distinguished club 'Society of Injustice', the "+
    "club for people who feel abused and harassed by the powers "+
    "that rule the world. You can use 'pinhelp' to show your "+
    "emotes.\n");

  add_prop(OBJ_I_NO_DROP,"You don't want to loose your badge, do you?\n");
}

void
init()
{
  ::init();

  add_action("pinhelp","pinhelp");
  add_action("iban","iban");
  add_action("iraise","iraise");
  add_action("iresign","iresign");

  TP->set_prop(CIRATHCLUB,1);
  call_out("sulkhail",3);
}

int
pinhelp()
{
  write("The Society of Injustice has the following emotes:\n"+
        "- iban...................ban the rulers for being dictatorial\n"+
        "- iraise....raise your fist towards the sky, showing what you\n"+
        "                                         think of the rulers.\n"+
        "\n");
  return 1;
}

int
iban()
{
  write("You ban every ruler that abuses your right to do what you want.\n");
  say(QCTNAME(TP)+" bans every ruler that abuses "+TP->query_possessive()+
    " right to do what "+TP->query_pronoun()+" wants.\n");
  return 1;
}

int
iraise()
{
  write("You raise your fist in the air, in order to loose your aggressions "+
    "towards the rulers which you think have treated you in a very unfair way.\n");
  say(QCTNAME(TP)+" raises his fist in the air, loosing his aggressions "+
    "towards the rulers which "+TP->query_pronoun()+" thinks have treated "+
    TP->query_objective()+" in an very unfair way.\n");
  return 1;
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="a member of the Society of Injustice.\n";

  return data;
}

enter_env(object dest,object old)
{
  remove_name("sulker_pin");
  if(present("sulker_pin",E(TO)))
    {
      tell_room(E(TO),"The pins melts together in some mysterical way.\n");
      remove_object();
      return;
    }

  if(present("mm_badge",E(TO)))
    {
      tell_room(E(TO),"Aaarrrghhh. You're a MEMBER of the 'Society of Justice' "+
        "\nYou're NOT a worthy member of our club!!!!\n");
      present("mm_badge",TP)->remove_object();
      return;
    }
  else
    {
      add_name("sulker_pin");
      if(living(E(TO)))
      dest->add_subloc("sulker_pin", this_object());
    }
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("sulker_pin");
}

int
sulkhail()
{
  write("Greetings to another lousy day, Society of Injustice member.\n");
  return 1;
}
