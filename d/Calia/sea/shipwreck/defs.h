/*
 *   defs.h
 * 
 * Main definitions file for the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 */

#include "../defs.h"

/* Basic directories and files */
#define SHIPW  "/d/Calia/sea/shipwreck/"

#define WRECKU (SHIPW + "upper/")
#define WRECKM (SHIPW + "middle/")
#define WRECKL (SHIPW + "lower/")

#define OBJ     (SHIPW + "objects/")
#define ARM     (WATER + "armours/")
#define WEP     (WATER + "weapons/")
#define NPC     (WATER + "creatures/")
#define SCROLLS (OBJ   + "scrolls/")

#define HE(x)   x->query_pronoun()
#define HIS(x)  x->query_possessive()
#define HIM(x)  x->query_objective()

#define RONE(x)        x[random(sizeof(x))]

/* Props */                                             
#define OBJ_I_SHIPWRECK_EQUIPMENT  "_obj_i_shipwreck_equipment"
