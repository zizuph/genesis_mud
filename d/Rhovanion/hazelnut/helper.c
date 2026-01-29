/* Just a test monster */

inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

int log_file;
string get_file;

void create_monster() 
{
  set_name("helper");
  set_short("Vidur's helper");
  set_long(BS("This is Vidur's personal helper, which helps his master with "+
	      "producing bugs and other silly things.\n"));
  set_race_name("human");
  /*          str dex con int wis dis */
  set_stats(({34, 54, 30, 15, 17, 30}));
  set_hp(query_max_hp());
  
  set_aggressive(0);
  set_attack_chance(0);

  add_prop(OBJ_I_WEIGHT, 61000); /* weighs 61 kg */
  add_prop(OBJ_I_VOLUME, 65000);
  trig_new("%w 'introduces' %s","react_introduce");
}

void init_living() 
{
  ::init_living();
  add_action("do_order","order");
}


 
void catch_msg(mixed str, object from) 
{
  mixed *sarray;
  seteuid(getuid());
  ::catch_msg(str,from);
  if(log_file && (from != this_object())) {
    if(stringp(str)) 
      {
      write_file(get_file,check_call(str));
      } 
    else 
      {
      write_file(get_file,check_call(str[0]));
      }
  }
}



int do_order(string args) 
{
  object tp;

  seteuid(getuid());
  
  tp = this_player();
  
  if(!args)
    return 0;
  
  if(args == "helper stop log") 
    {
      log_file = 0;
      set_tell_active(0);
      write_file(get_file,"LOG STOPED: "+ctime(time())+"\n");
    }
  else if (sscanf(args, "helper log to %s",get_file) != 1) 
    {
      write("Usage: order helper log to <file>\n"+
	    "    or order helper stop log\n");
    } 
  else if (!(tp->query_domain() == "Rhovanion")) 
    {
      write("Only members of the Rhovanion domain can use the log feature.\n");
    } 
  else 
    {
      write("Setting log on ("+get_file+")\n");
      log_file = 1;
      set_tell_active(1);
      write_file(get_file,"LOG STARTED: "+ctime(time())+"\n");
    }
  return 1;
}


int react_introduce(string who, string foo) 
{
  if (who) 
    {
      who = lower_case(who);
      if (this_player()->query_met("helper")) 
	{
	  command("tell "+this_player()->query_real_name()+
		  " We have already been introduced to each other!");
	  return 1;
	}
      call_out("return_introduce", 3, who);
      return 1;
    }
}

void return_introduce(string who) 
{
  object ob;

  if (ob = present(who, environment())) 
    {
      command("introduce me");
      command("say Nice to meet you, "+ob->query_name()+".");
      command("bow to "+who);
    }
}
