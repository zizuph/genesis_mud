#include "default.h"

inherit CASTLE_ROOM;

object paladin;
object guard = allocate(5);

void reset_room();

void
create_room()
{
    set_short("Guardroom");
    set_long("This is a communal guardroom where the elven guards laze " +
             "around in the nice cool atmosphere. There is a fireplace " +
             "here, presumably for the winter evenings.\n");
    add_exit(CASTLE_DIR + "1k1", "south", 0);
   
    add_item(({"fireplace","fire"}),"The fireplace is large and ornate "+
    "to say the least. It has many\ncarvings all over it, and a beautiful "+
    "crest on the top.\n");
    add_item(({"crest","carvings"}), "The crest and carvings are really all one "+
    "since they run into each other.\nThe crest is of the Royal "+
    "House of Telberin, whereas the carvings \nare of royalty "+
    "displaying their affection for their rulers.\n");
    add_item("gate","You can just see the gate to the west from here.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    reset_room();
}

void
reset_room()
{
    int i;
    
    /* any member of the guard that is killed, will be restored */
    if (!paladin)
    {
        paladin = clone_object(NPC_DIR + "pal2");
        paladin->arm_me();
        paladin->move(this_object(), 1);
    }
    for (i = 0; i < 5; ++i)
    {
        if (!guard[i])
        {
            guard[i] = clone_object(NPC_DIR + "guard");
            guard[i]->arm_me();
            guard[i]->move(this_object(), 1);
            if (paladin)
                paladin->team_join(guard[i]);
        }
    }
}
