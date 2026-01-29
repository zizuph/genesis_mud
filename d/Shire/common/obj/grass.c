/*
 *  grass straw
 *             
 */

inherit "/std/herb.c";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/sys/herb.h"

create_herb()
{
  set_name("straw");
  add_name("straw");
  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 2);
  
  set_ingest_verb("smoke");
  set_herb_name("evendim grass");
  set_id_long("The straw of the evendim fields is known for its magic\n"
	      + "properties. It is said that the hobbits have used it\n"
	      + "to improve their abilities to dodge a thrown stone.\n");
  set_unid_long("The straw is a green colour and quite brittle.\n");
  set_herb_value(175);
  set_find_diff(2);
  set_id_diff(3);
  set_effect(HERB_ENHANCING,"dex",8);
  set_decay_time(500);
}

