inherit "/d/Gondor/common/battle/npc/battle_npc.c";

void
create_battle_npc()
{
    set_name("goblin");
    set_race_name("goblin");
    set_adj(({"dirty", "crude"}));
    set_short("dirty crude goblin");
    set_long("This goblin stinks like a pile of dung. You wouldn't be " +
        "too surprised if that's where the smell came from. He has a " +
        "foul mouth that spits out insults and taunts at allies and " +
        "enemies alike.\n");
    set_move_time(10.0);
    set_path(({"w", "w", "w", "w", "w", "w", "w", "w"}));
    default_config_npc(40);
    set_alignment(-500);
}
