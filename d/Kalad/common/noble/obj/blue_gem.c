inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("gem");
    set_adj("sparkling");
    add_adj("blue");
    set_short("sparkling blue gem");
    set_long("This is a big, blue gem that sparkles in the light. "+
    "You are not sure what kind of gem it is, but it looks very "+
    "valuable, since its so big!\n");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,500);
}

