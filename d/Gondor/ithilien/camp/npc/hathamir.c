/*
 * A npc ranger that is similar in stature to Dukano, the mage who
 * is found in the outpost after Osgiliath is attacked. He will be present
 * when other rangers are cloned into the camp.
 * Alto, 23 August 2002
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/npc/npc_ranger.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../defs.h"

#define WEP_ARRAY1 ({CAMP_WEP_DIR + "camp_longsword", CAMP_WEP_DIR + "camp_halberd", CAMP_WEP_DIR + "camp_battleaxe"})
#define ARM_ARRAY1 ({CAMP_ARM_DIR + "camp_helm"})
#define ARM_ARRAY2 ({CAMP_ARM_DIR + "camp_mail", CAMP_ARM_DIR + "camp_chainmail"})
#define ARM_ARRAY3 ({CAMP_ARM_DIR + "camp_leggings"})

string *wep1, *arm1, *arm2, *arm3;

void
create_ranger()
{
    int     rnd = random(10);

    set_name("hathamir");
    set_living_name("hathamir");
    set_adj(({"commanding", "secretive"}));
    set_long("This tall grim man of Gondor seems to be in charge of the camp. "
      + "His job is to keep the camp secure from the spies of Mordor. He looks "
      + "at you with suspicion, fingering his weapon thoughtfully.\n");
    set_race_name("human");
    set_title("Field Commander of the Resistance");
    set_stats(({196+rnd, 196+rnd, 195+rnd, 190+rnd, 190-rnd, 86+rnd,0, 190+rnd,0}));
    set_alignment(450);
    set_gender(G_MALE);
    set_company("Ithilien");

    remove_prop(LIVE_I_NEVERKNOWN);

    set_skill(SS_WEP_SWORD,	85);
    set_skill(SS_WEP_POLEARM,	85);
    set_skill(SS_WEP_AXE,	85);
    set_skill(SS_WEP_KNIFE,	50);
    set_skill(SS_WEP_CLUB,	50);
    set_skill(SS_DEFENCE,	75);
    set_skill(SS_PARRY,		60);

    set_restrain_path(CAMP_ROOM_DIR);
    set_monster_home(CAMP_ROOM_DIR + "fort4");
    set_random_move(10);

    set_mm_in("suddenly steps out of the trees.");
    set_mm_out("slips quietly away into the trees.");

    set_chat_time(20);
    add_chat("What are you doing here?");
    add_chat("You are not supposed to be here, stranger.");
    add_chat("Can I help you with something?");
    add_chat("The Eye is watching. Keep still!");
    add_chat("Have you seen any mages about?");
    add_chat("Hail Ithlien!");
    add_chat("Do you stand for Gondor or Mordor? We have no time "
        + "for fence-sitters.");
    add_chat("Show your badge!");

    set_cact_time(5);
    add_cact("shout You will pay for that, spy!");
    add_cact("shout For Ithilien!");
    add_cact("shout To arms! To arms! We have a spy in our midst!");

    set_default_answer("The commanding secretive human whispers: 'Hush'\n");
}

void
set_arm_arrays()
{
    wep1 = WEP_ARRAY1;
    arm1 = ARM_ARRAY1;
    arm2 = ARM_ARRAY2;
    arm3 = ARM_ARRAY3;
}

void
arm_me()
{
   int iw, is;
   
   set_arm_arrays();
   
   seteuid(getuid(TO));
   
   if(is = sizeof(wep1))
      {
      iw = random(is);
      clone_object(wep1[iw])->move(TO);
   }
   command("wield weapon");
      
   if(is = sizeof(arm1))
      {
      iw = random(is);
      clone_object(arm1[iw])->move(TO);
   }
   
   if(is = sizeof(arm2))
      {
      iw = random(is);
      clone_object(arm2[iw])->move(TO);
   }
   
   if(is = sizeof(arm3))
      {
      iw = random(is);
      clone_object(arm3[iw])->move(TO);
   }
   
   get_company_token();

   command("wield all");
   command("wear all");
   set_hp(query_max_hp());
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}

