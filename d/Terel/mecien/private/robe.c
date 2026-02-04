inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int cowl;

#define TO this_object()
#define TP this_player()

/* Code taken from Elessar's hood and modified. */

init(){
add_action("cover_face","cover");
add_action("uncover_face","uncover");
::init();
}

create_armour(){
set_name("robe");
set_adj("white");
add_name("mystic_robe");
set_long("A simple white robe, a religious garment.\n");
set_ac(10);
set_at(A_ROBE);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 300);
add_prop(OBJ_I_VOLUME, 300);
}

cover_face(string str)
{
  object wearer;
  if (!str || (str != "face" && str != "myself")) 
  { 
   notify_fail("Cover what?\n");
    return 0; 
  }
  wearer = query_worn();
  if (TP != query_worn()) { write("You have to be wearing the robe.\n"); return 1; }
  if (TP == cowl) { write("You already have the cowl drawn.\n"); return 1; }
  tell_object(wearer,
    "You draw the cowl of your robe over your face.\n");
  say(QCTNAME(TP)+" draws the cowl of "+TP->query_possessive()+" "+
    "robe to cover "+TP->query_possessive()+" face.\n");
  TP->add_prop(LIVE_I_NEVERKNOWN,1);
  cowl = 1;
  return 1;
}

uncover_face(string str)
{
  object wearer;
  if (!str || (str != "face" && str != "myself")) 
  { 
   notify_fail("Uncover what?\n");
    return 0; 
  }
  wearer = query_worn();
  if (TP != query_worn()) return 0;
  if (!cowl) { write("You do not have the cowl drawn.\n"); return 1; }
  tell_object(wearer,
    "You withdraw the cowl from about your face.\n");
    say(QCTNAME(TP)+" withdraws the cowl of "+TP->query_possessive()+
    " robe from about " + TP->query_possessive() + " face.\n",TP);
    TP->remove_prop(LIVE_I_NEVERKNOWN);
    cowl = 0;
    return 1;
}

leave_env(object inv, object to)
{
  ::leave_env(inv, to);
  if (inv->query_prop(LIVE_I_NEVERKNOWN) && inv == cowl) {
    tell_object(inv,"As you drop the robe, you withdraw the cowl.\n");
    say("As "+QTNAME(TP)+" lets the robe fall, you see "+
      TP->query_possessive()+" face.\n",TP);
    TP->remove_prop(LIVE_I_NEVERKNOWN);
    cowl = 0;
    }
}

remove()
{
  if (cowl) {
    write("You withdraw the cowl from about your face.\n");
    say(QTNAME(TP)+" withdraws the cowl from about "
     +TP->query_possessive()+" face.\n",TP);
    TP->remove_prop(LIVE_I_NEVERKNOWN);
    cowl = 0;
    return 1;
    }
  write("You remove the "+TO->query_name()+".\n");
  say(QCTNAME(TP)+" removes the "+TO->query_name()+".\n",TP);
  return 1;
}



