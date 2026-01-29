/* Kirk of Port City - Garden base room with herb support
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#pragma strict_types
#include "defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#define  STD_LONG                                                           \
         "   You are in the cloistered garden of the abbey, nestled between "+ \
         "the towering walls of the kirk along the east, and the abbey "+   \
         "walls along the north and west. A tall black iron fence "+        \
         "overgrown with ivy protects the garden from the street along "+   \
         "its south side. The garden is neatly landscaped with dozens "+    \
         "of varieties of trees, flowers and other plants. A cobblestone "+ \
         "path winds throughout the lush vegetation, serenaded by the "+    \
         "occasional melody of song birds. "
 
 
inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;
inherit SR_LIB+"branchcmd";
string *herbs;
 
 
public void
setup_kgard_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_GARDEN,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"grass","here"}), 2);
}
public void reset_room()
{
    set_searched(0);
    set_numbranches(1);
}
 
string query_std_long() { return STD_LONG; }

void setup_garden_room() {
    set_short("abbey garden");
    set_long("In the abbey garden");
    set_branchnum(0);
    add_item("kirk",
       "The towering stone walls of the kirk with their large arched "+
       "stained-glass windows wall the garden along its east side.\n");
    add_item(({"mosaics","windows"}),
       "The mosaics of the large stained-glass windows of the kirk "+
       "are obscured by the ivy which laces about their edges, while "+
       "the small cream-colored opaque windows of the abbey are "+
       "latticed with a diamond-shaped pattern.\n");
    add_item("abbey",
       "The stone walls of the abbey with their opaque cream-colored "+
       "latticed windows wall the garden along its north and west "+
       "sides. There is an entrance to the abbey in the center of "+
       "its front along the west side of the garden.\n");
    add_item(({"door","doorway","entrance"}),
       "An arched doorway marks the entrance to the abbey in the "+
       "center of its front along the western side of the garden.\n");
    add_item("gate",
       "There is a gate on the west end of the fence in the "+
       "southwestern corner of the garden.\n");
    add_item("path",
       "The old cobblestone path winds its way through the quiet "+
       "garden, its stones worn smooth by years of weather and "+
       "feet.\n");
    add_item("fence",
       "A tall iron fence protects the garden from the street along "+
       "the south side, connecting the corner of the kirk to that of "+
       "the abbey. It is constructed of tall black poles with speared "+
       "tips set evenly apart, thick bars crossing its breadth near "+
       "the top and bottom. It is covered in ivy, and there is a gate "+
       "on its western end leading out to the street.\n");
    add_item("street",
       "Obscured from view by the ivy covered fence, the street runs "+
       "along the south side of the garden.\n");
    add_item("grass",
       "Thick lush grass, the greenest green you have ever seen, carpets "+
       "the quiet garden.\n");
    add_item(({"copses","trees"}),
       "A variety of trees grow throughout the garden, mostly along the "+
       "edges and in copses throughout, shading the garden and its path, "+
       "some housing song birds.\n");
    add_item(({"bird","birds"}),
       "Occassionally one flutters into view between the trees, their "+
       "high-pitched songs the main evidence of their presence.\n");
    add_item(({"plants","flowers"}),
       "Lush green plants and several varieties of flowers adorn the "+
       "garden, filling it with sweet fragrances and earthy smells.\n");
    add_item("ivy",
       "Ivy struggles up the walls of both the kirk and abbey, while "+
       "it has all but covered the fence along the south side of "+
       "the garden.\n");
 
    setup_kgard_herbs();
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
    set_numbranches(1);
}

void create_khalakhor_room() {
   setup_garden_room();
   set_long("Garden base room.\n");
}

void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
