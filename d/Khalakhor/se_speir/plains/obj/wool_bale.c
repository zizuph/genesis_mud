//
// Bale of Wool - sheared from a sheep in the plains pasture
//
// Zima May 20, 1998 - taken from Argos & modified for color
//
inherit "/std/object";
#include <stdproperties.h>
#include "obj.h"
 
string color="white";
string query_color()       { return color; }
void   set_color(string c)
{
   if (stringp(color)) remove_adj(color);
   color=c;
   set_short("bale of "+color+" wool");
   set_pshort("bales of "+color+" wool");
   set_long(
      "It is a large bale or wad of "+color+ " wool recently sheared from "+
      "a sheep.\n");
   add_adj(color);
}
 
void create_object() {
   set_name("wool");
   add_name(({"bale","bale of wool",KHAL_WOOL}));
   set_color("white");
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_VALUE,  20);
}
