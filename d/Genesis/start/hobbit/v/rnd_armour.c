/*
 *  rnd_armour.c
 *    A random kind of armour
 */

#pragma save_binary

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

#define MY_A_NAME ({"jacket","shirt","shoes","hat","ring","foot"})
#define MY_A_PNAME ({"jackets","shirts","shoes","hats","rings","foots"})
#define MY_A_ADJ  ({"green","yellow","old","dented","iron",({"fluffy",\
                 "rabbits"})})
#define MY_A_SHORT ({"green jacket", "yellow shirt", "pair of old shoes",\
                     "dented hat", "iron ring", "fluffy rabbits foot"})
#define MY_A_PSHORT ({"green jackets", "yellow shirts", "pairs of old shoes",\
                      "dented hats", "iron rings", "fluffy rabbits feet"})
#define MY_A_TYPE ({A_BODY,A_TORSO,A_FEET,A_HEAD,A_L_FINGER,A_R_FINGER})
#define MY_A_MAX    ({   4,   4,   3,   2,   3,   3 })
#define MY_A_WEIGHT ({ 991, 342, 685, 360, 151, 224 })
#define MY_A_VOLUME ({1023, 430, 688, 413, 127, 220 })
#define MY_A_VALUE  ({  56,  12,  39,  27,  40,  17 })

void
create_armour()
{
   int i, max, type;

   i = random(sizeof(MY_A_NAME));

   set_name(MY_A_NAME[i]);
   set_pname(MY_A_PNAME[i]);
   set_short(MY_A_SHORT[i]);
   set_pshort(MY_A_PSHORT[i]);
   set_adj(MY_A_ADJ[i]);
   set_long("The " + MY_A_SHORT[i] + " is used, but still looks pretty normal.\n");
    
/*   Keep the armour well within the rules of found/bought armours
 *   These settings guarantee a simply bad armour. A heck, better
 *   any armour than no armour at all :-)...
 */
   set_default_armour(random(MY_A_MAX[i]) + 1, MY_A_TYPE[i], 0, 0);

   add_prop(OBJ_I_WEIGHT,MY_A_WEIGHT[i]);
   add_prop(OBJ_I_VOLUME,MY_A_VOLUME[i]);
   add_prop(OBJ_I_VALUE,MY_A_VALUE[i]);
}