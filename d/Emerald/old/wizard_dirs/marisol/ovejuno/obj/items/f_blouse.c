// updated 4:25 PM 1/15/97 by Lilith
// added recovery code borrowed from special_hat.c

/* Modified by Marisol (07/15/98) to be used in the village of
 * Ovejuno in Emerald. */

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
void init_the_blouse();

void set_color(string str)  {    color = str;    }
void set_type(string str)   {    type = str;     }

public nomask void
create_object()
{
   init_the_blouse();
   set_name("gorgi_blouse");
   add_name(({"blouse", "V-neck blouse"}));
   add_adj("short");
   set_slots(A_BODY | A_ARMS);
   set_layers(0);
   set_looseness(0);

   add_prop(HEAP_S_UNIQUE_ID, "blouse_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
   add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
   add_prop(OBJ_I_VALUE, 500);

}

void 
init_the_blouse()
{
    if (!color) color = randtnt(); 
    if (!type) type = randsize();

    set_short(""+ color +" "+ type +" blouse");

    set_long("The blouses that come from Gorgi's store are quite "+
        "pretty and also functional for his customers, being the "+
        "villagers or the maids of the castle. These clothes are "+
        "beautiful in color and weave. This blouse has a V-neck "+
        "with white lace, that enhance the line of the neck of the "+
        "bearer. They are long-sleeved to warn off the cold wind from "+
        "land or sea. This particular blouse is "+ color +" in "+
        "color.\n");


    switch(type)
    {
    case "wool":
    add_item("wool", "The wool of this blouse come from the sheep "+
        "rise here in the mountains in Emerald. The locals are good "+
        "working with wool fibers to create a textile warm and nice "+
        "for this blouse. A seamtress, that works for Gorgi, makes "+
        "this dainty piece.\n");
    break;

    case "gauze":
    add_item("gauze", "This very thin, light and almost transparent "+
    "material is loosely woven with the finest silk of Telbarin. "+
    "These blouses are mostly traded with the nomadic people that "+
    "visit the village from time to time.\n");

    break;

    case "silk":
    add_item("silk", "This silk is so fine that feels and looks like "+
    "buterfly' wings. The origin of this material is hard to tell. "+
    "It seems that come from a far away land, something that Gorgi "+
    "undoubtly bought from traders.\n");
    break;
    }

    set_adj(({color, type}));
    return;
}

string
randtnt()
{
   string str;

   switch(random(8))
   {
      case 0: str="azure";    break;
      case 1: str="green";    break;
      case 2: str="crimson";  break;
      case 3: str="lemon";    break;
      case 4: str="ivory";    break;
      case 5: str="lavender"; break;
      case 6: str="white";    break;
      case 7: str="silver";   break;
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
      case 1: str="gauze";          break;
      case 2: str="silk";          break;
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


    init_the_blouse();

    return;
}    

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
