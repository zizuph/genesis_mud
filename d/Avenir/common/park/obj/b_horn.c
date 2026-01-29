// file name: b_horn.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose: Bicorn horn, for a quest
// note:
// bug(s):
// to-do:

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
        set_name("horn");
        set_adj("bicorn");
        set_long("This is a broken bicorn horn.  It is"
                +" ebony black, and it radiates with a tangible"
                +" sense of dark powers.\n");
        add_prop(OBJ_I_VALUE, 500);
}

