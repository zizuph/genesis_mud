#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit DEPOSITORY;
inherit STRINGLIB;

#define LONG \
  "It is a huge stone, shaped almost as an altar. There is a small crack in "+\
  "its top, barely wide enough for a coin to enter, and " +\
  "some writing is engraved into its surface.\n"

#define CRACK_ITEM ({"crack", "opening"})
#define CRACK_DESC \
  "It is a small opening into the stone, strangely straight and regular, "+\
  "but yet not appearing man-made. It is clean and empty too, not filled "+\
  "with the old leaves, twigs and other debris you would expect to find "+\
  "there.\n"

#define TEXT_ITEM ({"text", "writing"})
#define TEXT_DESC \
  "The text is not very legible, and the letters are shaped oddly, but you "+\
  "manage to decipher:\n"+\
  "\"The generous donor will find more virtue in what he receives.\"\n"

#define GET_FAIL_MSG \
  "That is far beyond mortal abilities.\n"

#define WEIGHT 2000000
#define VOLUME 1000000


create_container() {
  set_name("stone");
  add_name(CRACK_ITEM);
  set_adj(({"rectangular", "large"}));

  set_long(WRAP(LONG));

  add_item(CRACK_ITEM, WRAP(CRACK_DESC));
  add_item( TEXT_ITEM, WRAP( TEXT_DESC));

  add_cmd_item(TEXT_ITEM, "read", WRAP(TEXT_DESC));
  add_cmd_item("stone",   "read", WRAP(TEXT_DESC));

  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
  add_prop(CONT_I_WEIGHT, WEIGHT);
  add_prop(CONT_I_VOLUME, VOLUME);
  add_prop(CONT_I_TRANSP, 0);
  add_prop(CONT_I_CLOSED, 0);
  add_prop(CONT_I_MAX_WEIGHT, WEIGHT + 100);
  add_prop(CONT_I_MAX_VOLUME, VOLUME + 100);
}

// string *parse_command_id_list()
// { 
//     if (member_array(query_verb(), ({"put", "drop"})) >=0) {
//         return ::parse_command_id_list() + CRACK_ITEM;
//     }
//     else
//         return ::parse_command_id_list();
// }
