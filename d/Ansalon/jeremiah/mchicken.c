#include "/d/Ansalon/common/defs.h"
inherit AC_FILE

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit "std/act/domove";
inherit "std/act/action";


void
create_creature()
{
    set_name("morgul chicken");
    set_short("chicken");
    set_long("A large black morgul chicken. Its eyeless sockets are "
      + "gleaming like red coals.\n");
    set_adj("black morgul");
    set_race_name("chicken");
    set_gender(G_MALE);

    set_act_time(3);
    add_act("emote goes: cluck cluck!");
    add_act("emote goes: buk buk buk bkaaaawk!");
    add_act("emote eyes you carefully through its eyeless sockets.");
    add_act("emote scratches in the earth.");
    add_act("emote pecks at your leg.");
    add_act("emote goes: bkaaaawk! buk buk bkaaaawk");
    add_act("emote stalks around.");

    add_prop(OBJ_M_NO_ATTACK, "The " + query_adj()
      + " chicken flutters away from you, out of harms way.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
}


void
init_living()
{
    ::init_living();
    add_action("kick_me", "kick");
    add_action("wrestle_me", "wrestle");
    add_action("elbow_me", "elbow");
}


int
kick_me(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!TO->id(str))
    {
        return 0;
    }

    TP->catch_msg("You kick the chicken across the room "
      + "where it lands in a cloud of dust and feathers.\n");
    tell_room(E(TO), QCTNAME(TP) + " kicks the chicken across "
      + "the room where it lands in a cloud of dust and "
      + "feathers.\n", ({ TP, TO }));

    return 1;
}


int
wrestle_me(string str)
{
    if (!strlen(str))
    {
        NF("Wrestle who?\n");
        return 0;
    }

    if (!TO->id(str))
    {
        NF("Wrestle who or what?\n");
        return 0;
    }

    TP->catch_msg("You viciously attempt to wrestle the chicken, "
      + "but you are badly defeated.\n");
    tell_room(E(TO), QCTNAME(TP) + " attempts to wrestle "
      + "the chicken, but is badly defeated!\n", ({ TP, TO }));

    return 1;
}


int
elbow_me(string str)
{
    if (!strlen(str))
    {
        NF("Elbow drop who?\n");
        return 0;
    }

    if (!TO->id(str))
    {
        NF("Elbow drop who or what?\n");
        return 0;
    }

    TP->catch_msg("Yout throw yourself at the chicken in an "
      + "attempt to elbow drop it. The chicken deftly sidesteps "
      + "your attempt and pecks you in the eye as you hit the "
      + "ground. Ouch that hurt!\n");
    tell_room(E(TO), QCTNAME(TP) + " throws " + OBJECTIVE(TP)
      + "self at the chicken in an attempt to elbow drop it. The "
      + "chicken deftly sidesteps " + POSSESSIVE(TP) + " attempt, " 
      + "and pecks " + OBJECTIVE(TP) + " in the eye as " 
      + PRONOUN(TP) + " hits the ground. Ouch that looked painful!\n",
      ({ TP, TO }));

    return 1;
}
