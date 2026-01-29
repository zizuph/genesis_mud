
/* 
 * A knight of the Sword of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/knight_base";

int level;
int sublevel = 3; // Sword knight

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 3; // 50% 'fearless' (139 stat average)
        break;
        case 5..7:
            level = 4; // 30% 'heroic' (169 stat average) 
        break;
        default:
            level = 5; // 20% 'elite' (189 stat average)
        break;
    }

    return level;
}

public void
create_knight_soldier()
{
    set_knight_level(random_soldier_type(), sublevel, "sword");
}
 