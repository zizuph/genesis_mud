
/*
 * This is a rebootable armour 
 * to be created by Bubba, the blacksmith of Gelan
 * Based on code by Olorin for Calmacil
 *
 * Adapted by Maniac, 7.94
 * keepability added, Maniac, 16/9/96
 * revised, Maniac, 8/4/98, 21/4/98
 */

inherit "/std/armour";
inherit "/lib/keep"; 

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "armours.h"
#include "/d/Calia/gelan/monsters/make_armour.h"

string metal, armtype, const;

int
make_the_armour()
{
   int rho, i_ac, size_f, conw_f, i_armtype;

   /* Set the name */
   if (armour_type_at[armtype])
       set_name(armtype);
   else 
       return 0;

   /* Set first adjective */
   if ((armtype == "body-armour") || (armtype == "greaves") || 
       (armtype == "bracers")) 
       if (armour_const_rating[const]) 
           set_adj(const);
       else
           return 0;
   else if (armtype == "shield") 
       if (shield_const_rating[const])
           set_adj(const);
       else
           return 0;
   else if (armtype == "helm") 
       if (helm_const_rating[const])
           set_adj(const);
       else
           return 0;
   else return 0;


   /* Set second adjective */
   if (armour_metal_rating[metal])
       set_adj(metal);
   else
       return 0;


   /* Set the armour type */
   if (i_armtype = armour_type_at[armtype])
       set_at(i_armtype); 
   else
       return 0;

   i_ac = query_made_armour_ac(armtype, metal, const);
   if ((i_ac > 40) || (i_ac < 1))
       return 0;
   set_ac(i_ac);

   set_am(A_NAKED_MOD);

   rho = armour_metal_weight_mult[metal];
   size_f = armour_type_size_mult[armtype];
   conw_f = armour_const_weight_mult[const];

   /* configure armour */
   /* No point in doing weights, volumes & prices as only the defaults 
      are legal currently!!

   add_prop(OBJ_I_VOLUME, 
                      (VOL_STAND * size_f * conw_f) / 1000);
   add_prop(OBJ_I_WEIGHT,
                      (WGT_STAND * size_f * rho * conw_f) / 40000);
   add_prop(OBJ_I_VALUE, query_made_armour_value(armtype, metal, const));
    */ 

   if ((armtype == "bracers") || (armtype == "greaves"))
       set_short("pair of " + metal + " " + const + " " + armtype);
   else
       set_short(metal + " " + const + " " + armtype);
   set_long("This " + metal + " " + const + " " +
            armtype + " looks well crafted. You notice a " +
            "little inscription: Made in Gelan by Bubba " +
            "Hammerhead.\n");
   set_keep(1); 

   update_prop_settings(); 

   return 1;
}


string
query_recover()
{
   string rec;
   rec = MASTER + ":";
   rec += "#a#" + armtype;
   rec += "#m#" + metal;
   rec += "#c#" + const;
   rec += "#myend";
   rec += query_arm_recover();
   rec += query_keep_recover(); 
   return rec;
}


void
init_recover(string arg)
{
  string foobar;

  sscanf(arg, "%s#a#%s#m#%s#c#%s#myend%s", 
                foobar, armtype, metal, const, foobar);
  init_arm_recover(arg);

  if(!make_the_armour())
  {
      log_file("armour_recover", ctime(time()) + ":" + " " +
               armtype + " " + metal + " " + const + "\n" );
      remove_object();
  }

  init_keep_recover(arg); 
}


void
set_metal(string m)
{
   metal = m;
}

void
set_armtype(string a)
{
   armtype = a;
}

void
set_const(string s)
{
   const = s;
}

public int *
query_shield_slots()
{
    if (query_at() & A_SHIELD)
    {
        return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
    }
    
    return ::query_shield_slots();
}
