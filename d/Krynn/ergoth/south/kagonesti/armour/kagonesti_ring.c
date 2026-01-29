#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/armour";

string get_long_desc()
{
    string desc = "This beautiful silver ring was handmade by the Kagonesti. ",
           color;

    switch(random(4))
    {
        case 0:
            color = "greenish";
            break;
        case 1:
            color = "baby";
            break;
        case 2:
            color = "aqua";
            break;
        default:
            color = "sky";
            break;
    }

    color += "-blue";
    
    if(random(2))
    {
        desc += "It is set with a large " + color
            + " turquoise stone, which is ";

        if(random(2))
            desc += "oval";
        else
            desc += "circular";

        desc += " in shape and features an interesting set of mineral "
            + "veins.";
    }
    else
    {
        desc += "It is inlaid with a dazzling pattern of " + color
            + " turquoise resembling a ";
        switch(random(5))
        {
            case 0:
                desc += "fish";
                break;
            case 1:
                desc += "leaf";
                break;
            case 2:
                desc += "bird";
                break;
            case 3:
                desc += "turtle";
                break;
            default:
                desc += "flower";
                break;
        }

        desc += ".";
    }

    return desc + "\n";
}
    
void create_armour()
{
    string material = one_of_list(({"silver", "turquoise"}));
    
    set_name("ring");
    set_adj(material);
    set_short(material + " ring");
    set_long(get_long_desc());
    set_ac(1);
    set_at(A_ANY_FINGER);
    
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 50 + random(1000));
}
