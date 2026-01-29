inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
    ::create_object();
    set_name("sail");
    set_adj("billowing");
    add_adj("white");
    set_long("A large piece of white canvas used as one of the many sails "+
      "found upon a sea-going vessel.\n");
    add_prop(OBJ_I_VALUE,72);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,5000);
}

string query_recover() { return MASTER; }
