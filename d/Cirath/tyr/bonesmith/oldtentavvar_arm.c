/*
 * This is a rebootable armour 
 * manufactured by Tentavvar, Master Smith of Tyr
 *
 * Modeled after:
 * /d/Gondor/minas/obj/mtarmour.c by Olorin
 *
 * Fylo, Feb 2000
 */
#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "tentavvar.h"

string   Material,
         Armtype,
         Construction;

int
config_armour(string type, string mat, string construct)
{
   int   ac, blu,
         volume,
         weight;

   string   sh_txt,
            l_txt,
            mat_desc,
            con_verb,
            con_desc;
            
   mixed *arm_data,
         *mat_data,
         *con_data;
   
   Material = mat;
   Armtype = type;
   Construction = construct;

   arm_data = ARM_MAP[Armtype];
   mat_data = MAT_MAP[Material];
   con_data = CON_MAP[Construction];

   TO->set_name(Armtype);

   remove_adj(query_adjs());

   TO->set_adj(Construction);

   TO->set_adj(explode(Material, " "));
   TO->set_at(arm_data[ARM_TYPE]);

   ac = mat_data[MAT_AC] + con_data[CON_AC];
   
   if(ac > MAX_BOUGHT_AC)
      ac = MAX_BOUGHT_AC;
      
   TO->set_ac(ac);
   
   blu = -mat_data[MAT_IMP]-mat_data[MAT_SLA];
   
   TO->set_am(({mat_data[MAT_IMP], mat_data[MAT_SLA], blu}));

   /* configure armour */
   
   volume = VOL_STAND * arm_data[ARM_WGT] * con_data[CON_WGT];
   weight = WGT_STAND * arm_data[ARM_WGT] * mat_data[MAT_WGT] * 
            con_data[CON_WGT] / 1000;
   
   TO->add_prop(OBJ_I_VOLUME, volume);
   TO->add_prop(OBJ_I_WEIGHT, weight);
   TO->add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac)*mat_data[MAT_PRI]/100);
   TO->set_likely_cond(mat_data[MAT_CON]);
   TO->set_likely_break(mat_data[MAT_BRK]);

   TO->update_prop_settings();

   sh_txt = Construction + " " + Material + " " + Armtype;
   
   if (Armtype == "greaves" || Armtype == "bracers"  ||
       Armtype == "boots"   || Armtype == "gauntlets")
   {
      TO->set_short("pair of " + sh_txt);
      TO->set_pshort("pairs of " + sh_txt);
   }
   else
      TO->set_short(sh_txt);

   con_desc = "The " + Material + " has been ";
   con_desc += mat_data[MAT_VRB] + con_data[CON_LNG];
   mat_desc = break_string(mat_data[MAT_LNG], 70) + "\n";
   con_desc = break_string(con_desc, 70) + "\n";
   
   l_txt = "This is a " + TO->short() + ".\n";
   l_txt += mat_desc;
   l_txt += con_desc;

   TO->set_long(l_txt+ "\n");
   return 1;
}

string
query_recover()
{
   string rec = "";
   rec += "#ta_a#" + Armtype;
   rec += "#ta_m#" + Material;
   rec += "#ta_c#" + Construction;
   return MASTER + ":" + query_arm_recover() + rec + "#";}

void
init_recover(string arg)
{
   string foobar;
   sscanf(arg, "%s#ta_a#%s#%s", foobar, Armtype, foobar);
   sscanf(arg, "%s#ta_m#%s#%s", foobar, Material, foobar);
   sscanf(arg, "%s#ta_c#%s#%s", foobar, Construction, foobar);
   init_arm_recover(arg);
   if(!config_armour(Armtype, Material, Construction))
   {
      write("ERROR in init_recover: " + Armtype + Material + Construction);
      TO->remove_object();
   }
   return;
}
