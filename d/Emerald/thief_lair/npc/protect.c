inherit "/d/Emerald/std/emerald_monster";

#include <macros.h>
#include <stdproperties.h>

public mixed check_for_protectors();
public void protect_me();

void
create_emerald_monster()
{
    set_name("mon");
    add_prop(OBJ_M_NO_ATTACK, check_for_protectors);
}

public void
start_attack(object target)
{
    command("$kill " + OB_NAME(target));
    set_alarm(3.0, 0.0, protect_me);
}

public void
protect_me()
{
    int i;
    object *enemies;
    // Find the npcs who protect me
    object *protectors =
        filter(all_inventory(environment()), &->query_protector());

    if (!sizeof(protectors))
    {
        return;
    }

    enemies = query_enemy(-1);
    // Stop people from attacking me
    map(enemies, &->stop_fight(this_object()));

    // Redirect their attacks to random protectors
    for (i = 0; i < sizeof(enemies); i++)
    {
        if (!present(enemies[i], environment()))
	{
	    continue;
	}

        enemies->attack_object(protectors[random(sizeof(protectors))]);
    }
}

public mixed
check_for_protectors()
{
    if (sizeof(filter(all_inventory(environment()), &->query_protector())))
    {
        return "He is protected by his guards!\n";
    }

    return 0;
}
