#pragma strict_types
#include "/d/Kalad/defs.h"

inherit "/d/Kalad/room_std";

/* by Antharanos */
// Polished by Ibun 2007-05-11

void
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("At the top of the pinnacle of rock");
    set_long("A strong, gusting wind races at you from the east, its " +
      "force giving you difficulties in maintaining your balance. Here, " +
      "you are at the very summit of the great pinnacle of rock, which " +
      "stretches downwards hundreds of feet to the ground far below. " +
      "Surprisingly, this place is completely flat with but one thing " +
      "disturbing that uniform flatness. At the very center of this " +
      "flat area is a great stone bier.\n");
   add_item(({"here","very summit","summit","place","flat area","area"}),
      "A perfectly flat, if not smooth area of stone here atop the great " +
      "pinnacle of rock.\n");
   add_item(({"great pinnacle of rock","great pinnacle","pinnacle",
       "pinnacle of rock"}), "You are at its top, hundreds of feet " +
       "above the ground.\n");
   add_item(({"ground"}), "It lies far below you.\n");
   add_item("rock", "It is dark grey, almost black here atop the " +
       "pinnacle.\n");
   add_item(({"great stone bier","great bier","stone bier","bier"}),
      "A large structure built from stone and shaped in the form of a " +
      "pentagon. Dark stains lie upon its upward face.\n");
   add_item(({"dark stains","stains","stain"}), "Faint red in color, " +
       "they remind you of dried blood.\n");
   add_exit(CPASS(desert/mount/p2),"down","@@check_heart",5);
}

void
reset_room()
{
object abdell;

    if (!present("abdell", this_object()))
    {
        abdell = clone_object(CPASS(npc/oracle));
        abdell->move(TO);
        return;
    }
}

int
check_heart()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
        if(ob[i]->id("heart"))
        {
            write("You carefully begin to descend down the side of " +
                "the pinnacle but soon lose your grasp! You plummet " +
                "down the rock face!!\n");
            say(QCTNAME(TP) + " carefully begins to descend down " +
                "the side of the pinnacle but soon loses " +
                TP->query_possessive() + " grasp and plummets " +
                "down the side of the rock face!!\n");
            ob[i]->remove_object();
            set_alarm(2.0,0.0,"death");
            return 0;
        }

   write("You carefully descend down the side of the pinnacle but " +
       "soon lose your grasp! You begin to plummet when suddenly " +
       "you find several good handholds and painfully control " +
       "your descent.\n");
   say(QCTNAME(TP) + " carefully descends down the side of the " +
       "pinnacle but soon loses " + TP->query_possessive() +
       " grasp and begins to plummet down when suddenly " +
       TP->query_pronoun() + " finds several good handholds and " +
       "painfully controls " + TP->query_possessive()+ " descent.\n");
   return 0;
}

int
death()
{
   TP->catch_msg("You slam into the ground with a bone-crushing sound "+
      "and soon discover that you have lost the heart!!\n");
   TP->heal_hp((TP->query_max_hp() * 50) / 100);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   return 1;
}

void
enter_inv(object ob, object from)
{
    object abdell;

    ::enter_inv(ob, from);

    if (!present("abdell", this_object()))
    {
        abdell = clone_object(CPASS(npc/oracle));
        abdell->move(TO);
    }
}
