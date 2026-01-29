/* A platoon in the attack on Que Kiri */

/* Aridor 07/95 */


inherit "/d/Krynn/common/army/platoon";


void
create_platoon()
{
    set_action_interval(1); /*9 do something every 9 Krynn hours */
    set_max_troop_size(5);
}

void
end_action()
{
    soldiers->command("kill thing");
    soldiers->set_aggressive(1);
}
