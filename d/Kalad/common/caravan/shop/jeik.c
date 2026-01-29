#include "../default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include <ss_types.h>

void
create_monster()
{
    ::create_monster();

    set_default_answer("The innkeeper looks confused.\n");
    add_ask(({"anything"}), "The innkeeper whispers drunkingly: Um, the "+
      "answer is ... 42!\n");
    set_name("jenn");
    add_name("innkeeper");
    set_race_name("human");
    set_adj("portly");
    add_adj("balding");
    set_long("This jovial-looking individual looks like the innkeeper of "+
      "the Journey's End Inn. Clearly he's been an innkeeper for quite a "+
      "while, the cause of his hanging gut and thirst for beer.\n");
    set_stats(({75, 50, 75, 75, 75, 50}));
    set_alignment(500);
    set_skill(SS_AWARENESS, 50);

    set_act_time(3);
    add_act("burp");
    add_act("greet all");
    add_act("hug all");
    add_act("emote farts silently but violently.");
    add_act("ask human Got any beer?");
    add_act("ask elf Got any flowers?");
    add_act("ask dwarf Got any scissors?");
    add_act("ask gnome Got any gizmos?");
    add_act("ask hobbit Got any stew?");
    add_act("ask goblin Got any dung?");

    set_title("the Innkeeper");

    add_speak("huh?\n");
    set_knight_prestige(-5);
}

/*
void
do_die(object killer)
{
    string text;
    if(query_hp() > 0) return;
    killer->catch_msg("A large group of city guardsmen arrives.\n");
    say("A large group of city guardsmen arrives.\n");
    killer->catch_msg("One guard shouts: Murderer! You'll rot in jail for this!\n");
    say("One guard shouts: Murderer! You'll rot in jail for this!\n");
    killer->catch_msg("You are bodily dragged to jail!!\n");
    killer->move_living("out the door and to the jail, accompanied by several guardsmen", "/d/Kalad/common/trade/jail");
    ::do_die(killer);
}
 */
