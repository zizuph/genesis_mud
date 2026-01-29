inherit "/d/Rhovanion/common/esgaroth/genmonster";

#include <ss_types.h>
#define W_DIR_W "/d/Rhovanion/common/esgaroth/weapons/"
#define A_DIR_A "/d/Rhovanion/common/esgaroth/armours/"

arm_me()
{
    begin_object(W_DIR_W + "sword", 100);
    slide_pen();
    slide_hit();
    end_object();
    begin_object(A_DIR_A + "platemail", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "shield", 75);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "helmet", 75);
    slide_ac();
    end_object();
    begin_random_list(1);
    begin_object(A_DIR_A + "cloak", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "gloves", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "boots", 100);
    slide_ac();
    end_object();
    end_random_list();
    end_monster();
}

create_monster()
{
    begin_monster(65, 60);
    slide_alignment(3);
    slide_skill(SS_WEP_SWORD);
    slide_skill(SS_UNARM_COMBAT);
    slide_skill(SS_DEFENCE);
    slide_skill(SS_PARRY);
    cash_flow(15);
    slide_skill(SS_BLIND_COMBAT);
    my_pick_list(({ "handsome", "dashing", "lean", "tanned", "strong",
        "noble" }));
    set_adj(opinion());
    set_chat_time(3);
    add_chat("My job is to protect the city, they pay me for it.");
    add_chat("Are you enjoying your stay in Esgaroth?");
    add_chat("Hello, nice day, isn't it?");
    set_cchat_time(1);
    add_cchat("Now I get to earn my pay!");
    add_cchat("What did I ever do to you?");
    refresh_mobile();
    set_short(query_adj() + " guard");
    set_race_name("human");
    set_long("This is one of the stalwart defenders of Esgaroth.  In " +
        "the past, many of the guards were corrupt, but this one does " +
        "not seem to suffer from that.\n");
    set_name("guard");
    add_name("_guard_");
    add_name("_esgaroth_monster_");
}
