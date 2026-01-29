

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit AC_FILE
inherit "/std/act/attack";

inherit "/std/act/action";

void
create_creature()
{
    int i;

    set_name("dragon");
    set_race_name("dragon");
    set_adj("faery");
    add_adj("tiny");
    set_short("tiny faery dragon");

    set_gender(0);
    set_long("This tiny serpent is about twice the length " +
      "of your arm, with a large lizard-like head that seems " +
      "permenantly stuck with a mischievous grin. Butterfly " +
      "wings sprout out from tiny scales that shimmer from " +
      "deep purple to emerald green.\n");

    set_stats(({35,160,70, 70, 45, 75}));

    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_AWARENESS, 100);

    set_act_time(9);
    add_act("hide");
    add_act("hide");
    add_act("hide");
    add_act("emote buzzes furiously through the trees.");
    add_act("giggle misc");
    add_act("grin misch");
    add_act("emote clasps his tiny claws together eagerly.");

    set_cact_time(5);
    add_cact("say Wassa matter? Can't take a friendly prank?");
    add_cact("emote doesn't like fighting.");
    add_cact("emote pulls his lips back and snarls a toothy snarl!");

    set_hp(5000);
    set_alignment(200);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_attack_unarmed(1, 75, 35, W_IMPALE, 30, "bite");
    set_attack_unarmed(2, 50, 20, W_SLASH, 35, "right claw");
    set_attack_unarmed(3, 50, 20, W_SLASH, 35, "left claw");

    set_hitloc_unarmed(1, 80, 86, "body");
    set_hitloc_unarmed(2, 50, 10, "head");
    set_hitloc_unarmed(3, 2, 2, "right butterfly wing");
    set_hitloc_unarmed(4, 2, 2, "left butterfly wing");


    clone_object("/d/Ansalon/balifor/flotsam_forest/obj/faery_egg")->move(TO);
    seteuid(getuid(TO));
}

void
do_prank(object enemy)
{
    command("reveal myself");
    write("A tiny faery dragon breathes a cloud of faery dust " +
      "into your face! You feel bedazzled...\n");
    say(QCTNAME(TO)+ " breathes a cloud of faery dust " +
      "into " +QTNAME(TP)+ "'s face! " +HE(TP)+ 
      " looks quite confused.\n");
    command("giggle misch");
    clone_object("/d/Ansalon/balifor/flotsam_forest/obj/faery_dust")->move(TP);
}

void
init_living()
{
    if(TP->query_race() != "elf" && TP->query_race_name() != "half-elf" &&
      TP->query_race_name() != "kender")
	if(!P("faery_dust",TP))
	    set_alarm(0.1, 0.0, "do_prank", TP);

    ::init_living();
}

