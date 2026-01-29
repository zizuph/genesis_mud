#include <stdproperties.h>

#define DT_SPECIAL	  0
#define DT_MAGICAL	  0
#define DT_IMPALE	  1
#define DT_SLASH	  2
#define DT_BLUDGEON	  4
#define DT_CRUSH	  4

#define DT_IMPACT	  8
#define DT_HEAT 	 16
#define DT_COLD 	 32
#define DT_ACID 	 64
#define DT_ELECTR	128
#define DT_ELECTRICITY	128
#define DT_VIBRATION	256
#define DT_RADIATION	512
#define DT_LIGHT	512
#define DT_VACUUM      1024

#define DT_NAMES ([ \
   0:"magical",	      1:"impale",      2:"slash",	 4:"crush",\
   8:"impact",	     16:"heat",	      32:"cold",	64:"acid",\
 128:"electricity", 256:"vibration", 512:"radiation", 1024:"vacuum"\
])

#define MAGIC_RES ([ \
    DT_MAGICAL : MAGIC_I_RES_MAGIC,  \
    DT_IMPACT  : MAGIC_I_RES_EARTH,  \
    DT_HEAT    : MAGIC_I_RES_FIRE,   \
    DT_COLD    : MAGIC_I_RES_COLD,   \
    DT_ACID    : MAGIC_I_RES_ACID,   \
    DT_ELECTR  : MAGIC_I_RES_ELECTRICITY, \
    DT_VIBRATION : MAGIC_I_RES_EARTH,\
    DT_LIGHT   : MAGIC_I_RES_LIGHT,  \
    DT_VACUUM  : MAGIC_I_RES_AIR     \
])
