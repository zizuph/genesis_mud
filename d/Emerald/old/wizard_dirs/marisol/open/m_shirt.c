// updated 4:25 PM 1/15/97 by Lilith
// added recovery code borrowed from special_hat.c
/* Used by Marisol for Fan's store in the new Re Albi
 * (3/5/98) */
/* Modified by Marisol(07/15/98) to be used for the village of
 * Ovejuno in Emerald.*/

inherit "/std/object";
inherit "/lib/wearable_item";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string randsize();
string randtnt();
varargs void init_the_tunic(string type, string color);

static string recover_string = "";

public nomask void
create_object()
{
    init_the_tunic();
    set_name("gorgi_tunic");
    add_name(({"tunic", "elegant tunic"}));
    add_adj("long");
    set_slots(A_BODY | A_ARMS);
    set_layers(0);
    set_looseness(0);

    add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
    add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
    add_prop(OBJ_I_VALUE, 550);
}

varargs void
init_the_tunic(string type, string color)
{
    if (!color) color = randtnt();
    if (!type) type = randsize();

    recover_string = type + ";" + color;

    set_short(color + " " + type + " tunic");

    set_long("This long and elegant tunic comes from Gorgi's clothes "+
        "shop. This tunic has a rectangular neck and long-sleeves. The "+
        "sides of the tunic has an invert V-cut that facilitate "+
        "body movement. They are long-sleeved to warn off the "+
        "cold wind from land or sea. Peasants, servants, soldiers and "+
        "even noblemen enjoying using these shirts. This particular "+
        "tunic is "+ color +" in color.\n");

    switch(type)
    {
        case "canvas":
            add_item("canvas", "Usually canvas is a closely woven, "+
                "coarse cloth of hemp, cotton or linen, but not these ones. "+
                "This canvas is made with wool, although not of great " +
                "quality, is good enough to create a really nice and cheap " +
                "textile.  The resulting cloth is soft and resistent at the " +
                "same time, the best combination for both peasants and the "+
                "not-to-rich servants in both Ovejuno and the lord's " +
                "castle.\n");
            break;         
    
        case "wool":
            add_item("wool", "The wool from Ovejuno is nice although not  "+
                "remarkable. The fiber is soft and warm, really good for " +
                "the cold weather of the mountains.\n");
            break;                           
    
        case "silk":
            add_item("silk", "This silk is so fine that feels and looks like "+
                "buterfly wings. The origin of this material is hard to " +
                "tell. It seems that comes from a far away land, something " +
                "that Gorgi undoubtedly bought from traders.\n");
            break;
    }

    set_adj(({color, type}));

    return;
}

string
randtnt()
{
   return ({ "azure",
             "green",
             "crimson",
             "lemon",
             "ivory",
             "white",
             "silver",
           })[random(7)];
}

string
randsize()
{
    return ({ "canvas", "wool", "silk", })[random(3)];
}

string
query_recover()
{
    return MASTER + ":" + recover_string;
} 

void
init_recover(string arg)
{
    string type, color;
    sscanf(arg, "%s;%s", type, color);
    init_the_tunic(type, color);
}                  

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
