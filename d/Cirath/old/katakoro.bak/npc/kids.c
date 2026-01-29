/* kids.c
 * 11 July 1995, Chaos
 * Original Code by Serpine
 */

inherit "/std/monster";
#include "defs.h"

#define RNDADJ ({"sad", "tired", "ugly", "pathetic", "dirty", "hungry"})

void
create_monster()
{
    set_adj(RNDADJ[random(6)]);
    set_name("kid");
    set_race_name("human");
    set_long  ("This is one of the children that makes up the "+
	"civilian portion of the Khahan's camp city.  It "+
	"probably belongs to one of the soldiers in the army.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);

    set_act_time(8);
    add_act("sigh");
    add_act("ponder");
    add_act("emote looks somewhat afraid of you.");
    add_act("say Why don't you just leave me alone?");
    set_gender(random(2));
    set_alignment(random(75));
}

void
arm_me()
{
    clone_object(KAT_DIR+"equipment/avgkalat.c")->move(TO);
    command("wear all");
}
