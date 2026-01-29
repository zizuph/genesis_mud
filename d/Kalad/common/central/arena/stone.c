/* stone.c: The thing that causes the tell effect. */
inherit "/std/object";
#include "/d/Kalad/defs.h"
#define RINGSIDE "/d/Kalad/common/central/arena/sit"
#include <options.h>

void
create_object()
{
    set_name("stone");
    add_name("test");
    set_short("small stone");
    set_long("A small stone.\n");
    add_prop(OBJ_I_NO_GET,1);
    enable_commands();
    set_no_show();
    seteuid(getuid(this_object()));
}

int
inner_circle(object ob)
{
    string st;
    if(objectp(E(ob)))
    {
        sscanf(file_name(E(ob)),"/d/Kalad/common/central/arena/%s_circle",st);
        if(st == "inner")
            return 1;
    }
    return 0;
}


void catch_msg(mixed str, object obj)
{
    int i;
    object *viewers;
    viewers = users();
    if (stringp(str))
    {
        str = "ARENA: " + str;
    }
    else if (pointerp(str))
    {
        for (i = 0; i < sizeof(str); i++)
        {
            if (strlen(str[i]))
            {
                str[i] = "ARENA: " + str[i];
            }
        }
    }
    viewers = filter(viewers,inner_circle);
    viewers->catch_msg(str);
}
