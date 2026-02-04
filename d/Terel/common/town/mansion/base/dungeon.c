/*  This is the dungeon, located withing the basement of the Mansion
 *  in the Terel domain.
 *
 *  Coded by Vader on 10/18/92
 *
 *  This is the ending locations for the sacrifice quest (see /d/Terel/open
 *  /BITS , group 0, bit 12 for more information)  You must unchain the
 *  virgin.  To do this, you must possess the key, which is obtained
 *  elsewhere in the mansion
 *
 *  Modified: 13 June 2003, by Bleys
 *      - Updated to modern includes.
 *      - Now logging to the right file.
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"

public void do_alt_quest();

object eve, priest;

public void
reset_room()
{
    if (!present("virgin")) {
        eve = clone_object(MANSION + "mon/virgin");
        eve->move_living("M", TO);
    }
    if (!priest) {
        priest = clone_object(MANSION + "mon/evil_key");
        priest->move_living("M", TO);
    }
}

public void
create_room()
{
    set_short("dungeon");
    set_long(
      "A dark and damp dungeon, which may have once been used to store " +
      "fresh meats before a feast.  Now, chains have been attached to the " +
      "cold stone walls.  Cobwebs cover the corners.\n");

    add_item(({"webs", "cobwebs"}),
      "Many generations of spiders have contributed to the many layers of " +
      "cobwebs here.\n");

    add_item(({"chain", "chains"}),
      "With only a slight bit of rust, these chains are well used, but VERY " +
      "sturdy.  No chance of breaking these apart.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(BASEMENT + "food_room", "east", 0);

    reset_room();
}

public void
init()
{
    ::init();
    add_action("do_quest", "unchain");
    add_action("do_quest", "rescue");
    add_action("do_quest", "free");
}

public int
do_quest(string str)
{
   int expnum;
   string name = TP->query_real_name();
   object key;

   seteuid(getuid());

   if (!eve || !present(eve)) return 0;

   notify_fail(capitalize(query_verb()) + " who?\n");
   if (str == "girl" || str == "girl." || str == "wide-eyed girl" ||
       str == "wide-eyed girl." || str == "beautiful girl" ||
       str == "beautiful girl." || str == "beautiful wide-eyed girl" ||
       str == "beautiful wide-eyed girl.") {
       key = present("virgins_key", TP);
       if (!key) {
          write("You don't have the proper key.\n");
          return 1;
       }
   } else {
       return 0;
   }

   write("You unchain the " + eve->short() + ", freeing her from " +
          "the Evil One.\n");
   say(QCTNAME(TP) + " frees " + QTNAME(eve) + " from the Evil One.\n");
   
   key->remove_object();

   if (TP->test_bit("Terel", QUEST_SAC_GROUP, QUEST_SAC_BIT)) {
      do_alt_quest();
      return 1;
   }

   if (TP->query_gender() == 0) {
       eve->command("kiss " + name);
   } else {
       eve->command("hug " + name);
   }
   write("You feel more experienced.\n");
   eve->command("say Thank you for saving me!");

   TP->set_bit(QUEST_SAC_GROUP, QUEST_SAC_BIT);

   expnum = this_player()->query_exp();

   if (expnum > QUEST_SAC_EXP)
       expnum = QUEST_SAC_EXP;

   TP->add_exp(expnum, 0);

    /*
   write_file(QUEST_LOG, capitalize(name) + " solved " +
              "Sacrifice Quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " rescued " +
        "a virgin from sacrifice (Sacrifice Quest) (" +
        ctime(time()) + ")\n");

   eve->command("say You know, I'll bet that " +
         "the only way for me to get those evil scumbags to leave me " +
         "alone is for me to not be a virgin!");

   if (TP->query_gender() == 0)
       eve->command("wink suggestively at " + name);
   else
       eve->command("smile wisely at " + name);

   eve->command("say Well, I'm off to find someone special! Bye!!");
   eve->command("wave " + name);
   eve->command("east");

   eve->remove_object();
   return 1;
}

public void
do_alt_quest()
{
   eve->command("say Thanks again!  You know, " +
                "it is so hard to find a decent man these days...");

   eve->command("east");
   eve->remove_object();
}
