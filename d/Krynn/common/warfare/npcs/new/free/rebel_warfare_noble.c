
/* 
 * A rebel noble of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_rebel";

int level;
int sublevel = 5; // noble

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 3; // 20% 'merciless' (155 stat average)
        break;
        case 2..6:
            level = 4; // 50% 'deadly' (170 stat average) 
        break;
        default:
            level = 5; // 30% 'legendary' (190 stat average)
        break;
    }

    return level;
}

public void
create_rebel_soldier()
{
    set_rebel_level(random_soldier_type(), sublevel, "rebel");
}
 