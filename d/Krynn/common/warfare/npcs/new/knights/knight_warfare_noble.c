
/* 
 * A nobleman fighting for the knights of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/knight_base";

int level;
int sublevel = 1; // nobleman

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 3; // 50% 'fearless' (139 stat average)
        break;
        case 5..8:
            level = 4; // 40% 'heroic' (169 stat average) 
        break;
        default:
            level = 5; // 10% 'elite' (189 stat average)
        break;
    }

    return level;
}

public void
create_knight_soldier()
{
    set_knight_level(random_soldier_type(), sublevel, "crown");
}
 