/*
 * The king of Telseron, 
 * also the questmaster
 * Coded by Finwe
 * March 1997
 */
 
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc.c";
 
#include "/d/Emerald/defs.h"
 
// void get_help(object enemy);
 
int alarmid, p;
 
void
create_emerald_monster()
{
    set_name("velandel");
    add_name( ({"king", }) );
//    set_title("the King of Telseron ");
    add_adj( ({"proud", "dignified"}) );
    set_race_name("elf");
    set_long("Standing before you is the proud and dignified " +
        "king of Telseron. He directs the affairs of the city " +
        "with the kindness borne only by those of great age and " +
        "wisdom. Nevertheless, he looks ageless and strikingly " +
        "fair as do all his race. However, he is someone to be " +
        "reckoned with as the king looks powerful.\n");
   
    set_stats( ({ 100, 130, 100, 100, 100, 100 }) );
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 80);
    set_skill(SS_WEP_SWORD, 70 + random(25));
    set_skill(SS_AWARENESS, 45 + random(10));
    set_alignment(700 + random(100));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_S_EXTRA_SHORT, ", the King of Telseron");
   
    set_cchat_time(6);  
    add_cchat("Thou fool! Guards!!");
   
    set_act_time(10);
    add_chat("Perhaps you can assist me?");
    add_chat("Times have become have been very good for us.");.
    add_chat("If you're up to it, I may be able to use your services.");
    add_chat("The Queen is the most beautiful lady in the world.");
    add_chat("Welcome to my kingdom.");
    add_act("smile happily");
//    add_act("");
 
/*   add_equipment( ({ "/d/Emerald/telberin/castle/wep/kingscepter",
                        "/d/Emerald/telberin/castle/arm/kingcrown",
                       "/d/Emerald/telberin/castle/arm/kingrobe"}) );
   
    set_default_answer("I'm not really interested. Ask the Queen.\n");
    trig_new("%w 'bows' %s", "react_bow");
*/
}
