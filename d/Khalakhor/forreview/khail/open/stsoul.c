#include "/d/Immortal/std/domain.h"

inherit "/cmd/std/tracer_tool_base";

string
get_soul_id()
{
  return "stexxs_soul";
}

int
query_tool_soul()
{
  return 1;
}

mapping
query_cmdlist()
{
  return ([
           "Zap": "Zap",
           "Mob": "Mob",
           "Eob": "Eob",
           "Cob": "Cob",
           "Tob": "Tob",
           "help": "help",
          ]);
}
int
Zap(string str)
{
object target;

  notify_fail("Zap who?\n");
  
  if(!strlen(str))
    return 0;

  if(!(target = present(str, environment(this_player()))))
    {
    notify_fail(capitalize(str) + " is not present.\n");
    return 0;
    }
  else
    {
    if(!living(target))
      {
      notify_fail(capitalize(str)+" is not alive to kill.\n");
      return 0;
      }
    else
      {
      this_player()->catch_msg("You summon a flash from the sky directed "+
        "towards "+target->query_name()+"!\n");
      target->catch_msg(this_player()->query_name()+" summons a flash from "+
        "the sky directed at you!\n");
      tell_room(environment(this_player()), this_player()->query_name() +
        " summons a flash from the sky directed at "+target->query_name()+
        "!\n",({target, this_player()}));
      target->heal_hp(-1000000);
      target->do_die(this_player());
      return 1;
      }
    }
}

int
Mob(string str)
{
object obj;
string str1, str2;

  notify_fail("You find no such object.\n");

  if(!strlen(str))
    return 0;

  if(!(obj = present(str, this_player())) && !(obj=present(str,environment(this_player()))))
    {
    if(str != "here")
      return 0;
    }

  if(str == "here")
    obj = environment(this_player());

  this_player()->catch_msg("Attempting to more "+obj->query_name()+"\n");
  if(str == "here")
    str1 = file_name(obj);
  else
    sscanf(file_name(obj),"%s#%s", str1, str2);
  str1 += ".c";

  this_player()->catch_msg("Trying more on "+str1+"\n");
  this_player()->command("more "+str1);
  return 1;
}

int
Eob(string str)
{
object obj;
string str1, str2;

  notify_fail("You find no such object.\n");

  if(!strlen(str))
    return 0;

  if(!(obj = present(str, TP)) && !(obj = present(str,environment(TP))))
    {
    if(str != "here")
    return 0;
    }

  if(str == "here")
    obj = environment(TP);

  TP->catch_msg("Attempting to edit "+obj->query_name()+".\n");
  if(str == "here")
    str1 = file_name(obj);
  else
    sscanf(file_name(obj), "%s#%s", str1, str2);
  str1 += ".c";

  TP->catch_msg("Trying to edit "+str1+".\n");
  TP->command("ed "+str1);
  return 1;
}

int
Cob(string str)
{
object obj;
string str1, str2;

  NF("You find no such object.\n");

  if(!strlen(str))
    return 0;

  if(!(obj = present(str, TP)) && !(obj = present(str, environment(TP))))
    {
    if(str != "here")
    return 0;
    }

  if(str == "here")
    obj = environment(TP);

  TP->catch_msg("Trying to cat "+obj->query_name()+".\n");

  if(str == "here")
    str1 = file_name(obj);
  else
    sscanf(file_name(obj), "%s#%s", str1, str2);
  str1 += ".c";

  TP->catch_msg("Trying to cat "+str1+".\n");
  TP->command("cat "+str1);
  return 1;
}

int
Tob(string str)
{
object obj;
string str1, str2;

  NF("You find no such object.\n");

  if(!strlen(str))
    return 0;

  if(!(obj = present(str, TP)) && !(obj = present(str, environment(TP))))
    {
    if(str != "here")
      return 0;
    }

  if(str == "here")
    obj = environment(TP);

  TP->catch_msg("Trying to tail "+obj->query_name()+".\n");


  if(str == "here")
    str1 = file_name(obj);
  else
    sscanf(file_name(obj), "%s#%s", str1, str2);
  str1 += ".c";

  TP->catch_msg("Trying to tail "+str1+".\n");
  TP->command("tail "+str1);
  return 1;
}

int
help(string str)
{
  if(str != "stsoul" && str != "stexxs soul")
    return 0;

  TP->catch_msg("The following commands are available:\n");
  TP->catch_msg("Cob <object>: cat <file_name(object)>\n");
  TP->catch_msg("Eob <object>: edit <file_name(object)>\n");
  TP->catch_msg("Mob <object>: more <file_name(object)>\n");
  TP->catch_msg("Tob <object>: tail <file_name(object)>\n");
  TP->catch_msg("Zap <who>: Inflicts 1000000 hp damage to any living and\n"+
                           "results in death. Zap's are logged as any other\n "+
                           "kill, so don't try it on a mortal.\n");
  TP->catch_msg("NOTE: The ?ob commands are really just shortcuts, and are\n"+
                      "'activated' simply by TP->command(whatever).\n"+
                      "Objects are specified just by their usual name, \n"+
                      "i.e. what you'd use to exa them. 'here' can also be\n"+
                      "used as an argument, in which case the environment \n"+
                      "will be the object used.\n");
  return 1;
}
