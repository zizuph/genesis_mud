/*
 * A mermaid.
 */

#include "../stddefs.h"
#include "../tefyma.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/const.h"

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;

#define MERMAID_NAME ({ "mermaid" })

#define COLOURS \
  ({  \
	"chartreuse", \
	"saffron", \
        "maroon", \
	"pink", \
	"navy-blue", \
        "silver", \
	"green", \
	"bronze", \
	"mauve", \
	"blue" , \
	"azure" , \
	"indigo", \
	"olive-green", \
	"pale-blue", \
	"pale-green" \
  })

#define MALE_ACTIONS \
 ({ \
    "wiggles her tail", \
    "happily waves", \
    "smiles at you", \
    "blushes", \
    "stops combing her hair for a moment", \
    "makes a show-off jump out of the water", \
    "rises partway out of the water", \
    "wrings the water out of her wet hair and smiles at you" \
    })

#define FEMALE_ACTIONS \
 ({ \
    "gives you a friendly wave", \
    "gives you a friendly smile", \
    "nods at you", \
    "looks quizzical for a moment", \
    "stops combing her hair for a moment" \
    })

#define MERMAID_DESC \
  "She is a sweet young thing with a fishy half.\n"

string *colours;

void noticed(object viewer);

create_monster() {
  set_name(MERMAID_NAME);
  set_race_name("mermaid");
  set_adj(({ get_colour() + "-haired"}));
  set_long(WRAP(MERMAID_DESC));

  set_gender(1);
  add_prop( NPC_I_NO_LOOKS,   1);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(CONT_I_WEIGHT,  70 KG);
  add_prop(CONT_I_HEIGHT, 170 CM);
  add_prop(CONT_I_VOLUME,  70 LITRES);

  set_base_stat(SS_STR, 8);
  set_base_stat(SS_DEX, 8);
  set_base_stat(SS_CON, 8);
  set_base_stat(SS_INT, 8);
  set_base_stat(SS_WIS, 8);
  set_base_stat(SS_DIS, 8);

  set_alignment(70);
  set_appearance(65);
  set_aggressive(0);
  set_attack_chance(0);

  refresh_mobile();
}

string short(object for_obj)
{
  set_alarm(1.0, 0.0, &noticed(for_obj));
  return ::short(for_obj);
}

string get_colour()
{
  string colour;
  int i, last;

  if (IS_CLONE) 
    return MASTER->get_colour();

  if (!colours ||
      sizeof(colours) < 3)
    colours = COLOURS;

  last = sizeof(colours) - 1;
  i    = random(last);
  colour     = colours[i];
  colours[i] = colours[last];
  colours    = colours[0..last-1];

  return colour;
}


void noticed(object viewer)
{
  if (viewer && random(100) < 25) {
    switch(viewer->query_gender()) {
    case G_MALE:
      viewer->catch_msg(WRAP("The " + query_nonmet_name() + " " +
			     MALE_ACTIONS[random(sizeof(MALE_ACTIONS))]  + 
			     ", as she sees you watching her.\n"));
      break;
    case G_FEMALE:
      viewer->catch_msg(WRAP("The " + query_nonmet_name() + " " +
			     FEMALE_ACTIONS[random(sizeof(FEMALE_ACTIONS))]  + 
			     ", as she sees you.\n"));
      break;
    }
  }
}
