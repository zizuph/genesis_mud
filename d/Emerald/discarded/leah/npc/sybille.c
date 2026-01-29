inherit "/std/monster";

#include "/d/Emerald/defs.h"

void
create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("sybille");
    set_race_name("human");
    set_gender(G_FEMALE);
    add_adj("tall");
    add_adj("beautiful");
    set_long(break_string("She is a tall, beautiful woman with flaxen "+
	"blonde hair and a vacant expression on her perfect face.\n", 76));

    set_stats( ({ 50, 60, 40, 10, 20, 40 }) );

    set_alignment(250);

    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    add_act( ({ "say I guess you saw the pitiful state the rose bushes are in.",

	"sigh",

	"say " + implode(exclude_array(explode(
	      break_string("My sweetheart, who is the gardener here, "+
		"won't take care of my once-lovely roses or even speak to "+
		"me because he caught me with a horrid elf who enchanted me "+
		"into believing he was my lover.", 51, 14), ""), 0, 13), ""),

	"giggle",

	"say " + implode(exclude_array(explode(
	      break_string("But when that elf heard my lover approaching, "+
		"he ran and hid them! He laughed as he scurried through the "+
		"window and said I would only find them \"when the enchanted "+
		"roses bloom thrice.\" Now, what does that mean?", 51, 14), ""), 0, 13), ""),

	"giggle",

	"say " + implode(exclude_array(explode(
	      break_string("When he called out, \"Look to the colors "+
		"to find where your treasure is hidden!\" I became totally "+
		"confused.", 51, 14), ""), 0, 13), ""),

	"sigh",

      }) );
}
