#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("jarvis");
    add_name("librarian");
    set_race_name("human");
    set_adj("quiet");
    set_short("librarian");
    set_long("This man must be the caretaker of all these wonderful books "+
      "surrounding you. He looks as if he expects you to cause some trouble "+
      "here.\n");
    set_stats(({50, 60, 50, 60, 60, 25}));
    set_alignment(100);
    set_skill(SS_AWARENESS, 100);
    set_act_time(3);
    add_act(({"poke all", "say Be careful with the books."}));
    add_act("emote looks lovingly at some books.");
    add_act("emote puts a book on a shelf.");
    add_act("put book in container");
    add_act("smile softly");
    add_speak("Please be quiet.\n");
    set_default_answer("The librarian says: What was it you were asking?\n");
    add_ask(({"books", "book"}), "The librarian says: You can borrow whatever books are in the glass container.\n");
    add_ask(({"help"}), "The librarian says: Please be more specific, what do you want help on?\n");
    add_ask(({"quest"}), "The librarian says: You don't really expect me to tell you that, do you?\n");
    add_ask(({"inner sanctum", "sanctum"}), "The librarian says: Ahh...I believe you must enter something to get to Entreri...but you didn't hear that from me.\n");
    add_ask(({"library"}), "The librarian says: Why, that's where we are!\n");
    add_ask(({"object"}), "The librarian says: Are you speaking of the "+
      "object our Lord so desires? If so, this is all the advice I can give "+
      "you...Search the wilderness in the northeast, and where the darkness "+
      "rules, the object lies.\n");
    set_knight_prestige(-1);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object(OBJ + "tcbook.c");
    arm->move(TO);
    arm = clone_object(OBJ + "tclspecs");
    arm->move(TO);
    command("emote goes shh at you.");
}
