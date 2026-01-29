inherit "/std/monster";
#include "/sys/ss_types.h"
#include <wa_types.h>
#include "/sys/macros.h"
#include <money.h>
#include <language.h>
#include <stdproperties.h>


create_monster() {

    if (!IS_CLONE)
	return;

    set_name("bonka");
    set_race_name("giant");
    set_adj("big");

    set_long("This giant is BIG. You should have reason to be worried.\n");

			/* str,  dex,  con,  int,  wis,  dis */
    set_stats(({ random(60)+100,   85,   55,   10,   22,   100}));
    
    set_hp(20000); /* reduced to correct level according to con. */

    set_alignment(-50);
    set_skill(SS_WEP_SWORD, 30);
    set_skill(SS_WEP_CLUB, 35);
    set_skill(SS_WEP_MISSILE, 55);

    add_prop(CONT_I_WEIGHT, 2000000);
    add_prop(CONT_I_HEIGHT, 13000);
    add_prop(CONT_I_VOLUME, 570000);
    /* add_prop(OBJ_I_NO_INS, 1); */

    seq_new("do_things");
    seq_addfirst("do_things", ({
	"@@equip_me" + " @@initsay",		"grin"
    }));
}

object wpn;

equip_me() {

    seteuid(getuid(this_object()));

    if (!random(3)) MONEY_MOVE(random(2)+1, "platinum", 0, this_object());
    MONEY_MOVE(random(21), "gold", 0, this_object());
    MONEY_MOVE(random(20)+50, "silver", 0, this_object());
    MONEY_MOVE(random(300)+520, "copper", 0, this_object());

    wpn = clone_object("/d/Genesis/start/human/obj/boulder");
    if (!wpn) return;
    wpn -> move(this_object());
}

initsay() {

    string *messages;
    int num, lines, i;

    messages = ({
        ({
	    "say How nice of you to drop by.",
	    "say I was just longing for someone to play with.",
	    "grin",
	    "wield "+ wpn->query_name()
        }),
	({
            "smile",
            "say Are you for real? I mean, realy, you're mortal right?",
            "flip",
	    "wield "+ wpn->query_name(),
	    "say I just LOOOVE mortals."
        }),
	({
	    "say Were you waiting for me?",
	    "say I'll just get my "+ wpn->query_name() +" ready.",
	    "wield "+ wpn->query_name(),
	    "spit",
	    "say Ok. I'm ready."

	}) ,
	({
	    "yawn",
	    "say Another one?",
	    "sigh",
	    "say Theese mortals begins to wear me out.",
	    "wield "+ wpn->query_name()
	}),
	({
	    "say This migh be fun...",
	    "wield "+ wpn->query_name(),
	    "smile"
	}),
        ({
	    "say Gee, I'd love to stomp a tiny one like you.",
            "wield "+ wpn->query_name(),
            "grin"
        }),
        ({
	    "start_fight",
            "wield "+ wpn->query_name()
        }),
        ({
            "start_fight",
            "wield "+ wpn->query_name()
        }),
        ({
            "start_fight",
            "wield "+ wpn->query_name()
        }),
        ({
            "start_fight",
            "wield "+ wpn->query_name()
        }),
        ({
            "start_fight",
            "wield "+ wpn->query_name()
        }),
        ({
            "start_fight",
            "wield "+ wpn->query_name()
        }),
	({
	    "say Look, here comes dinner!",
	    "smile",
	    "wield "+ wpn->query_name()
	})
    });
      	
    num = random(sizeof(messages));
    lines = sizeof(messages[num]);

    for (i=0 ; i < lines ; i++) {
	if (messages[num][i] == "start_fight") {    /* Needed if the giant   */
	    set_attack_chance(100);		    /* should start to fight */
	    set_aggressive(1);			    /* right away...	     */
	}
	else command(messages[num][i]);
    }
    set_attack_chance(100);
    set_aggressive(1);
}



find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
