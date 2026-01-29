/*
 * File:          /d/Avenir/common/dark/submissions/Pitch-black_Pit.c
 * Creator:       Destre
 * Date:          Thu Jan  5 02:23:58 2017
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#21180
 * Comments:      
 *                An idea for a pit underneath the fire pit at
 *                the center of the upper level tunnels.
 *                Inspired from the Greek myth of the monster
 *                Echidna, the mother of all monsters. Her
 *                priests can be the shadow lizards who are
 *                through out the tunnels and keep the pit lit,
 *                as the warmth is her source of life. Her
 *                children are the drakes, the chimera, and the
 *                wolves that are in the tunnels, and perhaps
 *                the aglyna as well. Her story can be that she
 *                was feared and revered by the monsters that
 *                roamed these tunnels before the Idrys
 *                arrived. She was driven back and injured by
 *                the Idrys and she managed to escape, but not
 *                before taking Aclolthayr's favored weapon.
 *                She stores the weapon inside of the chest.
 *                This can be a quest as well as a creature
 *                that provides either daggers or armour when
 *                killed. The quest item can be located inside
 *                of the wooden chest and the key is on her,
 *                but it can only be found when she is killed.
 *                The quest can be started at Aclolthayr's
 *                altar.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Pitch-black Pit");
    set_long("A pit of seemingly endless darkness filled with "
        + "sweltering hot air from the fire pit above it. The "
        + "air wafting from it and surrounding you smells "
        + "strongly of death and decay. From the feeble light "
        + "of the fire pit (you have just moved), you can "
        + "faintly make out the outline of narrow stone steps "
        + "descending into the darkness. A feeling of dread "
        + "overcomes you as you stare into the darkness.\n");

    add_item(({"staircase","stone"}),
        "a crumbling stone staircase cut from the walls of "
        + "the pit.\n");
    add_item(({"chest","wood","lock"}),
        "an ancient wooden chest chained and locked.\n");
    add_item(({"pile","snake skin","corner"}),
        "a pile of old snake skin lies in the corner and  "
        + "looks as if it is from a giant serpent.\n");
    add_item(({"monster","snake","wolf","lion","woman","chainmail"}),
        "a terrifying monster like none you have ever seen "
        + "before. The head of a woman with snakes for hair "
        + "in the center, a wolf's head to the right, and a "
        + "lion's head to the left. Her torso is covered in a "
        + "light silvery chainmail. Her bottom half is "
        + "connected to a snake's tail. She rests coiled up "
        + "at the moment, but you strongly suspect that death "
        + "will come for you as soon as she awakens.\n");
    add_item(({"wall","pit","hot","stone"}),
        "the walls of the pit are rough and hot to the "
        + "touch. They glitter with a slime you dare not "
        + "inspect further.\n");
    add_item(({"ceiling","hole","faint light"}),
        "looking above you, now looking as if only a speck, "
        + "you think you can make out the faint glow of the "
        + "fire pit.\n");
    add_cmd_item(({"wood","chest"}),
        ({"search"}),
        "You search through the wooden chest and find a "
        + "dazzling sword.\n");
    add_cmd_item(({"monster"}),
        ({"kill"}),
        "You have slain the monster. As she takes her last "
        + "breath, a key falls from her grasp. You quickly "
        + "snatch it up.\n");
    add_cmd_item(({"pit"}),
        ({"push"}),
        "You search the fire pit. You believe you will be "
        + "able to push it.\n");
    add_cmd_item(({"fire"," pit"}),
        ({"push"}),
        "As you push the fire pit, it budges a little, "
        + "revealing a dark pit. You have badly burned "
        + "yourself in the process.\n");
    add_cmd_item(({"stairs"," stone"}),
        ({"down"}),
        "You descend the crumbling stone stairs into the "
        + "darkness, gagging as the heat and the stench of "
        + "rot overwhelm your senses.\n");


}
