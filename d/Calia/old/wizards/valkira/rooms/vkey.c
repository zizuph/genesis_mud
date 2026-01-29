/* CALIA : KEY - Key to Valsroom /d/Calia/valkira/rooms/vkey.c
DATE	  CODER	    ACTION	NOTE/PURPOSE
-----     ------    -----------	-----------------
9/6/99    Valkira   Created	Key for Valsroom door - practice with doors */


inherit "/std/key";
#include "/sys/stdproperties.h"
#include <macros.h>
#define VKEY "_vals_room_key"
#define VKEY_NUM   830912
create_key() {
  set_adj("plain");
  add_adj("copper");
  add_name(VKEY);
  set_long("It is a plain copper key.\n");
  set_key(VKEY_NUM);
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE,0);
}
 

