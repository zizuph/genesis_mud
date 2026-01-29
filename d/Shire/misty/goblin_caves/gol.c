/*
 * Gollum left the cave years ago, some time after Bilbo found the Ring, 
 * so according to Genesis timeline, he's running free, either hunting 
 * for the Ring or with Frodo and Sam.
 * -- Finwe, October 2003
 *
/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    set_short("By the cave lake");
    set_long("Here the tunnel ends. North of you is some quite big "+
      "cave. Unfortunately it is very dark and filled with water. "+
      "You have a feeling that there is something dangerous hidden "+
      "in it. Better turn back and run away as quick as possible.\n");

    add_item("water","Water is dark and icy cold. No way to swim in it.\n");
    add_item("cave","It looks big but you can't tell more because it is "+
      "dark and full of water.\n");

    add_exit(CAVE_DIR + "t55", "south");
}

void
reset_shire_room()
{
/*    
    object fish_skeleton;

    seteuid(getuid());

    if (!present("_shire_fish_skeleton_",TO))
    {
        fish_skeleton = clone_object("/d/Shire/scav_hunt/fish_skeleton");
        fish_skeleton->add_prop(OBJ_I_HIDE, 10 + random(10));
        fish_skeleton->move(TO);
    }
*/
}
