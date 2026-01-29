#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("armour");

    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,10000);
}

void
configarmour(int l)
{
    string adj,lo,na;
    int at;

    switch(l)
    {
    case 0: adj = "wooden";
        na = "helmet";
        lo = "The helmet is made of oak, and reinforced with iron stripes.\n";
        at = A_HEAD;
        break;
    case 1: adj = "copper";
        na = "leggings";
        lo = "A pair of copper leggings, to protect your legs.\n";
        at = A_LEGS;
        break;
    case 2: adj = "leather";
        na = "shirt";
        lo = "Obviously an old cow has contributed with the material to this armour.\n";
        at = A_TORSO;
        break;

    case 3: adj = "old";
        na = "gloves";
        lo = "The gloves are made of thin leather, with a fine net of iron inside.\n";
        at = A_HANDS;
        break;

    case 4: adj = "splint";
        na = "mail";
        lo = "The splint mail was originally made for the Royal Guards.\n";
        at = A_TORSO;

    case 5: adj = "plate";
        na = "mail";
        lo = "The platemail looks a little rusty, but is still fully usable.\n";
        at = A_TORSO;

    }

    set_long(lo);
    set_short(adj + " " +na);
    set_adj(adj);
    add_name(na);

    set_at(at);
    set_ac(7*l);
}

void
init_recover(string arg)
{
    configarmour(random(6));
}

