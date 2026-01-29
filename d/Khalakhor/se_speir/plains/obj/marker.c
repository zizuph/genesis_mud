/*
 * marker.c
 *
 * Boundary marker between Calladon & Claryn provinces.
 *  Found in ../room/plain_38_20.c
 *
 * Khail - January 14/98
 * Zima  - March 8/98 - added honeysuckle
 * Zima  - June 2     - honeysuckle moved to shepherd's fence; replaced
 *                      with poison ivy ;)
 */
#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#define  HSUCKLE_ID_DIFF    44
#define  POISON_IVY_ID_DIFF 5
#define  KRYNN_POISON_IVY   "/d/Krynn/common/herbs/poison_ivy"
 
inherit "/std/object";
 
int     numflowers=0; // actually num leaves now
 
public string
read_writing()
{
    if (!CAN_SEE_IN_ROOM(TP))
        return "It's too dark to see anything.\n";
 
    if (!CAN_SEE(TP, TO))
        return "You see no such thing.\n";
 
    if (TP->query_skill(SS_LANGUAGE) < 15)
        return "It sure looks interesting, unfortunately you " +
            "don't know how to read well enough to decipher " +
            "the markings.\n";
 
    return "You see two words written on the stone; on the " +
        "north side is written the word 'Calladon', and on " +
        "the south, 'Claryn'.\n";
}
 
public void
create_object()
{
    set_name(({"stone","marker","column","pillar"}));
    set_adj(({"tall","grey","stone"}));
    set_short("tall stone column");
    set_long("This tall rectangular column is made from " +
        "grey stone, its base rooted deep in the soil. " +
        "It stands a full spear-length high, its sides " +
        "two hands wide. A leafy green vine with small white berries "+
        "is overtaking it, while you can see some "+
        "writing on the north and south sides of it.\n");
 
    add_item(({"vine","leaves","berries"}),"@@exa_vine");
    add_item(({"writing"}), VBFC_ME("read_writing"));
    add_cmd_item(query_names() + ({"writing"}),
        ({"read","touch","climb"}),
        ({VBFC_ME("read_writing"),
          "The stone pillar is cold to the touch.\n",
          "The stone is too smooth to climb.\n"}));
 
    set_no_show_composite(1);
 
    add_prop(OBJ_I_VOLUME, 500000);  /* 500 liters */
    add_prop(OBJ_I_WEIGHT, 5000000); /* 5 tonnes */
    add_prop(OBJ_M_NO_GET, "Even if you could manage " +
        "the weight, you could never get it out of " +
        "the ground!\n");
}
 
public void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
 
    if (inv->query_prop(ROOM_I_IS))
        inv->add_my_desc("A tall stone column has been " +
            "placed here.\n", this_object());
}
 
 
// invoked by reset_room
void set_num_flowers(int i) { numflowers = i; }
int  query_num_flowers()    { return numflowers; }
 
string exa_vine()
{
   string d="It is a green vine with a few small white berries and many "+
            "three-compound leaves. It is growing around the base of the "+
            "column and overtaking its sides. ";
   if (TP->query_skill(SS_HERBALISM)>=POISON_IVY_ID_DIFF)
      d+="You recognize the familiar leaf as poison ivy.";
   return (d+"\n");
}
 
int do_pick(string cmd) {
   object flower;
   int    rc;
 
   //check arguments to command
   seteuid(getuid());
   if (!stringp(cmd))
      { notify_fail("Pick what from what?\n"); return 0; }
   rc = parse_command(cmd,environment(),
        "'leaf' / 'berry' / 'flower' 'from' 'vine' / 'shrub' / 'column'");
   if (!rc)
      { notify_fail("Pick what from what?\n"); return 0; }
 
   // args OK, so do pick if any here
   if (numflowers <=0)
      write("None of the remaining leaves are pickable.\n");
   else {
      numflowers--;
      flower=clone_object(KRYNN_POISON_IVY);
      flower->move(TP);
      write("You pick a "+(flower->query_short())+" from the vine "+
            "growing up the column.\n");
      tell_room(TO,QCTNAME(TP)+" picks a "+(flower->query_short())+
                   " from the vine growing up the column.\n",TP);
   }
   return 1;
}
 
public void init()
{
   ::init();
   add_action(&do_pick(),"pick");
   add_action(&do_pick(),"pluck");
}
