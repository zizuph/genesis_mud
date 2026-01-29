/* This is the main entrance to the Grunts guild, which is guarded. */
/* Perhaps there is another way in...? Recoded 25/03/97, Tulix III. */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* This line is put in to keep Mercade happy */
#pragma strict_types

/* Prototype functions */
public void   reset_room();
public int    down_block();
public string sign_text();

/* Global variable */
object npc;

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    set_short("This is an huge icy cavern. A large ladder leads down");
    set_long("   " +
         "You have entered a huge cavern. Everywhere you look, there " +
         "is ice: on the walls of the cave are big sheets of ice; " +
         "huge icicles hang from the roof; and the floor seems to be a " +
         "great sea of ice. One thing strikes you as odd though: there is " +
         "lichen growing on the ice - it's very unusual for lichen to " +
         "thrive in the cold. Over in the corner you see a large ladder " +
         "that goes down into a hole.\nA sign hangs above the ladder.\n\n");

    add_item("lichen", 
        "There is lichen growing on ice. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(({"ice", "icicles"}), "Yup, looks like frozen water.\n");
    add_item(({"walls", "wall"}), "The walls are made of solid ice. " +
        "Amazingly, you see some lichen growing on it. Odd.\n");
    add_item(({"roof", "ceiling"}), 
        "The roof is filling with huge icicles which hang down in a " +
        "rather threatening manner.\n");
    add_item(({"floor", "ground"}),
        "The floor is solid, but rather slippery. Best not walk too fast, " +
        "or you might slip over.\n");
    add_item(({"ladder", "large ladder"}),
         "It is quite a large ladder. It leads down to the Grunts " +
         "guild.\n");
    add_item("hole", "The hole seems to have been enlarged recently.\n");
    add_item("sign", sign_text() );
    add_cmd_item("sign", "read", sign_text() );


    add_exit(THIS_DIR+"cave7b", "southwest", 0, 1);
    add_exit(GRUNTS_DIR + "room/main", "down", "@@down_block", 1);
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/giant_goblin");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}

public int
down_block()
{
    object giant;
   
    giant=present("giant");
    if (giant)
    {
        /* Wiz level check. Wizards are allowed down always. */
        if (this_player()->query_wiz_level()>=1)
        {
            write("The guard does not stop immortals.\n");
            return 0;
        }

        if (this_player()->query_prop(OBJ_I_INVIS) >= 1)
        {
            write("You slip invisibly past the guard.\n");
            return 0;
        }
        
        if (this_player()->query_race_name()!="goblin")
        {
            write("The guard stops you from going down the ladder.\n");
            tell_room( this_object(), QCTNAME(this_player()) +
                " rather foolishly tries to go past the guard, but fails.\n",
                this_player() );
            return 1;
        }
      
        write("You are not stopped by the guard.\n");
        return 0;
    }
   
    write("There is nothing stopping you, so you climb down the ladder.\n");
    return 0;
}

public string
sign_text()
{
    return "The sign has an arrow etched on it, pointing down the ladder.\n" +
        "There is some writing scribbled hastily underneath:\n\n" +
        "'To dA GrUnts GuIld'\n'PleEez nOte - gOblyns OnlY'\n";
}
