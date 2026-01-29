//
// A gold platter - used in rites
//
// Zima 5/28/98
//
inherit "/std/container";
#include <stdproperties.h>
#include "defs.h"
 
void create_container()
{
   set_name("platter");
   add_name(SR_GPLATTER);
   set_short("gold platter");
   set_long("It is an ornate platter made of gold, engraved with shamrocks "+
            "around the rim and three interlocked circles in the center.\n");
   add_adj(({"ornate","gold"}));
   add_prop(CONT_I_RIGID,1);
   add_prop(CONT_I_ATTACH,1);
   add_prop(CONT_I_MAX_WEIGHT,1000);
   add_prop(CONT_I_MAX_VOLUME,1000);
   add_prop(OBJ_I_VALUE,150);
}
