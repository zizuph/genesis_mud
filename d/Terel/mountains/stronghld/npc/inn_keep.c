/*  This is an NPC named "Jenna".  She is called by inn.c, and exists
 * to serve and watch over the Inn.  If killed, the Inn is useless.
 *
 * Coded by Vader on 7/2/92
 * Modified by Trofast 11/99, added all the add_ask().
*/
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>
#include "/d/Terel/include/Terel.h"


public string
reply_goblin()
{
  command("smirk");
  command("say Bah! Our boys make short work of em!");
  return "";
}


public string
reply_calathin()
{
  command ("say Calathin! ahh.. Tis a fine city for humans. " +
           "I prefer the great outdoors.");
  return "";
}



public string
reply_last()
{
  command("say Another fine town. Still to civilized for my taste.. ");
  return "";
}

public string
reply_dabaay()
{
  command("say Never been there myself. I hear you can catch passage " +
          "to just about anywhere from Dabaay though. Dont know why " +
          "anyone would want to go anywhere else.");
  command("emote polishes some silverware.");
  return "";
}

public string
reply_dragon()
{
  command("say Dragons! I hear tell of rumours that they exist " +
          "I haven't seen any myself.");
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
  command("say the pub is next store.");
  command("point east");
  return "";
}

public string
reply_smith()
{
  command("say we have a fine smithy. He's downstairs");
  return "";
}


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
        return;

   set_name("Dolath");
   set_race_name("dwarf");
   set_adj("grey-haired");
   set_long("The grey-haired dwarf looks busy managing the " +
      "messhall.\n");

    /* Average stat: 20 
     */
   default_config_npc(90);

    set_all_hitloc_unarmed(15);
   set_gender(0);
   set_chat_time(20);
   add_chat("What can I get you?");
   add_chat("How about some hard tac for the road?");
   add_chat("The venision is fresh! Killed the deer myself " +
      "just this morning.");
   add_chat("Killing this mornings menu is almost as half as fun " +
      "as killing goblins!");
   add_chat("The mountains are kind to use. Provides anything we need.");
   add_act("emote wipes down a table with a steaming hot towel.");
   add_act("emote polishes a piece of silverware.");
   add_ask(({"dragon","dragons"}), reply_dragon, 1);
   add_ask(({"goblins","goblin"}),reply_goblin, 1);
   add_ask(({"calathin","Calathin"}), reply_calathin, 1);
   add_ask(({"last","Last"}), reply_last, 1);
   add_ask(({"dabaay","Dabaay"}), reply_dabaay, 1);
   add_ask(({"pubs","pub"}), reply_pub, 1);
   add_ask(({"smith","smiths"}), reply_smith, 1);

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
