/* New functions for adding items to a mobile. Mucalytic 09-01-96 */

#include "../master_defs.h"

void move_and_wield(string path)
{
    object wep;

    seteuid(getuid());
    wep = clone_object(path);

    wep->move(TO);

    command("wield "+wep->query_name());
}

void add_weapon(string path)
{
    set_alarm(2.0, 0.0, "move_and_wield", path);
}

void move_and_wear(string path)
{
    object arm;

    seteuid(getuid());
    clone_object(path)->move(TO);

    arm->move(TO);

    command("wear "+arm->query_name());
}

void add_armour(string path)
{
    set_alarm(2.0, 0.0, "move_and_wear", path);
}

void add_object(string path)
{
    seteuid(getuid());
    clone_object(path)->move(TO);
}
