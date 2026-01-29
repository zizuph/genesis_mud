
// file name: greater_death
// creator(s): Tilorop (6/3, 2006)
// last update:
// purpose: Quest npc and entrance guardian of the crypt.
// note:
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/ranpick";

#include "../dead.h"
#include "money.h";
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/sys/macros.h"

void
arm_me()
{

   object key;
   seteuid(getuid());
 
   
   MONEY_MAKE_CC(2)->move(this_object());
}


void
create_creature()
{
    set_name("death");
    add_name("figure");
    add_name("greater_death_");
    add_name("grim reaper");
    set_race_name("immortal");
    set_adj("shadowlike");
    set_short("shadowlike figure, clad in black");
    set_long("An shadowlike figure, clad all in black. This being " +
        "has gone by many names over the eons, such as the Grim " +
        "Reaper, but he is what he is, Death itself, complete " +
        "with a cowled, black robe, and a long, vicious scythe. You are " +
        "convinced though that assaulting this creature could spell nothing " +
        "but almost immediate death to you and whoever dares to aid you in doing " +
        "so.\n");
    add_item(({"scythe"}),
        "An extremely sharp scythe, so sharp that gusts of wind " +
        "actually try to turn away from the edge rather than be " +
        "sliced in two by the wicked looking blade. It does strange " +
        "things with light as well, seeming to split it's very " +
        "essence into light and dark.\n");
    add_item(({"robe"}),
        "A black hooded robe with numerous pockets. It doesn't " +
        "seem to fit you very well however, as it looks to have " +
        "been tailored for a very lean customer. Someone who's all " +
        "'skin and bones', perhaps...\n");
  set_gender(G_NEUTER);

  set_alignment(0);

  set_stats(({250,250,250,250,250,250}));
  
  set_restrain_path(CRYPT);

  set_skill(SS_AWARENESS, 100);

 
  set_attack_unarmed(0,5,35,W_SLASH,0,"skeletal talons");
  set_attack_unarmed(1,35,35,W_SLASH,0,"skeletal talons");

  //set_hitloc_unarmed(0, ({50,35,20}),25,"head");
  set_hitloc_unarmed(0,({50,35,20}),50,"ethereal body");
  //set_hitloc_unarmed(2,({50,35,20}),25,"legs");

  add_prop(LIVE_I_NO_CORPSE,1);
  add_prop(LIVE_I_SEE_DARK,100);
  add_prop(LIVE_I_UNDEAD,100);
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(NPC_I_NO_FEAR, 1);

  
   arm_me();
   //add_act("emote brushes past you.");

}


int query_max_hp() { return 99000; }

int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    string how;


/*    tell_watcher("we get here.\n"); */

    /* Only execute the special attack 1 in 10 rounds */
    if (random(1))
    {
/*    tell_watcher("returning 0.\n"); */
        return 0;  /* Continue with the normal attacks */
    }
/*    tell_watcher("getting a special.\n"); */
    hitresult = enemy->hit_me(1000+random(2000), W_IMPALE, me, -1);
    
    enemy->catch_tell(query_The_name(enemy) + " suddenly swings its extremely sharp scythe at you " +
    "with a supernatural speed, slicing a horrible deep cut in your chest!\n"+"You are severly " +
    "hurt, blood splattering everywhere!\n");


    tell_watcher(QCTNAME(me) + " suddenly swings its extremely sharp scythe at " + QTNAME(enemy) + " with a " +
    "supernatural speed, slicing a horrible deep cut in the chest!\n" +
        capitalize(enemy->query_pronoun()) + " is severly hurt, blood splattering everywhere!\n", enemy);

    if (enemy->query_hp() <= 0)
    {

        enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}


