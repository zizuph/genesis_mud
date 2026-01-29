/* Darren of Tarsis, Shopkeeper of the Keep by Morrigan 1/97 */
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

inherit M_FILE

inherit "/std/act/action";

#include "./std/killer.h"

public void
create_krynn_monster()
{
    set_name("darren");
    set_living_name("darren");
    set_race_name("human");
    set_title("of Tarsis, the Merchant of Vingaard");
    set_long("This plump and jolly man works in Vingaard Keep as owner of "+
      "the General Store. His bald head, and black beard make you think "+
      "of pirates when you look upon him. Though he looks a bit untrust"+
      "worthy with his crooked grin, you imagine that anyone working in "+
      "Vingaard Keep is fair.\n");
    add_name(({"merchant","shopkeeper","man"}));
    set_adj("jovial");
    add_adj("plump");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);
    add_prop(CONT_I_WEIGHT,80000);

    set_stats(({120,80,118,52,69,81}));
    set_skill(SS_DEFENCE,        50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   75);

    set_alignment(450);
    set_knight_prestige(-2);

    set_act_time(5);
    add_act("say I've not had the cleanest past, I'll admit, but a Knight "+
      "convinced me to change my ways, and change I have!");
    add_act("say I miss the seas sometimes, though.");
    add_act("scratch chin");
    add_act("chuckle amusedly");
    add_act("ponder his old ways.");
    add_act("say I'll be more than happy to deal with you!");
    add_act("say This is a good life. Maybe not as exciting as my past, but "+
      "I don't miss those days much.");
    add_act("smile thoughtfully");

    set_cact_time(4);
    add_cact("fume");
    add_cact("growl");
    add_cact("say I've had my share of fights!");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'sea'","say Yes, I travelled " +
      "the sea for many years, but I'd rather not talk about it.", 1);
    add_ask(" [about] 'knight'","say Well, I didn't trust him at first, "+
      "but he showed me that his heart was true and good.",1);
}

void
attacked_by(object ob)
{
    TO->command("shout How dare you attack me! I may not be a Knight, but "+
      "I can hold my own in a fair fight!");
    ::attacked_by();
}

