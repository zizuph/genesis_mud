/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variable */
object npc;

/* Prototype function */
public void reset_room();

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Another dark cave");
    set_long("   " +
        "This is another dark cave. There is a distinct smell of Ogre in " +
        "here. It's just the kind of place an Ogre would like, they being " +
        "no great lovers of fresh air and sunshine. The floor looks " +
        "very pitted with large holes in abundance.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. There is some lichen growing on the floor.\n");
    add_item(({"holes","hole"}),
        "There are several holes in the floor. There's nothing special " +
        "about them, except for one that appears to lead down into " +
        "the lower depths of the caves. You're not sure about what may " +
        "be lurking down there....\n");

    add_exit(THIS_DIR+"cave15b", "south", 0, 1);
    add_exit(CAVE_DIR + "levelc/cave1c", "down", "@@down_block", 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/small_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}

public int
down_block()
{
    object ogre;

    ogre=present("giamari");
    if (ogre)
    {

        if (this_player()->query_wiz_level()>=1)
        {
            write("This Ogre does not stop immortals.\n");
            return 0;
        }

        write("The Ogre stops you from going down the hole.\n");
        say(QCTNAME(this_player()) + " tries to go down the hole, " +
            "but is stopped by the Ogre.\n");
        return 1;
    }

    if (this_player()->query_base_stat(SS_DIS)<=30)
    {    
        write("You want to go down, but you are too afraid.\n");
        say(QCTNAME(this_player()) + " ponders going down, but is too "
            + "much of a coward to dare.\n");
        return 1;
    }        
    
    if (this_player()->query_base_stat(SS_DIS)<=50)
    {
        write("You overcome your fears and go down the hole.\n");
        say(QCTNAME(this_player()) + " plucks up the courage to go down.\n");
        return 0;
    }
    say(QCTNAME(this_player()) + " boldly struts towards the hole.\n");
    return 0;
}

