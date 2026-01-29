inherit "/d/Rhovanion/common/esgaroth/genmonster";

#include <ss_types.h>

#define W_DIR_W "/d/Rhovanion/common/esgaroth/weapons/"
#define A_DIR_A "/d/Rhovanion/common/esgaroth/armours/"
#define O_DIR_O "/d/Rhovanion/common/esgaroth/objects/"

arm_me()
{
    begin_object(W_DIR_W + "dagger", 100);
    slide_pen();
    slide_hit();
    end_object();
    begin_random_list(2);
    begin_object(A_DIR_A + "cloak", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "gloves", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "cloak", 100);
    slide_ac();
    end_object();
    begin_object(O_DIR_O + "gem", 100);
    end_object();
    end_random_list();
    end_monster();
}

create_monster()
{
    begin_monster(30, 70);
    cash_flow(15);
    slide_alignment(-2);
    slide_skill(SS_WEP_KNIFE);
    slide_skill(SS_DEFENCE);
    slide_skill(SS_PARRY);
    my_pick_list(( { "sneaky", "dirty", "sly", "greedy", "ugly", "hooknosed",
        "scarred" }));
    set_adj(opinion());
    end_monster();
    set_chat_time(3);
    add_chat("Hiya!");
    add_chat("Do you think you could help me out here for a second?");
    add_chat("Those guards are pretty tough! One nearly killed me!");
    set_cchat_time(1);
    add_cchat("I didn't touch anything of yours.  Honest!");
    set_race_name("human");
    set_name("ruffian");
    add_name("_esgaroth_monster_");
    set_gender(random(2));
    set_long("This is one of the many ruffians who inhabit the city.\n");
    refresh_mobile();
}
