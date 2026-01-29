/*
 * This object is by common/guild/secret_room,
 * it is very random in looks, but dependable.
 */

inherit "/std/object";
 
#include <stdproperties.h>
#include "/d/Shire/open/randomize.h"
 
#define SNAME ({"key", "goblet", "chalice", "eye"})
#define SADJ ({"silver", "bronze", "antique", "glass"})

string adj;

create_object() {
  int ran, val, weight;

  ran = random(sizeof(SNAME));

  if (ran == 0 || ran == 1) /* key, goblet */
  {
     adj = random_metal();
     weight = (800 * query_metal_weight_factor(adj)) / 100;
     val = (500 * query_metal_price_factor(adj)) / 100;
  }
  else if (ran == 2) /* chalice */
  {
     adj = "antique";
     weight = 800;
     val = 500;
  }
  else /* eye */
  {
     adj = random_jewel();
     weight = (800);
     val = (500 * query_jewel_price_factor(adj)) / 100;
  }
  set_name(SNAME[ran]);
  set_short(adj + " " + SNAME[ran]);
  set_adj(adj);
  set_long("Consider this object as a token of Nob Nar's gratitude.\n");
  add_prop(OBJ_I_WEIGHT, weight);
  add_prop(OBJ_I_VOLUME, weight);
  add_prop(OBJ_I_VALUE, val);
}
