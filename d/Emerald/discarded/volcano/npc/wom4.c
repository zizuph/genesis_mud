// A worshipper for the top of the volcano. the pagan
// worship of these tribesman is rumored to be the only thing that keeps
// the spirits of the volcano happy and keeps them form spurring theiur
// hot fury over the nearby areas.
// This woman brings an offering of food for the spirits

inherit "/d/Emerald/std/emerald_monster.c";
#include "/d/Emerald/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "default.h"

int fnutt;
void worship();

void
create_emerald_monster()
{
    set_name("tribeswoman");
    add_name("woman");
    add_name("tribewoman");
    set_short("tribeswoman");
	set_long("This is a young woman, clothed in ceremonial clothing " +
       "She carrys a large bowl of food in offering for the spirits of the " +                "volcano/ This is part of her offering for the spirits of the " +
	"volcano, to keep it from erupting and destroying her village.\n\n");
    set_gender(1);
    set_stats(({65,64,55,56,64,63}));
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 38);
	set_act_time(10);
    set_alignment(350);
    add_act("@@worship");
}

void
worship()
{
    ++fnutt;
    if (fnutt <= 3)
        set_alarm(7.0,0.0,worship);
    switch(fnutt)
    {
    case 1:
        say("She bows her head, and kneels down as deeply as she can.\n"); 
        break;
    case 2:
        say("She begins a low, inaudiable chant, but her voice gradually " +
            "grows louder and louder.\n", TO);
        break;
    case 3:
        say("She raises the bowl above her head and slowly empties it into " +
            "the mouth of the volcano.\n", TO);
        break;
    default:
        say("She closes off her worship, lowering her voice slowly until it " +
            "can be heard no more.\n", TO);
        say("Smoke puffs from the volcano mouth, as if it is pleased.\n", TO);
        say("With great reverence, she gazes upon her gods.\n", TO);
	break;
        fnutt = 0;
    }
}

arm_me()
{
    seteuid(getuid());
	clone_object(VOBJ + "dress.c")->move(this_object(), 1);
	clone_object(VOBJ + "boots.c")->move(this_object(), 1);
	clone_object(VOBJ + "brealet.c")->move(this_object(), 1);
	clone_object(VOBJ + "wreath.c")->move(this_object(), 1);
	command("wear all");
}
