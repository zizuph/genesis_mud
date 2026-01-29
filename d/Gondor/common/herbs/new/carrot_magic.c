 /*
  */
#pragma save_binary

inherit "/std/herb";
#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define ENHANCE        2   /* skill enhancement */
#define EFFECT         ({SS_AWARENESS})
#define EFFECT_MSG     ({"be aware","observe your surroundings"})

void
create_herb()
{
  set_name("carrot");
  set_adj(({"green-topped","orange","tasty","crunchy"}));
  set_herb_name("nglormir");
  set_short("green-topped orange carrot");
  set_pshort("green-topped orange carrots");
  set_pname(({"herbs", "carrots" }));
  set_ingest_verb("eat");
  set_unid_long(BSN(
    "This orange carrot looks like an ordinary carrot.\n"));
  set_id_long(BSN("This orange carrot is a member of the "
  + "Carrota species of the genus Daucus. The carrot is a tasty "
  + "crunchy orange root.  Varying widely in size, the domestic. "
  + "carrot was first bred by the dwarves of the Blue Mountains "
  + "in the days before the Sun and Moon first rose over Middle-Earth. "
  + "The common orange carrot is ubiquitous thourghout Eriador and "
  + "Beleriand.  This rare Nglormir carrot was first bred by Olvandil"
  + "the Gardener of Eregion in the 11th Century of the Second Age."
  + "It is said by the Herblore of Gundobald of old Tharbad to have had"
  + "sight-enhancing properties."));
  set_herb_value(120);
  set_id_diff(30);
  set_find_diff(4);
  /* with HERB_SPECIAL, define only one effect! */
  set_effect(HERB_SPECIAL,"",0);
  set_decay_time(4600);
  set_amount(3);
  add_prop(OBJ_I_WEIGHT,36);
  add_prop(OBJ_I_VOLUME,45);
}

string query_recover() { return MASTER+":"+query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }

void
special_effect()
{
  object  shadow;
  int is;

  is = random(sizeof(EFFECT));
  shadow = clone_object(HERB_DIR + "skill_enhance");
  shadow->set_enhance_effect(EFFECT[is],EFFECT_MSG[is],ENHANCE);
  shadow->move(TP,1);
}
