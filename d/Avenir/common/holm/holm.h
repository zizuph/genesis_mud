// file name:        /d/Avenir/common/holm/holm.h
// creator(s):       Lilith, Oct '96
// revisions: 
// purpose:          Put defines and includes here that are needed
//                   in all the holm area files         
// note:             
// bug(s):           
// to-do:            

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* ADD_SKIN, etc */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* self-explanatory */

#define GET_ONE(x)   ((x) [random(sizeof(x))])

/* Area defines and connections */
#define CAVE       HOLM + "cave/"
#define JUNG       HOLM + "jungle/"
#define SHORE      HOLM + "shore/"
#define T_CAMP     HOLM + "t_camp/"

#define PJCON      PK + "w_path2"  /* Park - Jungle Connection */
#define SROOMS     ({ SHORE +"sh27", SHORE +"sh25",SHORE +"sh23", \
                      SHORE +"sh21", SHORE +"sh20",SHORE +"sh19", \
                      SHORE +"sh18", SHORE +"sh17",SHORE +"sh15" })

/* Where to find the monsters  */
#define HOLM_MON   HOLM + "mon/"

/* Where to find the objects */
#define HOLM_OBJ   HOLM + "obj/"

/* Keys and things */
#define KITCH_KEY  139900
#define HERB_KEY   139901
#define CAGE1_KEY  139902


