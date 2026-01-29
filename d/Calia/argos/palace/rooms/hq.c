/*
**   ARGOS - Royal Palace - Military HQ
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/96    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A large opulent office");
   set_long(
      "This very spacious chamber seems to be the office of some high-"+
      "ranking official. A large oval carpet is centered in the chamber, "+
      "on which sits an elegant desk with a plush, high-backed chair. "+
      "A row of shelves lines the western wall, housing what looks like "+
      "official documents and records. Two banners hang from gold-plated "+
      "poles, one on each side of the chair just behind the desk. A "+
      "tapestry hangs on the northern wall, and a great seal on the "+
      "southern. A large archway leads back into the palace entrance "+
      "hall to the east.\n");
 
   add_item("carpet",
      "It is a large oval carpet, woven from a high quality wool. A "+
      "pattern of interlocking ovals is fashoined into its threads.\n");
   add_item("desk",
      "It is a large desk made of highly polished dark oak, the edges "+
      "of its top studded with pewter stars. There is a small plaque "+
      "on the front-center of the desk, along with a parchment document.\n");
   add_item("chair",
      "It is a luxurious high-backed chair, carved of the same highly "+
      "polished dark oak as the desk. It is cushioned with plush blue "+
      "silk cushions.\n");
   add_item("plaque",
      "It is a small plaque which reads: Silvestrus - Grand Stratarch of "+
      "the Royal Army of Argos.\n");
   add_item(({"document","parchment document","document on desk"}),
      "It is an official-looking document of fine parchment, bearing the "+
      "royal seal of Argos. It reads: 'Congratulations to your spies on "+
      "locating the main Kretan encampment in the southwestern forest. "+
      "Prepare a batallion of our finest warriors for an assault on the "+
      "traitors.' It is signed 'COSMOPOLITUS BASILEUS ARGOSIOU'\n");
   add_item("shelves",
      "They are high shelves made of polished dark oak, lining the "+
      "western wall. They are filled with documents and other official "+
      "records.\n");
   add_item(({"documents","records","documents on shelves"}),
      "There are hundreds of them neatly stacked on the shelves. They're "+
      "probably boring government records, nothing to take interest in.\n");
   add_item(({"banner","banners","pole","poles"}),
      "Two regal banners hang from poles on either side of the desk. One "+
      "is the banner of Argos, a blue field with a shield emblazoned with "+
      "a rampant winged horse, surmounted by a crown with three jewels. "+
      "The other is the same color of blue, but bears a large unornamented "+
     "shield over two crossed swords. They hang from poles plated in gold.\n");
   add_item("tapestry",
      "It is a tapestry woven of silk, portraying a triumphant regal "+
      "figure in gold armour, raising a sword high in salute to a mass "+
      "of cheering well-armed soldiers.\n");
   add_item("seal",
      "Made of gold, the oval seal has a shield in the center over two "+
      "crossed swords, a small rampant winged horse over the shield. "+
      "An inscription written around the border of the seal reads: "+
      "TRITHEON AND MONARCH - OUR HONOR TO DEFEND.\n");
   add_item(({"archway","entrance"}),
      "It is a high rectangular archway marked with two of the stately "+
      "pillars on each side. It leads into the grand entrance.\n");
 
   /* exits */
   add_exit("foyer","east",0);
}
