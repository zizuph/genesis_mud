/* stone.c: The thing that causes the tell effect. */
inherit "/std/object";
#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#define RINGSIDE CALATHIN_DIR+"obj/ringside.c"
#include <options.h>

public void
create_object()
{
    set_name("stone");
    add_name("test");
    set_short("small stone");
    set_long("A small stone.\n");
    add_prop(OBJ_I_NO_GET,1);
    set_no_show();
    enable_commands();
    seteuid(getuid(this_object()));
}

void catch_msg(mixed str, object obj)
{
    int i;

    if (stringp(str))
    {
        str = "STADIUM: " + str;
    }
    else if (pointerp(str))
    {
        for (i = 0; i < sizeof(str); i++)
        {
            if (strlen(str[i]))
            {
                str[i] = "STADIUM: " + str[i];
            }
        }
    }
    tell_room(RINGSIDE, str);
}

int
query_option(int opt)
{
  if(opt == OPT_GAG_MISSES) return 1;
}

