/*
 * spellp.c
 *
 * Used in carisca/x1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Modified by Mirandus to remove a bug caused when you eat the paper
 * either on purpose or by accident before completing the quest, Aug 2015
 *
 * Cleaned up a bit more
 * Tapakah, 07/2021
 */

#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit "/std/object";

string
query_recover ()
{
  return MASTER;
}

void
create_object ()
{
  set_short("old elf skeleton");
  set_name("skeleton");
  set_adj("old");
  add_adj("elf");
  add_name("elf");
  set_long("The skeleton looks as if it has been away from its owner for " +
           "a while.\n");
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 5000);
  add_prop(OBJ_S_SEARCH_FUN, "lookforstuff");
}

void
remove_me ()
{
  tell_room(environment(), "The skeleton crumbles to dust!\n");
  remove_object();
}


string
lookforstuff (string s)
{
  object apa;

  seteuid(getuid(TO));

  if (QDONE(ROKEGROUP, SKELETON) && !present("sppapp", TP)) {
    write("Strange... You find the paper you ate again.\n" +
          "It must be something special about it, if it " +
          "is able to find its way back to you like this.\n");

    apa = clone_object(ROKEDIR + "obj/spellpaper");

    if(QDONE(ROKEGROUP, PAPERQUEST)) {
      apa->transform_me();
      apa->move(TP);
    }
    else
      apa->move(TP);
    return " ";
  }

  if (!QDONE(ROKEGROUP, SKELETON)) {
    write("As you search the skeleton it crumbles to dust and " +
          "you find an old paper.\n");
    clone_object(ROKEDIR + "obj/spellpaper")->move(TP);
    say(QCTNAME(TP) + " finds something in the skeleton.\n");
    write("You have performed well!\nYou feel more experienced!\n");
    TP->add_exp_quest(SKELETONXP);

    QSET(ROKEGROUP, SKELETON);
    QLOG("Skeleton quest", SKELETONXP);

    set_alarm(1.0, 0.0, remove_me);
    return "";
  }
  return 0;
}
