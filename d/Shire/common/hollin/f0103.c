#include "rom.h"

create_rom()
{
    set_short("On a trail between boulders");
    set_long(
	"You are walking on a small trail between large boulders. "+
	"You wouldn't be surprised if suddenly a large troll should "+
	"jump upon you from behind the boulders. Uh oh... You get the nasty "+
	"feeling that you shouldn't be here.\n");
    ADD_EXA("trail","It winds through boulders scattered around here.");
    ADD_EXA("boulders,rocks",
	"These boulders somehow give you an uneasy feeling. You "+
	"get the impression that if someone was behind them, you'd be "+
	"subject to an awesome ambush.");
    SOUTHEAST("f0202");
    add_exit(STAND_DIR+"f0004", "northwest", "@@hook_move");
}

int
hook_move()
{
    if(TP->query_npc())
	return 1;
    call_other(STAND_DIR+"f0004", "prepare_attack");
    return 0;
}
