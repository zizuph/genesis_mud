/*
   High Clerist Tower - Spur.
   Ellard's Prayerbook for the Visit Museum Quest from Gunthor.

   prayerbook.c
   -----------

   Coded ........: February 1998
   By ...........: Kentari

   Latest update : February 1998
   By........... : Kentari
*/

inherit "/std/object";
#include "../local.h"
#include <stdproperties.h> 

void
create_object()
 {
    set_name("prayerbook");
    add_name("book");
    add_name("_q_prayerbook");
    add_adj("small");
    set_short("small prayerbook");
    set_pshort("small prayerbooks");

    set_long("A prayerbook that holds a Knight's devout prayers to " +
	"Paladine and his sons. Written in old Solamnian, the book is new, " +
	"but the prayers are as old as history.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(MAGIC_AM_MAGIC,({5,"enchantment"}));
    add_prop(OBJ_S_WIZINFO, "A prayerbook for the 'Visit Knight " +
	"Museum' Quest.\n");
}

