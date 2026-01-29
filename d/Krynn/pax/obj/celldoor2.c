
inherit "/std/door";

#include "../local.h"
#include <macros.h>

#define  TP               this_player()
#define  TO               this_object()
#define  E(ob)            environment(ob)
#define  ELF_CAMP_QUEST   "_elf_camp_quest"

int open_door(string what);

create_door()
{
    set_door_id("celldoor");
    set_pass_command(({ "e", "east" }));
    set_door_desc("These are strong oaken door, reinforced by steel bars.\n");
    set_door_name(({ "door", "wooden door" }));
    set_other_room(PTHARKAS + "ground_level/cell");
    
    set_open(0);
}

void
init()
{
    ::init();
    add_action(open_door, "open");

}

int 
open_door(string what)
{
    if ( what == "door" || what == "wooden door" || what == "east door" )
    {
        if ( TP->query_prop(ELF_CAMP_QUEST) )
        {
            if ( query_open() == 0 )
            {
                write("You open the wooden door.\n");
                say(QCTNAME(TP) + " opens the wooden door.\n", TP);
                do_open_door("");
                other_door->do_open_door(check_call(open_mess[1]));
                return 1;
            }
            else 
            {
                write("The door is already open.\n");
                return 1;
            }

        }
        
        if ( (E(TO))->guards_present() && !(TP->query_prop(ELF_CAMP_QUEST)) )
        {
            if ( query_open() == 0 )
            {
                write("A draconian stands on your way, preventing " +
                    "you from opening the door.\n");
                return 1;
            }
            else
            {
                write("The door is already open.\n");
                return 1;
            }
        }
        
        if ( query_open() == 0 )
        {
            write("You open the wooden door.\n");
            say(QCTNAME(TP) + " opens the wooden door.\n", TP);
            do_open_door("");
            other_door->do_open_door(check_call(open_mess[1]));
            return 1;
        }
        else 
        {
            write("The door is already open.\n");
            return 1;
        }
            
    }
    
    notify_fail("Open what?\n");
    return 0;
}
