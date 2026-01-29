/* Include file for making armour. Included into bubba.c, the blacksmith
   of Gelan. Defines and important global variables.
   Figures partially based on those from Elessar's blacksmith in Gondor.

   Coded by Maniac 9/6/95
*/

#define VOL_STAND 180  /* Used to calculate the volume  */
#define WGT_STAND 180  /* Used to calculate weight */
#define ARMOUR_GREED   200   /* price = value * greed / 100 */

/* Armour weight percentage multipliers */
mapping
armour_metal_weight_mult = ([ "silver" : 105,
                              "brass" : 85,
                              "gold" : 193,
                              "bronze" : 89,
                              "iron" : 79,
                              "steel" : 69 ]); 

/* Construction weight percentage multipliers */
mapping armour_const_weight_mult = 
                           (["plate" : 130,
                             "tower" : 150,
                             "great" : 130 ]);

/* Quality rating for metals */
mapping
armour_metal_rating = ([ "silver" : 16,
                         "brass" : 10,
                         "gold" : 19,
                         "bronze" : 12,
                         "iron" : 14,
                         "steel" : 22 ]);

/* Quality ratings for constructions */
mapping
armour_const_rating = (["plate" : 13 ]); 

mapping
shield_const_rating = ([ "tower" : 13 ]);

mapping
helm_const_rating = (["great" : 13]);


/* Size multipler for differeng kinds of armour */
mapping
armour_type_size_mult = ([ "body-armour" : 100,
                           "shield" : 25,
                           "helm" : 35,
                           "greaves" : 45,
                           "bracers" : 45 ]);
 
mapping
armour_type_article = ([ "body-armour" : "a ",
                         "shield" : "a ",
                         "helm"   : "a ",
                         "greaves" : "",
                         "bracers" : "" ]);

/* Armour types */
mapping
armour_type_at = ([ "body-armour" : A_TORSO,
                    "shield" : A_SHIELD,
                    "helm" : A_HEAD,
                    "greaves" : A_LEGS,
                    "bracers" : A_ARMS ]);



/* Function to calculate the ac of made armour, given its the type 
   of armour, the metal and the construction. */
int
query_made_armour_ac(string a, string m, string c)
{
  if ((a == "body-armour") || (a == "greaves") ||
      (a == "bracers")) 
       return (armour_metal_rating[m] +
               armour_const_rating[c]);
  else if (a == "shield")  
       return (armour_metal_rating[m] +
               shield_const_rating[c]);
  else if (a == "helm") 
       return (armour_metal_rating[m] +
               helm_const_rating[c]);
}


/* Function to calculate the made armour value */
int
query_made_armour_value(string a, string m, string c)
{
    return F_VALUE_ARMOUR(query_made_armour_ac(a, m, c));  
}

