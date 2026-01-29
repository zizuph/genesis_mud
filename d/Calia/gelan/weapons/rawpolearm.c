/*
 * Polearms created by Bubba, the blacksmith of Gelan, use this file.
 *
 * Coded by Maniac, 24.6.95
 */
inherit "/std/weapon";
inherit "/lib/keep"; 

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Calia/gelan/monsters/make_polearm.h"

string polearm_name, metal, length, decor_type;

int
make_the_polearm()
{
  int rho, w, p, size_v, len_w;
  object this;

  this = this_object();
  /* Set the name */
  if (polearm_name_descs[polearm_name])
      this->set_name(polearm_name);
  else 
      return 0;

  /* set first adjective */
  if (polearm_decor_descs[decor_type]) 
      this->set_adj(decor_type);
  else
      return 0;
      
  /* Set second adjective */
  if (polearm_metal_descs[metal])
      this->set_adj(metal);
  else
      return 0;

    if ((!polearm_length_descs[length]) ||
        (!polearm_metal_descs[metal]) ||
        (!polearm_metal_weight_mult[metal]) ||
        (!polearm_length_weight_mult[length]) ||
        (!polearm_length_rating[length]) ||
        (!polearm_metal_rating[metal]))
    return 0;

  w = query_made_polearm_wc(metal, length);
  p = query_made_polearm_pen(metal, length);

  if ((w > 40) || (w < 1) || (p > 40) || (p < 1))
      return 0;

  this->set_pen(p);
  this->set_hit(w);
  this->set_wt(W_POLEARM); 
  this->set_dt(W_IMPALE);
  if (length == "short") 
      this->set_hands(W_ANYH);
  else
      this->set_hands(W_BOTH);

  rho = polearm_metal_weight_mult[metal];
  len_w = polearm_length_weight_mult[length];
  size_v = len_w;

  this->add_prop(OBJ_I_VOLUME, 
                     (size_v * len_w) / 3);
  this->add_prop(OBJ_I_WEIGHT,
                     (size_v * rho * len_w) / 150);
  this->add_prop(OBJ_I_VALUE, query_made_polearm_value(metal, length));
  this->set_short(decor_type + " " + metal + " " + polearm_name);
  this->set_long(polearm_name_descs[polearm_name] + 
                          polearm_metal_descs[metal] +
                          polearm_length_descs[length] +
                          polearm_decor_descs[decor_type] + 
                      "You notice a little inscription: Made in Gelan " +
                      "by Bubba Hammerhead.\n");
  set_keep(1); 
  return 1;
}


string
query_recover()
{
  string rec;
  rec = MASTER + ":";
  rec += "#p#" + polearm_name;
  rec += "#m#" + metal;
  rec += "#l#" + length;
  rec += "#d#" + decor_type;
  rec += "#myend";
  rec += query_wep_recover();
  rec += query_keep_recover(); 
  return rec;
}


void
init_recover(string arg)
{
  string foobar;

  sscanf(arg, "%s#p#%s#m#%s#l#%s#d#%s#myend%s", 
                foobar, polearm_name, metal, length, decor_type, foobar);
  init_wep_recover(arg);

  if(!make_the_polearm())
  {
    log_file("polearm_error", "Messed up when trying to make polearm " +
                              metal + length + decor_type + 
                              polearm_name + ".\n");
    this_object()->remove_object();
  }

  init_keep_recover(arg); 

  return;
}


void
set_polearm_name(string p)
{
    polearm_name = p; 
}

void
set_decor_type(string d)
{
    decor_type = d; 
}

void
set_metal(string m)
{
    metal = m;
}

void
set_length(string l)
{
    length = l;
}

