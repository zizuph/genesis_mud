
/* 
 * A Ice Folk reaver of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_ice_barbarian";

int level;
int sublevel = 3; // reaver

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 3; // 50% 'hardy' (139 stat average)
        break;
        case 5..7:
            level = 4; // 30% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 20% 'legendary' (189 stat average)
        break;
    }

    return level;
}

public void
create_barbarian_soldier()
{
    set_barbarian_level(random_soldier_type(), sublevel, "ice");
}
 