inherit "/std/object";

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

/*
c.       o.-.o       o.-.o
(_"      ((^))       ((^))
|\_>    0}._.{0     0) _ (0
\___>    O/ \O       O/ \O
*/

string *tpic = ({
" o.-.o    ",
" ((^))    ",
"0}._.{0   ",
" O/ \\O    ",
"          "});

string
add_teddy(string text)
{
    int t;
    string *strs = explode(text, "\n");   
    int size = sizeof(strs);
    if (size < 5) 
    {
	strs += ({"","","","",""})[0..(4-size)];
	size = 5;
    }
    for (t = 0; t < 4; t++)
	strs[t] = tpic[t]+strs[t];
    for (t = 4; t < size; t++)
	if (strs[t] != "")
	    strs[t] = tpic[4] + strs[t];
    return implode(strs,"\n")+"\n";
}

create_object()
{
  set_name("teddybear");
  add_name(({"bear","teddy", "_glindor_teddy_"}));
  set_short("teddybear");
  set_long(add_teddy("A cute furry teddybear.\n"));
  add_cmd_item(({"teddybear","bear","teddy"}),"hug","@@hug");
  add_cmd_item(({"teddybear","bear","teddy"}),"cuddle","@@cuddle");
}

string 
hug()
{
    say(QCTNAME(TP)+" hugs the teddybear. "+capitalize(TP->query_pronoun())+
	" looks very relieved.\n");
    return "You hug the teddybear. Everything feels much better now.\n";
}

string 
cuddle()
{
    say(QCTNAME(TP)+" cuddles the teddybear. "+capitalize(TP->query_pronoun())+
	" looks very relieved.\n");
    return "You cuddle the teddybear. Everything feels much better now.\n";
}

init()
{
    ::init();

    if (this_player()->query_real_name() != "glindor") return;
    add_action("do_shug","teddyshug");
    add_action("do_hug", "teddyhug");
    add_action("do_whug", "teddywhug");
    add_action("do_bhug", "teddybhug");
    add_action("do_comf","teddycomf");
}

int
do_shug(string str)
{
    object ob;
    notify_fail("Teddyshug who?\n");
    if (!str || !(ob = find_player(str)))
	return 0;
    ob->catch_msg("\n"+
"             #######\n"+
"         ####    ##\n"+
"       ##       ##\n"+
"     ###\n"+
"    ###\n"+
"    ###\n"+
"    ###      ##             #             #               ##\n"+
"    ###     ######        ####          ###             ######\n"+
"  #####    ##########   #######        ####           ############\n"+
" #  ###  ###   #####        ####       ####          ##     #####\n"+
"    ### ##      ###          ###       ####        ##         ###\n"+
"    ####       ####          ###       ###        #          ###\n"+
"    ###        ####          ###       ###       ##          ###\n"+
"    ###        ####          ##       ####      ####         ###\n"+
"    ###        ####          ##      # ###       ####       ####\n"+
"    ###        ####         ###    ##  ###    #  ######    # ###\n"+
"   ####        ####        ###### #   #####  #     ########  ###\n"+
"   #######     ####           ####      #####         ###    ###\n"+
"      ##       ####            #          #           #      ###\n"+
"               ####                             #            ###\n"+
"               ###                             #             ###\n"+
"              ###                             ###           ###\n"+
"              ##                             ######      ####\n"+
"            ###                               ###########\n"+
"           #\n"+
		  "\n");
    write(capitalize(str) + " got a big hug.\n");
    return 1;
}

int
do_comf(string str)
{
    object ob, t;
    notify_fail("Teddycomf who?\n");
    if (!str || !(ob = find_player(str)))
	return 0;

    t = present("_glindor_teddy_", ob);

    if (!objectp(t))
	{
	    seteuid(getuid());
	    t = clone_object("/d/Roke/glindor/teddy");
	    ob->catch_msg("A cute teddybear enters. It climbs up in your lap "+
			  "and gives you a comforting hug.\n");
	    t->move(ob); 
	    write("A teddybear was sent to " + capitalize(str) + ".\n");
  	}
    else
	{
	    ob->catch_msg("The teddybear gives you a comforting hug.\n");
	    write(capitalize(str) + " got a hug from the teddybear.\n");
	}
    return 1;
}

int
do_hug(string str)
{
    object ob;
    notify_fail("Teddyhug who?\n");
    if (!str || !(ob = find_player(str)))
	return 0;

    ob->catch_msg("A cute teddybear enters. It climbs up in your lap and "+
		  "gives you a hug. Then it climbs down and stumbles away.\n");
    write("A teddyhug was given to " + capitalize(str) + ".\n");
    return 1;
}

int
do_whug(string str)
{
    object ob;
    notify_fail("Teddywhug who?\n");
    if (!str || !(ob = find_player(str)))
	return 0;

    ob->catch_msg(add_teddy(break_string(
	"A cute teddybear appears, cheering. It dances around you "+
	"for a while, and then it gives you a big welcoming hug. "+
	"Then it disappears, as fast as it came.\n",60)));
    write("A teddywhug was given to " + capitalize(str) + ".\n");
    return 1;
}

int
do_bhug(string str)
{
    object ob;
    notify_fail("Teddybhug who?\n");
    if (!str || !(ob = find_player(str)))
	return 0;

    ob->catch_msg(add_teddy(break_string(
	"A sad-faced teddybear arrives. It climbs up in your lap, "+
	"and with a soft sob it gives you a goodbye hug. "+
	"Reluctantly it climbs down, and walks away slowly. "+
	"Just before it disappears out of sight it turns around, "+
	"looks at you, and waves sadly.\n",60)));

    write("A teddybhug was given to " + capitalize(str) + ".\n");
    return 1;
}

enter_env(to, from)
{
    ::enter_env(to,from);

    if (!interactive(to)) return;
    
    to->add_subloc("teddybear", this_object());
}

leave_env(from, to)
{
    ::leave_env(to, from);
    
    if (!interactive(from)) return;

    from->remove_subloc("teddybear");
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string apa;
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) 
       return "";

    if (subloc != "teddybear") 
	return "";

    if (for_obj == on)
	apa = "your";
    else
	apa = on->query_possessive();

    return "There is a cute teddybear sitting in " + apa + " lap.\n";
}

