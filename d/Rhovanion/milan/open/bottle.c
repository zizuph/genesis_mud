inherit "/std/object";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define MAX_AMOUNT 1500

static  int     alco_amount,
		soft_amount,
		max_amount;
static  string  *filled_with;
static  object  *gFail;

int
query_alco()
{
  return alco_amount;
}
int
query_soft()
{
  return soft_amount;
}
int
query_max()
{
  return max_amount;
}
void
set_alco(int i)
{
  alco_amount = i;
}
void
set_soft(int i)
{
  soft_amount = i;
  if(!i) filled_with = ({ });
}
void
set_max(int i)
{
  if(i>0) max_amount = i;
}
void
set_filled_with(string * arg)
{
  filled_with = arg;
}

void 
create_object()
{
  set_name("bottle");
  set_pname("bottles");
  set_adj(({"big","glass"}));
  set_short("big glass bottle");
  set_pshort("big glass bottles");
  set_long("@@my_long@@");
  max_amount = 1500;
  soft_amount = max_amount;
  alco_amount = soft_amount/2;
  filled_with = ({ "gold cognac" });

  add_prop(OBJ_I_VOLUME, "@@my_volume@@");
  add_prop(OBJ_I_WEIGHT, "@@my_weight@@");
}

int
my_volume()
{
  return (11*max_amount/10);
}
int
my_weight()
{
  return (soft_amount+(max_amount/3));
}

void
init()
{
  add_action("drink_from_bottle", "drink");
  add_action("empty_bottle", "empty");
  add_action("fill_bottle", "fill");
}

int
fill_bottle(string arg)
{
  string arg1, arg2;
  object *a;
  int i;

  if(parse_command(arg, TO, " [the] %o 'with' [the] 'water' ") && 
     (ENV(TO) == TP) && 
     ((ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) ||
      (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
      (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
    ))
  {
    soft_amount = max_amount;
    filled_with += ({ "water" });
    write("You fill the bottle with the water.\n");
    say(QCTNAME(TP)+" fills the bottle with the water.\n");
    return 1;
  }

  sscanf(arg, "%s with %s", arg1, arg2);
  if(!arg1) arg1 = arg;

  NF("Fill what?\n");
  if(!parse_command(arg1, TO, " [the] %o ")) return 0;

  NF("Fill bottle with what?\n");
  if(!arg2) return 0;

  a = CMDPARSE_ONE_ITEM(arg2, "fill_one_thing", "drink_access");
  if (sizeof(a) > 0) 
  {
    write("You fill the bottle with "+COMPOSITE_DEAD(a)+".\n");
    say(QCTNAME(TP)+" fills the bottle with "+QCOMPDEAD+".\n");
    for (i = 0; i < sizeof(a); i++)
      a[i]->destruct_object();
    return 1;
  }
  if(sizeof(gFail))
    NF("@@fill_fail:" + file_name(TO));
  return 0;
}

string
fill_fail()
{
  string str;

  str = "The bottle is too full for " + COMPOSITE_DEAD(gFail) + ".\n";
  say(QCTNAME(TP)+" tries to fill the bottle with "+QCOMPDEAD+
      " but it is already too full.\n");
  return str;
}

int
drink_access(object ob)
{ 
    if ((ENV(ob) == TP) &&
        (function_exists("create_heap", ob) == "/std/drink") &&
        (ob->short()))
        return 1;
    else
        return 0;
}

int
fill_one_thing(object ob)
{
  int am1, am2, pstuff, num, i;

  am1 = (int) ob->query_soft_amount();
  am2 = (int) ob->query_alco_amount();
  num = (int) ob->num_heap();

  for (i = 1; i <= num; i++)
  {
    if (am1 + soft_amount > max_amount)
    {
      if (i == 1)
      {
        ob->split_heap(1);
        gFail += ({ ob });
        return 0;
      }
      ob->split_heap(i - 1);
      return 1;
    }
    else 
    {
      if((i == 1) && (member_array(ob->query_short(), filled_with) == -1))
        filled_with += ({ ob->query_short() });
      soft_amount += am1;
      alco_amount += am2;
    }
  }
  return 1;
}

int
empty_bottle(string arg)
{
  string mix;

  NF("Empty what?\n");
  if(!parse_command(arg, TO, " [the] %o ")) return 0;
  NF("First you must have the bottle!\n");
  if(ENV(TO) != TP) return 0;
  NF("But the bottle is empty!\n");
  if(!soft_amount) return 0;

  if(sizeof(filled_with) == 1)
    mix = filled_with[0];
  else
    mix = "mixture of "+COMPOSITE_WORDS(filled_with);

  soft_amount = 0;
  alco_amount = 0;
  filled_with = ({ });
  write("You pour the "+mix+" from the bottle on the floor.\n");
  say(QCTNAME(TP)+" pours the "+mix+" from the bottle on the floor.\n");
  return 1;
}

int
drink_from_bottle(string arg)
{
  int d_a, d_s, i;
  string mix;

  NF("Drink from what?\n");
  if(!parse_command(arg, TO, " 'from' [the] %o ")) return 0;
  NF("First you must have the bottle!\n");
  if(ENV(TO) != TP) return 0;
  NF("But the bottle is empty!\n");
  if(!soft_amount) return 0;

  d_s = 0;
  d_a = 0;
  i = soft_amount;
  while (i > 0)
  {
    d_a = (alco_amount*(d_s+i))/soft_amount;
    if( (d_s+i <= soft_amount) &&
	(TP->drink_soft(d_s+i, 1)) && 
	(!alco_amount || d_a) && 
	(TP->drink_alco(d_a, 1)) )
      d_s += i;
    else
      i /= 2;
  }

  if(d_s)
  {
    if(sizeof(filled_with) == 1)
      mix = filled_with[0];
    else
      mix = "mixture of "+COMPOSITE_WORDS(filled_with);

    d_a = alco_amount * d_s / soft_amount;
    TP->drink_soft(d_s, 0);
    TP->drink_alco(d_a, 0);
    alco_amount -= d_a;
    soft_amount -= d_s;
    if(soft_amount)
    {
      write("You drink some of the "+mix+" from the bottle.\n");
      say(QCTNAME(TP)+" drinks some of the "+mix+" from the bottle.\n");
    }
    else
    {
      filled_with = ({ });
      write("You drink the "+mix+" from the bottle until it is empty.\n");
      say(QCTNAME(TP)+" drinks the "+mix+" from the bottle until it is empty.\n");
    }
    return 1;
  }
  NF("You can't drink any more.\n");
  return 0;
}


string
my_long()
{
  string text, mix;

  text = "This is big glass bottle. It can be emptied, filled by a drink and "+
	 "later when you feel like it, you can drink from it. Right now";

  if(!soft_amount)
    return text+" it is empty.\n";
  
  if(sizeof(filled_with) == 1)
    mix = filled_with[0];
  else
    mix = "mixture of "+COMPOSITE_WORDS(filled_with);

  if(max_amount > 8*soft_amount)
    return text+" it contains little of the "+mix+".\n";
  if(3*max_amount > 8*soft_amount)
    return text+" it contains approx one quarter of the "+mix+".\n";
  if(5*max_amount > 8*soft_amount)
    return text+" it contains approx one half of the "+mix+".\n";
  if(7*max_amount > 8*soft_amount)
    return text+" it contains approx three quarters of the "+mix+".\n";
  if(max_amount > soft_amount)
    return text+" it is nearly full of the "+mix+".\n";
  return text+" it is full of the "+mix+".\n";
} 

string
query_recover()
{
  string arg;
  int i;

  arg = "#m_a#"+max_amount +"#s_a#"+soft_amount +"#a_a#"+alco_amount +"#f_w#";
  for(i=0; i<sizeof(filled_with); i++)
    arg += filled_with[i]+">ff<";
  return MASTER+":"+arg + "#";
}

void
init_recover(string arg)
{
  string foo, foobar;

  sscanf(arg, "%s#m_a#%d#%s", foobar, max_amount, foobar);
  sscanf(arg, "%s#s_a#%d#%s", foobar, soft_amount, foobar);
  sscanf(arg, "%s#a_a#%d#%s", foobar, alco_amount, foobar);
  sscanf(arg, "%s#f_w#%s#%s", foobar, foo, foobar);
  filled_with = explode(foo, ">ff<");
  filled_with -= ({ "" });
}

string
stat_object()
{
  return ::stat_object()+ "Max Soft: "+max_amount+
			"\nSoft:     "+soft_amount+
			"\nAlco:     "+alco_amount+"\n";
}
