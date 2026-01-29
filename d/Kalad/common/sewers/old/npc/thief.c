inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

void
create_monster()
{
    ::create_monster();
    set_name("thief");
    set_adj("unkept");
    add_adj("dirty");
    set_race_name("human");
    set_short("dirty, unkept human");
    set_long("This is a rather dirty human, he smells of the sewers"+
    "and his clothes are filthy. He looks up at you and grins, showing"+
    "you his gross, rotting teeth.\n");
    set_stats(({60,60,60,60,60,60}));
    set_alignment(-300);
    set_knight_prestige(30);
    add_speak("Why don't you just go back to the surface?\n");
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,65);
    set_act_time(3);
    add_act("emote mumbles something to himself, while he looks at you.");
    add_act("say You should not be down here, you might get.....hurt");
    add_act("emote smiles grimly at you.");
    set_cact_time(5);
    add_cact("say You beeter hope Ryltar, er my boss, does not"+ 
    "find you!\n");
    add_cact("emote spits on you.");
}

void
attacked_by(object enemy)
{
    command("jump");
    command("say Hey, what the hell is your problem!.");
    command("say I'm gonna carve you up real good!.");
}
	
int
special_attack(object enemy)
{
    if(random(8))
        return 0;
    enemy->catch_msg(QCTNAME(TO)+" melts into the shadows and "+
    "appears behind you.\n"); 
   enemy->catch_msg("You feel a dagger stabbed into your back!\n");
    tell_room(E(TO),QCTNAME(TO)+" melts into the shadows and"+
    "appears behind "+QTNAME(enemy)+".\n "+QCTNAME(TO)+
    " backstabs "+HIM(enemy)+".\n",enemy);
    enemy->heal_hp(-80 + -random(120));
    if(enemy->query_hp() < 0)
        enemy->do_die(TO);
    return 1;
}

void
arm_me()
{
    object wep;
    seteuid(getuid());
    wep = clone_object(SEWERS(wep/tdagger));
    wep->move(TO);
    command("wield all");
}

