#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#define COLOURS ({"blue", "pale-blue","yellow", "grey", "white", "pink" })
#define STYLE ({"woolen", "linen", "tight-bodiced", "high-necked", "modest", "laced" })
#define TYPE ({"bliaud", "dress", "gown"})

public void
create_earthsea_wearable_item()
{
    string colour = COLOURS[random(sizeof(COLOURS))];
    string style = STYLE[random(sizeof(STYLE))];
    string type = TYPE[random(sizeof(TYPE))];
    set_name(type);
    add_name("dress");
    add_name("gown");
    add_name("bliaud");
    set_adj(colour);
    set_adj(style);
    set_adj(({"grey", "woolen"}));
    set_short( colour + " " + style + " " + type);
    set_long("The women's " + type + " fits closely through the torso, has long wide sleeves and " +
        "is belted. There is a waistline seam which permits " +
        "a closer fitting top and a fuller skirt. The upper half of the " +
        "garment can be laced to create the more form fitting silhouette.\n");
    set_layers(100);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_BODY | A_L_ARM | A_R_ARM | A_LEGS);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 100);
}

public mixed
wear_earthsea_item(object item)
{
    object tp = this_player();
    string poss = tp->query_possessive();

    write("You slip the " + short() + " over your head smoothing it out " +
        "over your hips. You then deftly lace up bodice followed by buckling " +
        "the belt around your waist.\n");
    say(QCTNAME(tp) + " slips the " + short() + " over " + poss +
        " head, smoothing it over " + poss + " hips then deftly lacing up " +
        "the bodice, followed by buckling the belt around " + poss +
        " waist.\n");
    return 1;
}

public mixed
remove_earthsea_item(object item)
{
    object tp = this_player();
    string poss = tp->query_possessive();

    write("You unbuckle the " + short() + ", unlace the bodice, then " +
        "pull it off over your head.\n");
    say(QCTNAME(tp) + " unbuckles the " + short() + ", unlaces the bodice, " +
        "then pulls it off over " + poss + " head.\n");
    return 1;
}
