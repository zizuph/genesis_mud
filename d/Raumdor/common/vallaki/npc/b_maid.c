/* Sarr */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

void
create_monster()
{
    ::create_monster();
    set_name("steffy");
    add_name("barmaid");
    set_adj("buxom");
    set_race_name("human");
    set_gender(1);
   set_long("This cute looking girl walks lightfooted from table to "+
      "table, serving food. She has short curly hair and "+
      "green eyes that easily warns off any blistered "+
       "guest.\n");
    set_stats(({60,80,60,70,70,70}));
    set_exp_factor(50);
    set_title("the Barmaid");
    set_act_time(5);
    add_act("say Hi there! What can I get you, hon?");
   add_act("emote walks from table to table, making sure the "+
      "customers have what they need.");
     add_act("emote cleans a glass with swift motions.");
     add_act("emote walks to a cornertable to serve some hot food.");
    add_act("say Wha'cha need hon?");
    add_act("emote sways her round behind quite sexily as she wiggles by.");
    add_act("emote hops between tables, making her ample chest bounce quite freely.");
    set_cact_time(3);
    add_cact("emote screams: Help! Help! Guards im being attacked!\n");
    add_cact("scream");
    add_cact("shout Someone save me!!");
    
    equip(({
        DRAKMERE_ARM_DIR + "blouse",
        DRAKMERE_ARM_DIR + "skirt",
    }));
}

void
do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,1);
    ::do_die(who);
}
