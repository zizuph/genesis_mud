// updated 4:25 PM 1/15/97 by Lilith
// added recovery code borrowed from special_hat.c

inherit "/d/Avenir/inherit/cloth_arm";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/wa_types.h"
#define HIS  this_player()->query_possessive()

string color, type;
string randsize();
string randtnt();

void set_color(string str)
{
    color = str;
}

void set_type(string str)
{
    type = str;
}

void init_the_blouse()
{
    if (!color) color = randtnt();
    if (!type) type = randsize();

    set_short(""+ color +" "+ type +" blouse");

    set_long("Among the Sybarite noblewomen, this blouse is known "+
        "as a cholie. It is cut from rich "+ type +". It is made to "+
        "fit snugly, clinging to shoulders and breasts while "+
        "while leaving the midriff bare. The sleeves are short, "+
        "ending well above the elbow, and edged with a wide "+
        "border of brocaded gold in a floral pattern. This "+         
        "particular cholie is "+ color +" in colour.\n");

    set_adj(({color, type}));
    return;        
}


void
create_armour()
{
   init_the_blouse();
   set_name("bazaar_blouse");
   add_name(({"blouse", "cholie"}));
   add_adj("short");
   set_ac(random(5) + 2);
   set_at(A_BODY);

   add_prop(HEAP_S_UNIQUE_ID, "blouse_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
   add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
   add_item(({"edge", "brocade", "pattern"}),
       "The edging of the sleeves is of brocaded gold in a pattern "+
       "of twining flowers.\n"); 
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
      case 4: str="ivory";   break;
      case 5: str="purple";   break;
      case 6: str="white";   break;
   }
   return str;                                                                               
}

string
randsize()
{
   string str;

   switch(random(4))
   {   

      case 0: str="satin";         break;
      case 1: str="velvet";        break;
      case 2: str="silk";          break;
      case 3: str="lace";          break;
   }
   return str;                                                                               
}

string 
query_recover()
{
    string rec;
    rec = MASTER + ":";
 
    rec += "#type#" + type;
    rec += "#color#" + color;

    rec += query_arm_recover();
    return rec;
}


void 
init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);

    init_arm_recover(arg);

    init_the_blouse();

    return;
}


