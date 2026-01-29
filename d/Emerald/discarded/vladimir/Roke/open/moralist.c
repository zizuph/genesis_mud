inherit "/d/Roke/gresolle/follower";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

static string *harrassed;
mapping weapons;

#define OBJ REDLIGHT+"moralist"

qw()
{
  return weapons;
}

create_weapon_log()
{
  string *ss,s;
  int i;

  ss = m_indexes(weapons);

  if(sizeof(ss))
    for(i=0;i<sizeof(ss);i++)
      {
	s = sprintf("%8s %30s hit:%d pen:%d\n",
		weapons[ss[i]][0],
		    ss[i],
		weapons[ss[i]][1],
		weapons[ss[i]][2]);
		
	write_file("/d/Roke/gresolle/open/weapons",s);
	write(s);
      }
}

query_victims()
{
  int i;
  string s;

  s="";

  if(!sizeof(harrassed))
    return "Noone so far.\n";

  for(i=0;i<sizeof(harrassed);i++)
    s+=capitalize(harrassed[i])+"\n";
  return s;
}

create_follower()
{
  weapons=([]);
  seteuid(getuid());

  set_name("joseph");
  add_name("moralist");
  set_adj("fanatic");
  set_living_name("moralist");
/*  set_short("fanatic moralist");*/
  set_race_name("moralist");
  set_title("the fanatic moralist");
  
    default_config_npc(80);
    set_hp(10000);

    set_skill(SS_UNARM_COMBAT,50);
    add_notify_meet_interactive("apa");

    harrassed =({});
    
    set_act_time(1);
    add_act("say You know, you shouldn't be drinking that much!");
    add_act("emote points at you.");
    add_act("scream Fornicator!!!");
    add_act("disagree");

    set_follow_on_ships(1);

    trig_new("%s 'drinks' %s","react_drink");
    trig_new("%s 'a' 'deep' 'and' 'passionate' %s","react_french");
    trig_new("%s 'beer' / 'beer.\n' %s","react_beer");
    trig_new("%s 'sells' %s","react_sell");
    trig_new("%s 'sold' %s","react_sell");
    trig_new("%s 'wields' %s","react_wield");
    trig_new("%s 'stops' 'wielding' %s","react_unwield");
    trig_new("%s 'wears' %s","react_wear");
    trig_new("%s 'died.\n' %s","react_death");
    trig_new("%s 'fuck' %s","react_fuck");
    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
  }

query_knight_prestige()
{
  return -1;
}
react_attacked(s,ss)
{
  call_out("attkd",1,TP);
  return 1;

}
attkd(object tp)
{
  command("shout HELP! I'm being murdered by "+tp->query_real_name()+".\n");
  command("kick "+tp->query_real_name());
  this_object()->hse();
  run_away();
  command("north");
  command("north");
  command("east");
  command("south");
  command("south");
  command("south");
  command("west");
  call_out("command",1,"shout HELP!!!");
  call_out("command",2,"shout MURDER!!!");
  call_out("command",3,"say It's a good thing I escaped that evil "+tp->query_real_name()+"!");
  return 1;
}
react_fuck(s,ss)
{
  command("emote is obviously extremly shocked!");
  return 1;
}
react_death(s,ss)
{
  command("scream");
  command("shout OH MY GOD!!! YOU KILLED HIM!!!");
  command("puke");
  command("panic");
  command("cry");
  command("emote mumbles a prayer.");
  return 1;
}

react_wear(s,ss)
{
  command("say So, we got new clothes, do we?");
  return 1;
}
react_unwield(s,ss)
{
  command("say Good! One shall not kill others! Now give me that weapon!");
  return 1;
}
react_wield(s,ss)
{
  command("say Thou shalt not kill.");
  command("say May God have mercy upon your soul.");
  return 1;
}
react_sell(s,ss)
{
  command("say Donate money to the poor children!");
  return 1;
}

react_french(s,ss)
{
  command("gasp");
  command("say Doing that in public!!! You immoral creature!");
  return 1;
}
react_beer(s,ss)
{
  command("say You know, beer is bad for your health!");
  return 1;
}
react_drink(s,ss)
{
  command("say Drinking is bad for your liver!");
  return 1;
}
apa()
{
  object *ob;
  int i;

  arrive_fun(this_player()->query_real_name());
  
  ob = deep_inventory(this_player());
  
  for(i=0;i<sizeof(ob);i++)
    {
      if(function_exists("create_object",ob[i])=="/std/weapon")
	{
	  if(member_array(MASTER_OB(ob[i]),m_indexes(weapons))<0)
	    {
	      weapons[MASTER_OB(ob[i])]=({ob[i]->query_short(),ob[i]->query_hit(),
					 ob[i]->query_pen()});
	    }
	}
    }
  seteuid(getuid());


}
arrive_fun(string s)
{
  object p;

  if(!stringp(followee) || followee=="")
    {
      if(member_array(capitalize(s),harrassed)<0)
	{
	  follow(s);
      
	  if(p = find_player("gresolle"))
	    p->catch_msg("*** Following "+s+".\n");
	  call_out("hse",600);
	}
    }
}
hse()
{
  harrassed+=({followee});
  followee="";
}

enter_inv(object ob,object from)
{
  ::enter_inv(ob,from);

    if(!from)
      return;

    if(!living(from))
      return;

    if(function_exists("set_pen",ob)=="/std/weapon")
      if(capitalize(from->query_real_name())==followee)
	{
	  call_out("command",1,"say Thank you! Now I can leave you to your own, knowing");
	  call_out("command",2,"say that you won't hurt anyone!");
	  hse();
	}

    if(function_exists("set_alco_amount",ob)=="/std/drink")
      {
	call_out("command",1,"drink all");
	call_out("command",2,"say Hey... Why havn't I tried this before?");
	call_out("command",3,"emote leaves for the closest bar.");
	call_out("remove_object",4);
      }
  }








