inherit "/d/Rhovanion/common/esgaroth/genmonster";

#include <ss_types.h>
#include <macros.h>

#define W_DIR_W "/d/Rhovanion/common/esgaroth/weapons/"
#define A_DIR_A "/d/Rhovanion/common/esgaroth/armours/"
#define O_DIR_O "/d/Rhovanion/common/esgaroth/objects/"

arm_me()
{
    begin_object(W_DIR_W + "knife", 100);
    slide_pen();
    slide_hit();
    end_object();
    my_pick_list(({ "spindly", "dirty", "pale", "ruddy", "fat",
        "skinny", "ugly", "handsome", "blue-eyed" }));
    set_adj(opinion());
    begin_random_list(2);
    begin_object(A_DIR_A + "cloak", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "boots", 100);
    slide_ac();
    end_object();
    begin_object(A_DIR_A + "gloves", 100);
    slide_ac();
    end_object();
    begin_object(O_DIR_O + "gem", 50);
    end_object();
    end_random_list();
    end_monster();
}

create_monster()
{
    begin_monster(35, 60);
    slide_alignment(random(4)+1);
    slide_skill(SS_WEP_KNIFE);
    slide_skill(SS_DEFENCE);
    slide_skill(SS_PARRY);
    slide_skill(SS_AWARENESS);
    slide_skill(SS_UNARM_COMBAT);
    set_chat_time(3);
    add_chat("It's a lovely day, isn't it?");
    add_chat("Have you been to the lonely mountain?");
    add_chat("I caught two fish today!");
    add_chat("The guards might get upset if you break into people's houses.");
    set_cchat_time(1);
    add_cchat("I wish things didn't have to be this way.");
    add_cchat("Can't we discuss this like rational creatures?");
    set_race_name("human");
    set_name("man");
    set_long("This is a townsman of Esgaroth.  He looks like he has seen " +
        "many hardships over the last few years, but things are finally " +
        "looking up for him and for the city.\n");
    add_name("_esgaroth_monster_");
    add_name("_man_");
    refresh_mobile();
    cash_flow(15);
}
