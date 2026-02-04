/*
 * delsanora.c 
 *
 *  This is an NPC named "Delsanora".  She is called by shop.c as a        
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 *  Coded by Shinto 040299
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

#include <ss_types.h>
#include <money.h>

void add_introduced(string swho);



create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
     return;

    set_name("delsanora");
    set_living_name("delsanora");
    set_race_name("human");
    set_title("Calirian, Innkeeper of the Silver Tree Inn");
    set_adj("attractive");
    set_adj("black-haired");
    set_long("This "+short()+" runs this establishment. She will take care of"+
             " your needs as far as lodging is concerned.\n");
    set_gender(1);

     /* Average stat: 80
     */
     default_config_npc(80);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

    set_chat_time(15);
    add_chat("Welcome to the Silver Tree Inn");
    add_chat("I can provide you with a comfortable room "+
                   " and a good nights rest.");
    add_chat("If you have horses, they can be stabled with "+
                   "Jonas. His stable is on the north side of town.");
    set_act_time(3);
    add_act("smile all");
    add_act("emote straightens up the room.");
    add_act("emote brushes a stray hair from her face.");
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}

