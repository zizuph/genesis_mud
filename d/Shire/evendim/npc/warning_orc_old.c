/*
 *  A guarding orc. He runs to get a task force if anybody comes near.
 *  Cloned by ~Shire/common/evendim/ev7
 */
 inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"
#define DIRS ({"southeast", "east", "east", "enter" })
 static int rooms_run;

void create_monster()
{
    set_name("orc");
   set_living_name("worc");
   set_adj(({"watching","small"}));
    set_alignment(-150 - random(50));
   set_race_name("orc");
   set_long("This orc seems to be put in an advanced position so he can\n"
          + "warn his friends if anyone approaches.\n");
    add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */
    set_stats(({ 30, 20, 20, 23, 25, 27}));
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_WEP_SWORD,30);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_PARRY,30);
   set_pick_up(75);
    set_aggressive(0);
   set_attack_chance(0);
    /* Actions */
    /* Combat actions */
   set_cact_time(5);
   add_cact("shout Help! Intruders!");
    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
    rooms_run = 0;
    set_alarm(1.0,0.0,"arm");
   MAKE_MONEY;
}
 init_living()
{
    ::init_living();
     if (interactive(this_player()))
    {
        run();
    }
}
 void
arm()
{
  clone_object(EVENDIM_DIR + "wep/orc_scimitar")->move(TO);
  command("wield scimitar");
}
 /* This is the run function */
int
run()
{
  object ob;
   ob = present(this_player(), environment());
  if (!ob) return 0;
     if (!CAN_SEE(this_object(), this_player()))
    {
        write("The orc doesn't see you. Maybe you can sneak by without him\n"
      + "noticing.\n");
        return 0;
    }
   if(rooms_run < 4)
 {
  command("scream");
    command(DIRS[rooms_run]);
   rooms_run++;
  /* Changed by Rogon. Sep 22/93. */
  }
  else
  {
    command("shout Get ready I'm being followed.");
    command("shout We will divide the treasure between us.");
  }
 }
  /* For the solamnic Knights */
 query_knight_prestige() { return(25); }

