inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

void
create_monster()
{
    ::create_monster();
    set_name("shantaris");
    set_race_name("elf");
    add_name("dark-elf");
    add_adj("black-eyed");
    add_adj("silver-haired");
    set_short("black-eyed silver-haired dark-elf");
    set_long("This is dark elf looks not only very old and wise, but "+
        "strong, quick and lethal. He wears a dark-cloak made of shimmering "+
        "scales, and his hood is drawn over his head. Dark eyes stare "+
        "back at you. His hand twitches a bit.\n"+
        "He is wielding a lethal vorpal dagger.\n"+
        "He is wearing a black shimmering cloak, a suede leather vest, a "+
        "pair of black leather boots, and a pair of black leather pants.\n");
    set_stats(({140,210,150,120,150,100}));
    add_speak("Welcome to the lair of the Shadow Walkers, foolish one...\n");
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_KNIFE,10);
    set_skill(SS_AWARENESS,100);
    set_act_time(6);
    add_act("emote smiles cruely.");
    add_act("emote plays with his lethal vorpal dagger.");
    add_act("scratch chin");
    add_act("emote wonders what you want.");
    add_act("sigh");
    add_act("say Business is good these days...lots of rich nobles "+
        "trading with the outside world now.");
    add_prop(OBJ_M_NO_ATTACK,"You don't think its time for you to die "+
        "yet, so you change your mind.\n");
    set_title("the Lord of the Shadows of South Kabal");
    set_default_answer("Don't bother me with that, fool!\n");
    add_ask(({"zintra","black rose"}),"I know nothing about them.\n");
    add_ask("shadow lords","I am a Shadow Lord, fool!\n");
    add_ask("shadow walkers","We are a guild of thieves and thugs, "+
        "we strike fear into the hearts of the petty citizens of Kabal! "+
        "However, we are seeking new members to help us expand past the "+
        "lands of Kalad to glorify our name in the Outside world.\n");
    add_ask(({"new members","members","joining"}),"If you want to "+
        "become a member, you must be ruthless. No wimping out, or I'll "+
        "kill you myself. You must be ready to accept the life of a thug "+
        "and live off the streets. You will be a Shadow Walker...taking " +
        "to the shadows, relying on deceit and trickery. Corruption, "+
        "deceit, and immorality are your friends. Live in it. If you wish "+
        "to accept these rules and terms, you may 'pledge to be a shadow "+
        "walker'. If you ever want to wimp out, you can 'wimp out'.\n"+
        "Tax is 10%.\n");
    add_prop(LIVE_M_ATTACK_THIEF,"nothing");
}

int
nothing()
{
    return 0;
}
