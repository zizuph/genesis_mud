inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"


#define TP this_player()
void
create_object()
{
   set_name("branch");
   set_pname("branches");
   set_adj("small");
   set_long("The branch swings back and forth in the wind.\n");
   set_short("branch");
   set_pshort("branches");

    set_no_show();
   add_prop(OBJ_I_INVIS,1);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_M_NO_GET,1);
}


void
init()
{
    ::init();

   add_action("do_pull","pull");
}

int
do_pull(string str)
{
     if (str == "branch")
    {
  write("A trap door opens beneath you and you fall down it.\n");
   this_player()->move_living("into a hole","/d/Shire/common/island/cave");
 	say(QCTNAME(TP) + " pulls a " + " tree branch.\n");
        return 1;
    }
    return 0;
}
