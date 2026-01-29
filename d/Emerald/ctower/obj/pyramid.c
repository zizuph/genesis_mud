/* ctower/obj/bpyr.c is cloned by ctower/trial1.c */

inherit "/std/object";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";
 
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

object *checked_color = ({ });
string color; 
 
string pyr_long();

void
reset_object()
{
    reset_ctower_object();
}

void
create_object()
{
    set_name("pyramid");
    add_name("crystal");
    add_name("ctower_pyramid");
    set_short("@@pyr_short@@");
    set_long(pyr_long);
    add_adj("small");
    add_adj("crystal");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 108);

    create_ctower_object();
}

void set_color(string pyramid_color)
{
    remove_name(color + "_ctower_pyramid");

    color = pyramid_color;
    add_name(color + "_ctower_pyramid");
}

int check()
{
    if (member_array(this_player(), checked_color) < 0)
    {
        checked_color += ({ this_player() });    
        return 1;
    }
  
    return 0;
}

string
pyr_long()
{
    if (member_array(this_player(), checked_color) < 0)
    {
        checked_color += ({ this_player() });
        add_adj(color);
        return  "This crystal pyramid is four sided, each " +
            "side being six centimeters across.  You also notice a faint " +
            color + " tint to the crystal.\n" ;
    }
  
    return "This " + color + " crystal pyramid is four sided, each side "+
      "being six centimeters across.\n";
}
 
string
pyr_short()
{
    if (member_array(this_player(), checked_color) < 0)
    {
        return "small crystal pyramid";
    }
  
    return color + " crystal pyramid";
}
 
