/*
 * can.c
 *
 * Used in npc/kato.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Tidied up a bit by Tapakah, 07/2021
 */

/* A can of paint
 * With big help from
 * Napture and Gresolle
 * Joshua 19950114
 *
 * Updated: Jakob 950301
 */

#pragma save_binary
#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#include "defs.h"

inherit "std/object";

int n;

void
create_object()
{
  n = 1;
  set_name("can");
  set_short("can of paint");
  set_long("This is a can of paint. There is some " +
           "black paint left in the can. \n");
  set_adj(({"painted", "black"}));

  add_prop(OBJ_I_VALUE, 293);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_WEIGHT, 750);
}

int
paint_me(string what)
{
  object dragobj;
  object *arr;
  string possesiv;

  if (!what)
    NF0("Paint what?");

  what = lower_case(what);
  sscanf(what, "%s black", what);  /* Remove `paint dragon black` */
  arr = FIND_STR_IN_OBJECT(what, environment(TP));
  if (!sizeof(arr))
    NF0("Paint what?");
  if (sizeof(arr) > 1)
    NF0("You can only paint one thing at a time!");

  dragobj = arr[0];

  if (n > 3) {
    TP->catch_msg("Damn, There is no paint left...\n");
    set_long("This is a paint can. There is no paint left in it.\n");
    return 1;
  }
  if (present("_the_paint_subloc", dragobj)) {
    TP->catch_msg(TP != dragobj ?
                  QCTNAME(dragobj) + " is already painted black!\n" :
                  "You are already painted black!\n");
    return 1;
  }
  setuid(); seteuid(getuid());
  clone_object(ROKEDIR + "obj/paint_subloc")->move(dragobj);
  n++;
  if (dragobj->id("kaheda_dragon_quest")) {
    TP->catch_msg("You paint the cute drooling dragon black!\n");
    say(QCTNAME(TP) + " paints the cute drooling dragon black!\n");
    if (!QDONE(ROKEGROUP, PAINTQUEST) && (TP->query_alignment() < 0)) {
      TP->catch_msg("You feel more experienced!\n");
      TP->add_exp_quest(PAINTQUESTXP);
      QSET(ROKEGROUP, PAINTQUEST);
      QLOG("Paint quest", PAINTQUESTXP);
    }
  }
  else {
      n++;
      if (TP != dragobj) {
        TP->catch_msg("Hee hee you paint " + QCTNAME(dragobj) +
                      " black. Great fun!\n");
        say(QCTNAME(TP) + " paints " + QCTNAME(dragobj) + " black!\n",
            ({dragobj, TP}));
        dragobj->catch_msg(QCTNAME(TP) + " paints you black!\n");
      }
      else {
        possesiv = TP->query_objective() + "self";
        write("Hee hee you paint yourself black. Great fun!\n");
        say(QCTNAME(TP) + " paints " + possesiv + " black!\n");
      }
  }
  return 1;
}

void
init()
{
  ::init();
  add_action(paint_me, "paint");
}
