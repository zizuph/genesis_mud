inherit "/d/Gondor/common/battle/npc/battle_npc.c";

void
create_battle_npc()
{
    set_name("uruk");
    set_race_name("uruk");
    set_adj(({"large", "fierce"}));
    set_short("large fierce uruk");
    set_long("This is an uruk, a breed of orc meant to be stronger, faster " +
        "and perhaps most frightening of all, able to withstand the sun. " +
        "Battle scars run along his face and body, evidence of an " +
        "experienced warrior. Sharp fangs overlap his bottom lip, making " +
        "his face even more gruesome.\n");
    set_move_time(10.0);
    set_path(({"w", "w", "w", "w", "w", "w", "w", "w"}));
    default_config_npc(120);
    set_alignment(-800);
}
