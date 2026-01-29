
/*
 * /some path to be determined/
 *
 * Coded by Fylo 2000
 *
 * An obsidian weapon manufactured by Kei, the Master Smith of SaMorgan. 
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

/* Defines specific to obsidian weapons */

/* Max pen and damage for obsidian weapons, different weights and 
 * obsidian types will modify this value when setting up the
 * weapon. Also make_two_handed() will modify as required so
 * it only needs to be set here for a two handed weapon.
 */
#define MAX_PD 40

/* All these axes are made of obsidian which has a strong bias to
 * dull and break with use. Different types of obsidian have
 * different strengths and will modify this average.
 */
#define AVG_DB 10

/* The average weight of the obsidian axes in kilos. This value
 * will be modified depending on the type of obsidian used.
 */
#define AVG_WEIGHT 9
        
#define OBS_VALUES ([\
   "brown":          ({ AVG_WEIGHT +3, MAX_PD -5, MAX_PD -2, AVG_DB -4 }),\
   "mahogany":       ({ AVG_WEIGHT +3, MAX_PD -5, MAX_PD -2, AVG_DB -4 }),\
   "lizard-skin":    ({ AVG_WEIGHT +2, MAX_PD -4, MAX_PD -2, AVG_DB -2 }),\
   "flame-red":      ({ AVG_WEIGHT +2, MAX_PD -4, MAX_PD -2, AVG_DB -2 }),\
   "jet-black":      ({ AVG_WEIGHT,    MAX_PD,    MAX_PD,    AVG_DB    }),\
   "deep-green":     ({ AVG_WEIGHT -1, MAX_PD -1, MAX_PD -1, AVG_DB +1 }),\
   "midnight-lace":  ({ AVG_WEIGHT -2, MAX_PD -2, MAX_PD -2, AVG_DB +2 }),\
   "snowflake":      ({ AVG_WEIGHT -3, MAX_PD -2, MAX_PD -4, AVG_DB +3 }),\
   "rainbow":        ({ AVG_WEIGHT -3, MAX_PD -2, MAX_PD -4, AVG_DB +3 }),\
   "gold-sheen":     ({ AVG_WEIGHT -4, MAX_PD -2, MAX_PD -5, AVG_DB +4 }),\
   "silver-sheen":   ({ AVG_WEIGHT -4, MAX_PD -2, MAX_PD -5, AVG_DB +4 }),\
])

#define OBS_DESC ([\
"brown":        "The stone has a smooth, rich rust brown color, spread "    +\
                "evenly throughout the stone.",                              \
"mahogany":     "The stone is dark brown-red, with thin streaks of black "  +\
                "stretched throughout the stone giving it the appearance "  +\
                "of mahogany wood.",                                         \
"lizard-skin":  "It has an evenly distributed patch work of lighter and "   +\
                "darker grey-brown stone. The regular patter of differing " +\
                "colours gives the stone the look of a lizard's back.",       \
"flame-red":    "It is a beautiful deep orange-red color. The color is "    +\
                "quite evenly mixed into the glass with no trace of "       +\
                "imperfections.",                                            \
"jet-black":    "The glass is a mysterious deep black in color. One of "    +\
                "the purest types of obsidian, the dark black color comes " +\
                "from the trace amounts of magnetite mixed in with the "    +\
                "silica and cooled slowly for thousands of years below "    +\
                "the surface.",                                              \
"deep-green":   "The stone is a dark and deep green color, almost black. "  +\
                "It is the addition of trace amounts of copper and "        +\
                "magnetite that gives it this quality of coloring.",         \
"midnight-lace":"This stone looks to be made of black obsidian, mixed "     +\
                "together with streaks of very opaque glass. The streaks "  +\
                "were stretched thin and gently turned by the slow flow "   +\
                "of magma that formed the obsidian, creating a beautiful "  +\
                "lace-like pattern.",                                        \
"snowflake":    "The stone is mostly black, with larger patches of white "  +\
                "scattered across its surface. The white 'snowflakes' are " +\
                "quartz crystals that have devitrified from the original "  +\
                "obsidian over millions of years under tremendous pressure.",\
"rainbow":      "It flashes with all the colors of the rainbow as the "     +\
                "surface catches and reflects the available light.",         \
"gold-sheen":   "The stone has a light golden shine to its surface. The "   +\
                "sheen is due to millions of tiny air bubble trapped in the "  +\
                "glass and the with some trace amounts of feldspar.",        \
"silver-sheen": "The stone has muted gray reflection and almost looks "     +\
                "like piece of metal. A mix of various trace impurities "   +\
                "and millions of tiny air pockets trapped in the glass "    +\
                "are responsible for this appearance."                       \
])
                        
#define WEP_DESC ([\
"sword":    "This is an obsidian sword. The blade and handle are one "    +\
            "piece, formed from a long slab of obsidian, an edge has "    +\
            "been formed along the front and back of the blade. Fan "     +\
            "shaped chips have been expertly knocked from "     +\
            "each side of the blade to make a perfect edge. Where one "   +\
            "chipping meets the next, a small peak is formed, taken all " +\
            "together these peaks give the blade a ghastly, uneven "      +\
            "serration, it could no doubt cut through bone as easily as " +\
            "flesh. At the base of the blade the obsidian is narrowed "   +\
            "and rounded to form the handle, which has been wrapped "     +\
            "with dried mekillot gut for a better grip.",                  \
"axe":      "This is an obsidian battleaxe. The axe head is formed from " +\
            "a large block of obsidian, cleaved expertly, once on each "  +\
            "side forming a wedge shape, with glassy concave faces. The " +\
            "breaks come together to form a sharp edge, many times "     +\
            "sharper than even the best metal weapons. Mekillot gut has " +\
            "been used to permanently attach the axe head to a handle "     +\
            "crafted of bone and oak.",                                    \
"halberd":  "This is an obsidian halberd. It has a long, very thick, "    +\
            "bone handle, the animal it came from must have been "        +\
            "immense. Along the top of the handle a large obsidian "      +\
            "blade has been affixed with mekillot gut. The weapon's "     +\
            "edge is formed by knapping flakes of stone off along the "   +\
            "front side of the blade, making it sharper than a razor "    +\
            "and giving it an ugly, jagged serration.",                    \
"club":     "This is an obsidian club. It is made from what must have "   +\
            "been a gigantic block of obsidian. It has a rather "         +\
            "slender head that tapers to form a mekillot hide wrapped "  +\
            "handle. The obsidian has been chipped in a way not seen "    +\
            "outside the tablelands of Athas, four channels have been "   +\
            "carved into the head, the ridges between them forming "      +\
            "four rough, savage edges. This weapon would surely cut a "   +\
            "foe's flesh as easily as crush its bones.",                   \
"knife":    "This is an obsidian bladed knife. It has a long, thin "      +\
            "blade, with a cutting edge on the front and back. The "      +\
            "edges have been formed by chipping off flakes of obsidian "  +\
            "from both sides of blade, this has left a sharp, serrated "  +\
            "cutting edge."                                                \
])

string Hands  = "two-handed";
    
string Type     = "axe",
       Finish   = "gleaming",
       Stone    = "jet-black";

string Engraving = "Crafted by Kei, Master Smith of SaMorgan.";

/* Prototypes */
void     config_weapon(string type, string finish, string stone, string hands);
void     make_one_handed();
string   exa_engraving();
int      set_type(string type);
int      set_stone(string stone);
int      set_finish(string finish);
int      set_wep_hands(string hands);
int      set_engraving(string engraving);
string   query_material();

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
config_weapon(string type, string finish, string stone, string hands)
{
   float weight = itof(OBS_VALUES[stone][0]);
   int hit = OBS_VALUES[stone][1];
   int pen = OBS_VALUES[stone][2];
   
   Type = type;
   Finish = finish;
   Stone = stone;
   Hands = hands;
   
   add_adj(Finish);
   add_adj(Stone);
   set_name(WEP_NAME[Type]);
   set_short(Finish + " " + Stone + " obsidian " + WEP_NAME[Type][0]);
   
   set_long(BSN(WEP_DESC[Type]) +
            BSN(OBS_DESC[Stone]) +
            "The handle has been engraved.\n");

   if(Type == "knife")
   {
      /* Adjust weight, hit, and pen values for knife */
      weight = weight * 0.1;
      hit = ftoi(0.6 * itof(hit));
      pen = ftoi(0.6 * itof(pen));
      make_one_handed();
   }

   set_default_weapon(hit,
                      pen,
                      WEP_TYPE[Type],
                      OBS_DAMAGE_TYPE[Type],
                      W_BOTH, 0);
                      
   set_likely_dull(OBS_VALUES[Stone][3]);
   set_likely_break(OBS_VALUES[Stone][3]);
   
   add_prop(OBJ_I_WEIGHT, ftoi(weight * 1000.0));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit, pen)+random(300) + 4000);
   add_prop(OBJ_M_NO_SELL, "That weapon is much too valuable for me to buy.\n");
            
   if(Hands == "one-handed")
      make_one_handed();
}

void
make_one_handed()
{
   int new_pen = query_pen() - 5;
   int new_hit = query_hit() - 5;
   int new_wgt = ftoi(0.875 * itof(query_prop(OBJ_I_WEIGHT)));
   
   set_default_weapon(new_pen, new_hit, WEP_TYPE[Type], OBS_DAMAGE_TYPE[Type], W_ANYH, 0);
   add_prop(OBJ_I_WEIGHT, new_wgt);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(new_pen, new_hit)+random(600) + 4000);
}

public void
create_weapon()
{
   set_adj("obsidian");
   
   add_item( ({"engraving", "engravings", "handle", "haft"}), exa_engraving);
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
   if(!OBS_DAMAGE_TYPE[type])
      return 0;
   remove_name(Type);
   Type = type;
   return 1;
}

int
set_stone(string stone)
{
   if(member_array(stone, OBS_TYPES) < 0)
      return 0;
      
   Stone = stone;
   return 1;
}

int
set_finish(string finish)
{
   if(member_array(finish, FINISH_TYPES) < 0)
      return 0;
      
   Finish = finish;
   return 1;
}

int
set_engraving(string engraving)
{
   if(!strlen(engraving))
      return 0;
   Engraving = "Crafted by Kei for ";
   Engraving += engraving;
   return 1;
}

int
set_wep_hands(string hands)
{
   if(hands != "one-handed" && hands != "two-handed")
      return 0;
   
   Hands = hands;
   return 1;
}

string
query_material()
{
   return "obsidian";
}

string
query_recover()
{
   string rec = "";
   rec += "#tow_t#" + Type;
   rec += "#tow_f#" + Finish;
   rec += "#tow_s#" + Stone;
   rec += "#tow_h#" + Hands;
   rec += "#tow_e#" + Engraving;
   return MASTER + ":" + query_wep_recover() + rec + "#";
}

void
init_recover(string arg)
{
   string foobar;
   sscanf(arg, "%s#tow_t#%d#%s", foobar, Type, foobar);
   sscanf(arg, "%s#tow_f#%d#%s", foobar, Finish, foobar);
   sscanf(arg, "%s#tow_s#%d#%s", foobar, Stone, foobar);
   sscanf(arg, "%s#tow_h#%d#%s", foobar, Hands, foobar);
   sscanf(arg, "%s#tow_e#%d#%s", foobar, Engraving, foobar);
   init_wep_recover(arg);
   if(!config_weapon(Type, Finish, Stone, Hands) && !set_engraving(Engraving))
   {
      write("ERROR in init_recover: " + Type + Finish + Stone + Hands);
      TO->remove_object();
   }
}
