/*
  
  by Udana, /2006
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume*/
#define WEIGHT_MOD 0.4
/* used to calculate value */
#define VALUE_MOD 0.8
#define HIT 20
#define PEN 22

/* For cracking a whip */
int crack_whip(string a);

create_weapon()
{
  set_name("whip");
  set_adj("leather");
  add_adj("long");
  set_short("leather whip");   
  set_long("A common tool of coachmen and drivers. The cracking noise they made with it " +
    "most popular way of speeding up any four-legged animal.\n");
  set_default_weapon(HIT, PEN, W_CLUB,W_BLUDGEON | W_SLASH, W_ANYH);
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}

public void init()
{
  ::init();
  add_action(crack_whip, "crack");
}

int crack_whip(string a)
{
  notify_fail("Crack what?\n");
  if(a != "whip")
    return 0;
  write("You crack the " + query_short() + " above your head.\n");
  say(QCTNAME(TP) + " cracks " + TP->query_possessive() + " " + query_short() +
    " above " + TP->query_possessive() + " head.\n");
  return 1;
}