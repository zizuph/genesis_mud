
/*
 * /some path to be determined/
 *
 * Coded by Fylo 2000
 *
 * An average weapon manufactured by Kei, the Master Smith of SaMorgan. 
 *
*/

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "kei.h"

#define MAT_DESC ([\
   "bone":"Carved from the bones of a gigantic mekillot makes it both "+ \
          "light and extremely durable.",\
   "black steel" : "It is made of a dark steel forged from the black iron " +\
          "of SaMorgan. Rare is metal of any type in that barren land, and rarer " +\
          "still metals of such quality. It is as black as night and " +\
          "razor sharp. Such valuable material is used only in the finest " +\
          "of weapons."\
])

#define WEP_DESC ([\
"sword":    "It has a long blade with a cutting edge on the back and " +\
            "front. ",                                                  \
"axe":      "The head of this axe is moderately sized, and has a long "+\
            "blade curved back at the top and bottom. ",                \
"halberd":  "This halberd has a long, very thick, bone handle, the "   +\
            "animal it came from must have been huge. Along the "      +\
            "top of the handle a long cutting edge. ",                  \
"club":     "This club is a simple design, large and heavy one end, "  +\
            "tapering to a leather wrapped handle on the other. ",      \
"knife":    "This knife is basic in design, with a short blade, and "  +\
            "a cutting edge on the front and back of the weapon. "      \
])

#define WEP_MAT_VALS ([\
   "black steel" : ({1, 1, 8}), \
   "bone" : ({25, 25, 6})\
])

string Hands  = "two-handed";
    
string Type     = "axe",
       Material = "bone";

string Engraving = "Crafted by Kei, Master Smith of SaMorgan.";

/* Prototypes */
void     config_weapon(string type, string material, string hands);
void     make_one_handed();
string   exa_engraving();
int      set_type(string type);
int      set_material(string material);
int      set_engraving(string engraving);

/*
 * Function name: config_weapon
 * Description:   Uses a matrix based on the type of obsidian
 *                to determine the values of weight, pen, damage,
 *                likely to break, and likely to dull settings.
 *                Note: always for a 2 handed axe, if the customer
 *                ordered a 1 handed axe make_one_handed() will modify
 *                these values to make it appropriate for one hand.
 * Arguments:     a string that is the stone type
 * Returns:       nothing
 */
void
config_weapon(string type, string material, string hands)
{
   float weight = itof(WEP_MAT_VALS[material][2]);
   int hit = WEP_MAT_VALS[material][0];
   int pen = WEP_MAT_VALS[material][1];
   Type = type;
   Material = material;
   Hands = hands;
   add_adj(Material);
   set_name(WEP_NAME[Type]);
   set_short(Material + " " + WEP_NAME[Type][0]);
   
   set_long(BSN(WEP_DESC[Type] + MAT_DESC[Material]) +
            "The handle has been engraved.\n");
            
   if(Type == "knife")
   {
      /* Adjust weight, hit, and pen values for knife */
      weight = weight * 0.1;
      hit -= 5;
      pen -= 5;
      if(hit > 40)
         hit = 40;
      if(pen > 40)
         pen = 40;
   }
   if(hit > 50)
      hit = 50;
   if(pen > 50)
      pen = 50;
   set_default_weapon(hit,
                      pen,
                      WEP_TYPE[Type],
                      STD_DAMAGE_TYPE[Type],
                      W_BOTH, 0);
   
   add_prop(OBJ_I_WEIGHT, ftoi(weight * 1000.0));
   
   if(Material == "black steel")
   {
      add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit, pen)+random(1000) + 19000);
      add_prop(OBJ_M_NO_SELL, "That weapon is much to valuable for me to buy.\n");
   }
   else
   {
      add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit, pen)+random(500));
   }
   
   if(Hands == "one-handed" || Type == "knife")
      make_one_handed();
}

void
make_one_handed()
{
   int new_pen = query_pen() - 5;
   int new_hit = query_hit() - 5;
   int new_wgt = ftoi(0.875 * itof(query_prop(OBJ_I_WEIGHT)));
   
   if(new_hit > 45)
      new_hit = 45;
      
   if(new_pen > 45)
      new_pen = 45;
      
   set_default_weapon(new_pen, new_hit, WEP_TYPE[Type], STD_DAMAGE_TYPE[Type], W_ANYH, 0);
   add_prop(OBJ_I_WEIGHT, new_wgt);
   add_prop(OBJ_I_VALUE, ftoi(itof(query_value()) * 0.75) );
}

public void
create_weapon()
{
   add_item( ({"engraving", "engravings", "handle"}), exa_engraving);
}

string
exa_engraving()
{
   string text;
   text = BSN("On the handle you see some words engraved. " +
              "They read:\n") + Engraving + "\n";
   return text;
}

int
set_type(string type)
{
   if(!STD_DAMAGE_TYPE[type])
      return 0;
   remove_name(Type);
   Type = type;
   return 1;
}

int
set_material(string material)
{
   if(!MAT_DESC[material])
      return 0;
      
   Material = material;
   return 1;
}

string
query_material()
{
   return Material;
}

int
set_engraving(string engraving)
{
   if(!strlen(engraving))
      return 0;
   Engraving = "Crafted by Kei for: ";
   Engraving += engraving;
   return 1;
}

string
query_recover()
{
   string rec = "";
   
   if(Material == "black steel")
      return 0;
   
   rec += "#tsw_t#" + Type;
   rec += "#tsw_m#" + Material;
   rec += "#tsw_h#" + Hands;
   rec += "#tsw_e#" + Engraving;
   return MASTER + ":" + query_wep_recover() + rec + "#";
}

void
init_recover(string arg)
{
   string foobar;
   sscanf(arg, "%s#tsw_t#%s#%s", foobar, Type, foobar);
   sscanf(arg, "%s#tsw_m#%s#%s", foobar, Material, foobar);
   sscanf(arg, "%s#tsw_h#%s#%s", foobar, Hands, foobar);
   sscanf(arg, "%s#tsw_e#%s#%s", foobar, Engraving, foobar);
   if(!config_weapon(Type, Material, Hands) && !set_engraving(Engraving))
   {
      write("ERROR in init_recover: " + Type + Material + Hands);
      TO->remove_object();
      ::init_recover(arg);
   }
   ::init_recover(arg);
}
