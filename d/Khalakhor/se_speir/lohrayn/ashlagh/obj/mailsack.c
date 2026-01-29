// Mail Sack - primary quest object for the postmaster tour
//
// Zima    June 10, 98
//
// Refactored - Tapakah, 08/2021

#pragma strict_types

#include <stdproperties.h>
#include "defs.h"
 
inherit "/std/container";

int letters = 0;

int
get_letters ()
{
  return letters;
}

void
remove_letter ()
{
  letters--;
}

void
make_letters (mapping *addresses)
{
  int    i, n = sizeof(addresses);
  object letter;
  seteuid(getuid());
  int r;
  for (i=0; i<n; i++) {
    letter = clone_object(OBJ+"letter");
    letter->set_address(addresses[i]);
    letters++;
    r = letter->move(this_object());
  }
}

void
create_container ()
{
  set_name("mailsack");
  add_name(({"sack","_ashlagh_mailsack"}));
  add_adj(({"leather","mail","small"}));
  set_short("leather mailsack");
  set_long(
           "It is a small leather sack used to carry letters. The words "+
           "'Baile Ashlagh Postmaster' are written on the side.\n");
 
  add_prop(CONT_I_MAX_WEIGHT, 3000);
  add_prop(CONT_I_MAX_VOLUME, 3000);
  add_prop(OBJ_I_VALUE,       1);
}
