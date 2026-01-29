/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";     
inherit "/std/act/seqaction";
inherit "/std/act/domove";     
     
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

#define ARM_DIR  SORGUMDIR + "armour/"
#define WEP_DIR  SORGUMDIR + "weapon/"

/*
 * Global variables
 */

string *chats = ({
    "I'm bad to the bone!",
    "It's all diet.",
    "Hey, just show the whole technique.",
    "I'm doing you all a favor just by training with you"
});

string *cchats = ({
    "I'm bad to the bone.\n"
});

     
create_monster()
{
    int i;
    
    set_name("Berry");
    add_name("barry");
    set_short("Barry Meklir");
    set_long("A dimunitive human with a bad attitude.  He's got a " +
	     "goatee because he thinks it makes him look tough.\n");

    set_race_name("human");
    set_gender(0);

    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(20, 20);

    set_whimpy(63);
    set_act_time(7);
    set_chat_time(1);
    set_cchat_time(1);

    for (i = 0; i < sizeof(chats); i++) {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }

    for (i = 0; i < sizeof(cchats); i++) {
	add_cchat(cchats[i]);
    }

    set_spell_prop(TO);

/*     trig_new("%w 'falls' 'down' %s", "react_laugh");
     trig_new("%w 'growls.\n' %s", "react_growl"); */
     trig_new("%s 'says:' %s", "react_say");
/*     trig_new("%w 'slaps' %s", "react_slap");
     trig_new("%w 'giggles' %s", "react_giggle");
     trig_new("%w 'burps' %s", "react_burp");
     trig_new("%w 'smiles' %s", "react_smile");
     trig_new("%w 'smirks.\n' %s", "react_smirk");
     trig_new("%w 'cackles'  %s", "react_cackle");    
     trig_new("%w 'grins' %s", "react_grin");    
     trig_new("%w 'lets' 'off' 'a' 'real' %s", "react_fart");    
   trig_new("%w 'throws' %w 'head' 'back' 'and' 'cackles' 'with' 'glee!\n' %s",
	    "react_cackle");
    trig_new("%w 'drops' %s", "react_drop");
    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
    trig_new("%s 'died.\n' %s","react_death");     */

    
}

int
react_say(string who, string str)
{
   if (who) {
       who = lower_case(who);
      if (str == "twelve dollars\n" || str == "12 dollars\n")
	   set_alarmv(2.0, -1.0, "return_bill", ({who}));
      return 1;
   }
}

void
return_bill(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
         command("say AGAIN?!?.");
   }
}


