// codpiece&breeches

// put in book in the library:
//    Large codpieces indicate large genitalia, high rank,
// or unmarried status. Smaller codpieces indicate the 
// reverse: small genitalia, low rank, or marriage. 
//    Sometimes, though, a man with many wives will have a
// large codpiece, so it isn't necessarily indicative of
// marriage status, but rather sexual availablity or 
// sexual prowess...
// Believe it or Not.

inherit "/std/armour";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/wa_types.h"

string randname();
string randsize();
string randtnt();

string name=randname();
string size=randsize();
string tnt=randtnt();

void
create_armour()
{
   set_name("_codpiece_");
   add_name(name);
   set_short("@@short_desc");
   set_long("@@long_desc");
   set_adj(size);
   set_adj(tnt);
   set_ac(random(5) + 10);
   set_at(A_LEGS);

   add_prop(HEAP_S_UNIQUE_ID, "codpiece_" + tnt + "_" +name);
   add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
   add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */

   add_item("codpiece", "It covers the crotch of tightfitting "+
      "men's trousers. It is decorated with various fertiliy "+
      "and virility symbols.\n");
   add_item(({"decoration", "decorations", "symbol", "symbols"}),
      "They are symbols of male potency.\n");
}             

string                                                                          
randname()
{                                                                               
   string str;

   switch(random(4))
   {
      case 0: str="leggings";  break;
      case 1: str="trousers";  break;
      case 2: str="hose";      break;
      case 3: str="breeches";  break;
   }
   return str;                                                                               
}

string
randtnt()
{
   string str;

   switch(random(10))
   {   
      case 0: str="blue";    break;
      case 1: str="green";   break;
      case 2: str="red";     break;
      case 3: str="yellow";  break;
      case 4: str="gray";    break;
      case 5: str="brown";   break;
      case 6: str="white";   break;
      case 7: str="purple";  break;
      case 8: str="maroon";  break;
      case 9: str="black";   break;
   }
   return str;                                                                               
}
string
randsize()
{
   string str;

   switch(random(9))
   {   
      case 0: str="a tiny";        break;
      case 1: str="a small";       break;
      case 2: str="an adequate";   break;
      case 3: str="a stupendous";  break;
      case 4: str="a huge";        break;
      case 5: str="an enormous";   break;
      case 6: str="an average";    break;
      case 7: str="a large";       break;
      case 8: str="a barely visible";  break;
   }
   return str;                                                                               
}

string
short_desc()
{
   return ""+tnt+ " " +name+ " with " +size+ " codpiece";
}

string
long_desc()
{
    return "These "+ name +" are "+ tnt +" in colour. They are "+
           "very form-fitting and have " +size+ " decorated "+
           "codpiece.\n";
}
