#include "/d/Ansalon/goodlund/nethosak/city/local.h" 
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_IN;

int fetch_summoned = 0; 
object fetch;

int check_fetch();
void 
reset_mithas_room()
{
   if(fetch_summoned)
   {
      fetch_summoned = 0;
   }

}

public void
set_fetch(int value)
{
    fetch_summoned = value;
}

void
create_mithas_room()
{
   set_short("beneath the ruins of Winston's Tower, before a dark pool");
   set_long("@@long_descr"); 

   add_item(({"ruins","abandoned ruins","tower","winston's tower","great tower",
         "lighthouse","beacon","holy beacon","ruins"}),
     "Once a holy beacon for travellers, Winston's Tower is now abandoned, " +
     "home only to the darkness.\n");
   add_item(({"chamber","large chamber","dark chamber"}),
     "This chamber is empty except for a circular pool in the centre of the room. " +
     "An eerie presence eminates from the pool... you feel like you should be " +
     "careful approaching it.\n");
   add_item(({"darkness","ominous darkness"}),
     "Darkness hovers around you in Winston's Tower, seemingly sucking up the " +
     "light around you.\n");
   add_item(({"pool","circular pool","presence","eerie presence"}), "@@look_pool");
   add_item(({"staircase","stone staircase"}),
     "A stone staircase rises up into ominous darkness.\n");

   add_prop(ROOM_S_DARK_LONG,                   
     "Beneath the ruins of a dark tower. It is impossible "+
     "to see anything in the ominous darkness.\n");

   DARK;


   add_exit(BISLAND + "tower01", "up", 0, 1);
/*  This block for the exit was suddenly added by who?
 *  It was abused by players to have smaller players killed
 *  A large player, legend/myth would go and summon the npc
 *  Then use a peace spell or the like to escape the room with the npc still there
 *  The next person to arrive, for example a greenhorn, would have to fight a paralyzing, blocking myth to escape.
 *  Not quite fair. Since we received a complaint from the mortals, of someone who died.
 *  I (Navarre), decided to change it back to the old exit without the block, Mortis agreed. And it was reported to the Lord of Krynn.
 
    add_exit(BISLAND + "tower01", "up", check_fetch, 1);
*/
   reset_mithas_room();
}

int
check_fetch()
{
   object ob;
    if (TP->query_wiz_level())
    {
        return 0;
    }

    if (ob = present("_fetch",E(TP)) && TP->query_attack()) {
        if (!ob->query_prop(LIVE_I_STUNNED)) {
        write("The reflection moves to block your exit.\n");
        return 1;
        }
    }
}

string
look_pool()
{
   string *adj;
   int stat0, stat1, stat2, stat3, stat4, stat5;   

   stat0 = TP->query_stat(0) + random(20);
   stat1 = TP->query_stat(1) + random(20);
   stat2 = TP->query_stat(2) + random(20);
   stat3 = TP->query_stat(3) + random(20);
   stat4 = TP->query_stat(4) + random(20);
   stat5 = TP->query_stat(5) + random(20);

   adj = TP->query_adj(1);

   if(fetch_summoned)
   {
      return "A dark pool of water. To your surprise and horror, when you look into " +
        "it you see nothing, not even your reflection!\n";
   }

   write("You look down into the dark pool of water, and see your reflection... " +
        "a haggard, and pale image of you! Your reflection meets your eyes and " +
        "scowls, leaping out of the pool at you!\n");
   say(QCTNAME(TP) + " looks into the pool for a moment, meeting the gaze of " +
        HIS(TP)+ " reflection. To your surprise, " +HIS(TP)+ " reflection scowls " +
        "at " + HIM(TP)+ ", and then leaps out of the pool!\n");
   
   fetch = clone_object(BNPC + "fetch");
   fetch->set_adj(adj[0]);
   fetch->add_adj(adj[1]);
   fetch->set_race_name(TP->query_race_name());
   fetch->set_gender(TP->query_gender());
    fetch->set_long(TP->long(fetch));
   fetch->set_name(TP->query_race_name());
   fetch->set_stats(({stat0,stat1,stat2,stat3,stat4,stat5}));
   fetch->heal_hp(10000);
   fetch->arm_me();
   fetch->move(TO);
   fetch->command("kill " +TP->query_name());

   fetch_summoned = 1;
   return "";
}
 


string
long_descr()
{ 
   return "You are standing beneath the ruins of Winston's Tower in a large, dark " +
      "chamber. The room is empty, except for a circular pool in the centre of the "+
      "room.\n";
}
