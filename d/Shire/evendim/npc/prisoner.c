/*
 *  The prisoner of the orcs
 *  Cloned by ~Shire/evendim/orc_camp/tent_20
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/d/Shire/sys/defs.h"

#define PRISONER_QUEST  "_freed_orc_prisoner_"

int tied_up;

create_monster()
{
    seteuid(getuid());
    if (!IS_CLONE)
      return;

    set_name(({"_orc_prisoner_", "prisoner","human"}));
    set_adj(({"poor","tired"}));
    set_race_name("human"); 
    set_long("This is a poor human that has been tied up and " +
        "tortured by orcs for their own pleasure. He has " +
        "numerous cuts and bruises on his body and looks like " +
        "he has been through alot of rough treatment at the " +
        "hands of the orcs.");

    add_item("bonds", "The poor human is tied up with some bonds.\n");

    add_prop(CONT_I_WEIGHT,102000);  /* 102 Kg */
    add_prop(CONT_I_HEIGHT,183);     /* 183 cm */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 43, 21, 57, 21, 25, 50}));
    set_hp(10000); /* Heal fully */
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,20);

   /* Actions */
    set_act_time(5);
    add_act("sigh");
    add_act("sniff");
    add_act("emote pleads for his life.");

    set_chat_time(5);
    add_chat("Please, untie me!");
    add_chat("These bonds hurt!");
    add_chat("Help me, please!");
    add_chat("The orcs are going to kill me soon, I just know it!");

   /* Combat chat-strings */
    set_cchat_time(5);
    add_cchat("I am already almost dead!");
    add_cchat("Don't beat me, please!");
    add_cchat("Haven't I suffered enough?");

    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
}

init_living() {
    if (this_player()->query_npc())
        return;

    add_action("do_untie","untie");
    add_action("do_untie", "free");
    add_action("do_untie", "release");
}

do_untie(str)
{
    object orc_leader;

    if (id(str))
    {
        if(present("_leader_orc_",ENV(TO)))
        {
            write("The orc leader snarls at you savagely.\n");
            return 1;
        }
      else
      {
         write("You untie the bonds and free the human.\n");
         say(QCTNAME(TP) + " unties the bonds of the human.\n");
         command("say Thank you! I knew I could count on you, " + 
             TP->query_race() + ".");

         /* Invent a new property to check if one has solved the quest */
         if (TP->query_prop(PRISONER_QUEST,1))
         {
            command("say I am eternally grateful, " + TP->query_race() + ".");
            command("thank " + TP->query_real_name());
            command("kick corpse");
         }
         else
         {
            /* Property == 2 means she hasn't taken the book yet */
            TP->add_prop(PRISONER_QUEST,1); 

            command("say I will tell you the information they " +
                "tried to get out of me.");
            command("say I was on my way back from the ancient " +
                "ruins of Annuminas and discovered orcs " +
                "were following me. I had some valubles with me " +
                "and I knew that those orcs would ruin what I " +
                "had spent a lifetime acquiring. So to protect " +
                "the items, I buried them. I can get more of the " +
                "artifacts, that is no problem.");
            command("sighs thankfully");
            command("say If you feel brave, you can go and dig " +
                "the stuff up for it is valuable. However, I " +
                "know a little bit about magic so I enchanted " +
                "the area. Only those who know the " +
                "secret can get the items. I had to protect it " +
                "against those filthy orcs.");
            command("say Now I must go. You have truly saved my " +
                "life. I can't stand another moment in this " +
                "disgusting place.");
            command ("emote kicks the corpse fanatically.");
/*
            command("whisper " + TP->query_real_name()
                  + " Go out, west and dig there.");
            command("whisper " + TP->query_real_name()
                  + " That is where I buried my treasure.");
*/
         }
         command("say Thank you for the help!");
         tell_room(environment(), "The human runs away.\n");
         remove_object();
         return 1;
      }
   }
}

/* For the solamnic Knights */

query_knight_prestige() { return(-2); }
