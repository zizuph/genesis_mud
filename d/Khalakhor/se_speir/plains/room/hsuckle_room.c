/*
 * hsuckle_room.c
 *
 * Any plains room with honeysuckle growing in it can inherit this room
 * Initially used in ../room/plains_28_9.c, 29_9, and 30_9
 * 
 * Zima  - June 3 - created
 * Patched count of available vines
 * Tidied up
 * Tapakah, 07/2021
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

#include "plains.h"

inherit PLAINBASE;

#define  HSUCKLE_ID_DIFF 44
#define MAX_SHEEP   3
#define MAX_FLOWERS 5

object *sheep = allocate(MAX_SHEEP);

int     numflowers=0;
string  where;
 
void set_num_flowers (int i) { numflowers = i; }
int  query_num_flowers ()    { return numflowers; }

string
flower_status ()
{
  string base_desc = "The fence is crudely made of twisted, sun and rain warped "+
    "wooden beams, posts set fairly evenly around the pasture, "+
    "with two rails strapped horizontally between each. It is "+
    "overgrown with a leafy vine bearing fragrant pink twinned "+
    "flowers along the south side. ";
  if (numflowers < 0)
    return base_desc + "Unfortunately, none of the flowers are pickable.\n";
  else if (numflowers < 3)
    return base_desc + "Just a few of them seem to be pickable.\n";
  else
    return base_desc + "Quite a few of them may be picked.\n";
}

// should be invoked by reset_room and create_khalakhor_room
 
string hsuckle_desc ()
{
  return ("A leafy green vine, actually a shrub with vine-like branches, "+
          "is overtaking the "+where+", covered with pink twinned "+
          "flowers. The flowers have a strong sweet smell which perfumes "+
          "the area, tempting you to pluck them from the vine. ");
}
 
string rec_hsuckle_desc ()
{
  return hsuckle_desc() + "You recognize the flowers as honeysuckle.\n";
}
 
string exa_hsucklex (string s)
{
  if (TP->query_skill(SS_HERBALISM) >= HSUCKLE_ID_DIFF)
    return rec_hsuckle_desc();
  return ("You find no honeysuckle"+s+".\n");
}
 
string exa_hsuckle ()  { return exa_hsucklex("");  }
string exa_hsuckles () { return exa_hsucklex("s"); }
 
string
exa_vine ()
{
  if (TP->query_skill(SS_HERBALISM) >= HSUCKLE_ID_DIFF)
    return rec_hsuckle_desc();
  return hsuckle_desc()+"\n";
}
 
int
do_pick (string cmd)
{
  object flower;
  int    rc;
  string desc;

  seteuid(getuid());
  if (!stringp(cmd))
    NF0("Pick what from what?");
  rc = parse_command(cmd,TO,
                     "[a] [the] 'honeysuckle' / 'honeysuckles' / 'flower' / 'flowers' "+
                     "'from' [a] [the] 'bush' / 'vine' / 'shrub' / 'fence'");
  if (!rc)
    NF0("Pick what from what?");
 
  // args OK, so do pick if any here
  if (numflowers <= 0)
    write("None of the remaining flowers are pickable.\n");
  else {
    numflowers--;
    flower=clone_object(COM_HERBS+"honeysuckle");
    flower->move(TP);
    desc = numflowers ? "a " : "the last pickable ";
    write("You pick " + desc + (flower->query_short()) + " from the vine "+
          "growing on the "+where+".\n");
    tell_room(TO,QCTNAME(TP)+" picks a "+(flower->query_short())+
              " from the vine growing on the "+where+".\n",TP);
  }
  return 1;
}
 
void
add_hsuckle_items (string w)
{
  where = w;
  add_item(({"vine","flowers","shrub","vines"}),"@@exa_vine");
  add_item(({"honeysuckle","honeysuckle vine","honeysuckle shrub"}),
           exa_hsuckle);
  add_item("honeysuckles","@@exa_hsuckles");
}
 
void
reset_room ()
{
  int i,num = random(MAX_SHEEP);

  set_num_flowers(MAX_FLOWERS); //num honeysuckles pickable per reset
  set_searched(0);
  for (i=0; i<num; i++)
    if (!objectp(sheep[i])) {
      sheep[i] = clone_object(NPC2+"sheep");
      (sheep[i])->move(TO);
      tell_room(TO,"A "+(sheep[i]->query_short())+" scampers up to you.\n");
    }
}

void
create_honeysuckle_room ()
{
  set_short("In a pasture on a grassy plain");
  set_long("   You in a pasture situated on the "+
           "grassy rolling hills of the plain. The smell of "+
           "livestock is strong here, the scent mixing with that of "+
           "the salt air brought in by a cool breeze. A crude fence "+
           "encloses the pasture on all sides.\n");

  add_item(({"area","fenced-in area","pasture"}),
           "The pasture is situated on the grassy hills of the plain, "+
           "obviously made to enclose livestock. A crude wooden fence "+
           "surrounds the pasture on all sides.\n");
  add_item("fence", flower_status);
  add_hsuckle_items("fence");
}
 
void
init ()
{
  ::init();
  foreach(string action: ({"pick", "pluck"}))
    add_action(do_pick, action);
}

int *
query_global_coords ()
{
  return ({3, 0});
}
