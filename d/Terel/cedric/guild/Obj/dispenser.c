#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/minstrels/dark/guild_defs.h"

string THIS_PED;

void
init()
{
    add_action("do_dispense", "retrieve");
    
}


/*
 * Note that the object which clones this had better call set_ped()
 * with the type of instrument as an argument.
 */
void
create_object()
{
    reset_euid();
    set_name("dispenser");
    add_prop(OBJ_M_NO_GET, "You decide that to remove the object would be in "
    + "the worst possible taste.\n");
    set_adj("cycle");
}

int
do_dispense(string str)
{
    object  ob;
    
    

    
    if (!str) return 0;    
    if ((str == "scroll") || (str == "Scroll")) {
       if (!TP()->query_special_title())
       {
          write("Hey!  You are not a member of the Cycle!\n");
          return 1;
       }
       else
       {
          ob=clone_object("/d/Terel/cedric/guild/Obj/scroll.c");
          ob->move(TP());
          write("The muses provide you with a scroll.\n"); 
	  return 1;  
       }
    }
    if ((str == "tablet") || (str == "Tablet")) {
       if (!TP()->query_special_title())
       {
          write("Hey!  You are not a member of the Cycle!\n");
          return 1;
       }
       else
       {
          ob=clone_object(GUILDOBJ + "scroll.c");
          ob->move(TP());
          write("The Sirens provide you with a tablet.\n");
          return 1;
       }      
    }
    write ("What do you wish to retrieve?\n");
    return 1;
}