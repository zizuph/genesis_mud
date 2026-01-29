
/* 
 * A rebel swordsman of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_rebel";

int level;
int sublevel = 4; // swordsman

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 3; // 50% 'merciless' (155 stat average)
        break;
        case 5..7:
            level = 4; // 30% 'deadly' (170 stat average) 
        break;
        default:
            level = 5; // 20% 'legendary' (190 stat average)
        break;
    }

    return level;
}

public void
create_rebel_soldier()
{
    set_rebel_level(random_soldier_type(), sublevel, "rebel");
}
 