
/* 
 * A Ice Folk barbarian chieftain of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_ice_barbarian";

int level;
int sublevel = 4; // chieftain

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 3; // 20% 'hardy' (139 stat average)
        break;
        case 2..6:
            level = 4; // 50% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 30% 'legendary' (189 stat average)
        break;
    }

    return level;
}

public void
create_barbarian_soldier()
{
    set_barbarian_level(random_soldier_type(), sublevel, "ice");
}
 