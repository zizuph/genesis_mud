inherit "/std/shadow";

#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <filter_funs.h>

#define   MAX_HEAR   6

static mixed  *heard = ({ });
static string *rumour = ({ });
static string *from = ({ });
static string *he = ({ });
static int    alarm;

mixed *heard = ({ });


object
query_rumour_shadow() { return TO; }

void
plant_rumour(string a, string b, string c)
{
  rumour += ({ a });  from += ({ b });  he += ({ CAP(c) });
  heard += ({ ({ shadow_who }) });
}

mixed
query_rumour() { return ({ rumour, from, he }); }
mixed
query_heard() { return heard; }
int
query_no_of_rumours() { return sizeof(rumour); }

void
init_living()
{
  if(!alarm && !random(5))
  {
    alarm = set_alarm(itof(4+random(10)), 0.0, "tell_rumour");
  }
  shadow_who->init_living();
}

string
answer_rumours()
{
  remove_alarm(alarm);
  alarm = 0;
  set_alarm(0.0, 0.0, "tell_all_rumours", 0);
  return "";
}

void
tell_all_rumours(int i)
{
  if(i<sizeof(rumour))
  {
    if(!i)
      shadow_who->command("say "+CAP(from[i])+" told me: "+rumour[i]+"...");
    else
      shadow_who->command("say then "+from[i]+" told me: "+rumour[i]+"...");
    set_alarm(2.0, 0.0, "tell_all_rumours", i+1);
    return;
  }
  if(!i)
    shadow_who->command("say Sorry, I have forgoten all of them.");
  else
    shadow_who->command("say and that is all I remember.");
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
  for(i=0; i<sizeof(he); i++)
    if(i != r)
      tmp += ({ he[i] });
  he = tmp;
}

void
tell_rumour()
{
  int i;
  object *list;

  alarm = 0;

  i = random(sizeof(from));
  list = FILTER_LIVE(all_inventory(ENV(shadow_who))) - (object *)heard[i];
  if(sizeof(list))
  {
    shadow_who->command("say Hello! Do you know what "+from[i]+" told me?");
    shadow_who->command("say "+he[i]+" told me: "+rumour[i]+".");
    shadow_who->command("say Would you believe it?");
    heard[i] += list;

    if(sizeof(heard[i]) > MAX_HEAR)
      remove_rumour(i);
  }
}
