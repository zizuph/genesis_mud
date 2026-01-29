// file name: ~Avenir/common/dark/obj/psource
// creator(s): Denis
// revision history: Kazz 5/95: allowed 'put source in HOLE'
// purpose: Open rock where the sacrificail hammer lies - for imp quest.
// note:
// bug(s):
// to-do:

inherit "/std/object";
#include "/d/Avenir/common/dark/dark.h"

create_object()
{
    set_name("crystal");
    add_name("piece");
    add_name("source");
	add_name("_avenir_Source_gives_light_");
    set_adj("small");
    add_adj("shining");
    add_adj("round");
    set_short("small shining crystal");
    set_long("It is a very small perfectly shaped crystal which has "+
	     "a faint glow about it. This glow isn't enough to light "+
	     "your way though.\n");
}

init()
{
    ::init();
    add_action("attach_fun","attach");
    add_action("attach_fun","place");
    add_action("attach_fun","put");
    add_action("attach_fun","apply");
    add_action("attach_fun","insert");
}

int attach_fun(string str)
{
    object rock;
    
    rock=present("_Unterdark_rock",environment(TP));
    
    if(query_verb()=="attach"||query_verb()=="apply")
        NF(capitalize(query_verb())+" what to where?\n");
    else
        NF(capitalize(query_verb())+" what in where?\n");

    if(str&&parse_command(str,({}),
       " 'crystal' / 'piece' / 'source' [on] [in] [upon] [to] [at] "+
       "[rock] [stone] [hole]")&&rock)
    {
	rock->add_shining_piece();
        remove_object();
        return 1;
    }
}

set_destroy()
{
    set_alarm(6000.0,0.0,"self_destruct");
}

self_destruct()
{
    if(interactive(environment(this_object())))
        environment(this_object())->catch_msg("The shining crystal breaks into pieces.\n");
    remove_object();
}

