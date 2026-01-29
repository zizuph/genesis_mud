/*  
    Lava engine for pickaxe quest

    Made by: Maelstrom, 2016/05

*/


inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


int cleaned = 0;

create_object()
{
    set_name(({"box", "dusty box", "old box", "dusty old box", "lava_engine_quest"}));

    set_short("@@short_desc@@");
    set_long("@@describe@@");    


	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
}

string
short_desc()
{
    if (cleaned)
    {
        return "miniature lava engine";
    }

    return "dusty old box";
}

string
describe(string which = "")
{
    string  desc = "A VERY dusty old box.";

    desc += which;

    if (cleaned)
    {
        desc = "The fabled miniature lava engine, or so the engraving claims.";
    }

    //desc = "You find no " + which + ".\n";

    return desc + "\n";
}
int
do_clean(string str)
{

    string * data;
    string item;
    string place;

        
    if (!str || cleaned)
    {
        notify_fail("clean what?\n");
        return 0;
    }

    data = explode(str, " from ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        item = data[0];
        place = "";
    }

    if (item == "box" || item == "dust")
    {
        this_player()->catch_msg("You dust the old box, only to find, that under the dust, " +
                "there is, a box. Oh wait, there's also an engraving, it reads: 'miniature lava engine'.\n");
        cleaned = 1;
        return 1;
    }

    notify_fail("clean what?\n");
    return 0;    
}

void
init()
{
    ::init();
    add_action(do_clean, "clean");
    add_action(do_clean, "dust");
    add_action(do_clean, "blow");
    add_action(do_clean, "remove");
    add_action(do_clean, "brush");
}