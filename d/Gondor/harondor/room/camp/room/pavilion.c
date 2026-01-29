/* Name      : /d/Gondor/harondor/room/camp/room/pavilion.c
 * Purpose   : The chief's pavilion inside the camp of Haradrim
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 * Modified  : Sir Toby, Gondor Domain, 2006-09-25
 *                   Added all the add_item =o) 
 *                   Had apparantly missed that before
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/std/room";


object	*Haradrim = allocate(2);
object	*Chief = allocate(1);

public void
create_gondor()
{
   set_short("Inside a large canvas pavilion");
   set_long("Inside a large canvas pavilion. The ground is covered with straw " +
            "mats and on top of those, in the inner half of the pavilion, rich " +
            "animal furs lie. Farthest in a large four poster bed stand royally " +
            "with large pillows and cushions all over. " +
            "Beside the bed a small table with a bowl and a can. In the centre a " +
            "thick wooden pole stand errected holding up the canvas ceiling. A " +
            "book stand have been placed to the left side, in front of it a reading " +
            "table with a small hooded lantern atop. Just inside the opening there " +
            "is a weapon rack alongside a rack holding armours.\n");

   add_item("canvas",
            "There is nothing special about the canvas. It is quite narrowly woven.\n");
   add_item(({"mats", "straw mats", "furs", "animal furs"}),
            "There is nothing special about them.\n");
   add_item(({"mat", "straw mat", "fur", "animal fur"}),
            "There is nothing special about it.\n");
   add_item(({"bed", "poster bed", "four poster bed"}),
            "The bed is rather big and suitable for a ruler. Large pillows and cushions " +
            "cover the top of it. A veil of silk is draped around the posters and also " +
            "forming a ceiling above the bed.\n");
   add_item(({"cushions", "pillows"}),
            "They are embroidered with various patterns and look very soft.\n");
   add_item(({"cushion", "pillow"}),
            "It is embroidered with various patterns and look very soft.\n");
   add_item(({"pattern", "patterns"}),
            "The embroidery is very neatly done, the lines straight and the curves bending " +
            "perfectly. These lines and curves make out intricate patterns in the pillows and cushions.\n");
   add_item(({"table", "small table", "bed side table", "small bed side table", "side table", "small side table"}),
            "There is nothing special about this bed side table.\n");
   add_item(({"bowl", "can", "lantern", "hooded lantern"}),
            "There is nothing special about it.\n");
   add_item(({"pole", "thick pole", "wooden pole", "thick wooden pole"}),
            "The thick pole supports the canvas ceiling.\n");
   add_item(({"book stand", "stand"}),
            "It is sparcely filled with books, in fact, you only spot three books written on the back " +
            "in a strange language.\n");
   add_item(({"book", "books"}),
            "The language is uncomprehensive and the books look very worn.\n");
   add_item("reading table",
            "The reading table has a lantern on top of it.\n");
   add_item(({"rack", "weapon rack", "armour rack", "sturdy rack", "sturdy weapon rack", "sturdy armour rack"}),
            "The rack is used for storing equipment in. it is very sturdy in its construction.\n");


   add_prop(ROOM_I_INSIDE, 1);

   add_exit(HAR_RM_CAMP_DIR + "campchief", "out");
   reset_room();
}


public void
reset_room()
{
   ::reset_room();
   

   if(!find_living("coul-mahlu"))
   {
      clone_npcs(Chief, HAR_RM_NPC_DIR + "chief", -1.0);
      clone_npcs(Haradrim, HAR_RM_NPC_DIR + "haradrim", -1.0);
   }
   else
      clone_npcs(Haradrim, HAR_RM_NPC_DIR + "haradrim", -1.0);

}


