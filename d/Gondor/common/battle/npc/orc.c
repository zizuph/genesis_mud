inherit "/d/Gondor/common/battle/npc/battle_npc.c";

void
create_battle_npc()
{
    set_name("orc");
    set_race_name("orc");
    set_adj(({"scarred", "cruel"}));
    set_short("scarred cruel orc");
    set_long("Many battle scars mar the face and body of this orc, evidence " +
        "of his prowess in battle. His mouth is set in a mean smirk, and " +
        "his eyes gleam with cruelty.\n");
    set_move_time(10.0);
    set_path(({"w", "w", "w", "w", "w", "w", "w", "w"}));
    default_config_npc(80);
    set_alignment(-650);
}
