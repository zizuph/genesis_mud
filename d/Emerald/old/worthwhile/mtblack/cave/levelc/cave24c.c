/* A part of the Emerald cave system. Recoded 18/07/95, Tulix III.         */
/* This room has a nasty shock in store for anyone who would normally use  */
/* either swarm, smash, or charge. They really don't work very well here.  */
inherit "/std/room";

#include "default.h"

/* Global variables */
object ogre1, ogre2, ogrelord;

/* Prototype functions */
public void reset_room();
public void clone_ogre_lord();
public int block_swarm(string str);
public int block_smash(string str);
public int block_charge(string str);

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
        "Well, this looks like the most comfortable cave that you have " +
        "seen so far. It looks like the Ogre who lives here is quite " +
        "an important one. The floor has been smoothed down and there " +
        "is not a bump in sight. There is even some form of carpet " +
        "on the floor, which is not normal for caves.\n" +
        "The ceiling is rather low in this cave.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");

    add_item(({"roof","ceiling"}), 
        "What you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff. You do notice some dents in the roof - " +
        "almost as if someone has hit it with a weapon.\n");

    add_item(({"dents", "bumps"}),
        "Hmmm. It looks like the dents in the ceiling have been caused " +
        "by several blows from a weapon of some sort. How very odd.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing has been carpeted, which " +
        "has been layed straight over the volcanic rock of the cave.\n");

    add_item(("carpet"), "It is a carpet woven from some " +
        "kind of thick, heavy wool. It is dark brown in colour and covers " +
        "most of the floor.\n");

    add_exit(THIS_DIR+"cave20c", "southwest", 0, 1);
    
    clone_ogre_lord();
    reset_room();
}

public void
init()
{
    ::init();
    add_action(block_swarm, "swarm");
    add_action(block_smash, "smash");
    add_action(block_charge, "charge");
}

public int
block_swarm(string str)
{
    write("You run into the wall. It seems this cave is too narrow.\n");
    tell_room( TO, QCTNAME(TP) + " runs into the wall of the cave "
        + "for some strange reason.\n", TP);
    return 1;
}

public int
block_smash(string str)
{
    write("You try to smash, but you merely dent the low ceiling.\n");
    tell_room( TO, QCTNAME(TP) + " viciously attacks the roof of the cave.\n"
        + "How very strange....\n", TP);
    return 1;
}

public int
block_charge(string str)
{
    write("You blunder back into the wall. There's not enough room to " + 
        "charge!\n");
    tell_room( TO, QCTNAME(TP) + " blunders back into the wall. "
        + "How very clumsy.\n", TP);
    return 1;
}

public void
reset_room()
{
    if (!objectp(ogre1))
    {
        ogre1=clone_object(CAVE_DIR + "npc/vicious_ogre");
        ogre1->arm_me();
        ogre1->move_living("into a cave", this_object(), 1, 1);
    
        if (objectp(ogrelord))
            ogrelord->team_join(ogre1);
    }
    
    if (!objectp(ogre2))
    {
        ogre2=clone_object(CAVE_DIR + "npc/vicious_ogre");
        ogre2->arm_me();
        ogre2->move_living("into a cave", this_object(), 1, 1);
        
        if (objectp(ogrelord))
            ogrelord->team_join(ogre2);
    }

    return;
}

/* There will only ever be one lord ogre cloned per reboot */
public void
clone_ogre_lord()
{
    if (!objectp(ogrelord))
    {
        ogrelord=clone_object(CAVE_DIR + "npc/ogrelord");
        ogrelord->arm_me();
        ogrelord->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}
