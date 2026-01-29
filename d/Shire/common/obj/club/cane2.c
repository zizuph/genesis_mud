// The guild object of the Old Fogey's Club...Dunstable 12/94

#pragma save_binary;

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"


void
create_object()
{
    set_name("cane");
    add_name("_new_fogey_cane");
    add_adj(({"old","gnarled"}));
    set_short("old gnarled cane");
    set_long("This old gnarled cane is made of the sternest of oak, "+
      "which withstands the test of time very well.  The epitaph "+
      "'fhelp' has been etched into the side.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"The cane grips your hand and will not "+
      "let go.\n");
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }
