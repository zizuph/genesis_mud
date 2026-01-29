// file name: w_path8.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:


inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

create_room()
{
set_short("Sharp turn");
set_long("The well-paved stone path makes"
        +" a sharp turn here, heading off to the north and west."
        +" The buzzing of insects hangs heavily in the air, and"
        +" the shrieks of faraway creatures can be softly heard. The dense"
        +" underbrush and dangling vines still line the path,"
        +" making an impenetrable wall along both sides of you.\n");

AE(PK+"w_path7","west",0);
AE(PK+"w_path9","north",0);

add_prop(ROOM_I_LIGHT,1); IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"attanar");
  add_herb_file(GONDOR+"morgurth");
  add_herb_file(SHIRE+"lianor_berry");
}

reset_room()
{
  set_searched(0);
}
