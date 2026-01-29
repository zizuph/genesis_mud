inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("The Entrance of the Gentlemen's Club");
    INSIDE;
    set_long("You step inside a spacious room. The scent of "+
        "rich herbs and spices fills the air. Along the "+
        "walls, you see many burning scented candles. There is "+
        "a staircase leading up from behind a large wooden desk. "+
        "A big leather couch sits against one wall, and there is a "+
        "small table in front of it.\n");
    
    add_item("candles","They burn softly, filling the room with "+
        "their scent.\n");
    add_item("desk","A large wooden desk with papers on it.\n");
    add_item("papers","They are documents of the members of the "+
        "club.\n");
    add_item("couch","It is made of black leather and looks very "+
        "comfortable.\n");
    add_item("table","It is a small, short table with cups of "+
        "tea on it.\n");
    add_exit(NOBLE(club/room2),"up","@@block@@",-1,-1);
    add_exit(NOBLE(market/s4),"east",0,-1,-1);
}

int
block()
{
    object tie;
    if(tie = present("bowtie",TO))
        {
        if(MASTER_OB(tie) == NOBLE(club/bowtie))
            return 0;
    }
    write("Only members of the club may go there.\n");
    say(QCTNAME(TP)+" is blocked from going up.\n");
    return 1;
}

