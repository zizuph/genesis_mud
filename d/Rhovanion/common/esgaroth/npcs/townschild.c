inherit "/d/Rhovanion/common/esgaroth/genmonster";

create_monster()
{
    begin_monster(random(30), 5);
    slide_alignment(random(2)+1);
    cash_flow(1);
    my_pick_list(({ "grubby", "pudgy", "stout", "fat", "obese", "red-faced", 
        "crying" }));
    set_adj(opinion());
    end_monster();
    set_chat_time(3);
    add_chat("You look funny!");
    add_chat("I fell in the water yesterday.");
    add_chat("My mom gave me some money to buy a pastry.");
    set_act_time(3);
    add_act("giggle");
    add_act("tickle all");
    add_act("emote looks gleefully at a few coppers.");
    set_race_name("human");
    set_long("This is one of the many children who live here in Esgaroth.\n");
    set_name("child");
    add_name("_child_");
    add_name("_esgaroth_monster_");
    refresh_mobile();
}

arm_me() {}
