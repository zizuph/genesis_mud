/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_OUT;

#define WOHS_NPC "/d/Krynn/guilds/wohs/test/living/"
#define ENGAGED_ERGOTHIANS "_wohs_test_engaged_city_siegers"
#define DMG_TAKEN      "_wohs_test_damage_taken"

object p1, p2, s1, s2, c1, c2, c3, c4, c5, serl;
int health;

void
reset_tower_room()
{
   if(!objectp(p1))
   {
      p1 = clone_object(WOHS_NPC + "presbyter");
      p1->arm_me();
      p1->move(TO);
   }
   if(!objectp(p2))
   {
      p2 = clone_object(WOHS_NPC + "presbyter");
      p2->arm_me();
      p2->move(TO);
   }
   if(!objectp(s1))
   {
      s1 = clone_object(WOHS_NPC + "scout");
      s1->arm_me();
      s1->move(TO);
   }
   if(!objectp(s2))
   {
      s2 = clone_object(WOHS_NPC + "scout");
      s2->arm_me();
      s2->move(TO);
   }
   if(!objectp(c1))
   {
      c1 = clone_object(WOHS_NPC + "cavalier");
      c1->arm_me();
      c1->move(TO);
   }
   if(!objectp(c2))
   {
      c2 = clone_object(WOHS_NPC + "cavalier");
      c2->arm_me();
      c2->move(TO);
   }
   if(!objectp(c3))
   {
      c3 = clone_object(WOHS_NPC + "cavalier");
      c3->arm_me();
      c3->move(TO);
   }
   if(!objectp(c4))
   {
      c4 = clone_object(WOHS_NPC + "cavalier");
      c4->arm_me();
      c4->move(TO);
   }
   if(!objectp(c5))
   {
      c5 = clone_object(WOHS_NPC + "cavalier");
      c5->arm_me();
      c5->move(TO);
   }
   if(!objectp(serl))
   {
      serl = clone_object(WOHS_NPC + "duke");
      serl->arm_me();
      serl->move(TO);
      serl->set_aggressive(0);
   }

}

void
create_tower_room()
{
   set_short("on the city streets of Daltigoth, before a grove of " +
       "tall pine trees");
   set_long("You find yourself standing on a cobbled street of a " +
       "great city, before the entry to a grove of tall pine trees. " +
       "Surrounding the entry to the grove is a large force of " +
       "Ergothian infantry, calvary, and presbyters blocking anyone " +
       "from leaving the grove into the city.\n");

   add_item(({"grove","grove of tall pine trees","peaceful grove",
       "forest","entry"}), "To your west is the entry to a grove of " +
       "tall pine trees that sway serenely to a gentle highland " +
       "breeze, almost hypnotically.\n");

   add_item(({"pine trees","trees","tree","pine tree","trunks"}),
       "Tall pine trees rise from the grove to your west, swaying " +
       "serenely to a gentle highland breeze, almost hypnotically. " +
       "You feel a sense of sleepiness pass over you as you watch " +
       "the trees move, and combined with the intoxicating scent of " +
       "pine you feel your eyelids grow heavy.\n");

   add_item(({"city","great city","daltigoth","city streets","streets",
       "houses", "shops","exits"}), "You stand on the streets of a " +
       "great city, the imperial capital of Ergoth, Daltigoth! In your " +
       "time Daltigoth is little more than a haunted ruin occupied " +
       "by giants, ogres and trolls... but the city you see is in its " +
       "prime - a thriving metropolis of markets, shops and houses " +
       "built around a grand imperial palace to your east. Blocking the " +
       "exits around you is a force of Ergothian infantry, cavalry and " +
       "presbyters.\n");

   add_item(({"ergothian infantry","infantry","cavalry","presbyters",
       "army","force"}), "At the entry of the grove to your east you " +
       "can see a large force of Ergothian infantry blockading the " +
       "exit, while cavalry seem to be preparing for an assault. " +
       "Clerical presbyters provide blessings to the soldiers, giving " +
       "you the impression that the military force will be acting upon " +
       "something soon. You notice the commander of the forces near " +
       "the entry of the glade kneeling beside something.\n");

   add_item(({"commander","duke","praetor-general","praetor general",
       "general"}), "Kneeling near the entry of the grove is the " +
       "commander of the army. Wearing the ancient trappings of an " +
       "Ergothian Praetor-General, this commander is one of very high " +
       "military standing. It looks like he is kneeling beside a " +
       "small tree sapling of some kind.\n");

   add_item(({"sapling","tree sapling","small tree sapling",
       "small sapling", "unnatural sapling", "black pine",
       "black needles","black bark","sticky black sap","black sap","sap"}),
       "Behind a wall of guards you notice the commander of the " +
       "military forces kneeling beside a small tree sapling. Strange " +
       "that a tree sapling would be growing in the middle of a city " +
       "street, and stranger that it had the attention of such a large " +
       "military force. Looking at it more closely you realise that " +
       "this sapling is twisting and writhing in rapid magical growth.\n");

   add_item(({"imperial palace","palace","minaret","minarets"}),
       "To your east towers a great imperial palace, the seat of power " +
       "of the emperor of Ergoth.\n");

   OUTSIDE;

   add_exit(WOHS_TEST + "room/kadothan_grove3", "west", "@@leave_west");

   reset_tower_room();

}

int
leave_west()
{

   if(TP->query_wiz_level())
      return 0;

   if(health > TP->query_hp())
   {
      int damage = health - TP->query_hp(); 
      int dmg_taken = TP->query_prop(DMG_TAKEN) + damage; 
      TP->add_prop(DMG_TAKEN, dmg_taken);
      WOHS_MANAGER->add_wohs_test_props(TP, DMG_TAKEN, dmg_taken);    
   }   

   return 0;
}

void
attack_wizard(object player)
{
    serl->command("shout A wizard leaves the grove! Don't let " +
        HIM(player)+ " escape!");
    serl->command("kill " +player->query_real_name());
    player->add_prop(ENGAGED_ERGOTHIANS, 1);
    WOHS_MANAGER->add_wohs_test_props(player, ENGAGED_ERGOTHIANS, 1);
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob) && !(ob->query_wiz_level()))
    {
       int stat = ob->query_average_stat();
       p1->set_stats(({stat, stat, stat, stat, stat, stat}));
       p1->heal_hp(10000);
       p2->set_stats(({stat, stat, stat, stat, stat, stat}));
       p2->heal_hp(10000);
       s1->set_stats(({stat, stat, stat, stat, stat, stat}));
       s1->heal_hp(10000);
       s2->set_stats(({stat, stat, stat, stat, stat, stat}));
       s2->heal_hp(10000);
       c1->set_stats(({stat, stat, stat, stat, stat, stat}));
       c1->heal_hp(10000);
       c2->set_stats(({stat, stat, stat, stat, stat, stat}));
       c2->heal_hp(10000);
       c3->set_stats(({stat, stat, stat, stat, stat, stat}));
       c3->heal_hp(10000);
       c4->set_stats(({stat, stat, stat, stat, stat, stat}));
       c4->heal_hp(10000);
       c5->set_stats(({stat, stat, stat, stat, stat, stat}));
       c5->heal_hp(10000);
       serl->set_stats(({stat + 30, stat + 30, stat + 30, 
           stat, stat, stat}));
       serl->heal_hp(10000);

       health = ob->query_hp();

       if(CAN_SEE(serl, ob))
       {
           set_alarm(0.5,0.0, &attack_wizard(ob));
       }
    }

}

