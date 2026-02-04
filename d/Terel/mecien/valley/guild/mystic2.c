/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP         this_player()
#define TO         this_object()
#define ETO        environment(TO)

object gkey, ckey, wkey;
string gname="", cname="", wname="";

public void
create_monster()
{
    ::create_monster();
    
    set_name("ilrilis");
    add_name("mystic");
    add_name("watcher");
    set_adj("wizened");
    add_adj("silver-haired");
    set_race_name("elf");

    set_title("the Mystic Watcher");

    set_stats(({76, 78, 78, 89, 90, 98}));

    set_hp(9999);
    set_mana(9999);
    set_mystic_skills(33);
    set_skill(SS_LANGUAGE, 76);    
    set_rank(MYSTIC_STAR);
    set_base_stat(SS_OCCUP, 80);
    set_base_stat(SS_LAYMAN, 53);
    set_alignment(567);
    set_random_move(32, 1);
    set_chat_time(5);
    enable_intro();
    enable_auto_salute();

    add_prop(NPC_M_NO_ACCEPT_GIVE, "@@check_giver");

    add_chat("Know thy way and you shall be great indeed");
    add_chat("Here is wisdom, speak to reveal, for thy voice "
             + "shall be Truth, thus say show yourself.");
    add_chat("Peace");

    add_ask(({"key", "about key"}),
            "The watcher says: Which key? I might have it here...\n");
    add_ask(({"about lattice", "about garden", "lattice"}),
            "The watcher says: Yes, the lattice leads to the courtyard " +
            "garden.\n");
    add_ask(({"truth", "Truth", "about truth", "about Truth"}),
            "The watcher says: Mysterious is it not?\n");
    add_ask("for key", "The watcher says: which key do you mean?\n");
    add_ask(({"for key to lattice", "for lattice key", "garden key",
              "for garden key", "lattice key", "key to garden",
              "for key to garden"}),
            VBFC("check_key|garden"), 1);
    add_ask(({"for key to winery", "for winery key", "winery key",
                  "for wine key", "wine key"}),
            VBFC("check_key|wine"), 1);
    add_ask(({"for key to crypt", "for crypt key", "crypt key",
                  "for death key", "death key"}),
            VBFC("check_key|crypt"), 1);
            
    set_all_attack_unarmed(25, 20);
    set_all_hitloc_unarmed(40);

    seteuid(getuid());
    
    gkey = clone_object(GUILD_DIR + "courtyard/lk");
    gkey->move(TO);
    ckey = clone_object(GUILD_DIR + "crypt/ckey");
    ckey->move(TO);
    wkey = clone_object(GUILD_DIR + "courtyard/wk");
    wkey->move(TO);
}

public string
check_key(string str)
{
    object key, where=0;
    string name;
    
    if (!MEMBER(TP)) return "say Your are not of the Order.";

    if (str == "garden") {
        key = gkey;
        name = gname;
    } else if (str == "crypt") {
        key = ckey;
        name = cname;
    } else if (str == "wine") {
        key = wkey;
        name = wname;
    } else {
        return "shrug";
    }
    if (key) where = environment(key);
    if (!key || !where) {
        command("ms I cannot locate it.");
        if (strlen(name))
            command("ms I gave it to " + capitalize(name) +
                    " and I haven't seen it since.");
        return "shrug";
    }
    if (!living(where)) {
        if (where == ETO) {
            command("point " + key->short());
            return "msmile";
        }
        command("emote closes his eyes for a moment.");
        command("ms I think it is a place called " + where->short() + ".");
        return "emote looks thoughtful.";
    }
    if (where == TO) {
        command("ms Here it is...");
        command("give " + key->short() + " to " + TP->query_real_name());
        if (str == "garden") gname = TP->query_name();
        if (str == "crypt")  cname = TP->query_name();
        if (str == "wine")   wname = TP->query_name();
        return ("smile at " + TP->query_real_name());
    }
    if (where == TP) {
        command("ms You already have it!");
        return "mlaugh";
    }
    if (MEMBER(where)) {
        command("ms I think " + where->query_name() + " has it now.");
        return "msmile";
    } else {
        command("emote closes his eyes for a moment.");
        command("ms A " + where->query_nonmet_name() +
                ", not of Order, has it now.");
        return "hmm";
    }
}

public int
check_giver()
{
    if (MEMBER(TP)) return 0;
    return 1;
}
