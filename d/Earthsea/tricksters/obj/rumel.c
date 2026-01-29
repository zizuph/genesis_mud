inherit "/std/object";

#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

string color="gray";

void create_object()
{
 set_name("rumel");
 add_name("_trickster_rumel_");
 set_long("@@long_desc");
 set_adj(color);
 add_prop(OBJ_M_NO_DROP,"Dropping rumel? Shame on you!!!\n");
}

void set_color(string clr)
{
 remove_adj(color);
 color=clr;
 set_short(0);
 set_adj(color);
}

string get_color() {return color;}

string long_desc()
{
 return "This is scarf made of "+color+" silk. It is used by "+
   "Tricksters to strangle their victims. Silk looks sturdy enough "+
   "to break someone's neck.\n";
}

void update_level() {set_color(ENV(TO)->query_rumel_color());}

