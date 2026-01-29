/* Avenir's trouser from the silkshop in Sybarus. Coded by
 * Lilith or Grace(?) Used by Marisol for Fan the Weaver 
 * in the new Re Albi. (3/3/98) */
/* Modified by Marisol (07/15/98) to be used in the village of
 *Ovejuno in Emerald.*/

inherit "/std/object";
inherit "/lib/wearable_item";
#include "/d/Emerald/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

string randsize();
string randtnt();

string size=randsize();
string tnt=randtnt();

public nomask void
create_object()
{
   set_name("gorgi_skirt");
   add_name("skirt");
    add_name(({"skirt", "peasant skirt"}));
   set_short("@@short_desc");
   set_long("@@long_desc");
   set_adj(size);
   set_adj(tnt);
   set_slots(A_LEGS);
   set_layers(0);
   set_looseness(0);

                                      
   add_prop(HEAP_S_UNIQUE_ID, "skirts_" + tnt + "_" +size);
   add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
   add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
   add_prop(OBJ_I_VALUE, 610);

    switch(size)
    {
    case "wool":
    add_item("wool", "The wool of this blouse come from the sheep "+
    "rise in the mountains of Emerald. The locals are good working "+
    "wool fibers to create a textile warm and nice for this blouse. "+
    "A seamtress, that works for Gorgi, makes this dainty piece.\n");
    break;

    case "silk":
    add_item("silk", "This silk is so fine that feels and looks like "+
    "buterfly's wings. The origin of this material is hard to tell. "+
    "It seems that comes from a far away land, something that Gorgi "+
    "undoubtly bought from traders.\n");
    break;

    case "felt":
    add_item("felt", "This pretty simple skirt is embelished with "+
    "a beautiful trip of soft sable fur. The local hunters trade this "+
    "nice fur with Gorgi, who would give it to his seamtress to add it "+
    "to the hem of the skirt.\n");
    break;
    }
}



string
randtnt()
{
   string str;

   switch(random(7))
   {
      case 0: str="saphire";    break;
      case 1: str="emerald";    break;
      case 2: str="burgundy";   break;
      case 3: str="golden";     break;
      case 4: str="black";      break;
      case 5: str="lavander";   break;
      case 6: str="white";      break;
   }
   return str;
}
string
randsize()
{
   string str;

   switch(random(3))
   {
      case 0: str="wool";         break;              
      case 1: str="silk";        break;
      case 2: str="felt";          break;
   }
   return str;
}

string
short_desc()
{
   return ""+tnt+ " "+size+ " peasant skirt";
}

string
long_desc()
{
    return "This skirt hang down from waist to ankle. "+
           "It is simple but elegant. Both peasants and "+
           "maids love to wear these clothes. "+
           "They are "+tnt+" in colour and are made of the "+
           "finest "+size+ ".\n";
}                                                                          

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
