#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_RPAW 0
#define A_LPAW 1
#define A_TOOTH 2

public int
pet_cat()
{
    object tp = this_player();
    write("You pet the little black cat.\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " pets the little "+
        "black cat.\n", ({ tp }));
    command("purr");
    return 1;
}

public void
create_creature()
{
    set_name("cat");
    set_living_name("_witchs_cat_");
    set_short("little black cat");
    set_adj(({"little", "black"}));
    set_long("A little black cat, the favourite pet belonging " +
        "to the witch.\n");
    set_gender(G_FEMALE);
    add_prop(OBJ_M_NO_ATTACK, "You feel the little cat is " +
        "protected by unseen forces.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "You feel the little cat is " +
        "protected by unseen forces.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, " accepts nothing from you.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    default_config_creature(5);
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);
    set_attack_unarmed(A_LPAW, 10, 20, W_BLUDGEON, 35, "left paw");
    set_attack_unarmed(A_RPAW, 10, 20, W_BLUDGEON, 35, "right paw");
    set_attack_unarmed(A_TOOTH, 10, 20, W_SLASH, 35, "sharp teeth");
    set_act_time(80);
    add_act("purr");
    add_act("emote licks a paw and cleans its face.");
    add_cmd_item(({"cat", "black cat", "little cat", "little black cat"}),
        "pet", pet_cat);
}
