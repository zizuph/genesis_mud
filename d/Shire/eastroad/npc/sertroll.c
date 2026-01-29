/*
 * Troll for eastroad near Bruinen
 * Star - April 20/95
 */
inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Shire/common/make_money.h"

#define TROLL_ADJ ({"big","ugly","dirty","hairy","smelly","black"})

#define TROLL_ACT ({({"emote growls when he sees you.",0}),\
                    ({"smirk",0}),\
                  ({"emotes starts looking for something to eat.",0}),\
                  ({"frowns as his stomach growls.",0}),\
                    ({"burp",0}),\
                    ({"emote looks you over hungrily.",0}),\
                    ({"grin",0})})


#define TROLL_CACT ({({"say I'm gonna stomp all over your face!",0}),\
                    ({"say You're gonna be dinner soon.",0}),\
                    ({"say Is that the best you can do?",0}),\
                    ({"say Now I'm gonna eat you alive!",0}),\
                    ({"say I'm getting angry!",0}),\
                    ({"say Can't you do any better than that?",0}),\
                    ({"shout WIMP!",0}),\
                    ({"shout Alright! Some grub!",0})})



/* global club var */
object club;

/* prototypes */
void arm_me();
void reset_monster();
void setup_adj();
void setup_trollact();

create_monster()
{
  set_name("troll");
  set_race_name("troll");
  setup_adj();
  set_long("This troll is ugly as hell.  Much to your dismay, he also "+
    "looks like he hasn't eaten in a while.\n");
  add_prop(CONT_I_WEIGHT,677*1000);
  add_prop(CONT_I_HEIGHT,300);
  set_stats(({100,35,75,10,10,50}));
  set_hp(query_max_hp());

  set_skill(SS_UNARM_COMBAT,30);
  set_skill(SS_WEP_CLUB,65);
  set_skill(SS_DEFENCE,55);
  set_skill(SS_PARRY,10);
  set_attack_chance(30);
  set_alignment(-400);
  MAKE_MONEY;
  make_gold(random(5));

  set_act_time(5);

   setup_trollact();

  set_cact_time(5);
   setup_trollcact();

   enable_commands();
  set_alarm(1.0, 0.0, "arm_me");
/*
  reset_monster(); 
 */
}

void 
arm_me()
{
  if (!club || !present(club,this_object()))
    {
    club = clone_object(STAND_WEAPON+ "woodclub");
    club->move(this_object());
    command("wield club");
    }
}

void
reset_monster()
{
  ::reset_monster();
  arm_me();
}

void
setup_adj()
{
string *adjs, adj1, adj2;

   adj1 = TROLL_ADJ[random(sizeof(TROLL_ADJ))];
   adjs = TROLL_ADJ - ({adj1});
   adj2 = adjs[random(sizeof(adjs))];
   set_adj(adj1);
   set_adj(adj2);
}

void
setup_trollact()
{
string *acts, act1, act2, act3;

   act1 = TROLL_ACT[random(sizeof(TROLL_ACT))];
   acts = TROLL_ACT - ({act1});
   act2 = acts[random(sizeof(acts))];
   acts -=({act2});
   act3 = acts[random(sizeof(acts))];
   add_act(act1);
   add_act(act2);
   add_act(act3);
}

void
setup_trollcact()
{
string *cacts, cact1, cact2, cact3;

   cact1 = TROLL_CACT[random(sizeof(TROLL_CACT))];
   cacts = TROLL_CACT - ({cact1});
   cact2 = cacts[random(sizeof(cacts))];
   cacts -= ({cact2});
   cact3 = cacts[random(sizeof(cacts))];
   add_cact(cact1);
   add_cact(cact2);
   add_cact(cact3);
}

