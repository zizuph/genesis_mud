/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variable */
object npc;

/* Prototype functions */
public void reset_room();
public int northeast_block();

public void 
create_room()
{
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   set_short("A dark cave");    
   set_long("   "+
      "This cave is not the most natural one you have ever seen. " +
      "It looks like it has been dug out and the floor is too " +
      "flat and smooth to be formed by nature. There seems to be " +
      "light coming from the cave to the east.\n\n");
   
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
   
   add_exit(THIS_DIR+"cave19c", "west", 0, 1);
   add_exit(THIS_DIR+"cave24c", "northeast", "@@northeast_block", 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/large_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}

public int 
northeast_block()
{
    object ogre;
   
    ogre=present(npc, TO);
    if (ogre)
    {
        if (this_player()->query_wiz_level()>=1)
        {
             write("This ogre does not stop immortals.\n");
             return 0;
        }
      
        write("The large ogre stops you from going northeast"+".\n");
        say(QCTNAME(this_player())+" tries to go northeast " +
            "but is stopped by the ogre.\n");
        ogre->command("say The Ogre lord is busy. Get lost.\n");
        return 1;
    }
    write("There is nothing to stop you from entering the cave.\n");
    return 0;
}

