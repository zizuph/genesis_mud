/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_palan_room()
{
    set_short("Entrance Hall of the Palace");
    set_long(BS("This is the grand entrance hall of the palace of "
           + "Palanthas. Fine tapestries hang from the walls showing "
           + "battle scenes, but also palace life and hunting scenes. "
           + "A sign on the west doorway says that offices are in that "
           + "direction, whereas the east entrance is guarded. "
           + "Marble stairs lead up into the tower, but there is a "
           + "dim violet light shining down from above.", SL));

    add_exit(PALACE + "palace2","east","@@guarded",0);
    add_exit(PALACE + "palace3","west","@@closed",0);
    add_exit("/d/Krynn/aridor/workroom","up","@@is_protected",0);
    add_exit(ROOM + "plaza","south");
}


guarded()
{
    if (present("iletter", TP))
    {   
        write(BS("The guard steps out of his cabin and says: "
           +  "\"It is a great honour to have you here.\"The guard "
           +  "bows deeply before you and beckons you to enter.",SL));
        return 1;/*change again if it works!!!!!!!*/
    }
    write(BS("The guard says: I am sorry, but you may only enter if "
           +  "you have been invited personally.",SL));
    return 1;
}


closed()
{
    write(BS("Due to a strike of the office clerks, it is impossible "
       +  "to enter. Negotiations are progressing slowly, but after "
       +  "they succeed, you will be able get any papers signed again."
          , SL));
    return 1;
}


is_protected()
{
    if (TP->query_wiz_level())
        return 0;
    write(BS("As you climb the stairs you feel a magical barrier hindering "
        + "you from ascending further. You have the feeling that this is "
        + "very strong magic working here, and only the great wizards "
        + "have the power to pass through.", SL));
    return 1;
}

 
