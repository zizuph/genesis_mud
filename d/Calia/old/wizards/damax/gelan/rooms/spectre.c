

inherit "/std/monster";            /* I'm not sure which of these are  */
inherit "/std/act/action";         /* necessary, but I've used them    */
inherit "/std/act/chat";           /* all.  I like to think of it as   */  
#include "/sys/stdproperties.h"    /* Tulixian logic.  After all, this */
#include "/sys/ss_types.h"         /* is his frame...thanks, big T.    */
#include "/sys/macros.h"



void equip_me()
{
    object sword, armour;
    seteuid(getuid(this_object()));
    sword=clone_object("/d/Dville/damax/ssword");
    sword->move(this_object());
    command("wield sword");
    armour=clone_object("/d/Dville/damax/armour");
    armour->move(this_object());
    command("wear armour");
}

void create_monster()
{
if (!IS_CLONE)
    return;
    set_name("the spectre");
    set_pname("spectres");
    set_race_name("spectre");
    set_short("shimmering spectre");
    set_pshort("shimmering spectres");
    set_adj(({"shimmering","ghostly"}));
    set_long("This is the spectre of a fallen Calian warrior.\n"+ 
        "He has failed at some task, and is now cursed to haunt this world forever.  \n");  
    set_random_move(30);
    
    add_prop(CONT_I_WEIGHT,10000);
    add_prop(CONT_I_HEIGHT,2100); 

    set_gender(0);  /* male=0, female=1, other=2 */

    set_stats(({ 80, 95, 90, 75, 75, 99 })); 
    set_hp(25000); /* Fully healed */
    set_alignment(400);
    set_aggressive(0);

    /* Set the all important skills. */
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    
    set_chat_time(5);
    add_chat("I am doomed to haunt this graveyard forever..."); 
    add_chat("My life was taken by an evil sorcerer...");
    add_chat("I can never rest until I know the name of he who killed me...");
    add_chat("I would welcome death...but we shall never meet.");
    add_chat("The gravedigger knows something...");
    add_chat("I can be freed only by the sorcerer's wand..."); 

    set_cchat_time(3);  
    add_cchat("Your soul is doomed forever..."); 
    add_cchat("The gravedigger will be digging one more grave this night...");
    add_cchat("It's no use...this spirit form will only rise again...");
    add_cchat("Your spirit will soon join me here!");

    set_act_time(10);
    add_act("moan");    
    add_act("scream");
    add_act("sigh");

    call_out("equip_me", 1); 
}
