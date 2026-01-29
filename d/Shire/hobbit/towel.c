#pragma save_binary

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

int do_dry(string str);

void
create_object()
{

     set_short("plush towel");
     set_name("towel");
     add_adj(({"plush"}));
     set_long("The plush towel is soft and comfortable, very "+
     "absorbent.  It has been dyed a deep shade of royal blue.\n");

     add_prop(OBJ_I_WEIGHT, 125 + random(100));
     add_prop(OBJ_I_VOLUME, 100 + random(50));
     add_prop(OBJ_I_VALUE, 0);

}

void
init()
{
    ::init();
    add_action("do_dry","dry");
}

int
do_dry(string str)
{
   if(str != "myself")
   {
     write("Dry whom? Yourself?\n");
     return 1;
    }

    if(!TP->query_prop("i_am_wet"))
    {
      write("But you are not even wet!\n");
       return 1;
    }
 
     TP->remove_prop("i_am_wet");
     write("You dry yourself off with the plush blue towel.\n");
     say(QCTNAME(TP) + " dries "+HIM_HER(TP)+"self off with the plush blue towel.\n");
     return 1;

}