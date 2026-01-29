/*
* Palmer added intro when introed to. Jan 2003
*/

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "../huntclub.h"

//   Protoypes
int return_sigh(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("rumbald");
    set_title("Master Hunter");
    set_race_name("human");
    set_adj(({"tall","lanky"}));
    set_long("He looks like your typical hunter type. His skin is weathered " +
        "from many years out in the wild. There are deep lines in his " +
        "forehead and around his eyes. His long, brown hair is braided " +
        "into a single tail which hangs acrossed his back. His brown " +
        "beard shows some gray and is bushy. Nonetheless, he appears " +
        "to be friendly enough.\n");
    set_stats(({75,80,75,70,70,95}));
    MAKE_MONEY;
    set_alignment(50);

    set_skill(SS_WEP_POLEARM,75);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_HUNTING,100);
    set_skill(SS_ANI_HANDL,75);
    set_skill(SS_LOC_SENSE,80);
    set_skill(SS_TRACKING,75);
    set_skill(SS_WEP_MISSILE,100);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 175);
    set_gender(G_MALE);
    
    add_ask(({"task","help","quest","job"}),VBFC("ask_quest"));
    
    add_ask(({"sell"}),VBFC("ask_sell"));
    
    add_ask(({"sharpen","fix"}), VBFC("ask_sharpen"));
    
    add_ask(({"skills","improve","learn","teach"}), VBFC("ask_skills"));
    
    add_ask(({"hunters","huntress","hunters and huntress club","club","join"}), VBFC("ask_hunters"));
    
    add_ask(({"tallystick","stick","tally stick"}), VBFC("ask_tallystick"));
    
   // https://lingojam.com/RedneckTranslator

   set_act_time(600);
   add_act("emote rubs down his hornbeam bow n' strings with a stick of beeswax.");
   add_act("emote pulls out a bowstring from a leather pouch, and rubs it against " +
     "some beeswax.");
   add_act("emote starts sharpening a knife with a smooth flat stone.");
   add_act("Stokes the fire with one of the long white objects from the basket.");
   add_act("emote mouth moves slightly, as he counts the notches on his tallystick.");
      
   set_chat_time(30);
   add_cact(({"Hunting ain't ayy spawt, it's ayy way av survival. Damn " +
        "townies! They think thay'r food comes frawum ayy can!"}));
   add_chat("The faahyr could use some stoking, don't ya know?");
   add_chat("I can sharpen yer weppon fer you, ifn you need it.");
   add_chat("When tracking awful small game, make sure y'all're up waand.");
   add_chat("Dem trolls seem busy, scaring off all the darn good game.");
   add_chat("It's getting colduurr out dere.");
   add_chat("What's yer count on conies these days?");
   add_chat("I git mah shafts from those elves up in Rivendell these days.");
   add_chat("Ay've been way up in those there hills. Nuttin' but goblins though!"); 
   add_chat("Rub down y'all's bow with beeswax often, otherwise it will get " +
        "brittle n' break on ya, when y'all least expec it."); 
   add_chat("Don't leave yuurr bow out in the sunlaheet faw any longuurr " +
        "then y'all have ta.");
   add_chat("I can larn you stuff, jest ast.");
   
   set_chat_time(10);
   add_chat("So, have you come to larn cummenced me?");
   add_chat("I have equipment to sell, read the signs and I'll sell it to you.");
   

    set_act_time(20);
    add_act("emote stares at the firelight a while.");
      
    set_cact_time(5);
    add_cact("slap all");
    add_cact("emote screams: Dadgum it all YEE DAWGIES! Ifn dat doesn' t knock " +
    	"some sense into you, this will YEE DAWGIES!");


// Arm the npc
    equip(({HUNTCLUB_DIR + "wep/" + "hornbeam_bow.c",
        HUNTCLUB_DIR     + "wep/" + "longknife.c",
        HUNTCLUB_DIR     + "wep/" + "arrows.c",
        HUNTCLUB_DIR     + "obj/" + "bowstring.c",
        HUNTCLUB_DIR     + "arm/" + "leather.c",
        HUNTCLUB_DIR     + "arm/" + "widehat.c",
        HUNTCLUB_DIR     + "arm/" + "furcoat.c",
        HUNTCLUB_DIR     + "arm/" + "boots.c"}));
    command("lean by the fire");        

    /*Triggers*/
//    set_alarm(0.5,0.0,"arm_me");

}

string 
ask_quest()
{
	command("say I don't know whut yer talkin' about. See me later, who knows. I might " +
    "need somethin done one of these days.");
    return "";
}

string
ask_sell()
{
	command("say I' m sellin ifn you're buyin!");
	return "";
}

string
ask_skills()
{
	command("say SSo, you' ve come to larn cummenced me? Well, I can larn you how to handle " +
    "critters, improov yer awareness, know which way you' re goin, track animals, " +
    "and how to hunt.\n");
    return "";
}

string
ask_sharpen()
{
   command("say I can sharpen yer weppon fer you, ifn you need it. " +
   "Jest type 'sharpen <weapon>\n");
   return "";
}

string
ask_hunters()
{
	command("say You've found it! See the wicker basket on the table. Its got a sign on it " +
    "with real letters n' everthing!");
    return "";
}

string
ask_tallystick()
{
	command("say It's purty simple, every time you kill somethin, a scratch er notayshun " +
    "appears on th' stick. Jest 'tally' or 'tally <race name>' to count em up!");
    return "";
}
    


init_living() {
   ::init_living();
   if (interactive(this_player()))
      {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}
void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Greetins and Welcum to th' Hunter/huntress Club " + 
   	ob->query_nonmet_name() + "!");
}
my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("jaunty");
   return("Mah name is Rumbald YEE DAWGIES! I' m a hunter in these parts. " +
   "Have a seat, res yer weary bones!\n");
}
int
return_smile(string who) {
   object ob;
   
   ob = present(who, environment());
   if (!ob) return 0;
   switch (random(4)) {
      case 0: command("smile"); return 1;
      case 1: command("smile " + who); return 1;
      case 2: if (notmet_me(ob)) {
         command("introduce myself to " + who);
         return 1; 
          }
      break;
   }
   return 0;
}

int
return_sigh(string who)
{
   if (!who) return 0;
   who = lower_case(who);
   if (random(3)) return 0;
   command("say You' re mood is brangin me down. Go out and hunt somethin, will ya??");
   return 1;
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob)) return 0;
   if (!random(20)) return 0;
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}
void
return_introduce()
{
   command("introduce myself");
}
void
emote_hook(string emote,object actor,string averb = 0)
{
   string name = actor->query_real_name();
   
   switch(emote)
   {
      case "sigh":
      set_alarm(3.0,0.0,&return_sigh(name));
      break;
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
/*
arm_me()
{
    object knife,bow,boots,arrows,bowstring,armour,widehat,furcoat;

    FIXEUID;
    bow       = clone_object(HUNTCLUB_DIR    + "wep/" + "hornbeam_bow.c");
    knife     = clone_object(HUNTCLUB_DIR    + "wep/" + "longknife.c");
    arrows    = clone_object(HUNTCLUB_DIR    + "wep/" + "arrows.c");
    bowstring = clone_object(HUNTCLUB_DIR    + "obj/" + "bowstring.c");
    armour    = clone_object(HUNTCLUB_DIR    + "arm/" + "leather.c");
    widehat   = clone_object(HUNTCLUB_DIR    + "arm/" + "widehat.c");
    furcoat   = clone_object(HUNTCLUB_DIR    + "arm/" + "furcoat.c");
	boots     = clone_object(HUNTCLUB_DIR    + "arm/" + "boots.c");
    
    furcoat->move(TO);
    boots->move(TO);
    armour->move(TO);
    widehat->move(TO);
    bow->move(TO);
    knife->move(TO);
    arrows->move(TO);
    bowstring->move(TO);
    command("wear all");
    command("lean by the fire");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say ou' ll direckly find out who' s th' hunter, and who' s th' prey!");
    command("stand up");
    command("emote grips the hilt of his long knife!");
    command("string bow");
    command("wield knife");

    alarm_id = set_alarm(10.0,20.0,"before_attack");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("unwield all");
    command("shout Run rabbit, RUN!");
    command("unstring bow");
    command("smirk");
    command("lean by the fire");
    command("sigh deeply");
    remove_alarm(alarm_id);
}
*/