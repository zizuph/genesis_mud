/*
 *  /d/Gondor/morgul/tower/interrogation_chamber.c
 *
 *  This is a room which may be used by the Mages of the Society
 *  to grant a audience to any who are unfortunate enough to 
 *  deserve such an honour.
 *
 *  Code for the light is borrowed from Gorboth's audience chamber. 
 *
 *  Base code for the bench borrowed from Thron Room.
 *
 *
 *     Created by Toby, 28-Sept-2006
 *
 *
 *     Modification log:
 *
 */
#pragma strict_types.h

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"


#define  OUTSIDE      (TOWER_DIR + "tower_0e.c")
#define  LOG_FILE     "/d/Gondor/common/guild2/log/morgul_interrogation"

#define MORGUL_S_BENCH  "_morgul_s_bench"
#define MAGE_BENCH      "_mage_bench"
#define CHAMBER_FLOOR   "_chamber_floor"
#define NO_MAGES        2


#define HE(xxx)	  (xxx)->query_pronoun()
#define HIS(xxx)  (xxx)->query_possessive()
#define HIM(xxx)  (xxx)->query_objective()

#define MY_COMPOSITE_LIVE(xxx, for)	COMPOSITE_WORDS((xxx)->query_art_name(for))

static object  gMage_bench = 0;

//  Global Variables
int     Eye_Opened = 0;

//  Prototypes
void  do_log(object ob, string logtxt);
int   rasp_command(string str);
int   tell_outside();
int   do_sit(string str);
int   do_rise(string str);

// Emotions
int do_inspect(string str);

void
create_gondor()
{
    set_short("a secret chamber in the Tower of Black Sorcery");
    set_long("A terrible blackness hangs heavily in this chamber, suffocating"
      + " the very presence of light with its weight. There is"
      + " nothing here to supply comfort. Smooth black stone comprises"
      + " the surface of all within. Only the faint lines in the western"
      + " wall, depicting an archway, break that cold smooth surface. There"
      + " is a small stone bench near the eastern wall.\n");

    add_item( ({"stone", "black stone", "smooth stone",
                "smooth black stone"}),
        "The stone which comprises the surfaces here is unblemished,"
      + " and does not bear the mark of any instrument of"
      + " Men or Elves.\n");
    add_item( ({"floor", "ground"}), 
        "The floor is smooth and black as pitch. Even a very"
      + " powerful light source would have a difficult time"
      + " illuminating its surface. In the center of the chamber it"
      + " looks rather worn.\n");
    add_item( ({"ceiling", "roof", "up"}), 
        "The ceiling of this room is very low, creating a feeling"
      + " of oppression and weight upon your shoulders. It, like"
      + " the floor below, is an unmarked surface of utter blackness.\n");
    add_item( ({"walls", "wall"}), 
        "There are four walls here. One to the north, south, east, and"
      + " west.\n");
    add_item( ({"north wall", "north walls", "northern wall"}), 
        "The wall to the north is bleak and unadorned.\n");
    add_item( ({"south wall", "south walls", "southern wall"}), 
        "The wall to the south is bleak and unadorned.\n");
    add_item( ({"west wall", "west walls", "western wall"}), 
        "The wall to the west is utterly black apart from the picture"
      + " outlining an archway leading out of here.\n");
    add_item( ({"east wall", "east walls", "eastern wall"}), 
        "The eastern wall is utterly black and unadorned.\n");
    add_item( ({"lines", "faint lines", "archway"}), 
        "In the utterly black western wall there are fine lines made"
      + " outlining an archway leading out of here.\n");
    add_item( ({"bench", "stone bench", "black bench", "small black bench",
                "black stone bench", "small black stone bench"}), "@@exa_bench");
    add_item( "marks", 
        "The marks in the ground next to the bench bears marks as if someone " 
      + "has, or a pair have, been standing on either side of the bench many "
      + "a time, in session.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -4);

    add_exit(TOWER_DIR + "tower_0e", "out", "@@tell_outside", 1);
}


void
init()
{
    ::init();

    add_action(rasp_command, "rasp");
    add_action(do_sit,       "sit");
    add_action(do_rise,      "stand");
    add_action(do_rise,      "rise");
    add_action(do_inspect,   "inspect");
}

int
do_sit(string str)
{
    int     level,
    size;
    string  where,
    where_old;
    object  tp = TP;

    if (!strlen(str))
    {
       NFN("Sit where?");
       return 0;
    }

    str = LOW(str);

    if (parse_command(str, ({ }), " [down] [on] [the] [stone] 'bench' "))
       where = MAGE_BENCH;
    else if (parse_command(str, ({ }), " [down] [on] [the] 'floor' "))
       where = CHAMBER_FLOOR;
    else
    {
       NFN("Sit down on one of the bench or on the floor?");
       return 0;
    }

    if (stringp(where_old = tp->query_prop(MORGUL_S_BENCH)))
    {
	  switch (where_old)
	  {
        case MAGE_BENCH:
          NFN("But you are already sitting on the bench!");
          return 0;
        case CHAMBER_FLOOR:
          NFN("But you are already sitting on the floor!");
	      return 0;
	  }
    }

    level = tp->query_morgul_level();

    if (!level)
	  level = -1;

    if(level > APPRENTICE_LEVEL || tp->query_nazgul() || tp->query_wiz_level())
    {
	  if ((where != MAGE_BENCH))
	  {
	    NFN("Why would you, like filthy Etani, wish to sit down"
          + " anywhere but on the stone bench?");
	    return 0;
	  }
	  if (objectp(gMage_bench))
	  {
	    if (!present(gMage_bench, TO) ||
	      (gMage_bench->query_prop(MORGUL_S_BENCH) != MAGE_BENCH))
		gMage_bench = 0;
	    else
	    {
		  NFN(gMage_bench->query_The_name(TP)
		    + " is already sitting on the bench!");
		  return 0;
	    }
	  }

      write("You walk up to the bench and slowly you sit down watching your" 
          + " surrounding carefully, eyes glowing.\n");
      set_alarm(4.0, 0.0, &write("As you sit down a presence invades your"
          + " mind, it leaves you as soon as it arrived though.\n"));
      say(QCTNAME(tp) + " walks up to the bench and sits down watching "
          + HIS(tp)+" surroundings carefully, eyes glowing like red coals.\n", tp);

      gMage_bench = tp;
      tp->add_prop(MORGUL_S_BENCH, MAGE_BENCH);
      tp->add_prop(LIVE_S_EXTRA_SHORT,", sitting on the stone bench");
      tp->add_subloc(MORGUL_S_BENCH, TO);
      tp->set_no_show_composite(1);

      return 1;
    }
    else if(level > 0)
    {
	  if (where == MAGE_BENCH)
	  {
	    write("As you bend your knees to sit on the stone bench a presence "
              + "invades your mind and you know it is not for you, you step back.\n");
	    say(QCTNAME(tp) + " tries to sit on the stone bench, but " + HE(tp)
	      + " quickly backs away.\n");
	    return 1;
	  }
	  else if (where == CHAMBER_FLOOR)
	  {
	      NFN("Why would you wish to sit down like Etani on the floor?");
	      return 0;
	  }

      return 1;
    }
    else
    { 
	  if (where == MAGE_BENCH)
	  {
	    write("As you walk toward the stone bench to sit down a presence "
              + "invades your mind, almost crushing it. A terrible rasping "
              + "voice says to you: Worthless Etani, sit on the floor!" 
              + " The presence leaves you tremling in the middle of the chamber.\n");
	    say(QCTNAME(tp) + " tries to sit on the stone bench, but " + HE(tp)
	      + " quickly backs away, glassy eyed, trembling with fear.\n");
	    return 1;
	  }
      else if (where == CHAMBER_FLOOR)
	  {
         write("You sit down on the floor.\n");
         say(QCTNAME(tp) + " sits down on the floor.\n", tp);

         tp->add_prop(MORGUL_S_BENCH, CHAMBER_FLOOR);
         tp->add_prop(LIVE_S_EXTRA_SHORT,", sitting on the floor in front of the stone bench");
         tp->add_subloc(MORGUL_S_BENCH, TO);

         return 1;
      }
    }
}

int
do_rise(string str)
{
    object  tp = TP;
    string  vb = query_verb(),
    where = tp->query_prop(MORGUL_S_BENCH);

    if (vb == "stand" && str != "up")
        NF0(CAP(vb)+" what? Up?\n");

    if (!strlen(tp->query_prop(MORGUL_S_BENCH)))
       NF0("But you are not sitting down!\n");

    switch (where)
    {
       case MAGE_BENCH:
          write("You rise from the stone bench, straightening your robe absently.\n");
          say(QCTNAME(tp)+" rises from the stone bench, straightening "+HIS(tp)
            + " robe absently.\n",tp);
          gMage_bench = 0;
          break;
       case CHAMBER_FLOOR:
          write("You stand up from your spot on the floor.\n");
          say(QCTNAME(tp)+" rises from "+HIS(tp)
            + " spot on the floor.\n",tp);
          break;
       default:
         break;
    }
    tp->remove_prop(LIVE_S_EXTRA_SHORT);
    tp->remove_prop(MORGUL_S_BENCH);
    tp->remove_subloc(MORGUL_S_BENCH);
    tp->set_no_show_composite(0);
    return 1;
}

void
leave_inv(object ob, object to)
{
    object tp = TP;
    string  where;

    ::leave_inv(ob, to);

    if (!objectp(ob))
       return;

    if (living(ob) && strlen(where = ob->query_prop(MORGUL_S_BENCH)))
    {
       switch (where)
       {
       case MAGE_BENCH:
	      write("You rise from the stone bench straightening your robe absently.\n");
	      tell_room(TO, QCTNAME(tp)+" rises from the stone bench straightening "+HIS(tp)
	        + " robe absently.\n", tp);
	      gMage_bench = 0;
          break;
       case CHAMBER_FLOOR:
          write("You stand up from your spot on the floor.\n");
	      tell_room(TO, QCTNAME(tp)+" rises from "+HIS(tp)
	        + " spot on the floor.\n",tp);
	      break;
	   default:
	      break;
	}

	ob->remove_prop(LIVE_S_EXTRA_SHORT);
	ob->remove_prop(MORGUL_S_BENCH);
	ob->remove_subloc(MORGUL_S_BENCH);
	ob->set_no_show_composite(0);
    }
}

public string
exa_bench()
{
    string  desc = 
    "It is utterly black and not bigger than it fits one person.", 
    name;

    if (objectp(gMage_bench) && present(gMage_bench, TO))
    {
        if (TP == gMage_bench)
            name = "You are";
        else if (TP->query_met(gMage_bench))
            name = gMage_bench->query_name() + ", "
          + gMage_bench->query_morgul_title() + ", is";
        else
            name = CAP(LANG_ADDART(gMage_bench->query_nonmet_name())) + " is";

        desc += " " + name + " sitting on the stone bench.";
    }
    else
	desc += " Its surface is smooth from apparant long use.";

    desc +=  " Next to the bench the ground bears marks as if someone has,"
      + " or a pair have, been standing on the sides of the bench in session.\n";

    return desc;
}

void
open_eye()
{
    tell_room(TO, "Suddenly the walls start to radiate a soft red glow.\n");

    add_prop(ROOM_I_LIGHT, 1);
    Eye_Opened = 1;

    return;
}

void
close_eye()
{
    tell_room(TO, "The red glow emitting from the walls suddenly flares up"
          + " and the light burns your eyes, then there is blackness.\n");

    add_prop(ROOM_I_LIGHT, -4);
    Eye_Opened = 0;

    return;
}

int
rasp_command(string str)
{
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (!IS_MORGUL_MAGE(TP) && !TP->query_wiz_level())
        return 0;

    if (str != "katuohek" && str != "beshnurza")
        return 0;

    write("Feeling a sudden sense of power flowing through your"
      + " undead veins, you rasp: " + CAP(str) + "!\n");
    say(QCTNAME(TP) + " stands suddenly erect, and with a low,"
      + " gutteral voice, rasps harshly, '" + CAP(str) + "!'\n");
    TP->add_mana(-30);

    if (str == "katuohek")
        if (Eye_Opened)
            set_alarm(2.0, 0.0, &tell_room(TO, "The soft red glow pulsates.\n"));
        else
            set_alarm(2.0, 0.0, &open_eye());

    if (str == "beshnurza")
        if (!Eye_Opened)
            return 1;
        else
            set_alarm(2.0, 0.0, &close_eye());

    return 1;
}

void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE, ob->query_name() + " ("
      + ob->query_average_stat() + ")" + logtxt + "on: "
      + ctime(time()) + ".\n");

    return;
}

int
tell_outside()
{
    string desc;

    if(OUTSIDE->query_door_state())
       tell_room(OUTSIDE, QTNAME(TP) + " steps out from the painting.\n");
    else
       tell_room(OUTSIDE, "The massive iron door in the painting swing "  +
                       "open briefly to allow " + QTNAME(TP) + " out " +
                       "into the large hall, then silently swings chut " +
                       "again.\n");

    return 0;
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string  str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
       return "";

    if (subloc != MORGUL_S_BENCH)
       return me->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
       str = "You are ";
    else
       str = CAP(HE(me)) + " is ";

    str += "sitting ";

    switch(me->query_prop(MORGUL_S_BENCH))
    {
    case MAGE_BENCH:
       str += "on the stone bench.\n";
       break;
    case CHAMBER_FLOOR:
       str += "at the floor in front of the stone bench.\n";
       break;
    }
    return str;
}

/* Emotions for the bench below this line. */

int
do_inspect(string str)
{
    object  tp = TP,
    *objs,
    *live,
    *dead;
    string  where,
            what;


    if (!stringp(where = tp->query_prop(MORGUL_S_BENCH)))
       return 0;

    if (!str)
       NF0("Inspect who?\n");

    if (!parse_command(str, TO, "%l", objs))
       NF0("You cannot find any "+str+" here.\n");

    objs = NORMAL_ACCESS(objs, 0, 0);
    objs -= ({ tp });

    if (!sizeof(objs))
       NF0("You cannot find any "+str+" here.\n");

    if (where == MAGE_BENCH)
       what = "stone bench";
    else
	   what = "from the shadows";

    write("You sit forward on the "+what+", inspecting "
      + COMPOSITE_LIVE(objs) + " thoughtfully.\n");
    objs->catch_msg(QCTNAME(tp) + " lean forward on the "
      +what+ ", scrutinizing you thoughtfully.\n");
    say(QCTNAME(tp)+" sits forward on the "+what+", inspecting "
      + COMPOSITE_LIVE(objs) + " thoughtfully.\n", ({ tp }) + objs);
    return 1;
}
