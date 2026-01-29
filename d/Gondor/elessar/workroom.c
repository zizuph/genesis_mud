#define	USE_CHAIRS 1	/* use gnad's chair code */

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/open/npcsize";

#ifdef USE_CHAIRS
inherit "/d/Gondor/open/room_chairs/room_chairs";
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define	COUCH_NAME	"large comfortable couch"
public string		look_couch();
#endif /* USE_CHAIRS */

/*
#include "/d/Gondor/elessar/lib/time.c"
*/
#include "/d/Gondor/defs.h"
#include "/sys/macros.h"


string last_place;

create_room() {
    set_short("A relaxed little workroom");
    set_long("In this place Elessar spends most of his time, \n" +
    "and receives visitors. A large couch stands in one corner,\n"+
    "and a large desk is placed by the wall.\n");
  add_exit("/d/Gondor/workroom","meeting","@@wiz_check");
  add_exit("/d/Gondor/elessar/project","project","@@wiz_check");
  add_exit("/d/Gondor/common/guild/north/post","post","@@wiz_check");

#ifndef USE_CHAIRS
  add_item("couch","It is large and comfortable, what more could you wish for?\n");
#else
    add_chair(COUCH_NAME,
	"[down] [in] / [on] [the] [large] [comfortable] 'couch'", 8);
    add_item( ({ "large comfortable couch", "large couch",
	"comfortable couch", "couch", }),
	look_couch);
    set_chair_invis_ok(1);
#endif /* USE_CHAIRS */

  add_item("desk","The desk is filled with papers and books.\n");
  add_item("papers","The papers are filled with writing, probably plans for Gondor, the\n"+
  "domain Elessar is Lord over. You see some maps drawn on the papers too.\n");
  add_item("writing","The writing is in the ancient Gondorian language, and you don't\n"+
  "understand much of it. You manage to read one line though. It says:\n"+
  "'Layout of Minas Tirith.'\n");
}

query_prevent_snoop() {
  return 1;
}


sunrise()
{
  return 1;
}

sunset()
{
  return 1;
}

wiz_check()
{
  if (TP->query_wiz_level())
  {
#ifdef USE_CHAIRS
	check_sitting();
#endif /* USE_CHAIRS */
	return 0;
  }
  return 1;
}

init()
{
  ::init();
    init_npcsize();
#ifdef USE_CHAIRS
  init_room_chairs();
#endif /* USE_CHAIRS */
  add_action("mortal_return","back");
  add_action("check_time","time");
}

mortal_return(string str)
{
  if (TP->query_wiz_level()) {
    write("But you are a wiz! Why would you need to use this exit?\n");
    return 1;
    }
  last_place = TP->query_prop("_player_transed_from");
  if (!last_place) { write("You no longer remember where you last were, so you cannot return.\n");
    say(QCTNAME(TP)+" fails to return back to the previous location.\n",TP);
    return 1;
    }
  tell_room(last_place,"A large hand comes out of a rift in thin air.\n"+
    QCNAME(TP)+" is carefully set down, and the hand disappears in the rift.\n");
#ifdef USE_CHAIRS
  check_sitting();
#endif /* USE_CHAIRS */
  TP->move_living("back to where "+TP->query_pronoun()+" was summoned from",last_place);
  return 1;
}

int
do_emote(string str)
{
    if (!str) NFN0("Emote what?");

    TP->catch_msg("You emote: " + TP->query_name() + " " + str + "\n");
    say(QCTNAME(TP) + " " + str + "\n", TP);
    return 1;
}

#ifdef USE_CHAIRS

/* 
 * Function name:	look_couch
 * Description	:	VBFC for the couch and its occupants
 * Returns	:	string - the desc
 */
public string
look_couch()
{
    return "The couch is quite large, and looks very comfortable.\n" +
	sitting_on_chair(COUCH_NAME, this_player(), 0);
} /* look_couch */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

#endif /* USE_CHAIRS */
