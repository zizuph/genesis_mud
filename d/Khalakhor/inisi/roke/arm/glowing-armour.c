/*
 * Glowing armour base inheir
 * A tidy-up thirty years late.
 * Tapakah, 07/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "glowing-armour.h"

inherit "/std/armour";

mapping glowing_armours = ([
  "shield": ([ "ac": 16, "weight": 7000,  "volume": 3000, "at": A_SHIELD ]),
  "helmet": ([ "ac": 24, "weight": 2100,  "volume": 3000, "at": A_HEAD   ]),
  "mail"  : ([ "ac": 40, "weight": 17000, "volume": 8000, "at": A_TORSO  ]),
]);

int is_coal;
int glowing_hits;

string _armour_type;

void
set_glowing_hits (int x) { glowing_hits = x; }

int
query_glowing_hits () { return glowing_hits; }

string
query_recover ()
{
  return
    MASTER + ":" + query_arm_recover() +
    "#ggg#" + query_glowing_hits() + "#" + _armour_type + "#";
}

void
extinguish_fire ()
{
  string name = query_name();
  set_ac(0-glowing_armours[name]["ac"]/8); /* coal in the wounds :) */
  if (wearer)
    wearer->update_armour(this_object());
  is_coal = 1;

  set_name(name);
  set_short("tiny coal " + name);
  set_adj(({"tiny", "coal"}));
  set_long("This is the most ridiculous excuse for an armour ever seen!\n");
  remove_adj("glowing");
  add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)/10);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_VOLUME)/10);
  add_prop(OBJ_I_VALUE, 1);
  remove_prop(OBJ_I_LIGHT);
  remove_prop(MAGIC_I_RES_COLD);
}

void
init_recover (string arg)
{
  string apa;

  init_arm_recover(arg);
  sscanf(arg, "%s#ggg#%d#%d#%s", apa, glowing_hits, _armour_type, apa);

  if (glowing_hits >= MAX_GLOWING_HITS)
    extinguish_fire();
}

void
create_glowing_armour (string armour_type)
{
  if (!glowing_armours[armour_type])
    throw("Invalid armour type");
  mapping armour = glowing_armours[armour_type];

  _armour_type = armour_type;
  set_am(({0, 0, 0}));
  set_name(armour_type);
  set_adj("glowing");
  set_short("glowing " + armour_type);
  set_long("Ancient magic has created this " + armour_type + " of fire.\n");
  set_ac(armour["ac"]);
  set_at(armour["at"]);
  add_prop(OBJ_I_WEIGHT, armour["weight"]);
  add_prop(OBJ_I_VOLUME, armour["volume"]);
  add_prop(OBJ_I_LIGHT, 1);
  add_prop(MAGIC_I_RES_COLD, ({25, 1}));
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(OBJ_S_WIZINFO, 
           "Grants 1 level of light and 50 MAGIC_I_RES_COLD additive. \n" +
           "Has " + MAX_GLOWING_HITS + " charges of fire damage with "+
           "pen=damage done by attacker.\n");
  add_prop(MAGIC_AM_ID_INFO,
           ({
             "The armour seems to be enchanted with an intense fire and " +
             "therefore protects the wearer from the cold. The fire " +
             "is too hot to touch on the outside and can probably " +
             "really hurt someone.\n", 25,
             "You realize that once the fire goes out, the armour " +
             "provides less protection than no armour at all.\n", 40
           }));
  add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

  glowing_hits = 0;
  is_coal = 0;
}

void
got_hit(int hid, int ph, object att, int dt, int dam)
{
  ::got_hit(hid, ph, att, dt, dam);

  if (is_coal)
    return;

  if (dam <= 0)
    return;

  glowing_hits++;
  string name = query_name();
  
  att->hit_me(random(dam), 0, wearer, 0);
  att->catch_msg("You burn yourself on the glowing " + name + "!\n");
  wearer->catch_msg(QCTNAME(att) + " is hurt by the glowing " + name +"'s fire\n");

  if (glowing_hits >= MAX_GLOWING_HITS) {
    wearer->catch_msg("The fire of the glowing " + name + " goes out...\n");
    att->catch_msg("The fire of the glowing " + name + " of your enemy fades...\n");
    extinguish_fire();
  }
}
