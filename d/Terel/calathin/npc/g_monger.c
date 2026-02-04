/* A gossip-monger. Mortricia 920927 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           0
#define WEP_DIR         MORTRICIADIR + "weapons/"

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("bitch");
    add_name("gossip-monger");
    add_name("woman");
    set_adj("gossip");
    set_living_name("wench");
    set_short("@@bitch");
    set_long("@@my_long");
    set_adj("old");
    set_gender(1);
    set_race_name("human");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({13,13,13,20,30,13}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
 
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_WEP_POLEARM, 10);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);

    set_chat_time(2);
    add_chat(
	"The gypsies are back. They have a camp south of town.\n" +
     BS("Their fortune teller is worth a visit. She is a very good " +
	"friend of mine, but don't tell anyone here in town about " +
	"that.")
    );
    add_chat(
	"At your age I was beautiful! Believe it or not."
    );
    add_chat(
	"My grandmother, and she has been dead for almost a\n" +
     BS("century, used to work at the mansion. What stories " +
	"she used to tell me about the Avenchirs...")
    );
     add_chat(
        BS("I heard that the witch in the forest is looking for "+
           "a lost inheritance...")
     );
    add_chat(
	"My ohh my! What have we here then?"
    );

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

string
bitch()
{
    if (TP->query_gender() == 1)
	return "gossip monger";
    else return "old bitch";
}

string
my_long()
{
    string str;
    
    if (TP->query_gender() == 1) {
	str = "It is an old woman.";
    }
    else str = "It is an old bitch.";

    str += " She is really tiresome, this gossip monger.\n";

    return str;
}
	
dress_me()
{
    object stick;

    seteuid(getuid(TO));
    stick = clone_object(WEP_DIR + "stick");
    stick -> move(TO);
    command("wield stick");
}
