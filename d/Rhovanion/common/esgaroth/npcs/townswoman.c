inherit "/d/Rhovanion/common/esgaroth/genmonster";

#include <ss_types.h>

#define O_DIR_O "/d/Rhovanion/common/esgaroth/objects/"

arm_me()
{
    begin_object(O_DIR_O + "sglove", 50);
    end_object();
    my_pick_list(({ "pretty", "beautiful", "young", "old", "ugly",
        "shy", "fat" }));
    set_adj(opinion());
    cash_flow(7);
    slide_alignment(random(4)+1);
    slide_skill(SS_DEFENCE);
    end_monster();
}
       
create_monster()
{
    begin_monster(20, 50);
    set_chat_time(3);
    add_chat("You'd never believe what I heard at the market pool today!");
    add_chat("Did you know that my neighbor is having an affair?");
    add_chat("Well aren't you a cute thing.");
    add_chat("Hmmm.  I seem to have misplaced one of my children.");
    set_cchat_time(1);
    add_cchat("So what does my worthless husband do when I'm attacked?");
    add_cchat("You'll be sorry when a guard comes by.");
    add_cchat("Is it something I said?");
    set_race_name("human");
    set_gender(1);
    set_name("woman");
    add_name("_woman_");
    add_name("_esgaroth_monster_");
    set_long("This is one of the women who live in Esgaroth.\n");
    refresh_mobile();
}
