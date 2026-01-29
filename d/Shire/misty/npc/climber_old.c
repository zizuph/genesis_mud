/*
 * This is climber used in MISTY_DIR room p18.c
 * 
 * Made by Milan *giggle*
 * 
 * Updated by Igneous
 */

#include <filter_funs.h>
#include "../local.h"

inherit SHIRE_MONSTER;

// Prototypes
void return_happy(object who);
void return_crazy(object who);
void return_start(object who);
void return_made();

void
create_shire_monster()
{
    set_name("mimo");
    set_race_name("human"); 
    set_living_name("_climber_");
    set_adj("desperate");
    add_adj("stout");
    set_title("Professional Climber");
    add_prop(CONT_I_WEIGHT,73000);   /* 73 Kg */
    add_prop(CONT_I_HEIGHT,178);      /* 178 cm */

    /*
	add_prop(DO_I_TELL_RUMOURS, 1);
    */

    set_stats(({ 65, 70, 50, 30, 40, 34}));

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_CLIMB, 19);

    set_scar(3);
    set_alignment(500);

    set_act_time(5); 
    add_act(({"emote studies the rock carefully.", "climb rock"})); 
    add_act(({"say Have you found the Climbers guild?", "smile knowingly", 
	"say Lots of XP only for climbing anything :)", "poke all"})); 
    add_act(({"say DAMNED LAG :(", "sigh"})); 
    add_act(({"say I am a professional climber.", 
	"say I must climb up every rock I find.", "climb rock"}));

    set_introduce(1);
}

query_knight_prestige(){return -200;}


void
notify_player_starts_climb(object player) 
{
    set_alarm(3.0,0.0,&return_start(player));
}

void
return_start(object who) 
{
    if (who)
    {
	if (present(who, ENV(TO))->query_met(TO))
	    command("shout Good luck "+who->query_name()+".");
	else
	    command("shout Good luck "+who->query_nonmet_name()+".");
	command("giggle");
    }
}

void
notify_player_made_it(object player) 
{
    set_alarm(4.0,0.0,return_made);
}

void
return_made() 
{
    command("say Only I am so clumsy...");
    command("cry");
}

void
notify_player_falls(object player) 
{
    set_alarm(2.5,0.0,&return_happy(player));
}

void
return_happy(object who) 
{
    if (present(who, environment())) 
    {
	command("ponder another clumsy climber.");
	command("poke "+who->query_real_name());
	command("bounce");
    }
}

void
notify_player_jumps(object player) 
{
    set_alarm(5.0,0.0,&return_crazy(player));
}

void
return_crazy(object who)
{
    if (present(who, environment())) 
    {
	command("say Going mad???");
	command("peer at "+who->query_real_name());
	command("pat "+who->query_real_name());
    }
}
