/*
 * /d/Ansalon/guild/kender_occ/npc/trainer.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender trainer
 *
 * Gwyneth, 1999
 */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    set_name("brimar");
    set_race_name("kender");
    set_title("Starthumb of Kendermore");
    set_long("This kender can't seem to sit still. She runs back and " +
        "forth between her students, correcting a grip here, giving an " +
        "extra tip there. Her topknot, decorated with ribbons and bells, " +
        "bounces from side to side as she darts around. Perhaps she could " +
        "give you a bit of training. If you've misplaced your guild item, " +
        "you can ask her for a new one.\n");
    add_name("trainer");
    set_adj("dark-haired");
    add_adj("energetic");
    set_gender(G_FEMALE);
    set_introduce(1);

    set_act_time(5);
    add_act("say I can teach you many different things!");
    add_act("say Would you like to train?");
    add_act("emote brushes her topknot back from her face.");
    add_act("emote claps a hand over her mouth to stifle a giggle.");
    add_act("emote demonstrates the correct way to hold a knife.");
    add_act("emote shows a student a defensive stance.");
    add_act("say No, no! Do it this way!");

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_WEP_POLEARM, 65);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_PARRY, 40);
    set_skill(SS_SNEAK, 90);
    set_skill(SS_HIDE, 90);
    set_skill(SS_TRACKING, 65);
    set_skill(SS_PICK_POCKET, 75);
    set_skill(SS_OPEN_LOCK, 75);
    set_skill(SS_LANGUAGE, 60);

    set_alignment(350);
    set_knight_prestige(-40);

    set_default_answer("The noise of training drowns out your question.\n");
    add_ask(({"train", "training", "trainer"}), "say I'm the trainer " +
        "here. What would you like to train?", 1);
    add_ask(({"pick pocket", "borrow", "borrow skill", "pick pocket skill"}),
        "say I can train you to borrow things. If diligent, you can " +
        "become a superior veteran!", 1);
    add_ask(({"find and remove traps", "find and remove traps skill"}),
        "say I can train you to disarm traps. If diligent, you can " +
        "become a superior layman!", 1);
    add_ask(({"open lock", "open lock skill"}), "say I can train you to " +
        "open locks. If diligent, you can become a superior veteran!", 1);
    add_ask(({"polearm", "polearm skill"}), "say I can train you to use " +
        "a polearm in battle. If diligent, you can become a superior " +
        "veteran!", 1);
    add_ask(({"hide", "hide skill"}), "say I can train you to hide things " +
        "and yourself from common notice. If diligent, you can become a " +
        "superior master!", 1);
    add_ask(({"sneak", "sneak skill"}), "say I can train you to sneak " +
        "past peoples' notice. If diligent, you can become a superior " +
        "master!", 1);
    add_ask(({"defence", "defence skill"}), "say I can teach you to " +
        "defend yourself in combat. If diligent, you can become a " +
        "superior professional!", 1);
    add_ask(({"awareness", "awareness skill"}), "say I can teach you to " +
        "be more aware of your surroundings. If diligent, you can " +
        "become a superior veteran!", 1);
    add_ask(({"sling", "sling skill"}), "say There's not enough room here " +
        "to teach that. Try the target area on the roof.", 1);
    add_ask(({"dodge", "dodge skill"}), "say There's not enough room here " +
        "to teach that. Try the practice ground on the roof.", 1);
    add_ask(({"taunt", "taunt skill"}), "say I can teach you how to " +
        "use your wit and a sharp tongue in combat. If diligent, you can " +
        "become a superior guru!", 1);
    add_ask(({"hoopak skill", "hoopak alteration", "alter"}),
        "say I can teach you the art of altering weapons into hoopaks. " +
        "If diligent, you can become a superior journeyman!", 1);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields misc. items, armours and weapons.
 */
void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));
    clone_object(KOBJ + "std_knife")->move(this_object());
    clone_object(KOBJ + "hoopak")->move(this_object());
    clone_object(KOBJ + "leggings")->move(this_object());
    clone_object(KOBJ + "boots")->move(this_object());
    clone_object(KOBJ + "cape")->move(this_object());
    clone_object(KOBJ + "blouse")->move(this_object());
    clone_object(KOBJ + "vest")->move(this_object());

    command("wear all");
    command("wield all");
}

