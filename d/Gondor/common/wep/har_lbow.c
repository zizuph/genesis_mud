/*
 * Haradrim longbow, used by the soldiers of Haradrim in the camp
 * -- Finwe, July 2005
 *
 *    Toby fixed typo @ 21 Feb 2007
 */

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

inherit "/std/bow";

int normal_hit = 47,
    normal_pen = 50,
    npc_hit    = 56,
    npc_pen    = 57;

public void
create_bow()
{
    set_adj("black");
    set_adj("wooden");
    add_name("longbow");
    set_short("wooden black longbow");
    set_long("This is a longbow commonly used by the soldiers of Harad. " +
        "It is made of wood that has been carved and decorated with dark " +
        "markings. It's design is simple, yet deadly when used by a " +
        "skilled bowman. @@check_string@@\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(normal_hit);
    set_pen(normal_pen);
    stringed = 1;

    add_item(({"markings", "dark markings"}),
        "They are black, and painted on by one skilled in the dark arts. " +
        "There is an red, lidles eye painted on the front of the bow. \n");
    add_item(({"eye", "lidless eye", "lidless red eye", "red eye"}),
        "The eye is rimmed with red fire, and oval shaped. It's slitted " +
        "like a cat's eye and is colored red.\n");
    add_item(({"limbs"}),
        "The limbs are the top and bottom ends of the bow. The limbs " +
        "are decorated with dark runes and @@check_limbs@@\n");
    add_item(({"handle"}),
        "This is the center of the bow, and often called the grip. It " +
        "does not bend while shooting the arrow and quite thick.\n");

    set_valid_projectile_function("is_quarrel");
}

// let npcs hit better with it
wield_check()
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(npc_hit);
        set_pen(npc_pen);
        query_wielded()->update_weapon(TO);
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, wield_check);
        set_secondary_wep_cmd("wield scimitar");
    }
    return 0;
}

mixed
unwield(object what)
{
    set_hit(normal_hit);
    set_pen(normal_pen);
    query_wielded()->update_weapon(TO);
    return 0;
}

string check_string()
{
    if(stringed == 0)
        return "The upper and lower limbs of the bow are straight. The " +
        "bow is not strung.\n";
    else
       return "The upper and lower limbs of the bow curve inwards. The " +
       "bow is strung from both limbs with a string.\n";
}

string check_limbs()
{
    if(stringed == 0)
        return "straight as the bow is not strung.\n";
    else
       return "curve inwards from the string stretched between them.\n";
}
