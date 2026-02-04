/*  This is an NPC named "Micah".  He is the bartender at the pub.
 *  If he is killed, noone can do business at the pub.
 *
 *  Coded by Vader on 6/29/92
 *
 */
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

    set_name("micah");
    set_race_name("bartender");
    set_adj("energetic");
   set_long("He is the pubs bartender.  He is known and "
    + "loved by everyone in town.\n");

     /* Average stat: 70
     */
    default_config_npc(70);

    /* But we want it to have more hitpoints
     */
   set_skill(SS_DEFENCE, 65);
   set_skill(SS_UNARM_COMBAT, 60);
   set_skill(SS_PARRY, 55);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

     set_chat_time(5);
   add_chat("Can I get you something?");  
   add_chat("How about some Silver beer.  Best recipe around!");
   add_chat("Well, Well!  You look like you could use a drink.");
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
