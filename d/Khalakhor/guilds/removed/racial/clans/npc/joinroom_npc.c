/* File         : /d/Khalakhor/guilds/racial/clans/npc/joinroom_npc.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March 2001         
 * Purpose      : Information NPC for the Clans of Khalakhor Race guild
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "npc.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
 
inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
 
mapping remembered;
object shop;
object last_attacker;
string store_room;
int return_alarm_id,
    attacker_alarm_id,
    has_armed;
 
/*
 * Function name: arm_me
 * Description  : Clones in the shopkeeper's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    if (has_armed)
        return;
 
    seteuid(getuid());
 
    clone_object("/d/Khalakhor/common/arm/shirt_wool")->move(TO);
    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/kilts/kilt_macdunn")->move(TO);
    command("wield all");
    command("wear all");
    has_armed = 1;
}
 

public string
ask_clans()
{
   command("say Which Clan would you be asking about? Khalakhor currently has " +
           "six known Clans. See the plaque for a listing.\n");
   command("point plaque");
   return "";
}


public string
ask_septs()
{
   command("say A listing of Septs may be found by reading this plaque.\n");
   command("point plaque");
   return "";
}


public string
ask_joining()
{
   command("say Joining is as simple as choosing a sept name in the beginning. " +
           "Should you want to go further and join one of the Clans, you must " +
           "seek out the right Clan for you and petition the Chief for acceptance. " +
           "See the plaque for a listing of Clans and their members.\n");
   command("point plaque");
   return "";
}

public string
ask_leaving()
{
   command("point plaque");
   return "";
}


public string
ask_guild()
{
   command("say The Clans of Khalakhor are comprised of six Clans which Humans " +
           "and Dwarves call home. Humans and Dwarves may 'choose' a sept name " +
           "then petition to join one of the various Clans throughout Khalakhor. " +
           "Should you choose not to join one of the Clans you may make the common " +
           "Hall here within MacDunn your home. The Hall is located south, east then north " +
           "of here. For a listing of sept names and the Clans please refer to the " +
           "plaque. If you have a question regarding one of the Clans, please  " +
           "ask me about the Clan by name.\n");
   command("point plaque");
   return "";
}


public string
ask_macdunn()
{
   command("say The Clan MacDunn can be found with the Port City of MacDunn. " +
           "Their Clan colours are Black and White. Their crest " + MACDUNN_BADGE+ ".\n");
   return "";
}

public string
ask_lohrayn()
{
   command("say Seek out sea Captain Leabag Ashlish. Capt'n Ashlish sails " +
           "to and from the village of Baile Ashlagh, homeland to the Clan " +
           "Lohrayn. Their Clan colours are purple and white. " +
           "Their crest " + LOHRAYN_BADGE + ".\n");
   return "";
}


public string
ask_mactabor()
{
   command("say The Clan MacTabor calls Tabor Sogh their home. No more " +
           "than a sleeply fishing village, but well protected by the " +
           "MacTabor. Their clan colours are blue and white. " +
           "Their crest " + MACTABOR_BADGE+ ".\n");
   return "";
}



public string
ask_macfadden()
{
   command("say The whereabouts of the Clan MacFadden are unknown. " +
           "However, their colours are green and purple and their " +
           "crest " + MACFADDEN_BADGE + ".\n");
   return "";
}


public string
ask_macvay()
{
   command("say the Clan MacVay be far away from here. Their colours " +
           "be green and red and their crest " + MACVAY_BADGE + ".\n");
   return "";
}


public string
ask_macfaolain()
{
   command("say the Clan MacFaolain call Rannoch their home. Tis " +
           "a shame about Rannoch.. Perhaps, they'll be able to " +
           "dig themselves back out in a year or two. MacFaolains " +
           "colours are crimson and green. Their crest " + MACFAOLAIN_BADGE + 
           ".\n");
   return "";
}


public string
ask_rules()
{
   command("say The rules are quite simple actually.. Harm noone within " +
           "your Clan less ye become a Kinslayer.. Only humans and dwarves " +
           "are accepted, walking corpses need apply.. There be no restriction "+
           "as far as alignment is concerned. So have fun!\n");
   return "";
}


/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_human()
{
    set_name("tavish");
    set_living_name("tavish");
    add_name("librarian");
    add_name("man");
    set_adj("thin");
    add_adj("long-fingered");
    cs_set_sept("Bodellaghe");
    cs_set_clan("Macdunn");
    set_long("The man appears to be waiting to answer any " +
        "questions that someone may have regarding the Clans.\n");
 
    default_config_npc(40);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_SWORD, 35);
 
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(400);
    set_exp_factor(50);
 
    set_act_time(15);
    add_act("emote tucks his thumbs in his belt, rocking back and forth " +
            "on his heels slightly.");
    add_act("say Ask me about the clans by name and i'll tell you what " +
            "I know.");
    add_act("say Ask me about the rules perhaps?");
    add_act("say Ask me about joining?");
    add_act("say Ask me about leaving?");
    add_act("say if you can read, this plaque may answer some of your questions.\n");
    add_act("point plaque");
    add_act("ponder");

    add_ask(({"eil-galaith"}),
      "say Hmm. Well I'm not sure. Sounds like something that might "+
      "be on the isle of Galaith.", 1);
    add_ask(({"galaith", "isle of galaith", "galaith isle"}),
      "say Oh yes, the isle of Galaith is near the southwestern speir. "+
      "I've heard there is a tower that suddenly appeared there. I do "+
      "not travel much myself to know for sure. You might try around "+
      "the docks.", 1); 

    add_ask(({"Clan","Clans","clans","about clans","clan"}),"@@ask_clans",1);
    add_ask(({"septs","about septs","sept"}),"@@ask_septs",1);
    add_ask(({"history","about history","clan history"}),"@@ask_history",1);
    add_ask(({"leaving","about leaving"}),"@@ask_leaving",1);
    add_ask(({"joining","about joining"}),"@@ask_joining",1);
    add_ask(({"rules","about rules"}),"@@ask_rules",1);
    add_ask(({"Clan MacDunn","clan macdunn","MacDunn","macdunn"}),"@@ask_macdunn",1);
    add_ask(({"Clan Lohrayn","clan lohrayn","Lohrayn","lohrayn"}),"@@ask_lohrayn",1);
    add_ask(({"Clan MacTabor","clan mactabor","MacTabor","mactabor"}), "@@ask_mactabor",1);
    add_ask(({"Clan MacFadden","clan macfadden","MacFadden","macfadden"}), "@@ask_macfadden",1);    
    add_ask(({"Clan MacVay","clan macvay","MacVay","macvay"}), "@@ask_macvay",1);
    add_ask(({"Clan MacFaolain","clan macfaolain","MacFaolain","macfaolain"}), "@@ask_macfaolain",1);

    add_cact("say Oh, so it's a fight you want, is it?");
    add_cact("emote growls.");
 
    remembered = ([]);
 
   set_alarm(0.5, 0.0, arm_me);
   set_size_descs("extremely tall", "thin");

}
