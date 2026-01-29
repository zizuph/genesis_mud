
/*
 * /some path to be determined/
 *
 * Coded by Fylo 2000
 *
 * An average weapon manufactured by Tentavvar, the Master Smith of Tyr. 
 *
*/

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "tentavvar.h"

#define MAT_DESC ([\
   "bone":"Carved from the bones of a gigantic mekillot makes it both "+ \
          "light and extremely durable.",\
          "black steel" : "It is made of a dark steel forged from the "+ \
          "black iron of Tyr. Rare is metal of any type in that barren "+ \
          "land, and rarer still metals of such quality. It is as "+ \
          "black as night and razor sharp. Such valuable material is "+ \
          "used only in the finest of weapons."\
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

string Engraving = "Crafted by Tentavvar, Master Smith of Tyr.";

/* Prototypes */
void     config_weapon(string type, string material, string hands);
void     make_one_handed();
string   exa_engraving();
int      set_type(string type);
int      set_material(string material);
int      set_engraving(string engraving);
int      raw_hit, raw_pen;

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
   int hit;
   int pen;

   float weight = itof(WEP_MAT_VALS[material][2]);
   if(!raw_hit)
       hit = WEP_MAT_VALS[material][0];
   else 
       hit = raw_hit;

   if(!raw_pen)
       pen = WEP_MAT_VALS[material][1];
   else
       pen = raw_pen;

   Type = type;
   Material = material;
   Hands = hands;
   add_adj(Material);

   if(Material == "black steel")
   {
       add_adj("black");
       add_adj("steel");
   }

   set_name(WEP_NAME[Type]);
   add_name(Material + " " + WEP_NAME[Type][0]);
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
      if(pen > 35)
         pen = 35;
   }
   else
   {
   if(hit > 50)
      hit = 50;
   if(pen > 50)
      pen = 50;
   }

   if(!raw_hit)
   {
       set_default_weapon(hit, pen, WEP_TYPE[Type], STD_DAMAGE_TYPE[Type], 
           W_BOTH, 0);
   }
   else
   {
       set_default_weapon(raw_hit, raw_pen, WEP_TYPE[Type], STD_DAMAGE_TYPE[Type], 
           W_BOTH, 0);
   }
   
   add_prop(OBJ_I_WEIGHT, ftoi(weight * 1000.0));
   
   if(Material == "black steel")
   {
      add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit, pen)+random(1000) + 19000);
      add_prop(OBJ_M_NO_SELL, "That weapon is much to valuable for me to buy.\n");
	  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	  add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
	  add_prop(MAGIC_AM_ID_INFO, ({ 
            "The Tyrant King of Tyr has allowed his smiths to create this weapon "
		+"Any who might have access to metal or "
		+"magic objects are seen by the Tyrant King as worthy of the full "
		+"skill of his smiths. He takes much of the magical essence for "
		+"himself, as magic is in short supply but allows some to be "
		+"imbued in the weapon so that it remains useful.\n", 30 }) );
       add_prop(OBJ_S_WIZINFO, 
            "Folks turn in magical weapons and convert them to another "
		+"magical weapon of a different type. The hit/pen are maxed out "
		+"but the weapons end up being pretty good. A good way to change "
		+"the type of weapon. It is created by the Bonesmith in Tyr who "
		+"can be found at /d/Cirath/tyr/bonesmith/tentavvar.c and the " 
		+"weapon code can be found in /d/Cirath/tyr/bonesmith/ It is "
		+"important to note that the created weapon is always worse than "
		+"the original. Also, AoD ogre weapons can't be converted.\n");
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
   
   if(Type == "knife")
   {
	   if(new_hit > 40)
          new_hit = 40;
      
      if(new_pen > 35)
          new_pen = 35;
   }  
   else
   {
   if(new_hit > 45)
      new_hit = 45;
      
   if(new_pen > 45)
      new_pen = 45;
   }

   if(!raw_hit)
   {
       set_default_weapon(new_hit, new_pen, WEP_TYPE[Type], STD_DAMAGE_TYPE[Type], 
           W_ANYH, 0);

   }
   else
   {
       set_default_weapon(raw_hit, raw_pen, WEP_TYPE[Type], STD_DAMAGE_TYPE[Type], 
           W_ANYH, 0);
   }
      
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
   Engraving = "Crafted by Tentavvar for: ";
   Engraving += engraving;
   return 1;
}

public string
query_recover()
{
   raw_hit = query_hit();
   raw_pen = query_pen();

   return MASTER + ":" + query_wep_recover() + "&&" + Type + "&&" + 
        Material + "&&" + Hands + "&&" + Engraving + "&&" + raw_hit  + 
        "&&" + raw_pen;

}

public void
init_recover(string arg)
{
   string *a = explode(arg,"&&");
   Type = (a[1]);
   Material = (a[2]);
   Hands = (a[3]);
   Engraving = (a[4]);
   raw_hit = atoi(a[5]);
   raw_pen = atoi(a[6]);
   init_wep_recover(a[0]);

   if(!config_weapon(Type, Material, Hands))
   {
      write("ERROR in init_recover: " + Type + Material + Hands);
      TO->remove_object();
      ::init_recover(arg);
   }
   ::init_recover(arg);
}
