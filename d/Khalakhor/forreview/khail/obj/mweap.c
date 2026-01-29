/*
 * The base object for bow/xbow missile weapons
 * Stexx, May 24/95
 */
#include "/d/Immortal/std/domain.h"
#include <language.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>

#define TPQP this_player()->query_possessive()

inherit STDWEAPON;

/* Global Vars */
int rate;               /* Number of attacks before npc reacts */
string *ammo,           /* Array of missiles which can be used */
       *load_msgs,      /* Custom loading messages */
       *fire_msgs,      /* Custom firing messages */
       *unload_msgs,    /* Custom unloading messages */
       missile_type,    /* Two-hands required to fire */
       load_desc;       /* Extra description for loaded status */
object ammoob;          /* The leaded missile object */

/* Prototypes */
void set_load_msg(string *msgs);
string *query_load_msg(object obj);
void set_load_desc(string desc);
string query_load_desc();
void set_fire_msg(string *msgs);
string *query_fire_msg(object obj);
void set_unload_msg(string *msgs);
string *query_unload_msg(object obj);
void set_rate(int i); 
int query_rate();
void set_ammo(string *ammotypes);
string *query_ammo();
int load_it(string str);
void set_load(object ob);
object query_load();
int fire_it(string str);
int unload_it(string str);
void set_type(string str);
string query_type();

void
create_weapon()
{
  add_prop(CONT_I_IN,1);
  add_prop(CONT_M_NO_INS,"That doesn't seem quite right, perhaps you could "+
    "load it instead?\n");
  add_prop(CONT_M_NO_REM,"That doesn't seem quite right, perhaps you could "+
    "unload it instead?\n");
  add_prop(CONT_I_MAX_WEIGHT,10000);
  add_prop(CONT_I_MAX_VOLUME,1000);
}

/*
 * Function name: set_type
 * Description: Sets the missile weapon type require one or two hands to
 *              fire (default 1 hand)
 * Arguments: str - "one handed" (default)
 *                  "two handed"
 */
void
set_type(string str)
{
  if(!strlen(str))
    return;
  else
    missile_type = str;
}

/*
 * Function name: query_type
 * Description: Gets the missile weapon type (one vs. two hands)
 * Returns: "one handed" or "two handed"
 */
string
query_type()
{
  if(!strlen(missile_type))
    return "one handed";
  else
    return missile_type;
}

/*
 * Function name: set_load_msg
 * Description: Allows custom loading messages
 * Arguments: *msgs - a string array of 2 elements.
 *                    The first element is the message this_player() gets.
 *                    The second element is the message others get.
 */
void
set_load_msg(string *msgs)
{
  if(sizeof(msgs) != 2)
    return;

  load_msgs = msgs;
}

/*
 * Function name: query_load_msg
 * Description: Gets the custom loading messages
 * Returns: The string array *load_msgs, or default values if custom not
 *          set.
 */
string *
query_load_msg(object obj)
{
  if(!load_msgs || !sizeof(load_msgs))
    return ({"load the "+TO->short()+" with "+LANG_ADDART(obj->short())+".\n",
             "loads a "+TO->short()+" with "+LANG_ADDART(obj->short())+".\n"});
  else
    return load_msgs;
}

/*
 * Function name: set_load_desc
 * Description: Sets custom extra desc for loaded status.
 * Arguments: desc - the extra description.
 */
void
set_load_desc(string desc)
{
  if(!strlen(desc))
    return;
  else
    load_desc = desc;
}

/*
 * Function name: query_load_desc
 * Description: Returns the extra description of loaded status.
 *              If not set, no value used.
 */
string
query_load_desc()
{
  if(!strlen(load_desc))
    return "";
  else
    return load_desc;
}

/*
 * Function name: set_fire_msg
 * Description: Sets custom firing message.
 * Arguments: *msgs - a string array of 2 elements.
 *                    First element is message player gets.
 *                    Second element is message others get.
 */
void
set_fire_msg(string *msgs)
{
  if(!sizeof(msgs))
    return;
  else
    fire_msgs = msgs;
}

/*
 * Function name: query_fire_msg
 * Description: Returns array of custom firing messages
 * Returns: two element array *fire_msgs
 */
string *
query_fire_msg(object obj)
{
  if(!fire_msgs || !sizeof(fire_msgs))
    return ({ "take aim and fire your "+TO->short()+" at "+QCTNAME(obj)+".\n",
      "takes aim and fires "+TPQP+" "+TO->short()+" at "+QCTNAME(obj)+".\n",
      "takes aim and fires "+TPQP+" "+TO->short()+" at you.\n" });
  else
    return fire_msgs;
}

/*
 * Function name: set_unload_msg
 * Description: Sets custom messages for unloading weapon
 * Arguments: *msgs - a string array of two elements.
 *                    First element is what this_player() sees.
 *                    Second element is what others see.
 */
void
set_unload_msg(string *msgs)
{
  if(!sizeof(msgs))
    return;
  else
    unload_msgs = msgs;
}

/*
 * Function name: query_unload_msg
 * Description: Returns the custom unloading messages.
 * Returns: A string array of two elements.
 */
string *
query_unload_msg(object obj)
{
  if(!unload_msgs || !sizeof(unload_msgs))
    return ({ "remove "+LANG_ADDART(obj->short())+" from your "+TO->short()+".\n",
              "removes "+LANG_ADDART(obj->short())+" from "+TPQP+" "+TO->short()+".\n"});
  else
    return unload_msgs;
}

/*
 * Function name: set_rate
 * Description: Sets the number of missiles an npc can be hit with before
 *              engaging hand-to-hand.
 *              Value is reduced by 1/2 inside.
 * Arguments: i - the integer number of missiles, between 1 and 4
 */
void
set_rate(int i)
{
  if(!intp(i))
    return ;
  if(i < 0)
    rate = 1;
  else if(i > 4)
    rate = 4;
  else
    rate = i;
}

/*
 * Function name: query_rate
 * Description: Returns the number of attacks before npc responds
 */
int
query_rate()
{
  return rate;
}

/*
 * Function name: set_ammo
 * Description: Sets the ammunition that may be used in this missile weapon.
 *              Such as 'long bow arrow', 'heavy bolt', etc. Most will be
 *              able to launch a few different missiles.
 * Arguments: *ammotypes - an array containing all the missile names.
 */
void
set_ammo(string *ammotypes)
{
  if(!sizeof(ammotypes))
    return;

  ammo = ammotypes;
}

/*
 * Function name: query_ammo
 * Description: Returns the list of ammunition that can be used.
 * Return: A string array of ammo
 */
string *
query_ammo()
{
  return ammo;
}

void
init()
{
  ::init();
  add_action("load_it", "Load");
  add_action("fire_it", "fire");
  add_action("unload_it", "unload");
}

/*
 * Function name: load_it
 * Description: Command that loads the missile weapon with a supplied missile.
 * Arguments: str - the string that identifies the missile
 */
int
load_it(string str)
{
int tmp, i;
string weap, mname;
object *obs, obj;

  notify_fail("Load what? The "+TO->short()+" with something perhaps?\n");

  if(!strlen(str))
    return 0;

  NF("failed at sscanf\n");
  if(sscanf(str,"%s with %s",weap, mname) != 2)
    return 0;

  if(!TO->id(weap))
    return 0;

  if(!query_wielded())
    {
    NF("The "+TO->short()+" must first be wielded.\n");
    return 0;
    }

  if(query_load())
    {
    notify_fail("The "+TO->short()+" is already loaded.\n");
    return 0;
    }

  NF("failed at parser\n");
  if(!parse_command(mname, TP, "[the] %i", obs) ||
    !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)) )
    return 0;
  
  tmp = sizeof(obs);

  for(i = 0; i < tmp; i++)
    {
    if(!obs[i]->is_ammunition())
      obs -= ({obs[i]});
    }

  NF("ammunition check failed\n");
  if(!sizeof(obs))
    return 0;

  if(sizeof(obs) > 1)
    {
    notify_fail("You can only use one missile in this weapon.\n");
    return 0;
    }
  
  obj = obs[0];

  TP->catch_msg("You "+query_load_msg(obj)[0]);
  tell_room(environment(TP), QCTNAME(TP)+" "+query_load_msg(obj)[1], TP);

  remove_prop(CONT_M_NO_INS);
  set_load(obj);
  add_prop(CONT_M_NO_INS,"That doesn't seem quite right, perhaps you could "+
    "load it instead?\n");

  return 1;
}

/*
 * Function name: set_loaded
 * Arguments: The ammunition loaded into the projecter
 */
void
set_load(object ob)
{
  if(!objectp(ob))
    return;

  else
    {
    ob->move(TO);
    ammoob = ob;
    }
}

/*
 * Function name: query_load
 * Description: Returns the object loaded into the projecter
 * Returns: Ammoob - ammunition object
 */
object
query_load()
{
  return ammoob;
}

/*
 * Function name: unload_it
 * Description: Removes loaded ammunition from weapon
 */
int
unload_it(string str)
{
  notify_fail("Unload what? Your "+TO->short()+" maybe?\n");

  if(!strlen(str))
    return 0;

  if(!TO->id(str))
    return 0;

  if(!query_load())
    {
    notify_fail("The "+TO->short()+" is not loaded.\n");
    return 0;
    }

  TP->catch_msg("You "+query_unload_msg(query_load())[0]);
  tell_room(environment(TP),QCTNAME(TP)+" "+query_unload_msg(query_load())[1],TP);

  remove_prop(CONT_M_NO_REM);
  query_load()->move(TP);
  ammoob = 0;

  add_prop(CONT_M_NO_REM,"That doesn't seem quite right, perhaps you could "+
    "load it instead?\n");
  return 1;
}

/*
 * Function name: fire_it
 * Description: Contains the actual firing sequence.
 * Arguments: str - the target living.
 */
int
fire_it(string str)
{
string weap, target;  
object *obs, tobj, mobj;

  NF("Fire what?\n");

  if(!strlen(str))
    return 0;

  if(sscanf(str, "%s at %s", weap, target) != 2)
    return 0;

  if(!TO->id(weap))
    return 0;
  
  NF("Fire the "+TO->short()+" at who?\n");
  if(!parse_command(target, environment(TP), "[the] %i", obs) ||
    !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)) )
    return 0;

  obs = FILTER_LIVE(obs);

  if(!sizeof(obs))
    return 0;

  tobj = obs[0];

  if(!query_load())
    {
    NF("You cannot fire the "+TO->short()+" until you have loaded it.\n");
    return 0;
    }

  if(!query_wielded())
    {
    NF("You must first wield the "+TO->short()+".\n");
    return 0;
    }

  if(TP->query_wielded(W_RIGHT) && TP->query_wielded(W_RIGHT))
    {
    if(query_type() == "two handed")
      {
      notify_fail("You need two hands free to fire the "+TO->short()+".\n");
      return 0;
      }
    }

  if(sizeof(TP->query_attack()))
    {
    NF("You have no room to aim your "+TO->short()+" in the heat of "+
      "combat.\n");
    return 0;
    }

  TP->catch_msg("You "+query_fire_msg(tobj)[0]);
  tell_room(environment(TP), QCTNAME(TP)+" "+query_fire_msg(tobj)[1],({TP,tobj}));
  tobj->catch_msg(QCTNAME(TP)+" "+query_fire_msg(tobj)[2]);
  
  remove_prop(CONT_M_NO_REM);
  if(random(150)+1 > TP->query_skill(SS_WEP_MISSILE))
    TP->catch_msg("You missed.\n");
  else
    TP->catch_msg("You hit.\n");
  query_load()->move(tobj);

  ammoob = 0;

  add_prop(CONT_M_NO_REM,"That doesn't seem quite right, perhaps you could "+
    "unload it instead?\n");
  return 1;
}
