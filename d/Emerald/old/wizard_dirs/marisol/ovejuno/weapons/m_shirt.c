// updated 4:25 PM 1/15/97 by Lilith
// added recovery code borrowed from special_hat.c
/* Used by Marisol for Fan's store in the new Re Albi
 * (3/5/98) */
/* Modified by Marisol(07/15/98) to be used for the village of
 * Ovejuno in Emerald.*/


inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Emerald/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define HIS  this_player()->query_possessive()

string color, type;
string randsize();
string randtnt();
void init_the_tunic();

void set_color(string str)  {    color = str;    }
void set_type(string str)   {    type = str;     }

public nomask void
create_object()
{
   init_the_tunic();
   set_name("shepherd_tunic");
   add_name(({"tunic", "humble tunic"}));
   add_adj("long");
    set_slots(A_BODY | A_ARMS);
    set_layers(0);
    set_looseness(0);

   add_prop(HEAP_S_UNIQUE_ID, "tunic_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
   add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
   add_prop(OBJ_I_VALUE, 550);

}

void
init_the_tunic()
{
    if (!color) color = randtnt();
    if (!type) type = randsize();

    set_short(""+ color +" "+ type +" tunic");

    set_long("This humble tunic is the one favor by the shepherds "+
        "here in Ovejuno. It has long-sleeves, a round neck and "+
        "its reach to mid-tigh. It is really good to warn off "+
        "the cold wind from mountain or the far sea.\n");

    switch(type)
    {

    case "canvas":
    add_item("canvas", "Usually canvas is a closely woven, "+
    "coarse cloth of hemp, cotton or linen, but not these ones. "+
    "This canvas is made with wool, although not of great quality, "+
    "is good enough to create a really nice and cheap textile. "+
    "This tunic seems to come from Gorgi's shop.\n");
    break;         

    case "wool":
    add_item("wool", "The wool from Ovejuno is nice although not  "+
    "remarkable. The fiber is soft and warm, really good for the cold "+
    "weather of the mountains.\n");
    break;                           

    }

    set_adj(({color, type}));
    return;
}

string
randtnt()
{
   string str;

   switch(random(5))
   {
      case 0: str="blue";    break;
      case 1: str="green";    break;
      case 2: str="red";  break;
      case 3: str="yellow";    break;
      case 4: str="white";    break;       
   }
   return str;
}

string
randsize()
{
   string str;

   switch(random(2))
   {

      case 0: str="canvas";        break;
      case 1: str="wool";          break;
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

    return rec;
}                                        
void
init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);


    init_the_tunic();

    return;
}                  

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
