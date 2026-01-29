// file name:        n2
// creator(s):       Cirion, April 1996
// revision history: May 96: Denis: Corrected 3 bugs; Optimized thingy a bit.
// purpose:          Tunnel for the newbie area that has
//                   spiders and other nasty creatures.
// note:             Contains a spider web that players will
//                   need to find a way past.
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"

int      spider_web;
object   spider;

void reset_room()
{
   if(!present(spider))
   {
     spider = clone_object(MON+"spider");
       spider->move(TO);
       spider->set_no_show();
   }

   if(!spider_web)
   {
     spider_web = 1;
     tell_room(TO, "A large spider completes its web "
        +"across the northern tunnel end.\n");
    }
}
  
void create_room()
{
  set_short("gloomy tunnel");
  set_long("This dark and rough-hewn tunnel leads north into "
          +"the dark gloom. All around, shadows play in the "
          +"corners, and you think you can see slight movement "
          +"along the walls. A harsh, cold wind blows from the "
          +"south up along the tunnel@@web@@.\n");

  add_item(({"wall","walls","rock"}),"The rock walls of this "
    +"tunnel are craggy and rough-hewn, their cold surface "
    +"glistening with moisture and lattices with numerous "
    +"shadows.\n");
  add_item(({"floor","ground"}),"The ground is cold and "
    +"rough, making your footing treacherous.\n");
  add_item(({"ceiling","roof"}),"The ceiling of the tunnel "
    +"is hidden in shadows.\n");
  add_item(({"shadow","shadows","darkness"}),"The shadows are "
    +"everywhere.\n");
  add_item(({"mist","south"}),"To the south, the tunnel "
    +"seems to open out into a bright white mist, from "
    +"where the sounds of water can be heard.\n");
  add_item(({"north","tunnel"}),"It leads into darkness and "
    +"gloom.\n");

  add_item(({"web", "spider web", "cobweb"}), "@@exa_web@@");

  IN;
  IN_IN;

  add_exit(OUTPATH+"n1", "south");
  add_exit(OUTPATH+"n3", "north", "@@pass_north@@");

  set_alarm(0.5, 0.0, reset_room);
}

mixed pass_north()
{
  if(!spider_web)
    return 0;

    if(TP->query_stat(SS_STR) < 45 && spider_web)
    {
        write("You would need to cut through the spider web to pass.\n");
	return 1;
    }

  write("You manage to push your way through the thick "
       +"spider's web, breaking it.\n");
  say(QCTNAME(TP)+" pushes "+POSSESS(TP)+" way through "
       +"the spider's web.\n");
  spider_web = 0;
  return 0;
}

string web()
{
  if(spider_web)
    return ", shaking a large spider's web that is extended "
          +"across the north passage";
  else
    return "";
}

string exa_web()
{
  if(!spider_web)
   return "The remaining strands of a spider's web "
         +"flutter in the wind.\n";

  if(present(spider))
  {
    spider->unset_no_show();
    spider->set_no_show_composite(0);
    return "It is a very large and thick web, covering over "
          +"the northern tunnel. In the centre of the web "
          +"sits "+LANG_ASHORT(spider)+".\n";
  }

  return "The web is large and sticky, running across "
    +"the tunnel and blocking the northern passage.\n";
}

void init()
{
  ::init();

  add_action("cut", "cut");
  add_action("cut", "slash");
  add_action("cut", "slice");
  add_action("burn", "burn");
}

int cut(string str)
{
  object    wep;

  if(!spider_web)
    return 0;

  NF(CAP(QVB) + " through what?\n");
  if(!strlen(str) ||
     !parse_command(str, ({}), "'through' [the] [spider] 'web'"))
    return 0;

  NF("You are too busy with other things at the moment.\n");
  if(TP->query_attack())
    return 0;

  NF("You would need to be holding something to "
    +"slash through the web with.\n");
  wep = TP->query_weapon(W_LEFT);
  if(!wep || wep->query_dt() != W_SLASH)
     wep = TP->query_weapon(W_RIGHT);
  if(!wep || wep->query_dt() != W_SLASH)
     wep = TP->query_weapon(W_BOTH);
  if(!wep || wep->query_dt() != W_SLASH)
     return 0;

  if(spider && present(spider))
  {
    spider->unset_no_show();
    spider->set_no_show_composite(0);
    TP->catch_msg("As you try to "+QVB+" through the web, "+QTNAME(spider)
         +" jumps off the web and "
         +"attacks you!\n");
    say(QCTNAME(TP)+" tries to "+QVB+" through the "
         +"web blocking the north passage.\n"+QCTNAME(spider)
         +" attacks "+TP->query_objective()+"!\n");
    if(TP->query_gender() == G_FEMALE)
        TP->command("$scream"); // Is this sexist?
    spider->attack_object(TP);
    return 1;
   }

   write("You "+QVB+" through the spider web with your "
        +wep->short()+", clearing the north passage.\n");
   say(QCTNAME(TP)+" cuts through the spider web with "
        +POSSESS(TP)+" "+wep->short()+", clearing the north "
        +"passage.\n");
   spider_web = 0;
   return 1;
}

int burn(string str)
{
  object    *stuff;

  if(!spider_web)
   return 0;

  NF(CAP(QVB)+" what?\n");
  if(!strlen(str) ||
     !parse_command(str, ({}), "[the] [spider] 'web' %s", str))
    return 0;

  stuff = filter(all_inventory(TP), &->query_prop(OBJ_I_HAS_FIRE));
 
  NF("But you do not have any fire to burn it with!\n");
  if(!sizeof(stuff))
    return 0;

  NF("You are too busy with other things at the moment.\n");
  if(TP->query_attack())
    return 0;

  write("You set your "+stuff[0]->short()+" against the spider web, "
       +"and it is instantly engulfed in flames.\n");
  say(QCTNAME(TP)+" sets "+POSSESS(TP)+" "+stuff[0]->short()
       +" against the spider web, "
       +"and it is instantly engulfed in flames.\n");
  if(present(spider))
  {
    spider->heal_hp(-spider->query_max_hp());
    spider->do_die(TP);
  }

  spider_web = 0;
  return 1;
}
