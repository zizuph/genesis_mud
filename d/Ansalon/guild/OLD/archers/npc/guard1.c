/* guard1.c
 *
 * The elf guarding the entrance to the Elven Archers guild.
 *
 * Blizzard, 05.11.2003
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/qualinesti/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "../guild.h"

inherit  GUILD_STD + "guard_base";

inherit  AUTO_TEAM
inherit  "/d/Krynn/std/equip";

public void attack_ranged(object *enemies, object room, string location);
public void attack_ranged_enemies(object *enemies, object room,
                                  string location);

void
create_elf_npc()
{
    add_name("_guard_");
    set_elf_type(1);
    set_skill(SS_HIDE, 90);
    clear_act();
    remove_descr();
    add_descr(" carefully studying the forest");

    seteuid(getuid(TO));
    equip(({ WEP + "elven_arrow" }));
}

void
attack_him(object *enemy, string room)
{
    object archer;

    seteuid(getuid(TO));
    (room)->load_me();

    archer = present("_guard_", find_object(room));
 /*
    DEBUG("Archer is: " + MASTER_OB(archer));
    DEBUG("We ask him to shoot at: " + MASTER_OB(environment(TO)));
 */
    archer->attack_ranged_enemies(enemy, environment(TO), "ground");
}

public void
attacked_by(object ob)
{
    if ( (E(TO))->query_sniper_room() )
        attack_him( ({ ob }), (E(TO))->query_sniper_room() );
    
    ::attacked_by(ob);

}

public void
hook_attack(object enemy)
{
 /*
    DEBUG("hook_attack is called, enemy is " + MASTER_OB(enemy));
    DEBUG("Do we have a sniper room?: " + (environment(enemy))->query_sniper_room());
 */ 
    if ( (E(TO))->query_sniper_room() )
        attack_him( ({ enemy }), (environment(enemy))->query_sniper_room() );

}


public void
attack_ranged_enemies(object *enemies, object room, string location)
{


    if (!query_attack())
    {
        command("emote silently prepares for battle.");
        attack_ranged(enemies, room, location);
    }
}

public void
attack_ranged(object *enemies, object room, string location)
{
    int size;
    object target;
    string description;

 /*
    DEBUG("Enemies: ");
    dump_array(enemies);
    DEBUG("\nRoom: " + MASTER_OB(room) + " Firing at: " + location);
    DEBUG("Environment being: " + MASTER_OB(environment(enemies[0])) );
 */
    enemies = filter(enemies, &operator(==)(room) @ &environment());
    size = sizeof(enemies);
 /*
    DEBUG("Enemies2: ");
    dump_array(enemies);
    DEBUG("");
 */
    if (size)
    {
    target = enemies[random(size)];
    description = implode(target->query_adjs(), " ") + " " +
                  target->query_race_name();
    command("shoot " + description + " " + location);

    set_alarm(2.0, 0.0,
          &attack_ranged(enemies, room, location));
    }
}

