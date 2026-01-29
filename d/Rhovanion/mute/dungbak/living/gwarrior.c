inherit "/std/monster";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
static int drank;

object ob1;

void
create_monster() {
   set_name("warrior");
   set_adj("ghost");
   set_adj("misty");
   set_living_name("_Fred_S");
   set_race_name("warrior");
   set_long("This tall humanoid figure is devoid of all flesh " +
      "and is instead covered with vaporous mists which seem to " +
      "trail off of it.  Its eyes glow with an eerie yellow light. " +
      "The creature smells of some otherplanar foulness and appears " +
      "as if it's been here quite some time.\n");
   set_whimpy(20);
   set_skill(SS_WEP_SWORD, 40);
   set_skill(SS_DEFENCE, 35);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 35);
   set_gender(G_NEUTER);
   set_stats(({ 30, 35, 45, 30, 30, 35 }));
   set_alignment(-250);
   set_aggressive(1);
   set_hp(300);
   add_prop(CONT_I_WEIGHT, 60000);
   add_prop(CONT_I_HEIGHT,  2100);
   add_prop(CONT_I_VOLUME, 65000);
   add_prop(LIVE_I_NO_CORPSE,  1);
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   seteuid(getuid());
   clone_object("/d/Rhovanion/mute/dungeon1/gwarmour1.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/gwarmour2.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/gwarmour3.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/gwarmour4.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/gwpouch.c")->move(TO);
    ob1=clone_object("/d/Rhovanion/mute/dungeon1/gwsword.c");
   ob1->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/hpotion2.c")->move(TO);
   command("wear all");
   command("wield all");
}
public void
run_away() {
   if(!drank)
      {
      command("uncork potion");
      command("drink potion");
      drank=1;
   }
   else
      {
      ob1->remove_object();
   }
}
