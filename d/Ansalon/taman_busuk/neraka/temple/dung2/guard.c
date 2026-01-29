/* This room should be very heavily guarded. */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <macros.h>


inherit TEMPLE + "std_guard.c";
inherit "/d/Ansalon/guild/new_pot/lib/train_comb";
inherit TEMPLE + "lib/blocking";

#define NUM     5

object *dracs = allocate(NUM), goblin1, *team;

void
set_up_allowed()
{
    int x;
    
#if 0
    /* Council members are allowed everywhere */
    for (x = T_LEADER ; x <= T_HERBMASTER ; x++)
        add_allowed(x, T_TEAMMEMBER, ({"west", "north", "east", "south"}));
    /* Other members are allowed everywhere except for west */
    for (x = T_HIGH_PRIEST ; x <= T_INITIATE ; x++)
        add_allowed(x, T_TEAMMEMBER, ({"north", "east", "south"}));
#else
    /* Priests and above may go everywhere. */
    for (x = T_LEADER ; x <= T_PRIEST ; x++)
        add_allowed(x, T_TEAMMEMBER, ({"west", "north", "east", "south"}));
#endif

    /* Same goes for highranking dragonarmy officers */
    add_allowed(T_GENERAL, T_TEAMLEADER, ({"north", "east", "south"}));
    add_allowed(T_HIGH_OFFICER, T_TEAMLEADER, ({"north", "east", "south"}));
    /* Those pesky wizards are allowed everywhere */
    add_allowed(T_WIZARD, 0, ({"north", "west", "south", "east"}));
}

void
reset_temple_room()
{
    int x;
    
    setuid();
    seteuid(getuid());

    for (x = 0 ; x < NUM ; x++)
    {
        if (!objectp(dracs[x]))
        {
            switch (x)
            {
                case 0..1:
                    dracs[x] = clone_object(NNPC + "sivak");
                    break;
                case 2..3:
                    dracs[x] = clone_object(NNPC + "kapak");
                    break;
                default:
                    dracs[x] = clone_object(NNPC + "bozak");
            }
            
            dracs[x]->set_act_time(18 + random(5));
            dracs[x]->set_chat_time(25 + random(5));
            dracs[x]->move(TO);
        }
    }

    if (!objectp(goblin1))
    {
        goblin1 = clone_object(GUILDNPC + "gruzz");
        goblin1->arm_me();
        goblin1->move(TO);

        set_trainer(goblin1);
    }

    set_guards(({goblin1 }) + dracs);
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("West guardroom");
    set_long("You are standing in the middle of a large guardroom. " +
        "Along the walls stand weaponracks and in the centre of this " +
        "room is a large round table with chairs around it. A stone " +
        "stairway in the corner of the room leads up.\n");

    add_exit( DUNGTWO + "corr3.c", "north", "@@check_guards");
    add_exit( DUNGTWO + "corr4.c", "south", "@@check_guards" );
    add_exit( DUNGTWO + "corr7.c", "east", "@@check_guards" );
    add_exit( DUNGTWO + "corr6.c", "west", "@@check_guards" );
    add_exit( DUNGONE + "stair0.c", "up" );

    create_skill_raise();
    set_up_skills();
    set_up_allowed();

    reset_temple_room();
}
#ifdef 0
int
check_guards()
{
    object ob;
    int x;

    if (TP->query_guild_name_occ() == GUILD_NAME &&
        TP->query_priest_level() >= GUILD_LEVEL_PRIEST)
    {
        /* Priests and high priests will always be allowed access
         * including the members of his team
         */
        team = TP->query_team();
        if (TP->query_leader() != TP)
            team += ({ TP->query_leader() });

        goblin1->command("nod briefly " + OB_NAME(TP));

        return 0;
    }
    else if (TP->query_guild_name_occ() == "Dragonarmy" &&
        TP->query_dragonarmy_rank() >= 3)
    {
        /* High ranking dragonarmy soldiers will be allowed access
         * including his team if he is the leader of it
         */
        if (TP->query_leader() == TP)
            team = TP->query_team();

        goblin1->command("nod briefly " + OB_NAME(TP));
        return 0;
    }
    else if (member_array(TP, team) >= 0)
    {
        /* Check if we are member of a team who were allowed in
         */
        goblin1->command("nod briefly " + OB_NAME(TP));
        return 0;
    }
    else if (TP->query_wiz_level())
    {
        /* Those pesky wizards naturally must go as they wish
         */
        goblin1->command("nod briefly " + OB_NAME(TP));
        return 0;
    }
    
    /* Otherwise, check if any of the hopefully living npcs notice
     * us and if so, stop that person.
     */
    for (x = 0 ; x < NUM ; x++)
    {
        if (CAN_SEE(dracs[x], TP))
            ob = dracs[x];
    }
    if (CAN_SEE(goblin1, TP))
        ob = goblin1;

    if (objectp(ob))
    {
        ob->command("say to " + OB_NAME(TP) + " I will have to see " +
            "some orders before I can let you pass.");
        return 1;
    }

    return 0;
}
#endif

void
init()
{
    ::init();

    init_skill_raise();
}
