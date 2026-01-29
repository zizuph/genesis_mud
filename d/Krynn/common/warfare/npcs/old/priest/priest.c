inherit "/d/Ansalon/taman_busuk/neraka/npc/priest";

void
create_pot_monster()
{
    ::create_pot_monster();
    set_max_team_size_auto_join(5);
    set_pick_up_team(({"_da_member_", "aurak", "sivak", "bozak", "kapak",
                           "baaz", "_priest_"}));
}