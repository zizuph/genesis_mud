#include <composite.h>

#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

//By Dunstable, from the wise monk in the monk guild of Roke
// Recoded by Igneous ot fix some major bugs with the quest
// Recoded again to use the hobbitmaker, -Igneous June 1997

// 01/12/17 Arandir	Added reporting of collected items
// 01/12/22 Arandir	Better formatting of the item list

#define HONEY 1
#define MUSTARD 2
#define BOWL 4
#define SPOON 8
#define SAUSAGE 16
#define PAN 32
#define CLOTH 64
#define CLOVE 128
#define SAVORY 256
#define THYME 512
#define MINT 1024
#define CHERVIL 2048
#define DONE (HONEY|MUSTARD|BOWL|SPOON|SAUSAGE|PAN|CLOTH|CLOVE|SAVORY|THYME|MINT|CHERVIL)

//   Protoypes
void cookit (object player);
void give_it (object player);
void thank_chat (object oWhat, object oFrom);

string *visitors;
int *bitm;

void
create_hobbit()
{
    set_type(MAIDEN);
    set_power(90);
    set_name("bedelia");
    set_family_name("Underhill");
    set_title("Chief Cook and Bottle Washer of the Pipe and Fork");
    add_name(({"cook","woman"}));
    set_adj(({"tall","busy"}));
    set_long("This tired busy hobbit is looking around for her things.  Perhaps "+
      "you could help her find them?\n");
    seteuid(getuid(TO));

    visitors = ({});
    bitm = ({});

    add_ask(({"help","job","task","quest"}),VBFC_ME("ask_help"));
    add_ask(({"pie","pies","bumbleberry pie"}),VBFC_ME("ask_pie"));
    set_default_answer("I don't know what you are talking about.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);

    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_HERBALISM,100);
    setuid(); seteuid(getuid());
    restore_object(MICH_DIR + "visitors");
}


void
introduce_hobbit(string str)
{
    if (!present(str,ENV(TO)))
	return;

    command("introduce myself to "+str);
}


string
ask_help()
{
    command("say I don't need much help, I guess I'm ok for now.");
    command("say Thank you for asking though.");
    command("say You might see the Mayor, he'd know more than me.");
    return "";
}

string
ask_pie()
{
    command("say I bake bumbleberry pies, and they are wonderful!");
    return "";
}


void
enter_inv(object what, object from)
{
    int ran;

    ::enter_inv(what, from);

    if (!from) /* Perhaps it was cloned and moved to me... */
	return;
    ran = 1 + random(10);
    set_alarm (itof(random(8)), 0.0, &thank_chat (what, from));
}


#define has_name(o,n)	(member_array ((n),(o)->query_names ()) >= 0)

void thank_chat (object oWhat, object oFrom)
{
  int   iIndex;
  int   iOldBits;
  int   iGotPlate = 0;
  float fLastAlarm = 0.0;

  if (!objectp (oWhat)) return;

  // We first see if that is a pie plate we are given. If it is, and
  // the giver is not yet registered as quest solver, we register him.

  if (has_name (oWhat, "_shire_pieplate_"))
  {
    command ("smile");
    set_alarm (fLastAlarm+2.0,0.0, &command ("say You want me to make a pie?"));
    set_alarm (fLastAlarm+5.0,0.0, &command ("say I will need some ingredients for that..."));
    fLastAlarm += 5.0;
    iGotPlate = 1;

    if (member_array (oFrom->query_real_name (), visitors) < 0)
    {
      visitors += ({oFrom->query_real_name ()});
      bitm     += ({0});
    };
  };

  // Now we see if the person is solving the quest, and if the item
  // we are given is related to it.
    
  iIndex = member_array (oFrom->query_real_name (), visitors);

  if (iIndex < 0)
  {
    command ("say What am I supposed to do with this?");
    command ("say You are lucky I did not keep it!");
    command ("drop " + OB_NAME(oWhat));
    return;
  };

  iOldBits = bitm [iIndex];

  if (has_name (oWhat, "_shire_honey_")) bitm[iIndex] |= HONEY;
  if (has_name (oWhat, "_shire_mustard_")) bitm[iIndex] |= MUSTARD;
  if (has_name (oWhat, "_shire_mixing_bowl_")) bitm[iIndex] |= BOWL;
  if (has_name (oWhat, "_shire_mixing_spoon_"))
  {
    if (oFrom->query_prop("_i_got_the_mixing_spoon_"))
    {
      bitm[iIndex] |= SPOON;
    }
    else
    {
      set_alarm(fLastAlarm+2.0,0.0, &command("say I don't want that, it looks stolen!"));
      set_alarm(fLastAlarm+5.0,0.0, &command("emote breaks the spoon in half."));
      fLastAlarm += 5.0;
      oWhat->remove_object ();
      return;
    };
  };
  if (has_name (oWhat, "_shire_sausage_")) bitm[iIndex] |= SAUSAGE;
  if (has_name (oWhat, "_shire_baking_pan_")) bitm[iIndex] |= PAN;
  if (has_name (oWhat, "_shire_cloth_")) bitm[iIndex] |= CLOTH;
  if (oWhat->query_herb_name() == "clove") bitm[iIndex] |= CLOVE;
  if (oWhat->query_herb_name() == "savory") bitm[iIndex] |= SAVORY;
  if (oWhat->query_herb_name() == "thyme") bitm[iIndex] |= THYME;
  if (oWhat->query_herb_name() == "mint") bitm[iIndex] |= MINT;
  if (oWhat->query_herb_name() == "chervil") bitm[iIndex] |= CHERVIL;

  if (!iGotPlate && (bitm[iIndex] == iOldBits))
  {
    command("say I don't want this!");
    command("drop " + OB_NAME(oWhat));
  }
  else
  {
    command("say Thank you, I can use this!");
    oWhat->remove_object ();
  };

  if (bitm[iIndex] == DONE)
  {
    set_alarm (fLastAlarm+2.0,0.0, &command("think"));
    set_alarm (fLastAlarm+5.0,0.0, &command("say Hmmm, seems you've already given me everything I need..."));
    set_alarm (fLastAlarm+7.0,0.0, &command("say I guess I will make that pie for you now."));
    set_alarm (fLastAlarm+10.0,0.0, &cookit (oFrom));
    fLastAlarm += 10.0;
  }
  else
  {
    string *asHave = ({ });
    string *asNeed = ({ });

    if (bitm[iIndex] & BOWL)    asHave += ({ "a mixing bowl" });
                           else asNeed += ({ "a mixing bowl" });
    if (bitm[iIndex] & MUSTARD) asHave += ({ "a pack of mustard seeds" });
                           else asNeed += ({ "a pack of mustard seeds" });
    if (bitm[iIndex] & HONEY)   asHave += ({ "a bottle of honey" });
                           else asNeed += ({ "a bottle of honey" });
    if (bitm[iIndex] & SPOON)   asHave += ({ "a spoon" });
                           else asNeed += ({ "a spoon" });
    if (bitm[iIndex] & PAN)     asHave += ({ "a cooking sheet" });
                           else asNeed += ({ "a cooking sheet" });
    if (bitm[iIndex] & SAUSAGE) asHave += ({ "a shire sausage" });
                           else asNeed += ({ "a shire sausage" });
    if (bitm[iIndex] & CLOTH)   asHave += ({ "a cloth" });
                           else asNeed += ({ "a cloth" });
    if (bitm[iIndex] & CLOVE)   asHave += ({ "a clove" });
                           else asNeed += ({ "a clove" });
    if (bitm[iIndex] & SAVORY)  asHave += ({ "a savory" });
                           else asNeed += ({ "a savory" });
    if (bitm[iIndex] & THYME)   asHave += ({ "a thyme" });
                           else asNeed += ({ "a thyme" });
    if (bitm[iIndex] & MINT)    asHave += ({ "a mint" });
                           else asNeed += ({ "a mint" });
    if (bitm[iIndex] & CHERVIL) asHave += ({ "a chervil" });
                           else asNeed += ({ "a chervil" });

    set_alarm (10.0,0.0, &command("sigh"));
    if (sizeof (asHave)) set_alarm (fLastAlarm+2.0,0.0, &command ("say I already have " + COMPOSITE_WORDS (asHave) + " from you."));
                    else set_alarm (fLastAlarm+2.0,0.0, &command ("say We have recently moved and all of my things are lost."));
    if (sizeof (asNeed)) set_alarm (fLastAlarm+4.0,0.0, &command ("say I need " + COMPOSITE_WORDS (asNeed) + " from you."));
                    else set_alarm (fLastAlarm+4.0,0.0, &command ("say Strange, I do not need anything from you."));
    fLastAlarm += 4.0;
  };

  save_object (MICH_DIR +"visitors");
}

void
cookit(object player)
{
    set_alarm(3.0,0.0,  "emote puts all the ingredients into the mixing bowl.\n");
    set_alarm(12.0,0.0, "emote measures flour and water and pours it into the bowl.\n");
    set_alarm(4.0,0.0,  "emote cracks some eggs into the batter.\n");
    set_alarm(10.0,0.0, "emote stirs the batter thouroughly.\n");
    set_alarm(7.0,0.0,  "emote greases the pan and pours the batter into it.\n");
    set_alarm(15.0,0.0, "emote opens up the oven and puts the pie in it.\n");
    set_alarm(5.0,0.0,  "tap ");
    set_alarm(10.0,0.0, "emote opens the stove and pulls out a hot pie!\n");
    set_alarm(9.0,0.0,  "emote sets it aside and covers it with the cloth to cool.\n");
    set_alarm(15.0,0.0,&give_it(player));

// old cooking routine
//    set_alarm(5.0,0.0, "tap");
//    set_alarm(10.0,0.0, "emote opens the stove and "+
//      "pulls out a hot pie!\n");
//    set_alarm(15.0,0.0,&give_it(player));
    /*  call_out("command",5,"tap");
    call_out("command",10,"emote opens the stove and pulls out a hot pie!\n");
    call_out("giveit",15);*/
}

void
give_it(object player)
{
    int index;
    object pie;

    set_this_player(player);
    pie =  clone_object(MICH_DIR + "obj/bumbleberry_pie");
    pie->move(TP,1);
    TP->add_prop("_had_the_pie_cooked_",1);

    command("say Here's your pie!");
    TP->catch_msg(QCTNAME(TO) + " gives you a pie.\n");
    say(QCTNAME(TO) + " gives "+QTNAME(TP)+" a pie.\n");
    command("smile joy");

    index = member_array(TP->query_real_name(),visitors);

    visitors = exclude_array(visitors,index,index);
    bitm = exclude_array(bitm,index,index);

    save_object(MICH_DIR + "visitors");
}
