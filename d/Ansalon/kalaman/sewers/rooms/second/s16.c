#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"
#include "/sys/macros.h"

inherit DWARF_VILLAGE;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s13", "northwest");
    add_exit(SECOND + "s17", "north");
    add_exit(SECOND + "s15", "west");
    
    set_spawn_dwarf(1);
    reset_room();
    
    set_long("@@cottage_desc");    
    add_item("cottage", "These small and very poorly crafted homes are constructed " +
     "out of all the kind of stuff these gully dwarves can gather in the sewers and " +
     "from the streets of the city. Uneven, broken wooden blanks, ports of large " +
     "tables and various driftwood make out the most part of the outer walls. Some " +
     "of the wall is actually made out of straw and mud. The cottage has a door or " +
     "well more of an opening that one can enter through.\n");
}

void
init()
{
    ::init();
    add_action("enter_cmd", "enter");
    set_dircmd("cottage");
}

string
cottage_desc()
{
    string temp;
    
    temp = look_desc();
    
    temp += "\nYou see a small cottage which you can enter.\n\n";
    return temp;
}

int
enter_cmd(string str)
{
    if (str != "cottage") 
    {
        notify_fail("Enter what?\n"); 
        return 0;
    }
    else
    {
        write("You enter the cottage.\n");
        say(QCTNAME(TP) + " enters the cottage.\n");
        TP->move_living("M", SECOND + "c6", 0, 0);
        
        return 1;
    }
}
