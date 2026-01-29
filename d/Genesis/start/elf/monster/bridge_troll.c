/*
 * A bridge troll
 */

#include "../stddefs.h"
#include "../tefyma.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;

#define NAMES \
({ "barsh", "skobb", "gresh", "sagg", "gnarsh", "skarth", "gratch" })

#define LONG \
  "It is a massive, overgrown troll.\n"


#define CLUB OBJDIR + "troll_club"

void equip();

void
create_monster() 
{
    if (IS_CLONE) 
      {
	  set_name(NAMES[random(sizeof(NAMES))]);
	  set_race_name("troll");
	  set_adj("massive");
	  set_long(WRAP(LONG));
	  
	  set_gender(G_MALE);
	  add_prop( NPC_I_NO_LOOKS,   1);
	  add_prop(LIVE_I_NEVERKNOWN, 1);
	  add_prop(CONT_I_WEIGHT, 120 KG);
	  add_prop(CONT_I_HEIGHT, 250 CM);
	  add_prop(CONT_I_VOLUME, 120 LITRES);
	  
	  set_base_stat(SS_STR, 50);
	  set_base_stat(SS_DEX, 40);
	  set_base_stat(SS_CON, 50);
	  set_base_stat(SS_INT, 20);
	  set_base_stat(SS_WIS, 20);
	  set_base_stat(SS_DIS, 50);
	  
	  set_alignment(-70);
	  set_appearance(65);
	  set_aggressive(0);
	  set_attack_chance(100);
	  
          set_alarm(0.5, 0.0, equip);
	  
	  refresh_mobile();
      }
}

void
equip()
{
    object club;
    
    club = clone_object(CLUB);
    club->move(this_object());
    command("wield club");
}
