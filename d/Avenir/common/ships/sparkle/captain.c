// -*-C++-*-
// name: Staek   /d/Avenir/common/ships/sparkle/keats.c
// creator(s):   Tepisch  Oct 1994
// last update:  Boriska  Mar 22 1995, special attack fixes, code cleanup
//               Cirion   Apr 19 1996, put in add_asks in relation to bury 
//                                     bones quest
//		 Denis, Aug'96: Removed triggers from introing process.
// purpose:      Ship Captain for the Melancholy
// note:         (modelled after John Keats [1795-1821])
// bug(s):
// to-do:
// revision:     Boriska Aug 1995, heal_hp tuning after hp formula change

#include <ss_types.h>
#include "/d/Avenir/common/ships/ship.h"
#include "/d/Avenir/common/port/bury_bones.h"

#define ETO     environment()
#define STICKET  SPAR_DIR + "ticket"
#define SPRICE   24

#pragma save_binary

inherit "/d/Genesis/ship/captain";
inherit "/d/Avenir/inherit/npc";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

private void call_demon();
private int no_demon = 0;
private object demon;

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("staek");
    add_name("captain");
    set_title("Captain of the Melancholy");
    set_living_name("staek");
    set_race_name("human");
    set_adj(({"thin", "sallow"}));
    set_stats(({ 80, 60, 90, 80, 60, 70 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_WEP_SWORD,75);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,50);
  
    LONG("He would be a handsome man if he wasn't so very slender.\n"+
        "Purest white lace at his collar and cuffs accent the sickly "+
        "sallow tint of his skin.\n" +
        "His eyes are sunken and feverish-looking.\nHis longish "+
        "dark hair is tied at the nape of his neck with a fine blue "+
        "ribband.\n");
    set_alignment(0);
    set_appearance_offset(-10);
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_FIRE, 50);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(3);   
    add_act("cough");
    add_act("sneeze");
    add_act("moan");
    add_act("groan");
    add_act("@@do_poem");
    add_act("@@on_death");
    add_act("emote coughs phlegm into his handkerchief.");

    set_chat_time(2);
    add_chat("Travelling by sea is a solitary journey of the spirit.");
    add_chat("Alas, I am tired unto death.");
    add_chat("Come sail with me aboard this barque of dead men's bones.");
    add_chat("Listen for the groans which fill these ghostly sails."); 
    add_chat("I mourn this, my fate. To long for home, forever exiled from "+
	"lovely Sybarus, Jewel of Avenir.");
    add_chat("Knowledge is power. Seek neither, my friend.");
    add_chat("They say there is an ancient machine of stone somewhere on the Isle of " +
    "the Dead that carries deep unexplored secrets, but the mist there covers it from " +
    "the unwary....Do you know something about this machine, traveller?");
    add_chat("They went down, alas, all died to the very last man.");
    add_chat("They say his ghost haunts the deeps, far below the port.");
    add_chat("Naught was left but a sad old book, all to tell the tale of "
        +"the sad tragedy.");
    add_chat("Alas! For I knew him well. I was his mate, and he listened to me.");
    add_chat("No one could have forseen the storms that would arise.");
    add_chat("At peace, he only would have wanted to be at peace, away from the "
        +"torment of the raging seas.");
  
    set_cchat_time(3);
    add_cchat("T'would be wise to cease this nonsense before it "+
	"is too late.");
    add_cchat("Death is deliverance from the nightmare of living.");
    add_cchat("Lost! All is lost!");
    add_cchat("Infidel!");
    add_cchat("All are slaughtered when faced with this spiritual alliance.");
    add_cchat("I give you Amyras Soultaker!");

    set_cact_time(4);
    add_cact("@@do_poem");
    add_cact("cackle madly");
    add_cact("smile insane");
    add_cact("emote licks his blood-flecked lips.");
    add_cact("wield all");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"where","where to","from", "destination", "sail",
        "sailing", "travel", "ship", "barque"}),
        "say The Melancholy sails between the Rift of Sybarus "+
        "and Sparkle township.",1);
    add_ask(({"tragedy","sadness","grief","misery"}),
        "Aye, twas misery indeed. Captain Branston was a great "+
        "man. I pity the widow most of all, though.", 1);
    add_ask(({"concubine","Concubine","SS Concubine",
        "about the concubine","about the Concubine",
        "about concubine","first", "wreck", "shipwreck"}),
        VBFC_ME("answer_ship") );
    add_ask(({"captain","braston","Braston","he", "him"}),
        VBFC_ME("answer_captain"));
    add_ask(({"wife","widow","maya","Maya","about maya",
        "about widow","about wife"}),VBFC_ME("answer_widow"));
    add_ask(({"book","log","logbook", "log book"}), 
        VBFC_ME("answer_log"));
    add_ask(({"sea","ocean","travel","ships"}), "say "
        +"the sea is in me.", 1);
    add_ask(({"eel","eels","fish"}),"say I heard that there "
        +"are eels deep beneath the waters of the port.", 1);
    add_ask(({"Sybarus", "sybarus", "rift", "Rift"}),
        "say Sybarus is the city of Faithful, who dwell in the "+
        "shadow of the Source", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
        "say We of Sybarus are the Faithful. We live to serve and "+
        "uphold the Pact, that the Source will always cast its illum"+
        "ination upon us.",1);
    add_ask(({"source", "Source", "crystal"}),
        "say The Source is a huge vein of crystal which, by the Will "+
        "of the Gods, illuminates the Great Cavern of Sybarus.", 1);
    add_ask(({"good", "Good", "evil", "Evil", "right", "Right",
        "wrong", "Wrong", "good and evil", "right and wrong",
        "morality"}), VBFC_ME("good_ask"));
    add_ask(({"holm", "Holm", "Park", "park"}),
        "say Ah the Holm! It is the ultimate hunting ground. It is "+
        "a place where chaos reigns, and anything can happen!",1);
    add_ask(({"knight", "Knight", "knights", "Knights", "Knighthood", 
        "knighthood"}), VBFC_ME("knight_ask"));
    add_ask(({"god", "gods", "Gods", "Will of the Gods", "will" }),
        VBFC_ME("gods_ask"));
    add_ask(({"Hizarbin", "hizarbin", "Jazur", "jazur", "Nantur", 
        "nantur"}), 
        "say Names of Power should not be spoken lest you would wish "+
        "the one so named to appear as though summoned.", 1);            
    add_ask("death", VBFC_ME("do_poem"));
    add_ask(({"union", "Union", "Shadow Warriors", "shadow warriors"}),
        "say They are the guardians of Sybarus, with the mandate of "+
        "the Hegemon.", 1);
    add_ask(({"drow", "Drow"}), "say I've heard of them. Very dark "+
        "people with white hair. They live below, like Sybarites do.",
        1);
    add_ask(({"dancer", "dancers", "dancers of the veil", "veil dancers",
        "qalita", "Dancers"}), "say Ah the Dancers! Aren't they "+
        "delightful! You can find Qalita down at the pub in Sybarus.",1);
    add_ask(({"pub", "pub in sybarus", "Icy Bod's"}), "say The pub is "+
        "called Icky Bod's. I've not been there in too long.",1);
    add_ask("exile", "say Alas, when the Concubine sank and I was the "+
        "sole survivor, the Lord Inquisitor banished me from Sybarus.",1);
    set_ticket(STICKET);
    set_price(SPRICE);

    seteuid(getuid());
}    

string
what_me()
{
    switch(random(6))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I don't know. I stick to what I know do know:"+
                " the deck of this ship.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("emote raises his eyebrows and blinks several "+
                "times in a row.");
            break;
        case 5:
            command("say Oddly enough, I don't know anything about that.");
            break;
    }
    return "";    
}

string answer_ship()
{
   delay_action(1.0, ({"sigh","say Aye, the fair ship "
      +"Concubine was my first assignment.",0,"say It was "
      +"a rough trip indeed, full of peril.",0,0,
       "glare search",0,"say I am the only one left alive "
      +"from that maiden journey."}));
   return "";
}

string answer_captain()
{
   TP->add_prop(SPOKENTO, "staek");
   delay_action(1.0, ({"say Braston was a great man indeed, the "
        +"captain of the fair Concubine.","say He went "
        +"down with his ship, of course.",0,0,"emote "
        +"peers out over the water.",0,"say His bones "
        +"probably rest in the wreck of the ship to "
        +"this day, which no one has ever found.",0,0,0,
         "say I believe his widow, Maya, is still "
        +"alive though."}));
   LOG_THIS(TP->query_name() +" spoke to Staek about Braston.");
   return "";
}

string answer_log()
{
   delay_action(1.0, ({"shrug .","say I remember the "
     +"captain kept a log book, but it probably went down "
     +"with the ship.",0,"say It was so long ago, I really don't "
     +"remember."}));
   return "";
}

string answer_widow()
{
   TP->add_prop(SPOKENTO, "staek");
   LOG_THIS(TP->query_name() +" spoke to Staek about Maya.");
   delay_action(1.0, ({"say Ahhh, Maya was "
        +"a beautiful woman in her time.", "say I fear "
        +"she was destroyed by Captain Braston's death "
        +"though.","ponder",0,"say I believe she "
        +"still lives down on the island, somewhere "
        +"near the bazaar.",0,"say I haven't seen her for "
        +"many years, though."}));

   return "";
}

string
gods_ask()
{
    command("say My patron God is Hizarbin, who saved me from "+
        "certain death in these waters.");
    return "";
}

string
good_ask()
{
    command("smile thoughtfully");
    command("say I've given that subject much thought during these "+
        "long days of exile at sea.");
    command("say What are good and evil, but a matter of perspective?"+
        " Neither are absolutes--they are but interpretations of a "+
        "moral code.");
    command("say It is not your place to say that something I do by "+
        "the Will of the Gods is good or evil.");
    command("say Morality does not apply to Gods, nor to those who "+
        "do their Will!");
    return "";
}

string 
knight_ask()
{
    command("spit");
    command("say A misguided group of fools, they are, serving a weak "+
        "god. So self-righteous and pompous, these Knightlings, "+
        "insisting so stridently upon their 'goodness', yet "+
        "distrusted even so by the people of their land.");
    command("say Good and Evil matter not! It is Right and "+
          "Wrong that matter. Doing the Will of the Gods is Right "+
          "and all else is Wrong. Mark my words if you venture into "+
          "Sybarus.");
    return "";
}

void
equip_me()
{
  clone_object(SPAR_DIR + "rapier")->move(this_object(),1);
  clone_object(SPAR_DIR + "shirt")->move(this_object(), 1);
  command("wear all");
  command("wield all");
}

string
on_death()
{
  command("say Can death be sleep, when life is but a dream,");
  command("say And scenes of bliss pass as a phantom by?");
  command("say The transient pleasures as a vision seem,");
  command("say And yet we think the greatest pain's to die.");
  command("ponder");
  command("say How strange it is that man on earth should roam,");
  command("say And lead a life of woe, but not forsake");
  command("say His rugged path; nor dare he view alone");
  command("say His future doom, which is but to awake.");
  return "sigh dreamily";
}

string
do_poem()
{
  command("say Darkling I listen; and for many a time");
  command("say I have been half in love with easeful death,");
  command("say Called him soft names in many a mused rhyme,");
  command("say To take into the air my quiet breath;");
  command("frown");
  command("say Now more than ever it seems rich to die,");  
  command("say To cease upon the midnight with no pain...");
  return "";
}

private void
call_demon()
{
  object me = this_object();
  
  if (no_demon >= 3) {
    command("shout Amyras! I am yours! Take my soul!");
    return;
  }

  if (query_hp() < query_max_hp()/2 && !objectp(demon) && no_demon <= 3)
    {
      tell_room(ETO, QCTNAME(me) + "'s body arches grotesquely and "+
		"flames appear to burst from his chest!\n");
      demon = clone_object(SPAR_DIR + "amyras");
      demon->move_living("M", ETO);
      tell_room(ETO, "The flames coalesce into a humanoid figure!\n");
      demon->command("shout You dare attack my Servant!");
      demon->set_follow("staek");
      demon->help_staek(me);
      no_demon++;
    }
}

int
special_attack(object victim)
{
  if(random(2)) return 0; /* normal attack */

  switch (random(2))
    {
    case 0:
      call_demon();
      break;
    case 1:
      tell_room(ETO, QCTNAME(TO) +
		" appears to draw strength from an unseen source.\n");
      heal_hp(200+random(70));
    }
  return 1;
}

void give_back(object what, object from)
{
  if(!command("give "+what->query_name()+" to "+from->query_real_name()))
   command("drop "+what->query_name());
}

void enter_inv(object what, object from)
{
  ::enter_inv(what, from);

  if(!living(from))
    return;

  if(what->id(RING_ID))
  {
    delay_action(1.0, ({"whistle","say This was Braston's ring!",
                 "say Where did you find it?",0,
                 "say His widow will probably want it as "
                +"a keepsake.","give ring to "+from->query_real_name(),
                 "drop "+RING_ID}));
    return;
  }

  if(what->id(BONES_ID))
  {
    set_alarm(1.0, 0.0, &command("say What are these?"));
  }

  set_alarm(1.0, 0.0, &give_back(what, from));
}

void
init_living()
{
    ::init_living();
 
    if (ticket)
        add_action("buy", "buy");
}

string race_sound()
{
  return "murmurs";
}

