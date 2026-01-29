//

// The dwarven alchemist.
// ----------------------
// This dwarven alchemist is a significant part of the Ogress Quest.
// Learn more about this quest in /d/Shire/moria/doc/OgressQuest
//
// Sir Rogon.
//

inherit "/std/monster";
#include "defs.h"
#include "/d/Shire/bits.h"
#define Kg *1000
#define cm
#define QUEST_NAME "alchemist"
#define QUEST_NAME2 "sprinkle"

object saviour;
void thank_player_on_slab(object who);
void trans_home();

object
query_saviour()
{
    return saviour;
}

create_monster()
{
    set_name("gwindor");
    add_name("_dwarven_alchemist_");
    set_living_name("gwindor");
    set_title("master Alchemist of Durin's Royal Laboratories");
    set_race_name("dwarf");
    set_alignment(500);
      add_prop(CONT_I_WEIGHT, 45 Kg);
    add_prop(CONT_I_HEIGHT, 65 cm);
    add_prop(LIVE_I_SEE_DARK, 10);

    set_stats( ({ 70, 90, 80, 150, 170, 130 }) );
      set_skill(SS_UNARM_COMBAT,  50);
    set_skill(SS_WEP_POLEARM,   60);
    set_skill(SS_DEFENCE,       65);
    set_skill(SS_PARRY,         60);
    set_skill(SS_AWARENESS,     99);
    set_skill(SS_BLIND_COMBAT, 100);
      /* --- Magical skills --- */

    set_skill(SS_SPELLCRAFT, 87);
    set_skill(SS_ALCHEMY,   100);
      set_skill(SS_FORM_TRANSMUTATION, 89); /* Forming changes. */
    set_skill(SS_FORM_DIVINATION,    54);
    set_skill(SS_FORM_ABJURATION,    67);
    set_skill(SS_FORM_CONJURATION,   77);

    set_skill(SS_ELEMENT_EARTH,      99);
    set_skill(SS_ELEMENT_FIRE,       50);
    set_skill(SS_ELEMENT_LIFE,       20);
    set_skill(SS_ELEMENT_WATER,      40);

    set_skill(SS_LOC_SENSE,          88); /* Dwarf, right? */
}

void
thank_player_on_slab(object who)
{
    object star;
    saviour = who;
    command("sigh");
    command("say I have been trapped for a long long time.");
    command("smile .");
    command("say Durin's bane had me imprisoned in gold!");
    command("say What a torment for a dwarf!");
    command("say Anyway, I'll be off now! Thanks!");
    command("oops");
    command("say I am sorry, I guess you ought to be rewarded.");
    command("say Take this diamond star, it is magical.");
    command("say You can wave it over things to sprinkle it with diamonds.");
         star = clone_object(MORIA_OBJ + "star");
       star -> move(TO);
     command("give star to " + who->query_real_name());
      if (ENV(star) == TO)
   command("drop star");

    if(who->test_bit("Shire",EASTERN_GROUP,ALC_FREE_BIT))
    {
      command("say At it again, eh?  Better luck this time!");
      return;
    }

          who->set_bit(EASTERN_GROUP,ALC_FREE_BIT);
          who->add_exp(ALC_FREE_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
 CAP(who->query_real_name()) + " rewarded with "+ALC_FREE_EXP+" exp, "+
  "<"+who->query_average_stat()+"> avg stats.\n");
      who->catch_msg("You feel much more experienced!\n");
       say(QCTNAME(TP) + " was rewarded by the alchemist.\n");

    trans_home();
}

void
trans_home()
{
    command("emote makes a magical gesture.");
    move_living("X", MINES_DIR + "alch_home");
}

void
fetch_the_glass(object who, object glass)
{
    string name = who->query_real_name();
    object key;

    who->add_prop("_moria_i_is_welcome_at_the_alchemist", 1);
    move_living("X", ENV(who));
    command("laugh");
    command("say You found my long lost magnifying glass!!");
    command("shout Where did you find it??");
    command("thank "+name);
    tell_room(ENV(who),
      QCTNAME(TO) + " takes the " + QSHORT(glass) + ".\n");
    glass->move(TO);
command("whisper "+ name + " Come to my office south of the main "+
"junction of the Mines of Moria, east and south of the old "+
"dwarven bedroom.");
command("whisper "+ name + " I will tell you the secrets of Moria!\n");
    key = clone_object(MORIA_OBJ + "closet_key");
    key->move(TO);
    command("give key to " + name);
    command("bow");
    move_living("X", MINES_DIR + "alch_home");
}

void
recieve_at_home(object who)
{
    string name;
    object ogress;

if (who != saviour || !who->query_prop("_moria_i_is_welcome_at_the_alchemist"))
    {
    name = who->query_real_name();
    command("point " +name);
    command("say You are not welcome here!");
   who->catch_msg("You are magically forced to leave!\n");
     who->move_living("X", MINES_DIR + "cross");
    }
    else
    {
   name = who->query_real_name();
   ogress = (MINES_DIR + "dwelling")->query_witch();
if (!living(ogress)) {
   who->catch_msg("Bug in the ogress, please leave a report.\n");
    return;
}
command("smile happily");
who->catch_msg(
    "The Dwarven Alchemist sits down and measures you solemnly.\n" +
    "   'You are looking for Durin's Axe that was lost,\n"+
    "    but it is hidden in the treasure chamber of the\n"+
    "    orcs. There is no way to trespass them on your\n"+
    "    own, but there is a person who can help you.\n"+
    "    Somewhere in the mountain there lives a witch\n"+
    "    who knows a secret entrance to the chamber.\n"+
"   Her name is "+ogress->query_hidden_name()+" and she will ask you\n"+
    "    three riddles. It means death if you can not solve them!\n"+
    "\n"+
    "    Go now, and may the Power of Mahal guide your path!\n");


    if(who->test_bit("Shire",EASTERN_GROUP,SPRINKLE_BIT))
    {
      command("say Be careful this time!");
      return;
    }
          who->set_bit(EASTERN_GROUP,SPRINKLE_BIT);
          who->add_exp(SPRINKLE_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME2, extract(ctime(time()),4,15) + " " +
CAP(who->query_real_name()) + " rewarded with "+SPRINKLE_EXP+" exp,"+
          "<"+who->query_average_stat()+"> avg stats.\n");
          tell_object(who,"You feel more experienced!\n");
          return;

    }
}
