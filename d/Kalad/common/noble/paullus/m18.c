inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* 	Created by:	Sarr 
 * 	Modified by:	Toby, 971014 (fixed typos)
 */

object ob,ob2,ob3;
void reset_room();

void
create_room()
{
    set_short("In the bath house of the House of Paullus");
    set_long("As you enter this room, you are greeted with "+
    "a blast of hot air in the face. The room here is steamy "+
    "and you begin to sweat. You seem to have entered a bath "+
    "house. The ground bellow you is wet and slick. In the "+
    "center of the room is a very large tub filled with "+
    "steaming water. Out of the wall behind it, a tube juts out "+
    "pouring steaming water into the tub. Around the room, you "+
    "notice towels and garments hanging around.\n");

    add_item("tub","A large tub filled with hot water. It looks "+
    "very inviting.\n");
    add_item(({"towels","garments"}),"Various clothes and drying "+
    "towels hang on hooks.\n");
    add_item("tube","It brings in the hot water, where? You have no "+
    "idea.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m14),"southeast",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/sama));
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/man-slave));
        ob2->move_living("xxx",TO);
    }
    if(!ob3)
    {
        ob3 = clone_object(NOBLE(npc/man-slave));
        ob3->move_living("xxx",TO);
    }
    ob->team_join(ob2);
    ob->team_join(ob3);
}
