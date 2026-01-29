/*
 * Genesis ShipLines - Sparkle office.
 * Timetable engineer
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#include <macros.h>

inherit "/std/monster";

void
create_monster () {

  if(! IS_CLONE)
    return;

  set_living_name("Shpish");
  set_name("Shpish");
  add_name(({"Shpish", "shpish", "engineer"}));
  set_race_name("gnome");
  set_adj(({"innovative", "talkative"}));
  set_gender(G_MALE);
  set_long("This gnome is a transport engineer working for Genesis ShipLines "+
           "Company. He is standing next to the timetable adjust some bells "+
           "and whistles and shaking his head from side to side.\n");
  //  set_default_answer("say IAmCurrentlyTooBusySettingThisNewOfficeSorry.\n");
  add_prop(OBJ_M_NO_ATTACK,
           "You cannot attack Genesis ShipLines employees.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,
           "You cannot attack Genesis ShipLines employees.\n");
  add_prop(OBJ_M_NO_GIVE, 1);
  add_act("The gnome pulls a lever next to the timetable. A whistle goes "+
          "off.\n");
  add_act("The gnome inspects the behind of the timetable carefully.\n");
}

void
catch_question (string question)
{
  command("say IAmCurrentlyTooBusySettingThisNewOfficeSorry.");
}

void
equip_me () {

}
