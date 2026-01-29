/*
 * This is a rebootable armour 
 * Created by the smith in Minas Morgul
 *
 * Modified November, 2004 by Serif from Olorin's Minas Tirith smith
 */
#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define METAL    ({"silver", "brass", "gold", "bronze", "iron", \
                   "tempered iron", "steel", "alloyed steel", \
                   "high steel", "mithril"})
#define ARMTYPE  ({"cuirass", "shield", "helm", "greaves", "bracers"})
#define PARMTYPE  ({"cuirasses", "shields", "helms", "greaves", "bracers"})
#define ARMCONST ({"ring", "scale", "splint", "chain", "double", \
                   "bar", "augmented", "banded", "plate"})
#define HELMCON  ({"ring", "chain", "double", "plate", "tabarded", \
                   "visored", "great"})
#define SHIELDC  ({"small", "normal", "large"})
#define VOL_STAND 50
#define WGT_STAND 50

int i_metal, i_armtype, i_const;

int
make_the_armour()
{
    int     rho, i_ac, price_f, size_f, cond_f, break_f, 
            imp_m, sla_m, blu_m, conw_f;
    string  s_const, 
            sh_txt;

    if (i_armtype > -1 && i_armtype < sizeof(ARMTYPE))
    {
        TO->set_name(ARMTYPE[i_armtype]);
        TO->set_pname(PARMTYPE[i_armtype]);
    }
    else
        return 0;

    if (i_const > -1)
    {
        // Remove old adjectives:
        remove_adj(query_adjs());

        if ((ARMTYPE[i_armtype] == "cuirass"    ||
            ARMTYPE[i_armtype] == "greaves"   ||
            ARMTYPE[i_armtype] == "bracers" ) &&
            i_const < sizeof(ARMCONST))
        {
            TO->set_adj(ARMCONST[i_const]);
            s_const = ARMCONST[i_const];
        }
        else if ( (ARMTYPE[i_armtype] == "shield") &&
            (i_const < sizeof(SHIELDC)) )
        {
            TO->set_adj(SHIELDC[i_const]);
            s_const = SHIELDC[i_const];
        }
        else if ( (ARMTYPE[i_armtype] == "helm") &&
            (i_const < sizeof(HELMCON)) )
        {
            TO->set_adj(HELMCON[i_const]);
            s_const = HELMCON[i_const];
        }
        else 
            return 0;
    }
    else 
        return 0;

    switch (ARMTYPE[i_armtype])
    {
    case "cuirass":
        TO->set_at(A_TORSO); size_f = 100; break;
    case "shield":
        TO->set_at(A_SHIELD); size_f = 25; break;
    case "helm":
        TO->set_at(A_HEAD); size_f = 35; break;
    case "greaves":
        TO->set_at(A_LEGS); size_f = 45; break;
    case "bracers":
        TO->set_at(A_ARMS); size_f = 45; break;
    }
    
    if ((i_metal > -1) && (i_metal < sizeof(METAL)))
        TO->set_adj(explode(METAL[i_metal], " "));
    else 
        return 0;

    /* Setting weight, price, condition, and likelihood of breaking
     * according to choice of metal
     */
    switch (METAL[i_metal])
    {
    case "silver":
        rho = 105; price_f = 115; cond_f = 12; break_f =  6; break;
    case "brass":
        rho =  85; price_f =  80; cond_f = 13; break_f =  8; break;
    case "gold":
        rho = 193; price_f = 135; cond_f = 15; break_f =  5; break;
    case "bronze":
        rho =  89; price_f =  85; cond_f = 12; break_f = 10; break;
    case "iron":
        rho =  79; price_f = 100; cond_f = 10; break_f =  7; break;
    case "tempered iron":
        rho =  73; price_f = 110; cond_f =  8; break_f =  9; break;
    case "steel":
        rho =  69; price_f = 120; cond_f =  5; break_f =  7; break;
    case "alloyed steel":
        rho =  65; price_f = 160; cond_f =  5; break_f =  4; break;
    case "high steel":
        rho =  60; price_f = 240; cond_f =  2; break_f =  2; break;
    case "mithril":
        rho =  40; price_f = 600; cond_f =  0; break_f =  0; break;
  }

/* Armour class according to construction and metal */
  i_ac = 5 + i_const * 2 + i_metal * 2;
/* max AC for bought armour: MAX_BOUGHT_AC from ~gondor/defs.h */
  if(i_ac > MAX_BOUGHT_AC) i_ac = MAX_BOUGHT_AC;
  TO->set_ac(i_ac);

/* calculated modifiers according to construction */
  switch(s_const)
  {
    case "ring":
      imp_m = -1; sla_m = 2; conw_f =  5; break;
    case "scale":
      imp_m =  1; sla_m = 1; conw_f =  6; break;
    case "splint":
      imp_m =  1; sla_m = 1; conw_f =  7; break;
    case "chain":
      imp_m = -1; sla_m = 2; conw_f =  9; break;
    case "double":
      imp_m = -1; sla_m = 1; conw_f = 10; break;
    case "bar":
      imp_m = -1; sla_m = 1; conw_f = 12; break;
    case "augmented":
      imp_m = -1; sla_m = 1; conw_f = 13; break;
    case "banded":
      imp_m =  0; sla_m = 0; conw_f = 14; break;
    case "plate":
      imp_m =  0; sla_m = 0; conw_f = 15; break;
    default:
      imp_m =  0; sla_m = 0; conw_f = 10;
  }
  blu_m = -imp_m-sla_m;
  TO->set_am(({imp_m, sla_m, blu_m}));

/* configure armour */
  TO->add_prop(OBJ_I_VOLUME,VOL_STAND * size_f * conw_f/ 100 );
  TO->add_prop(OBJ_I_WEIGHT,WGT_STAND * size_f * rho * conw_f / 1000);
  TO->add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(i_ac)*price_f/100);
  TO->set_likely_cond(cond_f);
  TO->set_likely_break(break_f);

  TO->update_prop_settings();

  sh_txt = METAL[i_metal] + " " + s_const + " " + ARMTYPE[i_armtype];
  if (ARMTYPE[i_armtype] == "greaves"  ||
      ARMTYPE[i_armtype] == "bracers")
  {
    TO->set_short("pair of " + sh_txt);
    TO->set_pshort("pairs of " + sh_txt);
  }
  else TO->set_short(sh_txt);
  TO->set_long(BS("This " + sh_txt + " "
    + "looks well crafted. You notice a small " +
    "mark shaped like a baleful, staring eye.\n"));
  return 1;
}

string
query_recover()
{
  string rec;
  rec = MASTER + ":";
/* i_armtype, i_metal, i_const */
  rec += "#i_a#" + i_armtype;
  rec += "#i_m#" + i_metal;
  rec += "#i_c#" + i_const;
  rec += query_arm_recover();
  return rec;
}

void
init_recover(string arg)
{
  string foobar;
  int i_check;
  sscanf(arg, "%s#i_a#%d#%s", foobar, i_armtype, foobar);
  sscanf(arg, "%s#i_m#%d#%s", foobar, i_metal, foobar);
  sscanf(arg, "%s#i_c#%d#%s", foobar, i_const, foobar);
  init_arm_recover(arg);
  if(!make_the_armour())
  {
    write("ERROR in init_recover: " + i_armtype + i_metal + i_const);
    TO->remove_object();
  }
  return;
}

int
estimate_value()
{
  int i_ac;
/* Armour class according to construction and metal */
  i_ac = 5 + i_const * 2 + i_metal * 2;
/* max AC for bought armour: MAX_BOUGHT_AC from ~gondor/defs.h */
  if(i_ac > MAX_BOUGHT_AC) i_ac = MAX_BOUGHT_AC;
  return F_VALUE_ARMOUR(i_ac);
}

int
set_metal(int i)
{
  i_metal = i;
  return make_the_armour();
}

int
set_armtype(int i)
{
  i_armtype = i;
  return make_the_armour();
}

int
set_const(int i)
{
  i_const = i;
  return make_the_armour();
}
