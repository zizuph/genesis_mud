/*
 * std/barrel.c
 *
 * A standard breakable barrel that clones its content
 * when broken.
 *
 * Put this in the room you want it in:

void
reset_room()
{
    if(!present(o))
    {
        o = clone_object(ALT_STD + "barrel.c");
        o->Short_d("wodden barrel");
        o->set_content(({ALT_OBJ + "torch.c",ALT_OBJ + "torch.c" }));
        o->move(this_object());
    }
    o->make_whole();
}

 *
 * by Azazel 2002
 */
 
inherit "/std/object.c";
#include "/d/Cirath/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

int break_it(string str);
int broken;
string *cont, *content;

string long_desc();
string short_desc();

void set_content(string *cont) { content = cont; }

string * query_content() { return content; }


void make_whole() { broken = 0; }

void
create_barrel()
{
}

public nomask void
create_object()
{
    create_barrel();
    set_name("barrel");
    set_adj("wooden");
    set_short(&short_desc());
    set_long(&long_desc());
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT,50000);
    add_prop(OBJ_I_VOLUME,20000);
}

void
init()
{
    ::init();
    add_action ("break_it", "break");
}

string
long_desc()
{
    if (broken == 0)
    {
        return("A wooden barrel. Its nailed shut. There might be" +
            " something inside it.\n");
    }
    return("A wooden barrel. Its broken and its content lies scatterd" +
        " all over the floor.\n");
}

string
short_desc()
{
    if (broken == 0)
    {
        return("wooden barrel");
    }
    return("broken wooden barrel");
}

int
break_it(string str)
{
    int i;
    
    notify_fail("Break what?\n");
    if (str == "barrel")
    {
    	if (broken == 1)
    	{
    	    notify_fail("The barrel is already broken!\n");
    	    return 0;
    	}
    	broken = 1;
    	
        for (i = 0; i < sizeof(content); i++)
        {
            clone_object(content[i])->move(environment(this_object()));
        }
     	write("You kick the barrel hard. It breaks and its content" +
    	    " scatters all over the floor.\n");
        say(QCTNAME(this_player()) + " kicks a barrel crushing" +
            " it. Bits fly everywhere.\n");   
        return 1;
    }
    return 0;
}