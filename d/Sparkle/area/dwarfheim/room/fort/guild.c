/*     The Guild in Dwarfheim, original code by Styles, modified by Gresolle.
       Remade totally by Lugdush 1996-06-05
 */

#pragma save_binary
#pragma strict_types

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>

#include "defs.h"

void set_up_skills();

void
create_room()
{
    set_short("Adventurer's guild");
    set_long("You are in the Adventurer's Guild in Dwarfheim.\n"+
      "Here you may <meditate> to estimate your stats.\n"+
      "You can also <improve> your skills or <learn>\n"+
      "new ones. There is an exit back to the street in\n"+
      "the west wall.\n");
    add_item(({"west wall", "wall"}), "It holds the exit to the streets.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit("corr2", "west", 0);

    /* Meditate */
    create_guild_support();

    /* Train */
    create_skill_raise();
    set_up_skills();
}

void
init()
{
    ::init();

    init_guild_support();
    init_skill_raise();
}

string
train_text(int skill)
{
    string what, does, *text;

    switch(skill) {
    case SS_WEP_AXE:
        what="handle an axe in combat";
        break;

    case SS_APPR_MON:
        what="appraise your opponents";

        break;
    case SS_APPR_OBJ:
        what="appraise different objects";

        break;
    case SS_LANGUAGE:
        what="understand foreign languages";

        break;

    case SS_CLIMB:
        what="climb walls and mountains";

        break;

    case SS_AWARENESS:
        what="be aware of your surroundings";

        break;
    case SS_LOC_SENSE:
        what="sense of location";

        break;

    case SS_TRADING:
        what="trade and make deals";

        break;

    case SS_SNEAK:
        what="be stealthy";

        break;

    case SS_HIDE:
        what="hide inside rooms";

        break;

    case SS_APPR_VAL:
        what="appraise the value of an object";

        break;

    case SS_OPEN_LOCK:
        what="open locks";

        break;

    default:
        what="do nothing. THIS IS A BUG";

        break;
    }
    return what;
}

void
set_up_skills()
{
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_UNARM_COMBAT, "fight unarmed",              0,0,30 );
    sk_add_train(SS_DEFENCE, ({ "defend yourself",
        "use defence skill"}),         0,0,20 );
    sk_add_train(SS_BLIND_COMBAT, "fight when blind",           0,0,20 );
    sk_add_train(SS_WEP_AXE,    train_text(SS_WEP_AXE),         0,0,30 );
    sk_add_train(SS_APPR_MON,	train_text(SS_APPR_MON),        0,0,30 );
    sk_add_train(SS_APPR_OBJ,	train_text(SS_APPR_OBJ),        0,0,30 );
    sk_add_train(SS_LANGUAGE,      train_text(SS_LANGUAGE),        0,0,30);

    sk_add_train(SS_CLIMB, train_text(SS_CLIMB),           0,0,30 );
    sk_add_train(SS_AWARENESS,     train_text(SS_AWARENESS),       0,0,30);
    sk_add_train(SS_LOC_SENSE,	train_text(SS_LOC_SENSE),       0,0,30 );
    sk_add_train(SS_TRADING, train_text(SS_TRADING),           0,0,30 );
    sk_add_train(SS_SNEAK, train_text(SS_SNEAK),           0,0,20 );
    sk_add_train(SS_HIDE, train_text(SS_HIDE),           0,0,20 );
    sk_add_train(SS_OPEN_LOCK, train_text(SS_OPEN_LOCK),           0,0,20 );
    sk_add_train(SS_APPR_VAL, train_text(SS_APPR_VAL),           0,0,30 );
}

