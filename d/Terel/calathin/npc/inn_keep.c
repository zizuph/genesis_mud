/*  This is an NPC named "Jenna".  She is called by inn.c, and exists
 * to serve and watch over the Inn.  If killed, the Inn is useless.
 *
 * Coded by Vader on 7/2/92
 * Modified by Trofast 11/99, added all the add_ask().
 *
 * Added set_act_time() as actions were too frequent/spammy.
 * Increased set_chat_time() just bit so she isn't so chatty.
 * Updates by Shanoga, 11/10/18
 *
*/
inherit "/std/monster";
inherit "/d/Terel/include/log_asks";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"

#define HUNTING_TREVIN "_i_hunting_trevin"
#define TALKED_TO_INNKEEP "_i_talked_innkeep"

public string
reply_goblin()
{
  command("tremble fear");
  command("say Where? Where?");
  return "";
}

public string
reply_maskyr()
{
  command("say I don't know anything about that.");
  command("frown");
 return "";
}

public string
reply_calathin()
{
  command ("say Oh isn't it nice here? I never want to move away, I "+
           "can't imagine anyplace better than Calathin.");
  return "";
}

public string
reply_silver()
{
  command ("say I'm not allowed to go there anymore, since I got "+
           "so lost there that time.  I go up to the stable, no farther.");
  return "";
}

public string
reply_enchanted()
{
  command("say It's far to the south, I've been through it before on "+
          "the way to Dabaay.");
  command("say I saw a dryad there.");
  command("nod sol");
  return "";
}

public string
reply_last()
{
  command("say Lots of people that stop in here came through Last. ");
  command("say We go up there sometimes to get shipments of food from "+
          "Calia.");

  return "";
}

public string
reply_dabaay()
{
  command("say It's far to the south, where all the boats go to faraway "+
          "lands.");
  command("whistle aimless");
  return "";
}

public string
reply_legion()
{
    return "";
}

public string
reply_dragon()
{
  command("say Dragons are silly, I'm not afraid of them anymore. "+
          "It really is amazing how much treasure one of them can "+
          "hoard though.");
  return "";
}

public string
reply_hoard()
{
  command("say I've heard that the quickest way to a dragon's heart "+
          "is through rare metals and fine gems.");
  return "";
}


public string
reply_horse()
{
  command("clap");
  command("say Oh, isnt Jonas the dreamiest? He promised to take "+
                 "me for a ride sometime on one of his horses!");
  command("ponder Jenna Blackmun. . .");
  return "";
}

public string
reply_inn()
{
  return "";
}

public string
reply_pub()
{
  return "";
}

public string
reply_smith()
{
  return "";
}

public string
reply_ribos()
{
  return "";
}

public string
reply_bags()
{
  return "";
}

public string
reply_sea()
{
  return "";
}

public string
reply_mansion()
{
  return "";
}

public string
reply_gypsy()
{
  return "";
}

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
          command("say Yeah, the adventurer said he was searching for "+
                         "a guy.");
          command("say Kept claiming hoarding was the key.");
          TP->add_prop(TALKED_TO_INNKEEP,1);
          return "";
    }
    if(TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
    {
      command("say I have heard some disturbing rumours involving "+
              "dragons and this character.");
    }
    return "";
}


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
        return;

   set_name("jenna");
   set_race_name("human");
   set_adj("long-haired");
   set_long("She is a very outgoing girl, with VERY long hair.\n");

    /* Average stat: 20 
     */
   default_config_npc(30);

    set_all_hitloc_unarmed(15);
   set_gender(1);
   set_chat_time(2);
   add_chat("My beaver stew is from an ancient recipe handed down "
    + "from my mother.");
   add_chat("How would you like some jerky for the road?");
   set_act_time(5);
   add_act("emote hums absentmindely as she works.");
   add_ask(({"adventurer","assassin","tall wiry male human"}), reply_assassin, 1);
   add_ask(({"dragon","dragons"}), reply_dragon, 1);
   add_ask(({"hoard","hoarding","treasure"}), reply_hoard, 1);
   add_ask(({"horse","horses",}), reply_horse, 1);
   add_ask(({"goblins","goblin"}),reply_goblin, 1);
   add_ask(({"calathin","Calathin"}), reply_calathin, 1);
   add_ask(({"silver forest","Silver forest","Silver Forest"}), 
           reply_silver,1);    
   add_ask(({"enchanted forest","Enchanted forest","Enchanted Forest"}),
           reply_enchanted, 1);
   add_ask(({"maskyr keep", "Maskyr keep", "Maskyr Keep"}), reply_maskyr, 1);
   add_ask(({"last","Last"}), reply_last, 1);
   add_ask(({"dabaay","Dabaay"}), reply_dabaay, 1);
   add_ask(({"legion","Legion"}), reply_legion, 1);
   add_ask(({"inn", "Inn", "Silver Tree Inn", "silver tree inn"}),
           reply_inn,1);  
   add_ask(({"pubs","pub"}), reply_pub, 1);
   add_ask(({"smith","smiths"}), reply_smith, 1);
   add_ask(({"Ribos", "ribos"}), reply_ribos, 1);
   add_ask(({"bags","pouch","pouches", "bag", "sack", "sacks", "backpacks",
               "backpack"}), reply_bags, 1);
   add_ask(({"sea","Sea","sea of terel","Sea of Terel", "sea of Terel"}),
           reply_sea, 1);
   add_ask(({"mansion","Mansion","Avenchir","avenchir"}), reply_mansion, 1);
   add_ask(({"gypsy","gypsies","gypsy camp","camp"}), reply_gypsy, 1);


}
/*
 * Find some player somewhere and go there
 */
find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
        return 0;

    move_living("X",environment(ob));
    return 0;
}
