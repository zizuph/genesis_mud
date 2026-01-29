inherit "/d/Kalad/std/monster";
/*
 * File Name  : /d/Kalad/common/guilds/sh_walkers/npc/shantaris.c
 * Created By : Sarr
 * Modified By: Rico
 * First Modif: 11.Feb.97
 */

#include "../defs.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#define LIVE_M_ATTACK_THIEF "_live_m_attack_thief"

void
create_monster()
{
   ::create_monster();

   set_name("shantaris");
   set_race_name("elf");
   add_name("dark-elf");
   add_adj(({ "black-eyed", "dark", "silver-haired" }));
   set_short("dark, silver-haired dark-elf");
   set_long("\nThis dark elf is not only extremely old and wise, "+
      "but he's also extremely dangerous.  It is natural, a result "+
      "of his many years of hard earned experience.  He must be the "+
      "guild guardian of the infamous Shadow Walkers of Kabal.\n"+
      "He is wielding a lethal vorpal dagger.\n"+
      "He is wearing a black shimmering cloak, a suede leather vest, a "+
      "pair of black leather boots, and a pair of black leather pants.\n");

            /*  STR  DEX  CON  INT  WIS  DIS  */
   set_stats(({ 115, 150, 120, 110, 150, 100}));

   add_speak("Welcome to the lair of the Shadow Walkers, foolish one...\n");

   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 50);
   set_skill(SS_WEP_KNIFE, 50);
   set_skill(SS_AWARENESS, 90);

   set_act_time(6 + random(4));
   add_act("emote smiles cruely.");
   add_act("emote plays with his lethal vorpal dagger.");
   add_act("emote runs his thumb along his lethal vorpal dagger.");
   add_act("scratch chin");
   add_act("emote wonders what you want.");
   add_act("sigh");
   add_act("say Business is good these days...lots of rich nobles "+
      "trading with the outside world now.");

   add_prop(OBJ_M_NO_ATTACK,"You don't think its time for you to die "+
      "yet, so you change your mind.\n");
   add_prop(LIVE_M_ATTACK_THIEF, "nothing");

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
      "and live off the streets. You will be a Shadow Walkers...taking "+
      "to the shadows, relying on decite and trickery. Corruption, "+
      "decite, and immorality are your friends. Live in it. If you wish "+
      "to accept these rules and terms, you may 'pledge to be a shadow "+
      "walker'. If you ever want to wimp out, you can 'wimp out'.\n"+
      "Tax is 10%.\n");


}

int
nothing()
{
    return 0;
}