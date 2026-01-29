#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit MITHAS_OUT;

void
reset_mithas_room()
{
    return;
}

create_mithas_room()
{
    set_short("Entrance to the Arena");
    set_long("@@long_descr");

    add_exit(MROOM + "mino_entrance","west","@@enter",0);
    add_exit(MROOM + "square7","east",0,0);
    add_exit(MROOM + "arena1","south","@@construction");

    reset_mithas_room();
}

string
long_descr()
{
    return tod_descr()+
         "You are standing next to the entrance to the "+
         "huge arena in Nethosak. The road to the east "+
         "takes you back towards the marketsquare, "+
         "while going south would take you to the Great "+
         "Arena of Nethosak. To the west a large "+
         "guildhall has been constructed, and a huge "+
         "minotaur guard protects it from outsiders. "+
         season_descr()+ "\n";
}


int
enter()
{
    if(this_player()->query_race_name() == "minotaur")
    {
        return 1;
    }
    write("A huge minotaur guard says: You're not a "+
          "minotaur, leave now.\n"+
          "The huge minotaur guard prevents you from "+
          "going west.\n");
    say(QCTNAME(TP)+ " is stopped from going west by "+
      "a huge minotaur.\n");
    return 1;
}

int
construction()
{
    write("A sign reads: The Arena is closed.\n");
    return 1;
}

