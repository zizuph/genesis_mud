#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "/sys/filter_funs.h"

string
random_extra()
{
    int i = random(29);

    if (i < 3)
	return "reginald";
    else if (i < 6)
	return "boris";
    else if (i < 7)
	return "anth";
    else if (i < 8)
	return "james";
    else if (i < 9)
	return "charles";
    else if (i < 10)
	return "norwood";
    else if (i < 11)
	return "febbo";
    else if (i < 12)
	return "amrocar";
    else if (i < 13)
	return "andian";
    else if (i < 14)
	return "ulf";
    else if (i < 15)
	return "gorbel";
    else if (i < 16)
	return "brit";
    else if (i < 17)
	return "daniel";
    else if (i < 18)
	return "wilhelm";
    else if (i < 19)
	return "obbo";
    else if (i < 20)
	return "tandel";
    else if (i < 21)
	return "ardindel";
    else if (i < 22)
	return "mitus";
    else if (i < 23)
	return "linus";
    else if (i < 24)
	return "landil";
    else if (i < 25)
	return "kathin";
    else if (i < 26)
	return "baern";
    else if (i < 27)
	return "sehkmaa";
    else
	return "fellir";
}

void
create_kalad_monster()
{
    string extra;

    extra = random_extra();

    set_name(extra);
    set_race_name("human");
    set_adj("hard-working");
    set_long("A tough-looking man that looks like he's been working all "+
      "day, one reason for his tired gaze and unemotionalness.\n");
    set_stats(({75, 50, 50, 40, 40, 50}));
    set_alignment(500);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);
    set_act_time(9);
    add_act("sigh");
    add_act("complain all");
    add_act("emote looks rather depressed.");
    add_speak("Life's a bitch.\n");
    set_knight_prestige(-5);
    set_title("the Labourer");
    MONEY_MAKE_SC(random(10))->move(this_object(), 1);
}
