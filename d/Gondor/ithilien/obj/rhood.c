/*
 *  The hood and mask of the Rangers of Ithilien.
 *  Makes it possible to disguise yourself.
 *  Commands: mask face, unmask face.
 *
 *  Coded by Lord Elessar Telcontar.
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object hooded;

void
create_armour()
{
  set_name("hood");
  add_name("mask");
  add_name("armour");
  set_adj("ranger");
  set_adj("dark-green");
  set_short("dark-green hood");
  set_long(break_string("This is a hood made of dark-green cloth. " +
    "When you wear it, you may 'mask face' to hide your face.\n",75));
  set_default_armour(3, A_HEAD, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3) + random(20) - 10);
  set_af(TO);
}

string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }

void
init()
{
  ::init();
  add_action("mask_face","mask");
  add_action("unmask_face","unmask");
}

int
mask_face(string str)
{
  object wearer;
  if (!str || (str != "face" && str != "me")) 
  { 
    NF("Mask what?\n"); 
    return 0; 
  }
  wearer = query_worn();
  if (TP != query_worn())
  {
    write("You have to wear the hood first.\n");
    return 1;
  }
  if (TP == hooded) { write("You are already masked!\n"); return 1; }
  tell_object(wearer,
    "You adjust the "+TO->short()+" to conceal your face.\n"+
    "You pull a part of the hood as a mask in front of your face,\n"+
    "but so that you can still view your surroundings.\n"+
    "You can 'unmask face' to remove the mask.\n");
  say(QCTNAME(TP)+" pulls part of "+TP->query_possessive()+" "+
    TO->short()+" across "+TP->query_possessive()+" face, masking "+
    TP->query_objective()+"self.\n",TP);
/*
  TP->add_prop(LIVE_I_NEVERKNOWN,1);
*/
  hooded = TP;
  return 1;
}

int
unmask_face(string str)
{
  object wearer;
  if (!str || (str != "face" && str != "me")) 
  { 
    NF("Unmask what?\n");
    return 0; 
  }
  wearer = query_worn();
  if (TP != query_worn()) return 0;
  if (TP != hooded) { write("You are not masked!\n"); return 1; }
  tell_object(wearer,
    "You remove the hood from your face, once again\n"+
    "revealing your true face and identity.\n");
  say(QCTNAME(TP)+" removes the mask and hood from "+TP->query_possessive()+
    " face, revealing "+TP->query_possessive()+" face again.\n",TP);
/*
  TP->remove_prop(LIVE_I_NEVERKNOWN,1);
*/
  hooded = 0;
  return 1;
}

void
leave_env(object inv, object to)
{
  ::leave_env(inv, to);
    if (inv && /* inv->query_prop(LIVE_I_NEVERKNOWN) */ inv == hooded)
  {
    tell_object(inv,"As you drop the "+TO->short()+", you once again reveal your face.\n");
    say("As "+QTNAME(inv)+" lets the "+TO->short()+" fall, you can again see\n"+
      inv->query_possessive()+" face.\n",TP);
/*
    TP->remove_prop(LIVE_I_NEVERKNOWN);
*/
    hooded = 0;
    }
}

int
remove(object obj)
{
  if (TP == hooded)
{
    write("As you take off the hood, you once again reveal your face.\n");
    say("As "+QTNAME(TP)+" takes off the hood and mask, you can\n"+
      "once again see "+TP->query_possessive()+" face.\n",TP);
/*
    TP->remove_prop(LIVE_I_NEVERKNOWN);
*/
    hooded = 0;
  }

  return 0;
}

