
inherit "/std/object";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h"
#include <macros.h>

create_object()
{
set_short("strange ointment");
set_name("ointment");
set_adj("strange");
add_name("sw_ent_quest_ointment");
set_long(break_string(
   "This is a strange magical ointment.  You wonder what it"
    +" could do.\n",75));

}

init()
{
    ::init();
    add_action("oint_add_func","rub");
}

int
oint_add_func(string str)
{
    NF("Rub what on where?\n");
    if(!strlen(str))
        return 0;

    if(!((str=="ointment on hands")||("hands with ointment")))
    {
        write("You rub the strange ointment on your hands.  You can feel"
		+" them tingling.\n");
	say(QCTNAME(TP)+" rubs a strange ointment on "+TPOS+" hands.\n");
	TP->add_prop(OINTMENT_ON_MY_HANDS,1);
	set_alarm(60.0,0.0,"remove_oint_func",TP);
	return 1;
    }
    return 0;
}

void
remove_oint_func(object ob)
{
    remove_prop(ob);
}
