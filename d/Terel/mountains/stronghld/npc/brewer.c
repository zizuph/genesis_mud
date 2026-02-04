/*
 *   Stronghold Brewer
 *   Tomas   -- Jan 2000
 */

#include "/d/Terel/include/Terel.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

inherit STDMONSTER;

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
        return;

    set_name("Tarin");
    set_race_name("dwarf");
    set_adj(({"scarred","one-eyed"}));
    set_title("Master Brewer");
   set_long("The dwarf looks adept at serving drinks. His face " +
      "is scarred from his hairline, through his right eye down " +
      "to his chin.\n");

   default_config_npc(70);
   set_skill(SS_DEFENCE, 65);
   set_skill(SS_UNARM_COMBAT, 60);
   set_skill(SS_PARRY, 55);
   set_hp(5500);

   enable_intro();
   set_all_hitloc_unarmed(15);
   
   set_chat_time(10);
   add_chat("Can I get you something?");  
   add_chat("How about a shot of refreshing Dwarven Spirits!");
   add_chat("You look like you could use a mug of my golden stout! " +
       "guaranteed to put hair on your chest!");
   add_chat("I'm a master at my craft.");
   add_chat("Brewing is an art, but for me its a labor of love.");
   add_chat("Are you here to drink? If not, dont waste my time!");
   add_act("rubs the scar on his face.");
   add_chat("I got me beauty mark in the last attack! You shoulda " +
      "seen the goblin afterwards.");
   
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
