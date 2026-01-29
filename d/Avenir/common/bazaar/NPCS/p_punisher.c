// creator(s):  Lilith  Sep 97
// last update: 
// purpose:     Patrolling bazaar/admin area
// note:        Modified from: The Punisher (/bazaar/NPCS/punisher.c)
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/spy_npc";
inherit "/d/Avenir/inherit/helper";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/relation.h"

#define WEP1 BAZAAR + "Obj/wield/bsword"
#define WEP2 BAZAAR + "Obj/wield/bmace"

string *randadj;
string *randatt;
string att;

object pouch;
void set_attribute(string str) {    att = str;    }
string my_long();
int start_travelling();

void
create_monster()
{
    int i;

    /*If not a clone, ignore the rest */
    if (!IS_CLONE)
        return;    

    /* Make sure sybarite stuff is initialized */
    ::create_sybarite();

    randadj = ({"massive","hairless","fierce","ferocious","terrifying",
                "menacing","brutal-looking","enormous","titanic"});
    randatt = ({"ram's horns curling down over his ears", 
                "a pig's snout for a nose", "a huge, bulbous nose",
                "eyes large as apples with very long lashes", 
                "absurdly small ears tipped with white fuzz",
                "a skeletal pincer where his right hand should be",
                "hooves instead of feet", "backward-bending knees",
                "one arm that is longer than the other",
                "delicate, long-fingered hands" }); 
               
    set_name("punisher");
    add_name(({"troloby", "monster"}));
    set_race_name("troloby");
    set_adj(randadj[random(sizeof(randadj))]);
    set_attribute(randatt[random(sizeof(randatt))]);
    set_long(my_long);
    set_pick_up(1);
    set_restrain_path("/d/Avenir/common/");

    for (i = 0; i < 6; i++)
    set_base_stat(i, 120 + random(30)); 
 
    set_alignment(0);
    set_knight_prestige(750);

    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 50 + random(15));
    set_skill(SS_PARRY, 80);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS, 50);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    add_spy_ask();

    NEVERKNOWN;
    MAKE_SYBARITE; 

    set_cchat_time(5);
      add_cchat("I'll take your corpse to the butcher and eat "+
          "you for my supper.");
      add_cchat("Die. You die now!");

    set_act_time(8);
      add_act("slaugh");
      add_act("hmm");
      add_act("flex");
      add_act("fart");
      add_act("sigh slow");
      add_act("grip mace");
      add_act("swing sword");
      add_act("emote grunts at you.");
      add_act("emote looks around suspiciously.");
      add_act("emote lowers his head for a moment.");

    seq_reset();
    seq_new ("travel", 1); // never stop
    start_travelling();
}

string
my_long()
{
    string str;
    str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";
    str += "An unnatural creature spawned by the breeding "+
           "experiments of the Shadow elves, "+
           "his skin is shiny pink, and so hairless and smooth it looks wet.\n"+
           "As broad as three humans and half again as tall, this fellow "+
           "has "+ att +".\n";

    if (IS_SYBARITE(this_player()) >= SYB_LAY)
    {
        str += "He appears to be very observant and might have "+
               "something to report if you ask nicely.\n";
    }

    return str;
}

void
equip_me()
{
    seteuid(getuid());
    clone_object(WEP1)->move(this_object());
    clone_object(WEP2)->move(this_object());
    command("wield all");

    pouch = clone_object(BAZAAR+"Obj/misc/gem_pouch");
    pouch->move( this_object() );
    pouch->fill_pouch();
    clone_object(BAZAAR +"Obj/worn/pboots")->move(this_object());
    clone_object(BAZAAR +"Obj/worn/harness")->move(this_object());
    clone_object(BAZAAR +"Obj/worn/loincloth")->move(this_object());    
    clone_object(HOLM + "obj/cesti")->move(this_object());
    command("wear all");
//    this_object()->add_cmdsoul("/d/Avenir/common/obj/npc_soul");
//    this_object()->update_hooks();
}

/* 
 * set_helper() is from the Avenir/inherit/helper
 * It does some nifty things I want done here ;)
 */
void
set_helper()
{
    string *actions = ({ "sigh joy",
                         "say It sounds like there's trouble next door!",
                         "say Ah-hah!" });

    set_helper_friends( ({ }) );
}

int
special_attack(object victim)
{
    switch (random(10))
    {
        case 0: command("punch");
            return 1;
        case 1: command("skick");
            return 1;
        case 2: command("heal me");
            return 0;        
        case 3: command("neck");
            return 1;
        case 4: command("pommel");
            return 1;
        case 5: command("heal me");
            return 0;
        case 6: command("skick");
            return 1;
        case 7: command("pommel");
            return 1;
        case 8: command("heal me");
            return 0;
        case 9: command("cure me");
            return 0;
        default: 
    }
    return 0;
}

int
start_travelling()
{
    seq_addfirst ("travel",
       ({ "frown", "up", "whisper to punisher Hiya Big Boy!",
          "shake punisher", "d", "e", "e", "e", "e", "n",
          "emote looks around.", "nod", "s", "s", "s", "s",
          "ask punisher How goes?", "smile .", "n", "n", "n",
          "w", "w", "w", "w", "@@start_travelling@@"}) );
  return 0;
}

string race_sound() {   return "booms";   }

