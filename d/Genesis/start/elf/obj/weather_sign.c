#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;

#define LONG \
  "It is a tall billboard, headed by a large, elaborate sign, carved in "+\
  "dark wood. The sign reads: \"Weather Forecast\". Posted on the billboard "+\
  "is a large parchment, filled with text.\n"

#define NAMES ({"billboard", "board", "sign"})

#define PARCHMENT_ITEM ({"parchment", "poster", "placard"})
#define PARCHMENT_DESC \
  "The parchment is filled with small, intricately well-lettered text, and "+\
  "at the bottom is a huge, gilded seal."

#define SEAL_ITEM ({"seal", "gilded seal"})
#define SEAL_DESC \
  "The seal depicts a coat of arms, crowned by a queen's and a king's crown."

#define TEXT_ITEM ({"text", "writing"})
#define TEXT_DESC \
  "The text reads:\n\n"+\
  "By Our Royal decree, all habitats, feifdoms, lands, places, zones, "+\
  "and areas of Faerie will have the following weather, season, time, "+\
  "and mood until further notice:\n\n"+\
  "The Glade of Beginnings: spring morning, foggy, pale and fresh;\n"+\
  "The Strawberry and Blueberry Hills: melancholic late summer, sunny;\n"+\
  "The Mountains of Mist: chilly fog and slightly damp, cold;\n"+\
  "The Underearth Warrens: dark;\n"+\
  "The Pit: randomly hot and fiery;\n"+\
  "other areas: as ruled by local tradition.\n\n"+\
  "Alchemists and Fortune-Tellers are advised that local space-time "+\
  "fluctuations may cause causality and entropy disturbances.\n\n"+\
  "                                  Signed,\n"+\
  "                       Oberon, King    Titania, Queen\n"

#define GET_FAIL_MSG \
  "It is quite attached to the ground.\n"

create_object() {
  set_name(NAMES);
  set_adj(({"firmly posted", "large"}));

  set_long(WRAP(LONG));

  add_item(PARCHMENT_ITEM, WRAP(PARCHMENT_DESC));
  add_item(SEAL_ITEM, WRAP(SEAL_DESC));
  add_item( TEXT_ITEM, WRAP( TEXT_DESC));

  add_cmd_item(TEXT_ITEM + PARCHMENT_ITEM + NAMES, "read", WRAP(TEXT_DESC));

  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}

