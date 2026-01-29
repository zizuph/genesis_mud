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
   set_short("before a crimson tower in a grove of pine trees");
   set_long("You stand before the walls of a short, stout tower on a " +
       "hill in the middle of a grove of tall pine trees. No more than " +
       "200 feet tall and featuring archaic yet ornate Ergothian " +
       "design, it is quite short compared to other towers you have " +
       "come across. The one thing that truly stands out about this " +
       "tower is the brilliant red colour of its walls - a crimson " +
       "almost the colour of blood. With the tower standing upon a " +
       "tall hill you notice it overlooks a great city. You also notice " +
       "the tower entry faces east towards where an imperial palace " +
       "rises beyond the grove. To your west is a gateless passage " +
       "through the barbican of the walls.\n");

   add_item(({"grove","grove of tall pine trees","peaceful grove",
       "forest"}), "You stand within a grove of tall pine trees that " +
       "sway serenely to a gentle highland breeze, almost hypnotically. " +
       "You feel a sense of sleepiness pass over you as you watch the " +
       "trees move, and combined with the intoxicating scent of pine " +
       "you feel your eyelids grow heavy. There is very little " +
       "undergrowth here making it quite easy to navigate through the " +
       "grove.\n");

   add_item(({"hill", "tall hill"}), "The crimson tower stands at the " +
       "top of a tall hill within the pine grove, overlooking a great " +
       "city that spreads around the grove. To your east you can " +
       "make out an imperial palace rising from an equally tall hill.\n");

   add_item(({"pine trees","trees","tree","pine tree","trunks"}),
       "Tall pine trees surround you here in this grove, swaying " +
       "serenely to a gentle highland breeze, almost hypnotically. You " +
       "feel a sense of sleepiness pass over you as you watch the trees " +
       "move, and combined with the intoxicating scent of pine you " +
       "feel your eyelids grow heavy.\n");

   add_item(({"tower","crimson tower","squat tower","short tower",
       "rathfast","crimson keep","keep","tower of high sorcery"}),
       "Built atop a tall hill within a grove of pine trees, this tower " +
       "is both shorter and broader than towers you are familiar with. " +
       "Its design is based on an early Ergothic style you have only " +
       "ever read about, although the deep, brilliant red colour of its " +
       "walls is unique to one building only - Rathfast, the Crimson " +
       "Keep, the Tower of High Sorcery in the city of Daltigoth that " +
       "was destroyed during the Lost Battles over 360 years ago!\n");

   add_item(({"walls","crimson walls","wall","stout wall","whorls",
       "silver lightning","lightning","stormclouds","inky black","black",
       "red stone","stone"}), "Surrounding the tower is a stout wall " +
       "of red stone, mottled and marked here and there with whorls of " +
       "inky black, forever twisting and turning like stormclouds that " +
       "occasionally flare with silver lightning. Atop the wall are " +
       "crenelated battlements and gargoyles, at odds with the " +
       "welcoming gateless opening allowing entry to the tower grounds " +
       "to your west.\n");

   add_item(({"battlements","gargoyles","gargoyle",
       "crenelated battlements"}), "Gargoyles stare down upon the entry " +
       "of the tower from the battlements of the wall, frozen guardians " +
       "of the tower.\n");

   add_item(({"gate","passage","gateless passage","barbican","opening",
       "gateless opening"}), "You notice the walls have no gate, only " +
       "an open passage through its barbican leading to a wide lawn of " +
       "emerald grass within the tower proper.\n");

   add_item(({"grass","emerald grass","tower proper","proper","lawn",
       "wide lawn"}), "Through the open passage to your west you can " +
       "see a wide lawn of emerald grass within the tower proper.\n");

   add_item(({"city","great city","daltigoth"}), "The tower stands upon " +
       "a high hill within a grove of pines overlooking a city " +
       "clearly of Ergothic design. To your east you can make out a " +
       "great imperial palace, its tall minarets rising high above the " +
       "height of the crimson tower you stand next to.\n");

   add_item(({"imperial palace","palace","minaret","minarets"}),
       "To your east rises a great imperial palace, the seat of power " +
       "of the emperor of Ergoth.\n");

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
       "pine needs here is a path leading west through the crimson " +
       "walls of a tower, and east towards the exit of the grove.\n");

   OUTSIDE;

   add_exit(WOHS_TEST + "room/daltigoth_tower1", "west", 0);
   add_exit(WOHS_TEST + "room/kadothan_grove1", "east", 0);

}
