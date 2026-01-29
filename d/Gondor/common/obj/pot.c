/*
 * A pot that can contain water (or anything else)
 *
 * modified from bucket.c by Dust
 *
 * Olorin, Apr 1993
 */
#pragma strict_types

inherit "/std/container";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int	filled = 0;	/* true if filled with water */
int     dirty  = 0;	/* true if pot is dirty */
object	water;		/* The actual water in the pot */
object  meal = 0;	/* eg some dead rabbit that's been cooked in the pot */

void test_spill();

#define MEAL_NO_REM \
    "You cannot take anything out of a pot that's cooking over a fire!\n" + \
    "You would burn yourself terribly!\n"

void
create_container() 
{
    set_name("pot");
    add_name("_stewed_rabbit_quest_pot");
    set_long(VBFC_ME("long"));
    set_adj(({"battered","old"}));
    add_prop(CONT_I_WEIGHT,      1000);
    add_prop(CONT_I_MAX_WEIGHT, 12000);
    add_prop(CONT_I_VOLUME,       400);
    add_prop(CONT_I_MAX_VOLUME,  6400);
    add_prop(CONT_I_TRANSP,         1);
    add_prop(CONT_I_RIGID,          1);
    add_prop(OBJ_I_VALUE,         144);
    add_prop(CONT_M_NO_REM,         0);
    set_alarm(60.0, 0.0, test_spill);

    setuid();
    seteuid(getuid());
}

public int
query_dirty()
{
    return dirty;
}

void
test_spill()
{
    object player;

    player = ENV(TO);
    if (living(player) && filled)
    {
	if (random(player->query_stat(SS_DEX)) < 1)
	{
	    tell_object(player,
		"Oops, clumsy as you are, you spill the water...\n" +
		"It vanishes in the ground immediately.\n");
	    tell_room(ENV(player),
		QCTNAME(player) + " spills water on the floor.\n" +
		"It vanishes in the ground immediately.\n",player);
	    water->remove_object();
       TO->remove_prop(OBJ_I_CONTAIN_WATER);
       if(!meal && !present("_rabbit_stew",TO))
         remove_prop(CONT_M_NO_REM);
	    filled = 0;
	}
    }
    set_alarm(60.0, 0.0, test_spill);
}

public void
enter_inv(object ob, object from)
{
  string *names;

  ::enter_inv(ob, from);
  if(!from) return;
  if(!meal && !present("_rabbit_stew",TO))
    remove_prop(CONT_M_NO_REM);
  if(!meal) return;
  if(ob->query_name() == "salt")
    meal->add_prop("_salt_added_to_stew",1);
  names = ob->query_names();
  if(member_array("spice",names) == -1) return;
  if(member_array("_rabbit_spice",names) > -1)
  {
    meal->add_prop("_rabbit_herb_added_to_stew",ob->query_herb_name());
    meal->add_prop("_herb_added_to_stew",1);
  }
  else if(member_array("_stew_spice",names) > -1)
  {
    meal->add_prop("_stew_herb_added_to_stew",ob->query_herb_name());
    meal->add_prop("_herb_added_to_stew",1);
  }
  else if(member_array("_spice",names) > -1)
  {
    meal->add_prop("_extra_herb_added_to_stew",ob->query_herb_name());
    meal->add_prop("_herb_added_to_stew",1);
  }
  return;
}

int
do_fill(string str)
{
  seteuid(getuid());
  if (!str)
  {
    notify_fail("Fill what?\n");
    return 0;
  }
  if (parse_command(str,ENV(TP), "'pot' [with] 'water'") ||
      parse_command(str,ENV(TP), "'water' [in] 'pot'"))
  {
    if (volume_left() < 2000 || weight() > 1000) 
    {
      notify_fail("But the pot isn't empty...\n");
      return 0;
    }
    if (ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER) ||
        ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
    {
      filled = 1;
      water = clone_object(OBJ_DIR + "water");
      if(!water->move(TO))
        TO->add_prop(OBJ_I_CONTAIN_WATER,1);
      if(ENV(TP)->query_prop("_water_is_poisoned"))
      {
        write("You fill the pot with the dirty water.\n");
        say(QCTNAME(TP) + " fills a pot with dirty water.\n");
        TO->set_dirty(1);
      } 
      else
      {
        write("You fill the pot with water.\n");
        say(QCTNAME(TP) + " fills a pot with water.\n");
      }
      if(TO->query_dirty())
      {
        water->set_long("This is some dirty water, about a pint of it.\n");
        water->change_prop("_heap_s_unique_id","This is some dirty water, about a pint of it.\n");
      }
      return 1;
    }
    notify_fail("But there is no water available in this room.\n");
    return 0;
  }
  NF("What do you want to fill with what?\n");
  return 0;
}

int
do_pour(string str)
{
  object fire;

  seteuid(getuid());
  if (str == 0)
  {
    notify_fail("Pour what?\n");
    return 0;
  }
  if (!filled) {
    notify_fail("But the pot doesn't contain any water.\n");
    return 0;
  }
  if(str == "water" || str == "pot")
  {
    write("You pour the water from the pot on the ground.\n");
    filled = 0;
    water->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    write("The water vanishes in the ground immediately.\n");
    return 1;
  }
  if (parse_command(str,ENV(TP), "'water' [on] 'fire'") ||
      parse_command(str,ENV(TP), "'water' [at] 'fire'") ||
      parse_command(str,ENV(TP), "'fire' [with] 'water'"))
  {
    if (!(fire = present("fire", ENV(TP))))
    {
      notify_fail("But there is no fire in this room.\n");
      return 0;
    }
    filled = 0;
    write("You pour water on the fire.\n");
    water->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    fire->extinguish("fire");
    return 1;
  }
  notify_fail("What do you want to pour on what?\n");
  return 0;
}

public int
remove_water()
{
    if (!filled)
	return 0;
    water->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    filled = 0;
    return 1;
}

public string
query_recover()
{
    string rec;

    rec = MASTER +  ":";
    rec += filled;
    rec += "#";
    rec += dirty;
    return rec;
}

public void
init_recover(string arg)
{
    int i1, i2;

    if (sscanf(arg, "%d#%d", i1, i2) != 2)
	write("Something went wrong with recovering the pot.\n");
    else
    {
	filled = i1;
	if(i1) 
	{    
	    TO->add_prop(OBJ_I_CONTAIN_WATER,1);
	    water = clone_object(OBJ_DIR + "water");
	    water->move(TO);
	}
	dirty = i2;
	if(dirty)
	{
	    TO->set_adj("dirty");
	}
    }
}

public int
set_dirty(int value)
{
    dirty = value;
    if (dirty) 
	set_adj("dirty");
    if (!dirty) 
	remove_adj("dirty");
    return dirty;
}

public string
short()
{
    if (dirty) 
	return "dirty old pot";
    return "battered old pot";
}

public string
long()
{
    if (dirty) 
	return BS("This is an old stinking battered pot. Water filled into it " + 
		  "would probably be poisonous to drink.\n");
    return "This battered old pot might hold some stuff.\n";
}

public void
poisoned(object player)
{
    object poison;

    seteuid(getuid(TO));
    
    poison = clone_object(OBJ_DIR + "poison_water_effect");
    poison->move(player);
    write_file("/d/Gondor/log/curses", TP->query_name() +
	  " was poisoned by dirty water from dirty pot on " + ctime(time())+".\n");
    poison->start_poison();
}

public int
do_drink(string str)
{
    NF("Drink what?\n");
    if (!str) 
	return 0;
    
    NF("Drink water from where?\n");
    if (str == "water") 
	return 0;

    NF("Drink what from where?\n");
    if (str != "water from pot") 
	return 0;

    NF("But there is no water in the pot.\n");
    if (!filled) 
	return 0;

    NF("You will need that water for cooking!\nYou cannot drink it!\n");
    if (meal) 
	return 0;

    NF(CAP(water->short()) + " is too much for you.\n");
    if (!TP->drink_soft(water->query_soft_amount())) 
	return 0;

    if (dirty) 
	set_alarm(4.0, 0.0, &poisoned(TP));

    write("You drink the water from the pot.\n");
    say(QCTNAME(TP) + " drinks water from a pot.\n");

    filled = 0;
    water->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    write("You feel refreshed.\n");
    return 1;
}

public int
do_clean(string str)
{
  object room;
  string vb, dstr;

  vb = query_verb();
  NF(CAP(vb) + " what?\n");
  if(!str) return 0;

  NF("You cannot " + vb + " that.\n");
  if(str != "pot") return 0;

  NF("But the pot is not dirty!\n");
  if(!dirty) return 0;

  room = ENV(TO);
  while(!room->query_prop(ROOM_I_IS)) room = ENV(room);
  NF("You need fresh water to " + vb + " the pot.\n");
  if(!room->query_prop(OBJ_I_CONTAIN_WATER) && !(room->query_prop(ROOM_I_TYPE) == ROOM_BEACH)) return 0;

  if(filled)
  {
    write("To " + vb + " the pot, you pour out the water.\n");
    do_pour("water");
  }
  if(meal)
    meal->interrupt_cooking(TO, "clean"); 
  if(room->query_prop("_water_is_poisoned"))
  {
    write("You try to " + vb + " the pot in the dirty water, but you fail.\n");
    say(QCTNAME(TP) + " unsuccessfully tries to " + vb + " a pot in the dirty water.\n");
    return 1;
  }
  write("You " + vb + " the pot in the water.\n");
  dstr = "";
  if(vb == "wash") dstr = "e";
  say(QCTNAME(TP) + " " + vb + dstr + "s a pot in the water.\n");
  TO->set_dirty(0);
  return 1;
}

public int
eat_from_pot(string str)
{
  object stew;
  if(!str) return 0;
  if(!meal && !(stew = present("_rabbit_stew",TO))) return 0;
  if(meal)
  {
/*  meal->short(); */
    NF("You cannot eat the " + meal->query_short() + " from the pot.\n" +
       "Why don't you take the " + meal->query_short() + " from the pot if you want to eat it?\n");
    return 0;
  }
  stew->eat_from_pot(str);
  remove_prop(CONT_M_NO_REM);
  return 1;
}

public void
set_meal(object what)
{
  object *cont, *names;
  int i;

  if(!what) 
  {
    remove_prop(CONT_M_NO_REM);
    return;
  }
  meal = what;
  add_prop(CONT_M_NO_REM,MEAL_NO_REM);
  cont = all_inventory(TO);
  for(i = 0; i < sizeof(cont); i++)
  {
    if(member_array("salt",cont[i]->query_names()) > -1)
      meal->add_prop("_salt_added_to_stew",1);
    names = cont[i]->query_names();
    if(member_array("_rabbit_spice",names) > -1)
    {
      meal->add_prop("_rabbit_herb_added_to_stew",cont[i]->query_herb_name());
      meal->add_prop("_herb_added_to_stew",1);
    }
    else if(member_array("_stew_spice",names) > -1)
    {
      meal->add_prop("_stew_herb_added_to_stew",cont[i]->query_herb_name());
      meal->add_prop("_herb_added_to_stew",1);
    }
    else if(member_array("_spice",names) > -1)
    {
      meal->add_prop("_extra_herb_added_to_stew",cont[i]->query_herb_name());
      meal->add_prop("_herb_added_to_stew",1);
    }
  }
}

object
query_meal()
{
  return meal;
}

int
do_cook(string str)
{
  string vb, s1, s2;

  vb = query_verb();
  if(!stringp(str))
  {
    NF(CAP(vb) + " what?\n");
    return 0;
  }
  if(str == "pot" || sscanf(str, "%s pot %s", s1, s2) > 0)
  {
    write(BS("If you want to cook something in this pot, " +
      "you must hold the pot and the item to cook in your hands. " +
      "Then you can start cooking with the command " +
      "'cook <item>'.\n"));
    return 1;
  }
  NF(CAP(vb) + " what?\n");
  return 0;
}

void
init()
{
    ::init();

    add_action(do_fill,      "fill");	/* filling the pot */
    add_action(do_pour,      "pour");	/* pour water out */
    add_action(do_pour,      "empty");	/* pour water out */
    add_action(do_drink,     "drink");	/* drink water from pot */
    add_action(do_clean,     "clean");	/* clean pot if it is dirty */
    add_action(do_clean,     "wash");	/* clean pot if it is dirty */
    add_action(eat_from_pot, "eat");	/* eat stew right out of the pot */
    add_action(do_cook,      "cook");

    if (!objectp(meal) && !objectp(present("_rabbit_stew",TO)))
	remove_prop(CONT_M_NO_REM);
}

