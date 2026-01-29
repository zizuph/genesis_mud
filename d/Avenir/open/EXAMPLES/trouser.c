
inherit "/d/Avenir/inherit/cloth_arm";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/wa_types.h"


string randsize();
string randtnt();

string size=randsize();
string tnt=randtnt();

void
create_armour()
{
   set_name("bazaar_trousers");
   add_name("trousers");
    add_name(({"harem", "pants", "harem pants"}));
   set_short("@@short_desc");
   set_long("@@long_desc");
   set_adj(size);
   set_adj(tnt);
   set_ac(random(5) + 10);
   set_at(A_LEGS);

   add_prop(HEAP_S_UNIQUE_ID, "trousers_" + tnt + "_" +size);
   add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
   add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
}             



string
randtnt()
{
   string str;

   switch(random(7))
   {   
      case 0: str="blue";    break;
      case 1: str="green";   break;
      case 2: str="red";     break;
      case 3: str="yellow";  break;
      case 4: str="black";    break;
      case 5: str="purple";   break;
      case 6: str="white";   break;
   }
   return str;                                                                               
}
string
randsize()
{
   string str;

   switch(random(3))
   {   
      case 0: str="satin";         break;
      case 1: str="velvet";        break;
      case 2: str="silk";          break;
   }
   return str;                                                                               
}

string
short_desc()
{
   return ""+tnt+ " "+size+ " harem pants";
}

string
long_desc()
{
    return "These trousers are loose-fitting from waist to thigh, "+
           "they taper to fit snugly below the knee to the ankle. "+
           "They are "+tnt+" in colour and are made of the "+
           "finest "+size+ ".\n";
}
