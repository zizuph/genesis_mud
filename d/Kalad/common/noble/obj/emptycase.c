inherit "/std/object";
#include "/d/Kalad/defs.h"
/* sarr */

object ob;

void
create_object()
{
    set_name("case");
    set_adj("glass");
    set_short("glass case");
    add_name("_empty_");
    set_long("This is a wooden table with a glass case over it. "+
    "Underneath the glass you see an artifact being displayed. A"+
    " gold plaque is placed under it.\n"+
    "The glass case contains:\n"+
    "   Nothing.\n");
    seteuid(getuid()); 
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
}

