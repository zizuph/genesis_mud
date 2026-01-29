// Taerie the Sooper
// creator(s):	Lilith, Aug 1997
// last update:	
//    Manat, Sep 2002 - Changed "An young gnome" to "A young gnome".
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "/d/Avenir/common/bazaar/bazaar.h"
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
# include "/d/Avenir/include/guilds.h"

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

void equip_me();

void
create_monster()
{
    set_name("taerie");
    set_title("ini Wer'a, assistant manager of the Dancing Goat");
    add_name(({"shopkeeper","keeper", "scooper", "manager", "assistant"}));
    set_race_name("gnome");
    set_gender(G_FEMALE);

    add_adj(({"friendly", "fair-haired"}));
    set_long("A young gnome who is happy to be scooping ice cream instead "+
	    "of herding goats.\n");
    set_act_time(4);
    add_act("bow");
    add_act("wiggle happ");
    add_act("bounce slightly");
    add_act("emote wipes up the counter.");
    add_act("emote washes an ice cream scooper.");
    add_act("emote bops happily around, cleaning up.");
    add_act("emote points at the sign.");
    add_act("say This is the best ice cream in the world... or maybe it's "+
	    "the only ice cream in the world.");
    add_act("say Please do enjoy a scoop of Happy Goat ice cream.");
    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(0);
    set_knight_prestige(-1);
    
    equip_me();
}

public void
equip_me()
{
    object chain, shirt, pants;

    seteuid(geteuid(this_object()));
    MONEY_MAKE_SC(random(20))->move(this_object());

    shirt = clone_object(BAZAAR + "Obj/worn/blouse");
    shirt->move(TO, 1);

    chain= clone_object(BAZAAR + "Obj/worn/belly_chain");
    chain->move(TO, 1);

    pants = clone_object(BAZAAR + "Obj/worn/trouser");
    pants->move(TO, 1);

    command("wear all");
}

