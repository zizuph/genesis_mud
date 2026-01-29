#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/OotS/defs.h"

inherit THARK_IN;
inherit "/lib/unique";

object chest, gem1, gem2, scroll, money, ogre;

#define DIAMOND_GEM clone_object("/d/Genesis/gems/obj/diamond_black")
#define BLOODSTONE  clone_object("/d/Genesis/gems/obj/bloodstone")
#define SCROLL      "/d/Krynn/common/scrolls/portents_and_omens_scroll"

void
reset_tharkadan_room()
{
    if (!objectp(chest))
    {
        chest = clone_object(TOBJ + "chest");
        chest->move(TO);
    }

    chest->add_prop(CONT_I_CLOSED, 1);
    chest->add_prop(CONT_I_LOCK, 1);

    if (!P(scroll, chest))
    {
        scroll = clone_object(SCROLL);
        scroll->move(chest, 1);
    }

    if (!P(money, chest))
      {
          money = MONEY_MAKE_GC(random(40) + 40);
          money->move(chest, 1);
      }
    if (!P(gem1, chest))
      {
          gem1 = DIAMOND_GEM;
          gem1->move(chest, 1);
      }
    if (!P(gem2, chest))
      {
          gem2 = BLOODSTONE;
          gem2->move(chest, 1);
      }

    if(!objectp(ogre))
    {
       ogre = clone_object(LIVING + "ogre_magi");
       ogre->arm_me();
       ogre->move(TO, 1);
    }

}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "fwatchtower","down",0);

    add_item(({"platform","top","centre","watchtower","tower",
        "dwarven watchtower"}),
        "You stand at the top of an ancient dwarven watchtower that " +
        "has been claimed as the lair of an ogre magi. Apart from a " +
        "brazier that burns in the centre of the room, there is nothing " +
        "else in here of note. You find that a bit unusual.\n");
    add_item(({"brazier","large brazier"}), "A large brazier burns with " +
        "a malevolent light in the middle of the room. The shadows " +
        "dance wildly against the walls, like tortured souls writhing " +
        "to the tune of a demonic piper.\n");
    add_item(({"shadows","walls","wall"}),"The light cast from the " +
        "brazier dance madly like the souls from hell. It is almost " +
        "hypnotic, and you sometimes think you see them dance around " +
        "the shadowy shape of a chest against the wall.\n");
    add_item(({"shadowy shape","shape"}),"The shadowy shape is gone, " +
        "and you see nothing to indicate what may have cast such a " +
        "shadow.\n");

    reset_tharkadan_room();
}

string
short_descr()
{
    return "platform of a dwarven watchtower";
}

string
long_descr()
{
    return "You stand on a platform at the top of an ancient and " +
       "abandoned dwarven watchtower. Abandoned at least by the " +
       "dwarves, for it seems this tower has been claimed as the lair " +
       "of an ogre magi. A large brazier burns with a malevolent light " +
       "in the centre of the platform, casting shadows around " +
       "the room that seemed to dance in a tortured, macabre way.\n";
}

int
curse_revelation(object ob)
{
     ob->catch_msg("\n\nThe light from the large brazier casts a " +
         "malevolent shadow across the wall of the ogre magi, " +
         "triggering a divine revelation!\n\n\n");
     OOTS_ADD_REV(ob, "curseofpaladine",
         "enlightenment - ogre races and the curse of paladine"); 

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
       if(IS_OOTS(ob) && objectp(ogre))
       {
          if(!OOTS_QUERY_REV(ob, "curseofpaladine"))
          {
            set_alarm(1.5, 0.0, &curse_revelation(ob)); 
          }
       }
    }

}

