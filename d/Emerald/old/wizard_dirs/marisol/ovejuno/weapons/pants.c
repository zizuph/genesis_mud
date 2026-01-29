
/* Avenir's trouser from the silkshop in Sybarus. Coded by
 * Lilith or Grace(?) Used by Marisol for Fan the Weaver
 * in the new Re Albi. (3/3/98) */
/* Modified by Marisol (07/15/98) to be used in the village of 
 * Ovejuno in Emerald. */

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
    set_name("shepherd_breeches");
    add_name("breeches");
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_adj(size);
    set_adj(tnt);
    set_slots(A_LEGS);
    set_layers(0);
    set_looseness(0);


    add_prop(HEAP_S_UNIQUE_ID, "breeches_" + tnt + "_" +size);
    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
    add_prop(OBJ_I_VALUE, 600);

    switch(size)
    {
    case "canvas":
    add_item("canvas", "Usually canvas is a closely woven, "+
    "coarse cloth of hemp, cotton or linen, but not these ones. "+
    "This canvas is made with wool. although not of great quality, "+
    "is good enough to create a really nice and cheap textile. "+
    "This beeches seems to come from Gorgi's shop.\n");
    break;

    case "wool":
    add_item("wool", "The wool from Ovejuno is nice although not "+
    "remarkable. The fiber is soft and warm, really good for the "+
    "cold weather of the mountains.\n");
    break;

    case "leather":
    add_item("leather", "This is a nice leather pant made from "+
    "imported leathers traded with gypsies. The leather is sturdy and "+
    "warm, really good against the cold weather of the mountains.\n");
    break;
    }

}
                                
string
randtnt()
{
   string str;

   switch(random(6))
   {
      case 0: str="sky-blue";   break;
      case 1: str="grass-green";  break;
      case 2: str="brick-red";      break;
      case 3: str="tan"; break;
      case 4: str="coal-black";   break;
      case 5: str="white";        break;
   }
   return str;
}
string
randsize()
{
   string str;

   switch(random(3))
   {
      case 0: str="canvas";      break;
      case 1: str="wool";        break;
      case 2: str="leather";     break;
   }
   return str;
}
                      
string
short_desc()
{
    return ""+tnt+ " "+size+ " breeches";
}

string
long_desc()
{
    return "These breeches reach reach down to mid-calf and "+
           "fit closely to the skin. Although simple in design, "+
           "they are comfortable and warm. "+
           "They are "+tnt+" in color and are made of "+
           ""+size+ ".\n";
}                                        

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
