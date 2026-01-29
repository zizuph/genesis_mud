inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_name("underhill");
    set_race_name("hobbit");
    set_adj(({"tall","sturdy"}));
    set_long("This is one of the merry hobbits living in Bree. He looks like "
    	    +"he has something to say and wants to hear much.\n");
    set_stats(({30,50,40,58,60,30}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(1);	    
   add_chat("Lovely weather in the Shire this time of year.");
   add_chat("I am from Buckland, where are you from?");
   add_chat("I've travelled for three days to get here.");
   add_chat("Where is that Barliman with my bed?");
   add_chat("I'm collecting information on hobbit genealogies.");

    set_act_time(3);
   add_act("snore");
   add_act("smile joy");
   add_act("introduce myself");
   add_act("singshiresong");
    add_act(({"emote takes out some nice tobacco.","emote stuffs his pipe with tobacco.","emote lights his pipe.","emote inhales deeply as he smokes his pipe.","emote sighs deeply, relaxing."}));
    
    set_cact_time(5);
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry at you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a hobbit eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Hopefully you will run when my frinds are here.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}
void
init()
{
    ::init();
    add_action("singshiresong","singshiresong");
}

arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "bknife");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
/*    boots = clone_object(BREE_DIR + "arm/" + "boots");
    boots->move(TO);
*/
    knife->move(TO);
    tunic->move(TO);
    command("wear all");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You would not mess with me, I have mighty friends.");
    command("emote grips the hilt of his long-knife!");
    command("wield all");
    command("wear all");
    
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
    command("say Puh, i managed to scare those bandits away!");
    command("say I hope master Took will come soon.");
    remove_alarm(alarm_id);
}

string
singshiresong()
{

   if(!TO->query_prop("_singing_shire_song"))
   {
    TO->add_prop("_singing_shire_song");
   command("stand on table");
   command("emote sings: There is an inn, a merry old inn,");
   command("emote sings: beneath an old grey hill,");
   command("emote sings: And there they brew the beer so brown");
   command("emote sings: That the Man in the Moon himself came down");
   command("emote sings: one night to drink his fill.");

   set_alarm(10.0,0.0,"second_verse");
   }

   return "";
}

string
second_verse()
{
   command("emote claps to the rhythm.");
   command("emote sings: The ostler has a tipsy cat");
   command("emote sings: that plays a five-stringed fiddle;");
   command("emote sings: And up and down he runs his bow, ");
   command("emote sings: Now squeaking high, now purring low,");
   command("emote sings: now sawing in the middle.");

   set_alarm(10.0,0,0,"third_verse");
   return "";

}

string
third_verse()
{
   command("dance");
   command("emote sings: The Man in the Moon was drinking deep,");
   command("emote sings: and the cat began to wail;");
   command("emote sings: A dish and a spoon on the table danced,");
   command("emote sings: The cow in the garden madly pranced,");
   command("emote sings: and the little dog chased his tail!");
   command("shout Hurrah!");

   set_alarm(10.0,0.0,"fourth_verse");
   return"";

}

string
fourth_verse()
{
   command("emote sings: The Man in the Moon took another mug,");
   command("emote sings: and then rolled beneath his chair;");
   command("emote sings: And there he dozed and dreamed of ale,");
   command("emote sings: Till in the sky the stars were pale,");
   command("emote sings: and dawn was in the air.");
   command("emote skips around on the table.");

   set_alarm(10.0,0.0,"fifth_verse");

   return"";

}
string
fifth_verse()
{
   command("emote sings: So the cat on his fiddle played hey-diddle-diddle,");
   command("emote sings: a jig that would wake the dead;");
   command("emote sings: He squeaked and sawed and quickened the tune,");
   command("emote sings: While the landlord shook the Man in the Moon:");
   command("emote sings: It's after three, he said.");
   command("clap");

   set_alarm(10.0,0.0,"sixth_verse");
   return"";

}
string
sixth_verse()
{
   command("emote sings: They rolled the Man slowly up the hill");
   command("emote sings: and bundled him into the Moon,");
   command("emote sings: While his horses galloped in rear,");
   command("emote sings: And the cow came capering like a deer,");
   command("emote sings: and a dish ran up with the spoon.");
   command("sing");

   set_alarm(10.0,0.0,"seventh_verse");
   return"";

}

string
seventh_verse()
{
   command("emote sings: Now quicker the fiddle went deedle-dum-diddle;");
   command("emote sings: the dog began to roar,");
   command("emote sings: The cows and the horses stood on their heads;");
   command("emote sings: The guests all bounded from their beds");
   command("emote sings: And danced upon the floor.");

   set_alarm(10.0,0.0,"eighth_verse");
   return"";
}

string
eighth_verse()
{
   command("say Everybody now!");
   command("emote sings: With a ping and a pang the fiddle-strings broke!");
   command("emote sings: the cow jumped over the Moon,");
   command("emote sings: And the little dog laughed to see such fun,");
   command("emote sings: And the Saturday dish went off at a run");
   command("emote sings with the silver Sunday spoon.");

   set_alarm(15.0,0.0,"ninth_verse");
   return"";
}

string
ninth_verse()
{
   command("emote sings: The round Moon rolled behind the hill,");
   command("emote sings: as the sun raised up her head.");
   command("emote sings: She hardly believed her fiery eyes;");
   command("emote sings: For though it was day, to her surprise");
   command("emote sings: they all went back to bed!");
   command("laugh");
   command("climb down");
   TO->remove_prop("_singing_shire_song");
   return"";

}
