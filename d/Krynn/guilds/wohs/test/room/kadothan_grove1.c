/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_OUT;

void
create_tower_room()
{
   set_short("a grove of tall pine trees");
   set_long("You find yourself in the middle of a peaceful grove of " +
       "tall pine trees. A gentle wind blows through the grove, " +
       "causing the trees to sway serenely above you. There is very " +
       "little undergrowth, with the occasional fern growing amid a " +
       "deep carpet of brown needles from which the lulling drone of " +
       "chirping crickets can be heard. Parting the carpet of needles " +
       "here is a path heading east and west.\n");

   add_item(({"grove","grove of tall pine trees","peaceful grove",
       "forest"}), "You stand within a grove of tall pine trees that " +
       "sway serenely to a gentle highland breeze, almost hypnotically. " +
       "You feel a sense of sleepiness pass over you as you watch the " +
       "trees move, and combined with the intoxicating scent of pine " +
       "you feel your eyelids grow heavy. There is very little " +
       "undergrowth here making it quite easy to navigate through the " +
       "grove. To your west you can make out the crimson walls of a " +
       "tower, while to your east the grove continues.\n");

   add_item(({"pine trees","trees","tree","pine tree","trunks"}),
       "Tall pine trees surround you here in this grove, swaying " +
       "serenely to a gentle highland breeze, almost hypnotically. " +
       "You feel a sense of sleepiness pass over you as you watch the " +
       "trees move, and combined with the intoxicating scent of pine " +
       "you feel your eyelids grow heavy. As the canopy of the pine " +
       "trees part to your west with the breeze you notice the " +
       "crimson walls of a squat tower.\n");

   add_item(({"tower","walls","crimson walls","crimson tower",
       "squat tower"}), "Looking to your west through the thin trunks " +
       "of the pine trees you can make out the crimson walls of " +
       "squat tower. You can't make out many details about it from " +
       "here, you'd need to get closer.\n");

   add_item(({"undergrowth","fern","carpet","deep carpet"}),
       "There is very little undergrowth in this grove of pine trees, " +
       "consisting of a deep carpet of brown pine needles and the odd " +
       "fern.\n");

   add_item(({"crickets","chirping crickets","cricket"}),
       "You cannot see any crickets, although you can certainly hear " +
       "their lulling drone which makes you feel increasingly sleepy.\n");

   add_item(({"needles","pine needles","brown pine needles",
       "carpet of needles"}), "A thick carpet of brown pine needles " +
       "covers the ground here.\n");

   add_item(({"path","exit"}), "Running through the carpet of brown " +
       "pine needs here is a path leading west towards the crimson " +
       "walls of a tower, and east towards the exit of the grove.\n");

   OUTSIDE;

   add_exit(WOHS_TEST + "room/kadothan_grove2", "west", 0);
   add_exit(WOHS_TEST + "room/kadothan_grove3", "east", 0);

}
