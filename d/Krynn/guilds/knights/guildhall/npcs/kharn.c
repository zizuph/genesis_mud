/* Kharn son of Khain, Shopkeeper of the Keep by Morrigan 1/97 */
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
    set_name("kharn");
    set_living_name("kharn");
    set_race_name("dwarf");
    set_title("the son of Khain");
    set_long("You look upon this very young dwarf and wonder why he's the "+
      "shopkeeper. He's short and stocky, as is typical with most dwarves, "+
      "but unlike most dwarves he has no beard, probably because of his "+
      "young age. He fidgets with the items in the storeroom, apparently "+
      "bored.\n");
    add_name(({"kid","shopkeeper","child"}));
    set_adj("very young");
    add_adj("sturdy");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);
    add_prop(CONT_I_WEIGHT,60000);

    set_stats(({60,50,65,52,55,60}));
    set_skill(SS_DEFENCE,        50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   50);

    set_alignment(450);
    set_knight_prestige(-2);

    set_act_time(5);
    add_act("say I hope my pa gets back soon.");
    add_act("sigh");
    add_act("emote smiles boredly at you.");
    add_act("twiddle");
    add_act("say My pa left on some quest, and left me here with my Uncle "+
      "Chert, who put me to work.");
    add_act("say Do you have any interesting stories to tell?");
    add_act("say It's an easy enough job, not much to do, though...");
    add_act("smile politely");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'pa'","say He's gone on some quest.",1);
    add_ask(" [about] 'quest'","say I don't know, pa didn't " +
      "tell me where he was going.",1);
    add_ask(" [about] 'uncle' / 'chert'","say My Uncle Chert " +
      "is a famous blacksmith! He works just down the street.",1);
    add_ask(" [about] 'stories'","say I like hearing stories!",1);


    set_cact_time(4);
    add_cact("gasp");
    add_cact("glare");
    add_cact("shout I'll be a bearded gnome before I'll run from you!");
}

void
attacked_by(object ob)
{
    TO->command("shout Uncle Chert! Uncle Chert! This person is trying to "+
      "kill me!");
    ::attacked_by();
}
