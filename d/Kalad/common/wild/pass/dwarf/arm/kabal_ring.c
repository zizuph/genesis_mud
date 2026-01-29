inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* Made by Korat
/* This ring is a quest-item that has different powers according
   * to how it ended up in the players possession.
* As a quest-item, it functions as a reward - with great powers.
* As an item aquired through killing the owner (kabal), it has
* lesser powers since it is not "blessed". The power of the
* ring shows itself in the strenght of the ruby's red colour.
*/

int strenght = 0; /* the strenght of the ring. Default is 0 */

/* function set_strenght()
* description: checks the strenght of the ring.
* returns: Strenght of the ring, 0 (weak) to 4 (strong)
*/
void
set_strenght(int new_strenght)
{
   if (new_strenght < 0) new_strenght = 0;
   if (new_strenght > 4) new_strenght = 4;
   strenght = new_strenght;
}

void
create_armour()
{
   ::create_armour();
   set_name("ring");
   set_adj("blood-red");
   add_adj("ruby");
   set_long("This ring, with its blood-red ruby shining "+
      "in the light, looks very expensive. A seldom item "+
      "of unknown value.\n");
   add_item("ruby","The ruby shines in a @@magic_strenght@@ colour, "+
      "making it look like a tear of blood with its smooth surface.\n");
   set_ac(1);
   set_at(A_ANY_FINGER);
   add_prop(OBJ_I_VALUE, 3000);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 200);
   
   /* Magic propertied: */
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_S_WIZINFO,"This ring has a variable magic strenght in it. "+
      "The strenght depends on how the ring got into the players possession. "+
      "If through a quest, it is fairly powerful.\n");
   add_prop(MAGIC_AM_ID_INFO,
      ({"The ring is magical.\n",10,
            "An enchantment has been laid upon it, making the ring most unusual.\n",20,
        "The ring will aid the wearer with an increased speed of "+
      "the hands.\n",60,
      "The current power of the ring is clearly visible on its "+
      "blood-red ruby, in that the fierceness of the colour "+
      "echoes the strenght it holds.\n",90,
      "The ring is personal in that it demands a blood-sacrifice "+
      "to be passed on. This blessing must be done at once the ring "+
      "is worn.\n",100}));
   add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
}

/* function: magic_strenght()
* returns: The string matching the strenght of the ring.
*/
string
magic_strenght()
{
   string str;
   switch (strenght)
   {
      case 0:
      str = "dull blood-red";
      break;
      case 1:
      str = "weak blood-red";
      break;
      case 2:
      str = "blood-red";
      break;
      case 3:
      str = "deep blood-red";
      break;
      case 4:
      str = "fierce blood-red";
      break;
      default: "bugged!! Please report this with a bugreport!";
      break;
   }
   
   return str;
}
