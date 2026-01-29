inherit "/d/Krynn/solamn/vin/std/vin_knight_base";

void
create_knight_npc()
{
    set_level(2);
    set_alarm(1.0, 0.0, &set_skill(67531, 70)); // kattack
    set_alarm(1.0, 0.0, &set_skill(67532, 50)); // block
}
