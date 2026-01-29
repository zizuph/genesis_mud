/*
 * Soren the shopkeeper
 * 	by Morrigan, 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_GONDOR_NPC

#include "attackers.h"
#include "assist.h"

void
create_gondor_monster()
{
    set_name("soren");
    add_name("shopkeeper");
    add_name("shop-keeper");
    set_title("");
    set_race_name("half-elf");
    set_gender(0);
    set_long("This middle-aged half-elf has a thin, rust-coloured beard, "+
	"but his pointy ears reveal his elven heritage. He seems strangely "+
	"quiet.\n");
    set_adj(({"quiet", "middle-aged"}));

    set_stats(({ 65, 75, 70, 60, 60, 60 }));
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_AWARENESS,   50);
    set_skill(SS_DEFENCE,     60);
    set_skill(SS_PARRY,       60);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    set_money(({ random(20), random(9), random(0), random(0) }));

    set_default_answer( ({ "smile quietly", "shrug slightly", "nod silently",
	"eyebrow curiously", "grin .", "laugh strangely" }) );
}

void
intro_me(object name)
{
    command("introduce me" );
    command("smile .");
}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
