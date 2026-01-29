
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/balinost/local.h"

#include <ss_types.h>
#include <macros.h>
inherit "/d/Genesis/lib/intro";
inherit AM_FILE
inherit AUTO_TEAM

#define SHIRT "/d/Ansalon/silvanesti/balinost/objs/shirt.c"
#define PANTS BOBJ + "pants.c"

string
ask_help()
{
    command("introduce myself");
    command("say Oh, I'm so glad you asked.  I seem to have lost something.");
    command("pout");
    command("say if you could help me find it I would be very thankful.");
    command("smile hopefully");
}

void
create_krynn_monster()
{
    set_name("hemdash");
    set_race_name("kender");
    set_adj(({"tired","forgetful"}));
    set_long("This kender has a worried expression on his face.  He "+
      "is always losing things he has borrowed and is afraid he won't "+
      "be able to give the items he's borrowed back.\n");
    set_title("Softfoot");
    set_short("tired forgetful kender");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_act_time(20);
    add_act("emote searches around the room for something he misplaced.");
    add_act("search here for something");
    add_act("yawn");

    add_ask("help", ask_help);

    trig_new("%w 'gives you a' %s", "react_given");

    set_stats(({ 50, 50, 47, 35, 35, 50 }));

    set_hp(6000);
    set_alignment(450);
    set_knight_prestige(-200);

    setuid();
    seteuid(getuid());

    clone_object(SHIRT)->move(this_object(), 1);
    clone_object(PANTS)->move(this_object(), 1);
    command("wear all");

    add_prop(LIVE_I_NEVERKNOWN,1);

}

void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));
    command("say I'm sure glad to see you, " + who->query_name() + "!");
    command("ponder");
    command("say Maybe you can help me with some things I've lost.");
}

void
react_given()
{
    command("say Thank you for finding it for me!");
    write("You feel a little more experienced!\n");
}
