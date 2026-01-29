/* Copied from /d/Rhovanion/common/objects/bottle.c
 * Originally by Milan of Rhovanion
 */
#pragma save_binary

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#define MINUS ({"bottle","mug","glass","pint","small","the","of","a","an"})

static  int     alco_amount,
                soft_amount,
                max_amount;
static  string  *filled_short;
static  string  *filled_names;
static  string  *filled_adjs;
static  object  *gFail = ({ });

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
string *
query_filled_short()
{
  return filled_short;
}
void
set_alco(int i)
{
  alco_amount = i;
}
void
set_soft(int i)
{
  mark_state();
  soft_amount = i;
  if(!i) filled_short = ({ });
  update_state();
}
void
set_max(int i)
{
  mark_state();
  if(i>0) max_amount = i;
  update_state();
}
void
set_filled_short(mixed arg)
{
  string *adjs, name;
  int i;

  if(stringp(arg) && (arg != ""))
  {
    filled_short = ({ arg });
    adjs = explode(arg, " ");
    name = adjs[sizeof(adjs)-1];
    adjs -= ({ name });
    filled_names = ({ name });
    filled_adjs = adjs;
    return;
  }
  filled_names = ({ });
  filled_adjs = ({ });
  filled_short = ({ });
  if(!pointerp(arg)) return;
  for(i=0; i<sizeof(arg); i++)
  {
    filled_short += ({ arg[i] });
    adjs = explode(arg[i], " ");
    name = adjs[sizeof(adjs)-1];
    adjs -= ({ name });
    filled_names += ({ name });
    filled_adjs += adjs;
  }
}

void
set_name(mixed name)
{
  remove_name(query_names());
  ::set_name(name);
}
void
set_pname(mixed pname)
{
  remove_pname(query_pnames());
  ::set_pname(pname);
}
void 
set_adj(mixed adj)
{
  remove_adj(query_adjs());
  ::set_adj(adj);
}

void 
create_object()
{
  set_name("wineskin");
  set_pname("wineskins");
  set_adj(({"large","leather"}));
  set_short("large leather wineskin");
  set_pshort("large leather wineskins");
  set_long("@@my_long@@");
  max_amount = 1500;

  add_prop(OBJ_I_VOLUME, "@@my_volume@@");
  add_prop(OBJ_I_WEIGHT, "@@my_weight@@");
  add_prop(OBJ_I_VALUE,  "@@my_value@@");
  add_prop(OBJ_M_NO_SELL,"@@my_no_sell@@");
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
int
my_value()
{
  return (max_amount/17);
}
mixed
my_no_sell()
{
  if(soft_amount == 0) return 0;
  return "Better empty the "+short()+" before you try to sell it.\n";
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

  NF("Fill what?\n");
  if(!arg) return 0;

  if(parse_command(arg, TO, " [the] %o 'with' [the] 'water' ") && 
     (ENV(TO) == TP) && 
     ((ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) ||
      (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
      (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
    ))
  {
    set_soft(max_amount);
    if(member_array("water", filled_short) == -1)
      filled_short += ({ "water" });
    if(member_array("water", filled_names) == -1)
      filled_names += ({ "water" });
    write("You fill the "+short()+" with the water.\n");
    say(QCTNAME(TP)+" fills the "+short()+" with the water.\n");
    return 1;
  }

  sscanf(arg, "%s with %s", arg1, arg2);
  if(!arg1) arg1 = arg;

  NF("Fill what?\n");
  if(!parse_command(arg1, TO, " [the] %o ")) return 0;

  NF("Fill "+short()+" with what?\n");
  if(!arg2) return 0;

  a = CMDPARSE_ONE_ITEM(arg2, "fill_one_thing", "drink_access");
  if (sizeof(a) > 0) 
  {
    write("You fill the "+short()+" with "+COMPOSITE_DEAD(a)+".\n");
    say(QCTNAME(TP)+" fills the "+short()+" with "+QCOMPDEAD+".\n");
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

  str = "The "+short()+" is too full for " + COMPOSITE_DEAD(gFail) + ".\n";
  say(QCTNAME(TP)+" tries to fill the "+short()+" with "+QCOMPDEAD+
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
  string short, *names, *adjs;

  am1 = ob->query_soft_amount();
  am2 = ob->query_alco_amount();
  num = ob->num_heap();

  for (i = 1; i <= num; i++)
  {
    if (am1 + soft_amount > max_amount)
    {
      if (i == 1)
      {
        ob->split_heap(1);
        if (sizeof(gFail) <= 0)
          gFail = ({ ob });
        else
        gFail += ({ ob });
        return 0;
      }
      ob->split_heap(i - 1);
      return 1;
    }
    else 
    {
      if(i == 1)
      { 
	short = implode(explode(ob->query_short()," ")-MINUS, " ");
        names = ob->query_names()-(filled_names+MINUS);
        adjs = ob->query_adjs()-(filled_adjs+MINUS);
	if(member_array(short, filled_short) == -1)
          filled_short += ({ ob->query_name() });
        filled_names += names;
        filled_adjs += adjs;
      }
      set_soft(soft_amount + am1);
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
  NF("First you must have the "+short()+"!\n");
  if(ENV(TO) != TP) return 0;
  NF("But the "+short()+" is empty!\n");
  if(!soft_amount) return 0;

  if(sizeof(filled_short) == 1)
    mix = filled_short[0];
  else
    mix = "mixture of "+COMPOSITE_WORDS(filled_short);

  set_soft(0);
  alco_amount = 0;
  filled_short = ({ });
  write("You pour the "+mix+" from the "+short()+" out on the ground.\n");
  say(QCTNAME(TP)+" pours the "+mix+" from the "+short()+" out on the ground.\n");
  return 1;
}

int
drink_from_bottle(string arg)
{
  int d_a, d_s, i, drink;
  string mix, *arr, name, *tmp;

  NF("Drink what?\n");
  if(!arg) return 0;

  NF("Drink from what?\n");
  if(!parse_command(arg, TO, " 'from' [the] %o "))
  {
    arr = explode(arg," ")-({"the","a","an","of","with"});
    if(!sizeof(arr)) return 0;
    name = arr[sizeof(arr)-1];
    arr -= ({ name });
    tmp = arr - filled_adjs;
    if ((sizeof(filled_short) == 1) &&
	(member_array(name,filled_names) != -1) &&
	!sizeof(tmp))
      drink = 1;

    tmp = (filled_adjs+filled_names);
    tmp = arr - tmp;
    if ((sizeof(filled_short) > 1) &&
	(name == "mixture") &&
	!sizeof(tmp))
      drink = 1;
    if(!drink) return 0;
  }

  NF("First you must have the "+short()+"!\n");
  if(ENV(TO) != TP) return 0;
  NF("But the "+short()+" is empty!\n");
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
    if(sizeof(filled_short) == 1)
      mix = filled_short[0];
    else
      mix = "mixture of "+COMPOSITE_WORDS(filled_short);

    d_a = alco_amount * d_s / soft_amount;
    TP->drink_soft(d_s, 0);
    TP->drink_alco(d_a, 0);
    alco_amount -= d_a;
    set_soft(soft_amount - d_s);
    if(soft_amount)
    {
      write("You drink some of the "+mix+" from the "+short()+".\n");
      say(QCTNAME(TP)+" drinks some of the "+mix+" from the "+short()+".\n");
    }
    else
    {
      filled_short = ({ });
      write("You drink the "+mix+" from the "+short()+" until it is empty.\n");
      say(QCTNAME(TP)+" drinks the "+mix+" from the "+short()+" until it is empty.\n");
    }
    return 1;
  }
  if(sizeof(filled_short) == 1)
    mix = filled_short[0];
  else
    mix = "mixture of "+COMPOSITE_WORDS(filled_short);
  write("You can't drink any more of the "+mix+".\n");
  return 1;
}


string
my_long()
{
  string text, mix;

  text = "This is "+short()+". It can be emptied, filled by a drink and "+
         "later when you feel like it, you can drink from it. Right now";

  if(!soft_amount)
    return text+" it is empty.\n";
  
  if(sizeof(filled_short) == 1)
    mix = filled_short[0];
  else
    mix = "mixture of "+COMPOSITE_WORDS(filled_short);

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
  string arg, *arr;
  int i;

  arg = "#m#"+max_amount +"#s#"+soft_amount +"#a#"+alco_amount +"#f#";
  for(i=0; i<sizeof(filled_short); i++)
    arg += filled_short[i]+"&";
  arg += "#n#";
  for(i=0; i<sizeof(arr=query_names()); i++)
    arg += arr[i]+"&";
  arg += "#pn#";
  for(i=0; i<sizeof(arr=query_pnames()); i++)
    arg += arr[i]+"&";
  arg += "#ad#";
  for(i=0; i<sizeof(arr=query_adjs()); i++)
    arg += arr[i]+"&";
  arg += "#sh#"+query_short();
  arg += "#ps#"+obj_pshort;
  arg += "#se#"+query_prop(OBJ_I_VALUE);

  return MASTER+":"+arg + "#";
}

void
init_recover(string arg)
{
  string foo, foobar, *arr;
  int sell;

  sscanf(arg, "%s#m#%d#%s", foobar, max_amount, foobar);
  sscanf(arg, "%s#s#%d#%s", foobar, soft_amount, foobar);
  sscanf(arg, "%s#a#%d#%s", foobar, alco_amount, foobar);
  sscanf(arg, "%s#f#%s#%s", foobar, foo, foobar);
  arr = explode(foo, "&");
  set_filled_short(arr);
  sscanf(arg, "%s#n#%s#%s", foobar, foo, foobar);
  arr = explode(foo, "&");
  set_name(arr);
  sscanf(arg, "%s#pn#%s#%s", foobar, foo, foobar);
  arr = explode(foo, "&");
  set_pname(arr);
  sscanf(arg, "%s#ad#%s#%s", foobar, foo, foobar);
  arr = explode(foo, "&");
  set_adj(arr);
  sscanf(arg, "%s#sh#%s#%s", foobar, foo, foobar);
  set_short(foo);
  sscanf(arg, "%s#ps#%s#%s", foobar, foo, foobar);
  set_pshort(foo);
  sscanf(arg, "%s#se#%d#%s", foobar, sell, foobar);
  if(!sell) remove_prop(OBJ_I_VALUE);
}

string
stat_object()
{
  return ::stat_object()+ "Max Soft: "+max_amount+
                        "\nSoft:     "+soft_amount+
                        "\nAlco:     "+alco_amount+"\n";
}