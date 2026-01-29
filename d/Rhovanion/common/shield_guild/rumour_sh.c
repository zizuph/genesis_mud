#pragma save_binary

inherit "/std/shadow";

#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <filter_funs.h>

#define   MAX_HEAR        5
#define   LASTING_TIME    5000

static mixed  *heard = ({ });
static string *rumour = ({ });
static string *from = ({ });
static int    *tt = ({ });
static int    alarm;

object
query_rumour_shadow() { return TO; }

void
plant_rumour(string a, string b, int c)
{
  int i;

  if((i = member_array(a, rumour)) != -1)
  {
    if(c>tt[i]) tt[i] = c;
    return;
  } 
  rumour += ({ a });  from += ({ b }); tt += ({ c }); heard += ({ ({ }) });
}

mixed
query_rumour() { return ({ rumour, from, tt }); }
mixed
query_heard() { return heard; }
int
query_no_of_rumours() { return sizeof(rumour); }

void
init_living()
{
  if(!alarm && random(2) && sizeof(rumour))
    alarm = set_alarm(itof(2+random(6)), 0.0, "tell_rumour");

  shadow_who->init_living();
}

string
answer_rumours()
{
  remove_alarm(alarm);
  alarm = 0;
  set_alarm(0.0, 0.0, "tell_all_rumours", 0);
  shadow_who->answer_rumours();
  return "";
}

void
tell_all_rumours(int i)
{
  if(i<sizeof(rumour))
  {
    if(!i)
      shadow_who->command("say I have heard that "+from[i]+" told: "+
				rumour[i]+"...");
    else
      shadow_who->command("say then that "+from[i]+" told: "+
				rumour[i]+"...");
    set_alarm(2.0, 0.0, "tell_all_rumours", i+1);
    return;
  }
  if(!i)
    shadow_who->command("say Sorry, I don't know any rumours.");
  else
    shadow_who->command("say Interesting, isn't it?");
}

void
remove_rumour(int r)
{
  mixed *tmp;
  int i;

  tmp = ({ });
  for(i=0; i<sizeof(heard); i++)
    if(i != r)
      tmp += ({ heard[i] });
  heard = tmp;
  tmp = ({ });
  for(i=0; i<sizeof(rumour); i++)
    if(i != r)
      tmp += ({ rumour[i] });
  rumour = tmp;
  tmp = ({ });
  for(i=0; i<sizeof(from); i++)
    if(i != r)
      tmp += ({ from[i] });
  from = tmp;
  tmp = ({ });
  for(i=0; i<sizeof(tt); i++)
    if(i != r)
      tmp += ({ tt[i] });
  tt = tmp;
}

void
tell_rumour()
{
  int i, j, k;
  object *list, shadow;

  alarm = 0;

  i = random(sizeof(from));

  if((tt[i] + LASTING_TIME) < time())
  {
    remove_rumour(i);
    return;
  }

  list = FILTER_LIVE(all_inventory(ENV(shadow_who))) - (object *)heard[i];
  list -= ({ shadow_who });
  if(sizeof(list))
  {
    if(shadow_who->query_npc() && list[j]->query_prop(DO_I_TELL_RUMOURS))
    {
      shadow_who->command("say Hello! Do you know what I have heard?");
      shadow_who->command("say "+from[i]+" told that: "+rumour[i]+".");
      shadow_who->command("say Do you believe it?");
      heard[i] += list;
    }
    j = random(sizeof(list));
    if(!list[j]->query_wiz_level() && !random(3))
    {
      setuid();
      seteuid(getuid());

      if(list[j]->query_rumour_shadow())
        list[j]->plant_rumour(rumour[i], from[i], tt[i]);
      else
      {
        shadow = clone_object(MASTER);
        if(shadow && shadow->shadow_me(list[j]))
        {
          if((k=list[j]->query_no_of_rumours()) > (2+random(4)))
            list[j]->remove_rumour(random(k));
          if(list[j]->query_npc() && list[j]->query_prop(DO_I_TELL_RUMOURS))
          {
            list[j]->set_dont_answer_unseen(1);
            list[j]->add_ask(({"rumours","about rumours","about the rumours"}), 
    		    	"@@answer_rumours:"+file_name(shadow)+"@@");
          }
          list[j]->plant_rumour(rumour[i], from[i], tt[i]);
        }
      }
    }
    if(sizeof(heard[i]) > MAX_HEAR)
      remove_rumour(i);
  }
}