/* gladspkr.c: Answers all the gladiators questions.... */

inherit "/std/monster.c";
#include "defs.h"
#include "/d/Cirath/common/introfnc.h"
#define MAIN_ASK(x) ("@@askmost:"+file_name(TO)+"|"+x+"@@")

void
create_monster()
{
    set_name("kebes");
    set_adj("blind");
    add_adj("limbless");
    set_title("the Speaker of the Warriors");
    set_race_name("mul");
    set_long("Horribly mutilated in some long-ago fight, this stout soul "+
             "nonetheless seems ready to kill. In spite of his sightless "+
             "eyes he knows exactly where you are standing. He knows "+
            "many things and may list them if you <ask mul list>.\n"+
             "He has a pierced nose.\n"+
             "He has the brutal look of a gladiator.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    default_config_npc(75);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "That would be low even for you.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "What would that proove?\n");
    add_act("emote leans against the wall to scratch some of his scars.");
    add_act("emote hobbles lazily around the room on his stumps.");
    add_act("emote cocks his ear in your direction and grins.");
    add_act("' I know much about the gladiators.");
    add_act("' Who goes there?");
    add_act("' You should see the other guy.");

    set_act_time(9);

    set_default_answer(VBFC_ME("otherask"));
    add_ask("list", MAIN_ASK("list"));

    add_ask("athas", MAIN_ASK("athas"));
    add_ask("commands", MAIN_ASK("commands"));
    add_ask("emotes1", MAIN_ASK("emotes1"));
    add_ask("emotes2", MAIN_ASK("emotes2"));
    add_ask(({"guild", "gladiator", "gladiators"}), MAIN_ASK("guild"));
    add_ask("kalak", MAIN_ASK("kalak"));
    add_ask("leaving", MAIN_ASK("leaving"));
    add_ask("overseer", MAIN_ASK("overseer"));
    add_ask("rules", MAIN_ASK("rules"));
    add_ask("skills", MAIN_ASK("skills"));
    add_ask("slaves", MAIN_ASK("slaves"));
    add_ask("song", MAIN_ASK("song"));
    add_ask("song2", MAIN_ASK("song2"));
    add_ask("song3", MAIN_ASK("song3"));
    add_ask("titles", MAIN_ASK("titles"));
    add_ask("tyr", MAIN_ASK("tyr"));
}

string
otherask()
{
    object who;
    who=PO;
    command("peer "+lower_case(who->query_name()));
    command("scratch");
    command("' I never heard of such a thing. Ask Brutus maybe.");
    return "\n> ";
}

string
askmost(string subject)
{
    string speach;
    speach = (read_file(PSION_HELP+subject) + "\n> ");
    say(QCTNAME(TO)+" whispers something to "+QCTNAME(TP)+".\n");
    return speach;
}
