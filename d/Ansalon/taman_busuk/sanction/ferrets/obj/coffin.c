
/*
 *coffin.c
 *Used in a ferret quest to find the 'missing' dead ferrets.
 *
 *Ares July 2004
 */

inherit "/std/object";

int did_open;

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "../defs.h"

void
init()
{
    ::init();
    add_action("open","open");
    
}

void
create_object()
{
    set_name("coffin");
    add_name("_quest_coffin_");
    set_adj("small");
    add_adj("wooden");

    set_short("small ferret coffin");
    set_pshort("small wooden coffins");
    set_long("A small wooden coffin box, too small for even a gnome to fit "+
       "in. This one must be for something smaller, like a rodent or a bird. "+
       "Someone has carved the word 'Ixi' on the lid. You "+
       "can open the lid if you want to see what's inside. \n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);

}

int
open(string str)
{

	object ob;
	
    notify_fail("Open what?\n");
    if((!str) || (!strlen(str)) || (str != "lid"))
        return 0;
        
    if(did_open)
    {
        write("The coffin lid is already open. \n");
        return 1;
    }
        
    did_open=1;

    write("You open the lid to the coffin. A mummified corpse of a long dead "+
        "ferret pops out at you!! It lands peacefully on the ground. \n");
    say(QCTNAME(TP)+" opens the lid to the coffin and a mummified ferret "+
        "flys out!\n");

    reset_euid();

    clone_object("/d/Ansalon/taman_busuk/sanction/ferrets/obj/dead_ferret.c")->move(environment(this_player()));
    
    return 1;
}