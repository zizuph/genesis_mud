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
    set_name("tarn");
    add_name("smith");
    set_title("the Master Blacksmith");
    set_race_name("dwarf");
    set_gender(0);
    set_long("This old dwarf has a grey beard to match his grey head. His arms "+
	"are still strong and he uses them to craft weapons and armour for the "+
	"mercenaries here.\n");
    set_adj(({"old", "grey-bearded"}));

    set_stats(({ 125, 80, 150, 80, 80, 130 }));
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_AWARENESS,   50);
    set_skill(SS_DEFENCE,     75);
    set_skill(SS_PARRY,       75);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    set_money(({ random(20), random(9), random(10), random(5) }));

    set_default_answer( ({ "say Can't ya see I'm busy here?", "say I don't care!",
	"say Leave me alone, I'm busy!", "say There's the door!", "say Get out of "+
	"my forge or shut up!" }) );
}

void
intro_me(object name)
{
    command("introduce me" );
    command("say If yer not needin' my services, don't waste my time!");
}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
