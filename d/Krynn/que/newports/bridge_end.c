/*
 * Filename:        bridge_end.c
 * Description:     Area around Newports, Abanasinia
 *
 * Coded by:        Aridor, 03/95
 *
 * Revision history:
 * Oct 25 1999 by Boron: Added warfare support
 *
 */

#include "/d/Krynn/common/warfare/warfare.h"
#include "local.h"
#include <macros.h>
#include <language.h>

inherit BASE_FILE;

mixed *guards = ({ 0,0,0,0 });

mixed
query_to_jail()
{
    return "southwest";
}

void
reset_newport_room()
{
    if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == RED_ARMY)
    {
        int i, best = 0, tmp, num = 0;

        set_num_npc(0);
        for(i=0;i<sizeof(guards);i++)
          if (!guards[i])
        {
            guards[i] = clone_object(GUARD);
            guards[i]->set_color("red");
            guards[i]->move_living("xxx",TO);
            tmp = guards[i]->query_average_stat();
            if (tmp > best)
              {
              best = tmp;
              num = i;
              }
        }
        for(i=0;i<sizeof(guards);i++)
          if (i != num)
        {
            guards[i]->set_leader(guards[num]);
            guards[num]->team_join(guards[i]);
        }
    }
    else if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) !=
            ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA))
    {
        set_num_npc(3);
    }
    else
        set_num_npc(0);


}

void
create_newport_room()
{
    set_short("Southwest end of the bridge");
    set_long("This is the southwestern end of the very high bridge spanning " +
         "a wild river. @@guards_here@@The road you are standing on " +
         "continues southwest, running along a large forest and eventually " +
         "disappears into some distant hills. " +
         "Looking southeast, you can see a few houses, which are " +
         "known as Newports. Across the bridge to the northeast, the " +
         "plains of Abanasinia begin.\n");

    add_item("road","This is a gravel road, leading northeast and southwest.\n");
    add_item("gravel","It looks very ordinary.\n");
    add_item("bridge","There is a bridge leading northeast from here. The river " +
         "is quite deep below you, and you marvel at the construction " +
         "of the bridge, being so high above the river.\n");
    add_item("river","You cannot see much of the river from here except that it " +
         "seems to be quite fast and a thunderous sound comes up from the gorge.\n");
    add_item(({"houses","cottages","village","newports"}),
         "The few houses making up the village of Newports can be seen to " +
         "the southeast.\n");
    add_item("forest","The forest is quite some distance away, but can be seen " +
         "very well, even from this distance. It lies to the southwest.\n");
    add_item("plains","You can't see anything from here. You have to go across the " +
         "bridge to get to the plains.\n");

    add_exit(TDIR + "road1","southwest",0,3);
    add_exit(NEWPORTS_TO_PLAINS, "northeast","@@check_guards@@");
    reset_room();
}

object *
get_aware_guards()
{
    int i;
    object *pg = ({}); /* guards present in this room who see TP*/
    for(i=0;i<sizeof(guards);i++)
      if (guards[i] && E(guards[i]) == TO && CAN_SEE(guards[i], TP))
    pg += ({ guards[i] });
    return pg;
}

string
guards_here()
{
    int g,i;
    object *pg = get_aware_guards();
    string guard;

    g = sizeof(pg);
    if (g == 1)
        guard = "is a guard";
    else
        guard = "are " + LANG_WNUM(g) + " guards";

    if (g)
      return "There " + guard +  " here, apparently guarding the " +
    "bridge. ";
    return "";
}

int
check_guards()
{
    int g,i;
    object speaker;
    object *pg = get_aware_guards();
    g = sizeof(pg);
    if (!g)
      return 0;
    speaker = pg[0];

    /*check here for something special. Don't allow everyone to pass.*/
    if(TP->query_average_stat() < 22)
      {
      speaker->command("say A little one!");
      speaker->command("giggle evilly");
      speaker->command("emote winks you through.");
      return 0;
      }
    if (TP->query_knight_level() > 1)
      {
      speaker->command("gasp");
      speaker->command("say A knight in this part of the country!");
      /*speaker->command("say You are under arrest! Just 'surrender' and we " +
               "will let you live.");*/
      speaker->block_completely(TP);
      return 1;
      }
    if (TP->query_race_name() == "goblin")
      {
      speaker->command("nod " + TP->query_real_name());
      return 0; /*goblins can pass*/
      }
    if (TP->query_race_name() == "elf")
      {
      speaker->command("shake");
      speaker->command("say No elves are allowed to pass.");
      /*speaker->command("say If you 'surrender', we might let you live " +
               "just a little bit longer!\n");*/
      return 1;
      }
    speaker->command("hmm");
    speaker->command("say What the hell.");
    speaker->command("wink");
    speaker->command("say You may pass.");
    return 0;
}
