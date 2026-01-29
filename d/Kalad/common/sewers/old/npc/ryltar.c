inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
    ::create_monster();
    set_name("ryltar");
    set_adj("shady");
    add_adj("black-cloaked");
    set_race_name("dark-elf");
    set_short("black-cloaked shady dark-elf");
    set_long("A shady, dark-elf, his features are hidden within "+
    "his black cloak. He glares at you as study him. You get a "+
    "VERY uneasy feeling about this individual.\n");
    set_stats(({100,120,110,95,110,100}));
    set_alignment(-750);
    set_knight_prestige(80);
    add_speak("You're starting to annoy me, leave me alone.\n");
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_PARRY,90);
    set_skill(SS_AWARENESS,95);
    set_act_time(3);
    add_act("emote picks at his fingernails with his dagger.");
    add_act("emote stares at you darkly, his ice blue eyes twinkle "+
    "with danger./n");
    set_cact_time(5);
    add_cact("say When I am through with you, I will carve your "+
    "corpse up and feed it to the rats!");
    add_cact("emote looks at you with hatred in his eyes.");
}

void
attacked_by(object enemy)
{
    command("emote grins at you coldly.");
    command("say That was foolish of you, swine.");
    command("say Get ready to die, asshole.");
}
	
int
special_attack(object enemy)
{
    if(random(8))
        return 0;
    enemy->catch_msg(QCTNAME(TO)+" melts into the shadows and "+
    "appears behind you.\n"); 
   enemy->catch_msg("You feel a dagger brutally stabbed into"+
   " your back!\n");
    tell_room(E(TO),QCTNAME(TO)+" melts into the shadows and"+
    "appears behind "+QTNAME(enemy)+".\n "+QCTNAME(TO)+
    " backstabs "+HIM(enemy)+".\n",enemy);
    enemy->heal_hp(-149 + -random(300));
    if(enemy->query_hp() < 0)
        enemy->do_die(TO);
    return 1;
}

void
arm_me()
{
    object wep;
    seteuid(getuid());
    wep = clone_object(SEWERS(wep/rdagger));
    wep->move(TO);
    command("wield all");
}

