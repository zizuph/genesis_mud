inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"

#define TP this_player()

void
create_object()
{
    set_name(({"vines","green vines"}));
    set_pname("vines");
    set_adj("green");
    set_long("These vines cover the rock face.\n");
    set_short("long green vines");

    add_prop(OBJ_I_VALUE, 100);
    set_no_show();
    add_prop(OBJ_M_NO_GET,1);

}


void
init()
{
    ::init();

    add_action("do_pull","pull");
    add_action("do_open","open");
    add_action("do_entere","enter");
}

int
do_pull(string str)
{
    if (str == "vines" || str == "green vines")
    {
        write("You pull the vines and enter a the hole hidden "
           +  "behind it.\n");
  this_player()->move_living("through something.","/d/Shire/common/island/f6");
        say(QCTNAME(TP) + " pulls " + " something and disappears.\n");
        return 1;
    }
    notify_fail("Pull what? Your what??\n");
    return 0;
}

/***********************************************************/
int
do_open(string str)
{
     if (str == "vines" || str == "green vines")
     {
        write("You pull the vines and enter a the hole hidden "
           +  "behind it.\n");
  this_player()->move_living("through something.","/d/Shire/common/island/f6");
        say(QCTNAME(TP) + " pulls " + " something and disappears.\n");
        return 1;
    }
    notify_fail("Pull what? Your what??\n");
    return 0;
}
/***********************************************************/
int
do_squeeze(string str)
{
     if (str == "vines" || str == "green vines")
     {
        write("You pull the vines and enter a the hole hidden "
           +  "behind it.\n");
  this_player()->move_living("through something.","/d/Shire/common/island/f6");
        say(QCTNAME(TP) + " pulls " + " something and disappears.\n");
        return 1;
    }
    notify_fail("Pull what? Your what??\n");
    return 0;
}
