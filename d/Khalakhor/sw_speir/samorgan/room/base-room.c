/*
 * Base room for SaMorgan
 * Tapakah, 04/2021
 */

#pragma no_clone
#pragma strict_types

#include "../defs.h"

inherit KSTDROOM;

int *
query_local_coords ()
{
  int match, xy, x ,y;
  
  foreach (string prefix: ({"vil", "house", "pier"})) {
    int match = sscanf(file_name(TO), ROOM + prefix + "%d", xy);
    if (match) {
      if (xy > 99) {
        x = xy / 100;
        y = xy % 100;
      }
      else if (xy > 9) {
        x = xy / 10;
        y = xy % 10;
      }
      else 
        return ({0, 0});
      return ({x, y});
    }
  }
  return ({0, 0});
}

int *
query_global_coords ()
{
	return SAMORGAN_COORDS;
}

void
populate_house (string *file_choices)
{
  object this_ob, *ob;
  foreach (string person: file_choices) {
    this_ob = find_object(person);
    if (!objectp(this_ob)) {
      this_ob = clone_object(person);
      this_ob->move(TO);
      this_ob->equip_me();
      return;
    }
    ob = object_clones(find_object(person));
    if (! sizeof(ob)) {
      this_ob = clone_object(person);
      this_ob->move(TO);
      this_ob->equip_me();
      return;
    }
  }  
}

void
reset_room ()
{
  ::reset_room();
}
