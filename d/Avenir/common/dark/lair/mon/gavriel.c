// -*-C++-*-
// name: Gavriel /d/Avenir/common/dark/mon/gavriel
// creator(s):   Tep&Grace March 1995
// last update:  Lilith Aug 2021: Updated npc and location
// purpose:      Former Mystic NPC: In memory of the
//		          Ancient order of Mystic Wisdom
// note:        npc loaded in room /dark/l2/add/c6.c
// bug(s):
// to-do:


inherit "/d/Avenir/inherit/monster";
#include "/d/Avenir/common/dark/dark.h" 
#include <macros.h>
#include <stdproperties.h>

void
equip_me()
{
    add_armour(DARK+"obj/gavriels_robe");
	add_armour(DARK+"obj/gavriels_cowl");
	add_armour(DARK+"obj/gavriels_signet");
	equip(DARK+"obj/gavriels_lamp");
}

void
create_monster()
{  
   if (!IS_CLONE)
       return;
  
   set_name("gavriel");
   set_race_name("gnome");
   set_living_name("gavriel");
   set_title("the former Mystic Cantor");
   set_adj("blind");
   add_adj("bent-shouldered");
   add_name("mystic");  
   add_name("cantor");
  
   set_long("He is a creature broken; sorrowful and disoriented.\n"+
 	"His face is not old, but his hair has turned the gray-"+
   	"white colour of the aged. The many cares heaped upon "+
	"his once-straight shoulders have caused them to slump "+
	"dejectedly. In his blinded eyes you can see the emotions at "+
	"war inside him, with despair seeming to win over hope."+
//    "\nHe is wearing an Amulet of the Ancients around his "+
//    "neck."+
	"\n");
   
   set_stats(({ 175, 210, 175, 175, 200, 175 }));
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT, 60);
   set_skill(SS_AWARENESS, 60); 
   set_skill(SS_ACROBAT, 50);
   set_all_hitloc_unarmed(50);  
   set_all_attack_unarmed(50, 30);

   set_random_move(20, 1);    
   set_restrain_path("/d/Avenir/common/dark/l2/add/");     
   set_monster_home("/d/Avenir/common/dark/l2/add/c6");

   add_prop(LIVE_I_SEE_DARK, 1);
  
   set_appearance(99);
   set_alignment(1200);
   set_hp(5000);

   set_chat_time(2);
   add_chat("@@storm");
   add_chat("I long to hear even the ancient bells of the sacred "+
	   "Shrine sounding. Anything but this ominous silence.");
   add_chat("The Ancients must have found me unworthy, for I "+
       "no longer hear their Voices within me.");
   add_chat("Know ye the way to the Shrine? I am lost.");
   add_chat("Avirigh said that peace comes to those who pray.");
   add_chat("I once had the wisdom and the glory of the Ancients. "+
   	   "Now I have an aching emptiness.");
   add_chat("Jolly, saintly Sofinis, would that I had even one of "+
       "your candles to light my path.");       
   add_chat("The sacred ember has grown cold, and my heart "+
	   "with it.");
   add_chat("But for the kindness of the albi, I would no longer "+
       "live.");

   set_cchat_time(5);
   add_cchat("Violence is a last resort. Where is Peace?");
   add_cchat("I am truly unworthy.");
   add_cchat("Though the Ancients choose to visit Death upon me, "+
	"I shall never renounce my vows!");
   
   set_cact_time(2);
   add_cact(({"emote closes his eyes and focusses his attention "+
       "on something mysterious.", "emote fails to cast a spell "+
       "correctly."}));
   add_cact("emote scolds you for being such a scourge.");
   add_cact("cries out to the Ancients in despair.");
   
   set_act_time(5);
   add_act(({"say It is true, the Prophet has left us.","sigh sadl"}));
   add_act("emote intones a long canticle in honour of the stars.");
   add_act("emote prays to the Ancients.");
   add_act("emote smiles mysteriously.");

   add_ask(({"mystic","mytics"}), "say I was once a member of the "+
	"Ancient Order of Mystic Wisdom, but now I am lost to the "+
	"Ancients, and they unto me.", 1);
   add_ask("ancients", "say If you know naught of the Ancients, I "+
	"can tell you little.", 1);
   add_ask(({"shrine", "valley"}),
	"say The Holiest of Holy places, so beautiful as to bring "+
	"tears to my eyes at its rememberance.", 1);
   add_ask(({"quest", "task", "help"}),
	"say I have wandered so long in this utterdark my wits have "+
	"addled. I can be of little help to you.", 1);
   add_ask(({"vamp", "vamps", "vampyre", "vampire", "vampyres", 
        "vampires"}),VBFC_ME("do_vamps"));
   add_ask(({"underdark", "utterdark", "unterdark"}),
        "say You're in it! And a darker, more dangerous place "+
        "you won't find.",1);
   add_ask(({"sybarus", "city", "island", "islands"}),
	"say There are islands in a sea down here, and on it "+
	"a great city is built.", 1);
   add_ask(({"eyes", "blind", "blindness", "sight"}),
	"say My sight... The light faded from my eyes when the Ancients "+
	"faded from this world.", 1);

  trig_new("%s 'introduces' %s", "intro_me");    
                       

}

string
storm()
{
	command("say The sky became dark as pitch and Nallasar raised");
	command("say his arms, summoning the Wrath of the Ancients.");
	command("say The winds rose and the mother of storms came,");
	command("say obscuring the Valley from view.");
	return("It was then that I lost the way to the Shrine.");
} 


string
do_vamps()
{	
    command("say Don't you know: Vamps Rock! Vamps Rock! VAMPS ROCK!");
    set_alarm(4.0, 0.0, "command", "say And if you believe that, "+
        "I know of a lovely piece of property by a subterranean sea...");
    set_alarm(8.0, 0.0, "command", "wink . all");
    return "";
} 

// ~quetzl/open/intro.h is used here.                        
int                                                          
intro_me (string s1, string s2)                              
{                                                            
  string *foo;                                               
  object who;                                                
                                                             
  if (sizeof (foo = explode (s2, " as:\n")) != 2)            
    return 0;                                                
  foo = explode (foo[1], " ");                               
                                                             
  if (!(who = find_player(lower_case(foo[0]))))              
    who = find_player(lower_case(foo[1]));                   
                                                             
  if (!who)                                                  
    return 0;                                                
                                                                    
  if (who->query_met(this_object()))                                
    return 1;                                                       
                                                                    
  foo[0] = "introduce myself to " + who->query_real_name();         
  set_alarm (2.0, 0.0, "command", foo[0]);                          
                                                                    
  return 1;                                                         
}                                                                   

