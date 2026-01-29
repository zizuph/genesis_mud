/**********************************************************************
 * - seamstress.h                                                   - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
#pragma strict_types

#define CLOTHING_PATH          ("/std/armour")
#define OBTAIN_COST(item)      (item->query_prop(OBJ_I_VALUE) *  4)
#define MODULE_CLOTHING        (   0)
#define SEAMSTRESS_S_CLIENT    ("_seamstress_s_client")

#define SEAMSTRESS_FABRICS /*  default fabric's modifiers   */ \
([/* Fabrics                  AC/WP   DULL  WEIGHT  COST */ \
  "chemise"               :({  0.65,  3.00,  0.40,  2.00 }),\
  "cotton"                :({  0.65,  2.00,  0.60,  1.00 }),\
  "taffeta"               :({  0.65,  2.00,  0.60,  1.00 }),\
  "silk"                  :({  0.70,  1.90,  0.50,  6.00 }),\
  "satin"                 :({  0.85,  1.50,  0.80,  7.00 }),\
  "velvet"                :({  0.85,  1.50,  0.80,  5.00 }),\
  "samite"                :({  0.95,  1.50,  0.90,  6.00 }),\
  "brocade"               :({  0.95,  1.50,  0.90,  6.00 }),\
  "corduroy"              :({  1.00,  1.00,  1.00,  3.00 }),\
  "fleece"                :({  1.00,  1.00,  1.00,  4.00 }),\
  "wool"                  :({  1.00,  1.00,  1.00,  4.00 }),\
  "felt"                  :({  1.00,  1.00,  1.00,  4.00 }),\
  "leather"               :({  1.00,  1.00,  1.00,  6.00 }),\
])

#define SEAMSTRESS_CLOTHING  /* default clothing configurations   */ \
([                     /* TYPE      AC    IM SM BM  VOLUME */ \
  "cap"                :({A_HEAD  , 10, ({-2, 4,-2}),  400 }),\
  "veil"               :({A_HEAD  , 10, ({-2, 4,-2}),  400 }),\
  "cap"                :({A_HEAD  , 10, ({-2, 4,-2}),  400 }),\
  "beret"              :({A_HEAD  , 10, ({-4, 6,-2}),  800 }),\
  "fedora hat"         :({A_HEAD  , 10, ({-4, 6,-2}),  800 }),\
  "plush hat"          :({A_HEAD  , 10, ({-4, 6,-2}),  800 }),\
  "charmeuse hat"      :({A_HEAD  , 10, ({-4, 6,-2}),  800 }),\
  "scarf"              :({A_NECK  , 10, ({ 2, 2,-4}),  400 }),\
  "shirt"              :({A_TORSO , 15, ({-2, 4,-2}),  400 }),\
  "blouse"             :({A_TORSO , 15, ({ 2, 2,-4}),  400 }),\
  "vest"               :({A_TORSO , 15, ({ 2, 2,-4}),  400 }),\
  "vest"               :({A_TORSO , 15, ({ 2, 2,-4}),  400 }),\
  "gloves"             :({A_HANDS , 12, ({ 2, 2,-4}),  500 }),\
  "shoes"              :({A_FEET  , 12, ({ 2, 2,-4}),  500 }),\
  "sandals"            :({A_FEET  , 12, ({ 2, 2,-4}),  500 }),\
  "slippers"           :({A_FEET  , 12, ({-4, 6,-2}),  500 }),\
  "button shoes"       :({A_FEET  , 15, ({-4, 6,-2}),  500 }),\
  "skirt"              :({A_BODY  , 20, ({ 2, 2,-4}),  500 }),\
  "short skirt"        :({A_BODY  , 20, ({ 2, 2,-4}),  500 }),\
  "long skirt"         :({A_BODY  , 20, ({ 2, 2,-4}),  500 }),\
  "pants"              :({A_LEGS  , 22, ({ 2, 2,-4}),  500 }),\
  "chaps"              :({A_LEGS  , 22, ({-4, 6,-2}),  500 }),\
  "leggings"           :({A_LEGS  , 22, ({ 0, 0, 0}),  500 }),\
  "trousers"           :({A_LEGS  , 22, ({ 0, 0, 0}),  500 }),\
  "gown"               :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "dress"              :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "short dress"        :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "long dress"         :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "shift"              :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "cloak"              :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "cape"               :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
  "mantle"             :({A_BODY  , 25, ({ 2, 2,-4}),  400 }),\
])

mapping seamstress_clothing = ([]), /* clothing attributes and options */
        seamstress_design = ([]);   /* information about the order     */
object  seamstress_repository;      /* produced clothing               */
int     seamstress_crafts =    0;   /* flag if the seamstress is busy  */
